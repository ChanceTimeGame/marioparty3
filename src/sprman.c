#include "game/sprite.h"
#include "game/hmfman.h"
#include "game/camera.h"
#include "mallocblock.h"
#include "include_asm.h"
#include "macros.h"

#define offsetof(st, m) ((u32) & (((st *)0)->m))
#define HUSPR_READ16(p) (((p)[0] << 8) + (p)[1])
#define HUSPR_READ32(p) (((p)[0] << 24) + ((p)[1] << 16) + ((p)[2] << 8) + (p)[3])

typedef struct {
    u8 images[4];
    u8 animations[4];
    u8 pixels[4];
    u8 palette[4];
    u8 imageCount[2];
    u8 animationCount[2];
    u8 width[2];
    u8 height[2];
    u8 pixelBits[2];
    u8 paletteCount;
} HuSprFileHeader;

typedef struct {
    u8 pixels[4];
    u8 width[2];
    u8 height[2];
    u8 centerX[2];
    u8 centerY[2];
} HuSprFileImage;

typedef struct {
    u8 image[2];
    u8 duration[2];
    u8 unk04;
    u8 unk05;
    u8 unk06;
} HuSprFileFrame;

/* Palette animation state, HuSprite 0x98-0x113 */
typedef struct SprPalAnim {
    /* 0x00 */ HuSprAnmDesc* desc;
    /* 0x04 */ u16 frame[0x10];
    /* 0x24 */ f32 timer[0x10];
    /* 0x64 */ f32 speed;
    /* 0x68 */ u16 bufIdx;
    /* 0x6C */ u16* cur;
    /* 0x70 */ u16* bufs[3];
} SprPalAnim;

typedef struct SprPalEntry {
    /* 0x00 */ u16 idx;
    /* 0x02 */ u16 color;
} SprPalEntry;

typedef struct SprPalFrame {
    /* 0x00 */ s16 dur;
    /* 0x04 */ SprPalEntry* entries;
} SprPalFrame;

typedef struct SprPalGroup {
    /* 0x00 */ u16 count; /* palette entries per frame; 0 = not animated */
    /* 0x02 */ u16 nframes;
    /* 0x04 */ SprPalFrame** frames;
} SprPalGroup;

typedef struct {
    HuSprite *last;
    HuSprite *first;
} HuSprPrioBucket;

void *HuMemAlloc(s32 size);
void *HuMemMemoryReallocPerm(void *mem, u32 new_size);
HuSprite *func_800530AC_main(void);

void func_80052E68_main(HuSprGrp *group, u16 count);
void func_8008A0D0_main(Mtx *);
void func_80052518_main(HuSprite *arg0);
void func_80056F80_main(s16 arg0);
s16 func_8005630C_main(HuSprAnm *arg0);
void AnimateSprite(HuSprAnm *arg0);
void func_800571C8_main(struct SprPalAnim *arg0);
void SprExec(Gfx **gfx, Mtx *mtx, HuCamera *cam);
void func_80053558_main(void);
void func_80054170_main(void);
void SprDisp(Gfx **gfx, HuSprite *obj, HuCamera *cam);
s16 func_8004D6AC_main(u8 red, u8 green, u8 blue);
void func_8004D6E8_main(s16 sampleIdx);
void SprLayerHook(Gfx **gfx, Mtx *mtx, HuCamera *cam);
void func_80055628_main(void);
void func_80056CD0_main(void);
void func_80057158_main(void);

extern s32 D_800A1EA0_main; // redraw?
extern Mtx D_800BD7C0_main;
extern Vp D_800A1E90_main;
extern Gfx *D_800BD800_main; /* the sprites drawn after the 3D layer (SprLayerHook) */
extern void *D_800CCF30_main;
extern f32 D_800BD808_main; /* SprPos3DSet's last view distance */
extern s16 D_800D418E_main; /* the viewport being drawn */
void func_80089980_main(f32 mf[4][4], Mtx *m); /* guMtxL2F */
f32 fabsf(f32);
f64 fmod(f64, f64);
f64 fabs(f64);
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */

/* HuSprite fields include/game/sprite.h types otherwise: the rotation (f32), the index of the
   current buffer in unk_128/unk_134, and the attributes as last drawn. */
#define SPR_ROT(s) (*(f32 *)&(s)->unk_20)
#define SPR_BUFIDX(s) (*(s32 *)&(s)->unk_120)
#define SPR_LASTATTR(s) (*(s32 *)(s)->unk_200_pad)
extern HuSprite *D_800BD804_main; // head of sorted draw list
extern s16 D_800D0468_main;
extern s16 D_800D10F2_main;
extern HuSprAnmDesc *D_800D0A50_main[0x100];
extern u16 D_800D554E_main;
extern u16 D_800CC3E6_main;
extern u16 D_800CB8A0_main;
extern HuSprite_Unk84_Struct *D_800C9530_main[];
extern void *D_800CE1B8_main[3];
extern u8 D_800D2008_main;
extern s32 D_800D1FDC_main;
extern void *D_800D59F4_main;
extern s8 HmfPauseF;
extern HuSprGrp *HuSprGrpLast;
extern HuSprGrp *HuSprGrpFirst;
HuSprGrp *HuSprGrpData[HUSPR_GRP_MAX] BSS;
extern u16 HuSprGrpNum;

void func_80052330_main(void) {
    s16 i;
    void **p;

    HuSprGrpNum = 0;
    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        HuSprGrpData[i] = NULL;
    }
    HuSprGrpFirst = NULL;
    HuSprGrpLast = NULL;
    D_800CB8A0_main = 0;
    D_800CE1B8_main[0] =
        D_800CE1B8_main[1] =
            D_800CE1B8_main[2] =
                D_800D59F4_main = NULL;
    D_800D1FDC_main = NULL;
    guOrtho(&D_800BD7C0_main, -160.0f, 160.0f, -120.0f, 120.0f, 0.0f, 8000.0f, 2.0f);
    D_800D0468_main = func_8001AC8C_main(0, (void (*)(Gfx **, s32, s32)) SprExec, 0);
    func_8001C8A8_main(D_800D0468_main, 1);
    D_800D10F2_main = func_8001AC8C_main(0, (void (*)(Gfx **, s32, s32)) SprLayerHook, 6);
    func_80055628_main();
    func_80056CD0_main();
    D_800A1EA0_main = 1;
}

HuSprGrp *func_80052468_main(s16 arg0, u16 arg1) {
    HuSprGrp *temp_v0;

    // Allocation assumes 'members' is the last member of HuSprGrp.
    temp_v0 = HuMemAlloc(offsetof(HuSprGrp, members) + arg0 * sizeof(*temp_v0->members));
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_v0->unk_08 = arg1;
    temp_v0->unk_0A = arg0;
    if (HuSprGrpLast == NULL) {
        HuSprGrpLast = temp_v0;
    }
    temp_v0->next = HuSprGrpFirst;
    if (temp_v0->next != NULL) {
        temp_v0->next->prev = temp_v0;
    }
    temp_v0->prev = NULL;
    HuSprGrpFirst = temp_v0;
    HuSprGrpNum++;
    D_800A1EA0_main = 1;
    return temp_v0;
}

void func_80052518_main(HuSprite *arg0) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (arg0->unk_128[i] != NULL) {
            func_80019C00_main(arg0->unk_128[i]);
        }
        if (arg0->unk_134[i] != NULL) {
            func_80019C00_main(arg0->unk_134[i]);
        }
        if (arg0->unk_108[i] != NULL) {
            func_80019C00_main(arg0->unk_108[i]);
        }
    }
    func_80019C00_main(arg0);
}

void HuSprGrpKill(s16 arg0) {
    HuSprGrp *group = HuSprGrpData[arg0];
    HuSprGrp *next = group->next;
    HuSprGrp *prev = group->prev;

    if (group->members[0] != NULL) {
        s16 i;
        HuSprite **mp = group->members;

        for (i = 0; i < group->unk_0A; i++) {
            func_80052518_main(*mp++);
        }
    }
    if (next != NULL) {
        next->prev = prev;
    }
    if (prev != NULL) {
        prev->next = next;
    }
    if (HuSprGrpLast == group) {
        HuSprGrpLast = prev;
        if (prev != NULL) {
            prev->next = NULL;
        }
    }
    if (HuSprGrpFirst == group) {
        HuSprGrpFirst = next;
        if (next != NULL) {
            next->prev = NULL;
        }
    }
    HuMemFree(group);
    HuSprGrpData[arg0] = NULL;
    HuSprGrpNum--;
    D_800A1EA0_main = 1;
}

void func_80052700_main(void) {
    s16 i;

    HuSprGrpNum = 0;
    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        if (HuSprGrpData[i] != NULL) {
            HuSprGrpKill(i);
        }
    }
    HuSprGrpFirst = NULL;
    HuSprGrpLast = NULL;
    D_800CB8A0_main = 0;
    D_800A1EA0_main = 1;
}

s16 HuSprGrpCreate(u16 arg0, u16 arg1) {
    HuSprGrp *temp_v0_2;
    HuSprite **var_s2;
    HuSprite *temp_v0_3;
    s16 var_s4;
    s16 i;

    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        if (HuSprGrpData[i] == NULL) {
            break;
        }
    }
    if (i == HUSPR_GRP_MAX) {
        return -1;
    }
    var_s4 = i;
    temp_v0_2 = func_80052468_main(arg0, arg1);
    if (temp_v0_2 == NULL) {
        return -1;
    }
    HuSprGrpData[var_s4] = temp_v0_2;
    temp_v0_2->unk_0A = 0;
    temp_v0_2->unk_0C = 1;
    var_s2 = temp_v0_2->members;
    for (i = 0; i < arg0; i++) {
        *(var_s2++) = temp_v0_3 = HuMemAlloc(0x210);
        if (temp_v0_3 == NULL) {
            HuSprGrpKill(var_s4);
            return -1;
        }
        temp_v0_2->unk_0A++;
    }
    func_80052E68_main(temp_v0_2, arg0);
    return var_s4;
}

s32 func_800528EC_main(s16 group, s16 member, u16 count) {
    HuSprGrp *groupPtr = HuSprGrpData[group];
    HuSprite **mp = &groupPtr->members[member];
    HuSprite *sprite;
    s16 i;

    for (i = 0; i < count; i++) {
        func_80052518_main(*mp++);
    }
    groupPtr->unk_0A -= count;
    if (groupPtr->unk_0A == 0) {
        groupPtr->members[0] = NULL;
        HuSprGrpKill(group);
        return 0;
    }
    HuMemMemoryReallocPerm(groupPtr, offsetof(HuSprGrp, members) + groupPtr->unk_0A * sizeof(*groupPtr->members));
    mp = &groupPtr->members[member];
    for (i = 0; i < groupPtr->unk_0A - member; i++) {
        *mp = mp[count];
        mp++;
    }
    for (i = 0; i < groupPtr->unk_0A; i++) {
        sprite = groupPtr->members[i];
        sprite->unk_00 = i;
        sprite->unk_02 = groupPtr->unk_0A;
    }
    return 0;
}

s32 func_80052A90_main(s16 group, s16 member, u16 count) {
    HuSprGrp *oldGroup = HuSprGrpData[group];
    HuSprGrp *newGroup;
    HuSprite **mp;
    HuSprite *sprite;
    s16 newSlot;
    s16 i;

    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        if (HuSprGrpData[i] == NULL) {
            break;
        }
    }
    if (i == HUSPR_GRP_MAX) {
        return -1;
    }
    newSlot = i;
    newGroup = func_80052468_main(count + oldGroup->unk_0A, oldGroup->unk_08);
    if (newGroup == NULL) {
        return -1;
    }
    HuSprGrpData[newSlot] = newGroup;
    newGroup->unk_0A = 0;
    newGroup->unk_0C = 1;
    mp = newGroup->members;
    for (i = 0; i < count; i++) {
        *(mp++) = sprite = HuMemAlloc(0x210);
        if (sprite == NULL) {
            HuSprGrpKill(newSlot);
            return -1;
        }
        newGroup->unk_0A++;
    }
    func_80052E68_main(newGroup, count);
    newGroup->members[0]->unk_2E = 0;
    if (member >= 0) {
        mp = newGroup->members + count - 1;
        for (i = 0; i < count; i++) {
            mp[member + 1] = *mp;
            mp--;
        }
        mp = newGroup->members;
        for (i = 0; i < member + 1; i++) {
            *(mp++) = oldGroup->members[i];
        }
    }
    mp = &newGroup->members[member] + count + 1;
    for (i = 0; i < oldGroup->unk_0A - (member + 1); i++) {
        *(mp++) = (oldGroup->members + member)[i + 1];
    }
    newGroup->unk_0A = count + oldGroup->unk_0A;
    for (i = 0; i < newGroup->unk_0A; i++) {
        HuSprite *member_sprite = newGroup->members[i];

        member_sprite->unk_00 = i;
        member_sprite->unk_02 = newGroup->unk_0A;
    }
    oldGroup->members[0] = NULL;
    HuSprGrpKill(group);
    HuSprGrpData[group] = newGroup;
    HuSprGrpData[newSlot] = NULL;
    return 0;
}

void func_80052DD8_main(HuSprAnm *arg0) {
    arg0->unk00 = NULL;
    arg0->unk04 = 0;
    arg0->unk06 = 0;
    arg0->unk08 = 0;
    arg0->unk0A = 0;
    arg0->unk0C = 0.0f;
    arg0->unk10 = 1.0f;
    arg0->unk14 = 0;
    arg0->unk16 = 0;
    arg0->unk18 = 0;
    arg0->unk17 = 0;
}

void func_80052E14_main(HuSprite *arg0) {
    arg0->unk_68.unk00 = arg0->unk_84;
    arg0->unk_68.unk04 = arg0->unk_88;
    arg0->unk_68.unk06 = arg0->unk_0E;
    arg0->unk_68.unk0A = arg0->unk_8A;
    arg0->unk_68.unk08 = arg0->unk_0C;
    arg0->unk_68.unk0C = arg0->unk_8C;
    arg0->unk_68.unk10 = arg0->unk_10;
    arg0->unk_68.unk16 = arg0->unk_92;
    arg0->unk_68.unk14 = arg0->unk_90;
    arg0->unk_68.unk18 = 0;
    arg0->unk_68.unk17 = 0;
}

void func_80052E68_main(HuSprGrp *group, u16 count) {
    HuSprite *sprite;
    s16 i;
    s16 j;

    for (i = 0; i < count; i++) {
        sprite = group->members[i];
        sprite->unk_04 = 0;
        sprite->unk_08 = 0;
        sprite->unk_18 = sprite->unk_1C = 1.0f;
        sprite->prio = 0x8000;
        sprite->unk_20 = 0;
        sprite->unk_24 = 0;
        sprite->unk_28[0] = sprite->unk_28[1] = sprite->unk_28[2] = 0;
        sprite->unk_2C = 0x100;
        if (i != 0) {
            sprite->unk_2E = 0;
        } else {
            sprite->unk_2E = -1;
        }
        sprite->unk_30.f = sprite->unk_34.f = 1.0f;
        sprite->unk_38 = sprite->unk_3A = 0;
        sprite->unk_3C = sprite->unk_3E = sprite->unk_40 = sprite->unk_42 = 0;
        sprite->unk_44 = 0;
        sprite->unk_116 = sprite->unk_114 = -1;
        sprite->unk_48 = 0.0f;
        sprite->unk_4C = 0.0f;
        sprite->unk_50 = sprite->unk_54 = 1.0f;
        sprite->unk_58 = 0.0f;
        sprite->unk_5C = 0;
        sprite->unk_60 = sprite->unk_64 = 1.0f;
        func_80052DD8_main(&sprite->unk_68);
        sprite->unk_84 = sprite->unk_68.unk00;
        sprite->unk_88 = sprite->unk_68.unk04;
        sprite->unk_0E = (u16)sprite->unk_68.unk06;
        sprite->unk_0C = (u16)sprite->unk_68.unk08;
        sprite->unk_8C = sprite->unk_68.unk0C;
        sprite->unk_10 = sprite->unk_68.unk10;
        sprite->unk_90 = (u16)sprite->unk_68.unk14;
        sprite->unk_92 = sprite->unk_68.unk16;
        sprite->unk_93 = sprite->unk_68.unk17;
        sprite->unk_94 = sprite->unk_68.unk18;
        sprite->unk_98 = NULL;
        sprite->unk_FC.f = 1.0f;
        for (j = 0; j < 0x10; j++) {
            sprite->unk_9C[j] = 0xFFFF;
            sprite->unk_BC[j] = 0;
        }
        sprite->unk_100 = 0;
        sprite->unk_104 = 0;
        sprite->unk_108[0] = sprite->unk_108[1] = sprite->unk_108[2] = NULL;
        sprite->unk_00 = i;
        sprite->unk_02 = count;
        sprite->unk_118 = sprite->unk_11C = NULL;
        sprite->unk_128[0] = sprite->unk_128[1] = sprite->unk_128[2] = NULL;
        sprite->unk_134[0] = sprite->unk_134[1] = sprite->unk_134[2] = NULL;
        func_8008A0D0_main(&sprite->unk_140[0]);
        func_8008A0D0_main(&sprite->unk_140[1]);
        func_8008A0D0_main(&sprite->unk_140[2]);
        sprite->unk_120 = NULL;
        sprite->unk_124 = NULL;
        sprite->unk_204 = sprite->unk_206 = 0;
        sprite->unk_208 = 0x140;
        sprite->unk_20A = 0xF0;
    }
}

// rebuild sprite draw list (highest priority first)
HuSprite *func_800530AC_main(void) {
    HuSprPrioBucket buckets[0x100];
    HuSprGrp *group;
    HuSprite *sprite;
    HuSprite *last;
    s32 i;
    s32 j;
    s32 bucket;
    s32 minBucket = -1;
    s32 maxBucket = 0;
    HuSprite *node = NULL;

    if (D_800A1EA0_main == 0) {
        return D_800BD804_main;
    }
    D_800A1EA0_main = 0;
    D_800CB8A0_main = 0;
    group = HuSprGrpLast;
    bzero(buckets, sizeof(buckets));
    while (group != NULL) {
        for (i = 0; i < group->unk_0A; i++) {
            sprite = group->members[i];
            sprite->unk_11C = NULL;
            sprite->unk_118 = NULL;
        }
        group = group->prev;
    }
    for (group = HuSprGrpLast; group != NULL; group = group->prev) {
        for (i = 0; i < group->unk_0A; i++) {
            sprite = group->members[i];
            if (sprite->unk_24 & 0x8000) {
                continue;
            }
            bucket = sprite->prio >> 8;
            if (minBucket < 0) {
                maxBucket = bucket;
                minBucket = maxBucket;
                buckets[maxBucket].first = sprite;
                buckets[maxBucket].last = sprite;
            } else {
                if (maxBucket < bucket) {
                    node = buckets[maxBucket].first;
                } else {
                    for (j = bucket; j < maxBucket + 1; j++) {
                        node = buckets[j].first;
                        if (node != NULL && sprite->prio <= node->prio) {
                            last = buckets[j].last;
                            if (last != NULL && sprite->prio <= last->prio) {
                                node = last;
                            }
                            break;
                        }
                    }
                    if (j == maxBucket + 1) {
                        node = buckets[maxBucket].first;
                    }
                }
                while (node != NULL) {
                    if (sprite->prio > node->prio) {
                        break;
                    }
                    node = node->unk_118;
                }
                if (node != NULL) {
                    sprite->unk_118 = node;
                    sprite->unk_11C = node->unk_11C;
                    if (node->unk_11C != NULL) {
                        node->unk_11C->unk_118 = sprite;
                    }
                    node->unk_11C = sprite;
                } else {
                    sprite->unk_118 = NULL;
                    sprite->unk_11C = buckets[minBucket].last;
                    buckets[minBucket].last->unk_118 = sprite;
                }
                if (buckets[bucket].last == NULL || sprite->prio <= buckets[bucket].last->prio) {
                    buckets[bucket].last = sprite;
                }
                if (buckets[bucket].first == NULL || sprite->prio > buckets[bucket].first->prio) {
                    buckets[bucket].first = sprite;
                }
                if (bucket < minBucket) {
                    minBucket = bucket;
                }
                if (maxBucket < bucket) {
                    maxBucket = bucket;
                }
            }
            D_800CB8A0_main++;
        }
    }
    D_800BD804_main = buckets[maxBucket].first;
    return buckets[maxBucket].first;
}

s16 func_8005338C_main(HuSprGrp *arg0) {
    HuSprite *sprite;
    s16 result = 0;
    s16 i;
    s16 j;

    for (j = 0; j < arg0->unk_0A; j++) {
        sprite = arg0->members[j];
        sprite->unk_116 = -1;
        sprite->unk_114 = -1;
    }
    for (i = 0; i < arg0->unk_0A; i++) {
        sprite = arg0->members[i];

        if (sprite->unk_2E >= 0) {
            HuSprite *parent = arg0->members[sprite->unk_2E];

            if (parent->unk_116 < 0) {
                parent->unk_116 = i;
            } else {
                for (j = 0; j < i; j++) {
                    HuSprite *other = arg0->members[j];

                    if (j != i && sprite->unk_2E == other->unk_2E && other->unk_114 < 0) {
                        other->unk_114 = i;
                        break;
                    }
                }
            }
        } else {
            result = i;
        }
    }
    return result;
}

void func_800534C8_main(f32 a0[][2], f32 a1[][2], f32 a2[][2]) {
    s16 i;

    for (i = 0; i < 3; i++) {
        a2[i][0] = a0[i][0] * a1[0][0] + a0[i][1] * a1[1][0];
        a2[i][1] = a0[i][0] * a1[0][1] + a0[i][1] * a1[1][1];
    }
    a2[2][0] += a1[2][0];
    a2[2][1] += a1[2][1];
}

INCLUDE_ASM("asm/nonmatchings/sprman", func_80053558_main);

void func_80054170_main(void) {
    if (D_800CE1B8_main[D_800D2008_main] != NULL) {
        HuMemFree(D_800CE1B8_main[D_800D2008_main]);
    }
    if (D_800D1FDC_main != NULL) {
        D_800CE1B8_main[D_800D2008_main] = HuMemAlloc(D_800D1FDC_main);
    } else {
        D_800CE1B8_main[D_800D2008_main] = NULL;
    }
    D_800D59F4_main = D_800CE1B8_main[D_800D2008_main];
}

/* The sprite layer's draw hook (MP2 too; MP1 func_8006677C); MP3 adds the profiler marks and
   no longer clears each sprite's list links. */
void SprExec(Gfx** gfx, Mtx* mtx, HuCamera* cam) {
    HuSprite* obj;
    s16 flag = 0;
    Gfx* branch = NULL;
    Gfx* end = NULL;
    s16 sample;

    D_800D1FDC_main = 0;
    sample = func_8004D6AC_main(0, 200, 0);
    func_80053558_main();
    func_8004D6E8_main(sample);
    obj = func_800530AC_main();
    func_80054170_main();
    D_800CCF30_main = HuMemAlloc(0x4000);
    sample = func_8004D6AC_main(0, 0, 200);
    gSPViewport((*gfx)++, &D_800A1E90_main);
    gSPPerspNormalize((*gfx)++, 0x8000);
    gSPMatrix((*gfx)++, osVirtualToPhysical(&D_800BD7C0_main), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync((*gfx)++);
    gDPSetTexturePersp((*gfx)++, G_TP_NONE);
    gSPTexture((*gfx)++, 0xFFFF, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode((*gfx)++, G_CULL_BOTH);
    gSPSetGeometryMode((*gfx)++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR); /* 0x80001 */
    gDPSetBlendColor((*gfx)++, 0, 0, 0, 1);
    gDPSetAlphaCompare((*gfx)++, G_AC_THRESHOLD);
    D_800BD800_main = NULL;
    while (obj != NULL) {
        if (obj->unk_24 & 0x4000) {
            if (flag) {
                if (branch != NULL) {
                    gSPBranchList(branch, *gfx + 1);
                }
                end = (*gfx)++;
            }
            flag = 0;
        } else {
            if (!flag) {
                if (end != NULL) {
                    gSPBranchList(end, *gfx + 1);
                }
                branch = (*gfx)++;
                if (D_800BD800_main == NULL) {
                    D_800BD800_main = *gfx;
                }
            }
            flag = 1;
        }
        SprDisp(gfx, obj, cam);
        obj = obj->unk_118;
    }
    if (flag) {
        gSPEndDisplayList((*gfx)++);
        if (branch != NULL) {
            gSPBranchList(branch, *gfx);
        }
    } else if (D_800BD800_main != NULL) {
        gSPEndDisplayList(end);
    }
    gDPSetTextureLUT((*gfx)++, G_TT_NONE);
    HuMemFree(D_800CCF30_main);
    gSPMatrix((*gfx)++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix((*gfx)++, mtx + 1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, cam->screenLeft, cam->screenTop, cam->screenRight, cam->screenBottom);
    func_8004D6E8_main(sample);
}

/* Draws the sprites SprExec set aside for after the 3D layer. */
void SprLayerHook(Gfx** gfx, Mtx* mtx, HuCamera* cam) {
    if (D_800BD800_main != NULL) {
        gSPViewport((*gfx)++, &D_800A1E90_main);
        gSPPerspNormalize((*gfx)++, 0x8000);
        gSPMatrix((*gfx)++, osVirtualToPhysical(&D_800BD7C0_main), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
        gDPPipeSync((*gfx)++);
        gDPSetTexturePersp((*gfx)++, G_TP_NONE);
        gSPTexture((*gfx)++, 0xFFFF, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        gSPClearGeometryMode((*gfx)++, G_CULL_BOTH);
        gSPSetGeometryMode((*gfx)++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR); /* 0x80001 */
        gDPSetBlendColor((*gfx)++, 0, 0, 0, 1);
        gDPSetAlphaCompare((*gfx)++, G_AC_THRESHOLD);
        gSPDisplayList((*gfx)++, D_800BD800_main);
        gDPSetTextureLUT((*gfx)++, G_TT_NONE);
        gSPMatrix((*gfx)++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix((*gfx)++, mtx + 1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetScissor((*gfx)++, G_SC_NON_INTERLACE, cam->screenLeft, cam->screenTop, cam->screenRight, cam->screenBottom);
    }
}

// HuSprPosSet?
void func_80054904_main(s16 group, s16 member, s16 arg2, s16 arg3) {
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite_ptr = group_ptr->members[member];

    if ((sprite_ptr->unk_48 != arg2) || (sprite_ptr->unk_4C != arg3)) {
        group_ptr->unk_0C = 1;
        sprite_ptr->unk_48 = arg2;
        sprite_ptr->unk_4C = arg3;
    }
}

void func_800549C0_main(s16 group, s16 member, s16 arg2) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_44 = arg2;
}

void TransformPoint(Mtx* m, f32 x, f32 y, f32 z, f32 w, f32* ox, f32* oy, f32* oz, f32* ow) {
    f32 mf[4][4];

    func_80089980_main(mf, m);
    *ox = x * mf[0][0] + y * mf[1][0] + z * mf[2][0] + mf[3][0];
    *oy = x * mf[0][1] + y * mf[1][1] + z * mf[2][1] + mf[3][1];
    *oz = x * mf[0][2] + y * mf[1][2] + z * mf[2][2] + mf[3][2];
    *ow = x * mf[0][3] + y * mf[1][3] + z * mf[2][3] + mf[3][3];
}

/* Screen position (and depth in unk_44) of world point (x, y, z) seen from camera camIdx; returns
   the view distance (as MP2; MP3 also flags the group and returns the distance). */
f32 SprPos3DSet(s16 grpIdx, s16 idx, s16 camIdx, f32 x, f32 y, f32 z) {
    Mtx persp;
    Mtx lookAt;
    u16 perspNorm;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 vw;
    f32 px;
    f32 py;
    f32 pz;
    f32 pw;
    HuSprGrp* group = HuSprGrpData[grpIdx];
    HuSprite* sprite = group->members[idx];
    HuCamera* cam = &gCameraList[camIdx];
    s32 depth;
    f32 dist;

    guPerspective(&persp, &perspNorm, cam->fov[0], 1.3333334f, cam->fov[1], cam->fov[2], 1.0f);
    guLookAt(&lookAt, cam->pos.x, cam->pos.y, cam->pos.z, cam->at.x, cam->at.y, cam->at.z, cam->up.x, cam->up.y,
             cam->up.z);
    TransformPoint(&lookAt, x, y, z, 1.0f, &vx, &vy, &vz, &vw);
    TransformPoint(&persp, vx, vy, vz, vw, &px, &py, &pz, &pw);
    if (pw != 0.0f) {
        depth = (cam->viewports[D_800D418E_main].vp.vscale[2] << 5) * pz / pw + (cam->viewports[D_800D418E_main].vp.vtrans[2] << 5);
    } else {
        depth = cam->viewports[D_800D418E_main].vp.vtrans[2] << 5;
    }
    if (depth < 0) {
        depth = 0;
    } else if (depth > 0x7FC0) {
        depth = 0x7FC0;
    }
    dist = fabsf(sindf(gCameraList[camIdx].fov[0] * 0.5) * vz / cosdf(gCameraList[camIdx].fov[0] * 0.5));
    D_800BD808_main = dist;
    if (dist != 0.0) {
        sprite->unk_48 = cam->viewports[D_800D418E_main].vp.vscale[0] / 4.0 * vx / dist / 1.3333334f + cam->viewports[D_800D418E_main].vp.vtrans[0] / 4.0;
        sprite->unk_4C = cam->viewports[D_800D418E_main].vp.vscale[1] / 4.0 * -vy / dist + cam->viewports[D_800D418E_main].vp.vtrans[1] / 4.0;
    }
    sprite->unk_44 = depth;
    group->unk_0C = 1;
    return D_800BD808_main;
}

/* SprPos3DSet plus the perspective scale for that distance. */
void SprPosPerspectiveSet(s16 grpIdx, s16 idx, s16 camIdx, f32 x, f32 y, f32 z) {
    HuSprite* sprite = HuSprGrpData[grpIdx]->members[idx];
    HuCamera* cam = &gCameraList[camIdx];
    HuCamera* vp;

    SprPos3DSet(grpIdx, idx, camIdx, x, y, z);
    if (D_800BD808_main != 0.0) {
        vp = (HuCamera*) ((u8*) cam + D_800D418E_main * 16);
        sprite->unk_60 = vp->viewports[0].vp.vscale[0] / 4.0 / D_800BD808_main / 1.3333334f;
        sprite->unk_64 = vp->viewports[0].vp.vscale[1] / 4.0 / D_800BD808_main;
    }
}

void func_80054FF8_main(s16 group, s16 member, s32 arg2) {
    HuSprGrpData[group]->members[member]->unk_90 = arg2;
}

void func_80055024_main(s16 group, s16 member, s16 arg2, u16 arg3) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->unk_84 = D_800C9530_main[arg2];
    if (D_800C9530_main[arg2]->unk04 != 0) {
        sprite_ptr->unk_0E = 1;
    }
    sprite_ptr->unk_0C = arg3;
    sprite_ptr->unk_8C = 0.0f;
    sprite_ptr->unk_10 = 1.0f;
    sprite_ptr->unk_8A = 0;
    sprite_ptr->unk_88 = 0;
    sprite_ptr->unk_90 = 0;
    func_80052E14_main(sprite_ptr);
}

void func_800550B4_main(s16 group, s16 member, f32 arg2) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->unk_10 = arg2;
    func_80052E14_main(sprite_ptr);
}

void func_800550F4_main(s16 group, s16 member, s32 arg2) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->unk_88 &= 0x7F;
    sprite_ptr->unk_0E = arg2;
    func_80052E14_main(sprite_ptr);
}

void func_80055140_main(s16 group, s16 member, u16 arg2, s32 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_88 &= 0x7F;
    sprite->unk_0C = arg2;
    sprite->unk_8A = arg3;
    sprite->unk_8C = 0;
    func_80052E14_main(sprite);
}

HuSprite_Unk84_Struct *func_80055194_main(s16 arg0) {
    return D_800C9530_main[arg0];
}

u8 func_800551AC_main(s16 group, s16 member) {
    return HuSprGrpData[group]->members[member]->unk_88;
}

void HuSprScaleSet(s16 group, s16 member, f32 x, f32 y) {
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite_ptr = group_ptr->members[member];

    if (sprite_ptr->unk_50 != x || sprite_ptr->unk_54 != y || sprite_ptr->unk_60 != 1.0f || sprite_ptr->unk_64 != 1.0f) {
        group_ptr->unk_0C = 1;
        sprite_ptr->unk_50 = x;
        sprite_ptr->unk_54 = y;
        sprite_ptr->unk_64 = 1.0f;
        sprite_ptr->unk_60 = 1.0f;
    }
}

void HuSprPriSet(s16 group, s16 member, u16 prio) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    if (sprite_ptr->prio != prio) {
        sprite_ptr->prio = prio;
        D_800A1EA0_main = 1;
    }
}

void func_800552DC_main(s16 group, s16 member, f32 arg2) {
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite_ptr = group_ptr->members[member];

    if (sprite_ptr->unk_58 != arg2) {
        group_ptr->unk_0C = 1;
        sprite_ptr->unk_58 = arg2;
    }
}

void HuSprAttrReset(s16 group, s16 member, s32 attr) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    if ((sprite_ptr->unk_5C & 0x8000) && (attr & 0x8000)) {
        D_800A1EA0_main = 1;
    }
    if ((sprite_ptr->unk_5C & 0x4000) && (attr & 0x4000)) {
        D_800A1EA0_main = 1;
    }
    sprite_ptr->unk_5C &= ~attr;
    sprite_ptr->unk_24 = sprite_ptr->unk_5C;
}

void HuSprAttrSet(s16 group, s16 member, s32 attr) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    if (!(sprite_ptr->unk_5C & 0x8000) && (attr & 0x8000)) {
        D_800A1EA0_main = 1;
    }
    if (!(sprite_ptr->unk_5C & 0x4000) && (attr & 0x4000)) {
        D_800A1EA0_main = 1;
    }
    sprite_ptr->unk_5C |= attr;
    sprite_ptr->unk_24 = sprite_ptr->unk_5C;
}

void func_80055420_main(s16 group, s16 member, u8 r, u8 g, u8 b) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->unk_28[0] = r;
    sprite_ptr->unk_28[1] = g;
    sprite_ptr->unk_28[2] = b;
}

void func_80055458_main(s16 group, s16 member, u16 arg2) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->unk_2C = arg2;
}

void func_80055484_main(s16 group, s16 member, u8 arg2, u8 arg3, u8 arg4, u16 arg5) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->unk_28[0] = arg2;
    sprite_ptr->unk_28[1] = arg3;
    sprite_ptr->unk_28[2] = arg4;
    sprite_ptr->unk_2C = arg5;
}

void func_800554C4_main(s16 group, s16 member, s16 arg2) {
    HuSprGrpData[group]->members[member]->unk_2E = arg2;
}

void func_800554F0_main(s16 group, s16 member, u8 arg2, u8 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_93 = arg2;
    sprite->unk_94 = arg3;
}

HuSprite *HuSprGet(s16 group, s16 member) {
    return HuSprGrpData[group]->members[member];
}

void func_80055548_main(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_3C = arg2;
    sprite->unk_3E = arg3;
    sprite->unk_40 = arg4;
    sprite->unk_42 = arg5;
}

void func_80055588_main(s16 group, s16 member, s32 arg2, s32 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_30.i = arg2;
    sprite->unk_34.i = arg3;
}

void func_800555B8_main(s16 group, s16 member, u16 arg2, u16 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_38 = arg2;
    sprite->unk_3A = arg3;
}

void func_800555E8_main(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_204 = arg2;
    sprite->unk_206 = arg3;
    sprite->unk_208 = arg4;
    sprite->unk_20A = arg5;
}

void func_80055628_main(void) {
    s16 i;

    D_800CC3E6_main = 0;
    for (i = 0; i < 0x100; i++) {
        D_800C9530_main[i] = NULL;
    }
}

void HuSprKill(s16 arg0) {
    HuSprite_Unk84_Struct *desc = D_800C9530_main[arg0];
    s16 i;

    if (desc->unk04 != NULL) {
        HuSprCelAnm *cel = *desc->unk04;
        if (cel != NULL) {
            for (i = 0; i < desc->unk12; i++) {
                HuMemFree(cel->unk04);
                cel++;
            }
        }
        HuMemFree(*desc->unk04);
        HuMemFree(desc->unk04);
    }
    func_80019C00_main(desc->unk0C);
    {
        HuSprite_Unk84_Unk00_Struct *cel = desc->unk00;
        for (i = 0; i < desc->unk10; i++) {
            func_80019C00_main(cel->unk00);
            cel++;
        }
    }
    HuMemFree(desc->unk00);
    HuMemFree(desc);
    D_800C9530_main[arg0] = NULL;
    D_800CC3E6_main--;
}

void func_800557A0_main(void) {
    s16 i;

    for (i = 0; i < 0x100; i++) {
        if (D_800C9530_main[i] != NULL) {
            HuSprKill(i);
        }
    }
}

s16 func_80055810_main(void *arg0) {
    HuSprCelFrame *frames[0x100];
    HuSprite_Unk84_Struct *desc;
    HuSprite_Unk84_Unk00_Struct *image;
    HuSprCelAnm **animations;
    HuSprCelAnm *animation;
    HuSprCelFrame *frame;
    HuSprFileHeader *header = arg0;
    HuSprFileImage *fileImage;
    u8(*animationOffsets)[4];
    u8 *pixels;
    u8 *palette;
    u8 *dest;
    u8 *src;
    s32 size;
    u32 j;
    s16 i;
    s16 slot;
    s16 k;

    for (i = 0; i < 0x100 && D_800C9530_main[i] != NULL; i++) {
    }
    if (i == 0x100) {
        return -1;
    }
    slot = i;
    desc = HuMemAlloc(sizeof(*desc));
    if (desc == NULL) {
        return -1;
    }
    fileImage = (HuSprFileImage *)((u8 *)header + HUSPR_READ32(header->images));
    animationOffsets = (u8(*)[4])((u8 *)header + HUSPR_READ32(header->animations));
    pixels = (u8 *)header + HUSPR_READ32(header->pixels);
    palette = (u8 *)header + HUSPR_READ32(header->palette);
    desc->unk10 = HUSPR_READ16(header->imageCount);
    desc->unk12 = HUSPR_READ16(header->animationCount);
    desc->unk14 = HUSPR_READ16(header->width);
    desc->unk16 = HUSPR_READ16(header->height);
    desc->unk18 = HUSPR_READ16(header->pixelBits);
    desc->unk1A = header->paletteCount;
    // A zero palette count represents 256 colors for 8-bit images.
    if (desc->unk18 == 8 && desc->unk1A == 0) {
        desc->unk1A = 0x100;
    }
    desc->unk00 = NULL;
    desc->unk04 = NULL;
    desc->unk08 = NULL;
    desc->unk0C = NULL;
    D_800C9530_main[slot] = desc;
    D_800CC3E6_main++;
    image = HuMemAlloc(desc->unk10 * sizeof(*image));
    if (image != NULL) {
        desc->unk00 = image;
    } else {
        HuSprKill(slot);
        return -1;
    }
    for (i = 0; i < desc->unk10; i++) {
        image->unk04 = HUSPR_READ16(fileImage->width);
        image->unk06 = HUSPR_READ16(fileImage->height);
        image->unk08 = HUSPR_READ16(fileImage->centerX);
        image->unk0A = HUSPR_READ16(fileImage->centerY);
        size = image->unk04 * image->unk06 * (desc->unk18 & 0x7FFF) / 8;
        image->unk00 = HuMemAlloc(size);
        if (image->unk00 == NULL) {
            desc->unk10 = i;
            HuSprKill(slot);
            return -1;
        }
        for (j = 0; j < size; j++) {
            ((u8 *)image->unk00)[j] = *pixels++;
        }
        fileImage++;
        if (i == 0) {
            desc->unk08 = image->unk00;
        }
        image++;
    }
    if (desc->unk1A != 0) {
        dest = HuMemAlloc(desc->unk1A * 2);
        if (dest != NULL) {
            desc->unk0C = dest;
        } else {
            HuSprKill(slot);
            return -1;
        }
        for (i = 0; i < desc->unk1A; i++) {
            *dest++ = palette[i * 2];
            *dest++ = palette[i * 2 + 1];
        }
    }
    if (desc->unk12 == 0) {
        return slot;
    }
    animations = HuMemAlloc(desc->unk12 * (s32)sizeof(*animations));
    if (animations != NULL) {
        desc->unk04 = animations;
    } else {
        HuSprKill(slot);
        return -1;
    }
    animation = HuMemAlloc(desc->unk12 * (s32)sizeof(*animation));
    if (animation == NULL) {
        HuSprKill(slot);
        return -1;
    }
    for (i = 0; i < desc->unk12; i++) {
        // The original loader scales this index by the record size twice.
        animations[i] = &animation[i * sizeof(*animation)];
    }
    for (k = 0; k < desc->unk12; k++) {
        src = (u8 *)header + HUSPR_READ32(animationOffsets[k]);
        animation->unk00 = HUSPR_READ16(src);
        src += 2;
        frames[k] = HuMemAlloc(animation->unk00 * sizeof(*frame));
        if (frames[k] == NULL) {
            desc->unk12 = k;
            HuSprKill(slot);
            return -1;
        }
        animation->unk04 = frames[k];
        frame = frames[k];
        for (i = 0; i < animation->unk00; i++) {
            frame->unk00 = HUSPR_READ16(((HuSprFileFrame *)src)->image);
            frame->unk02 = HUSPR_READ16(((HuSprFileFrame *)src)->duration);
            frame->unk04 = ((HuSprFileFrame *)src)->unk04;
            frame->unk05 = ((HuSprFileFrame *)src)->unk05;
            frame->unk06 = ((HuSprFileFrame *)src)->unk06;
            src += sizeof(HuSprFileFrame);
            frame++;
        }
        animation++;
    }
    return slot;
}

s32 func_80055DBC_main(u16 arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    HuSprite_Unk84_Struct *desc;
    HuSprite_Unk84_Unk00_Struct *cel;
    s16 i;
    s16 slot;

    for (i = 0; i < 0x100 && D_800C9530_main[i] != NULL; i++) {
    }
    if (i == 0x100) {
        return -1;
    }
    slot = i;
    desc = HuMemAlloc(0x1C);
    if (desc == NULL) {
        return -1;
    }
    desc->unk10 = arg4;
    desc->unk12 = 0;
    desc->unk14 = arg0;
    desc->unk16 = arg1 * arg4;
    desc->unk18 = arg2;
    desc->unk1A = arg3;
    desc->unk00 = NULL;
    desc->unk04 = 0;
    desc->unk08 = NULL;
    desc->unk0C = NULL;
    D_800C9530_main[slot] = desc;
    D_800CC3E6_main++;
    cel = HuMemAlloc(desc->unk10 * 0xC);
    if (cel != NULL) {
        desc->unk00 = cel;
    } else {
        HuSprKill(slot);
        return -1;
    }
    for (i = 0; i < desc->unk10; i++) {
        s32 size;

        cel->unk04 = arg0;
        cel->unk06 = arg1;
        cel->unk08 = arg0 >> 1;
        cel->unk0A = arg1 >> 1;
        size = cel->unk04 * cel->unk06 * (desc->unk18 & 0x7FFF);
        cel->unk00 = HuMemAlloc(size / 8);
        if (cel->unk00 == NULL) {
            desc->unk10 = i;
            HuSprKill(slot);
            return -1;
        }
        if (i == 0) {
            desc->unk08 = cel->unk00;
        }
        cel++;
    }
    if (desc->unk1A != 0) {
        void *pal = HuMemAlloc(desc->unk1A * 2);

        if (pal != NULL) {
            desc->unk0C = pal;
        } else {
            HuSprKill(slot);
            return -1;
        }
    }
    return slot;
}

void func_80055FF4_main(HuSprAnm *arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_80052DD8_main(arg0);
    arg0->unk06 = arg3;
    arg0->unk08 = arg2;
    arg0->unk00 = func_80055194_main(arg1);
}

s16 func_80056054_main(void *arg0, HuSprAnm *arg1, u16 arg2, u16 arg3) {
    s16 temp = func_80055810_main(arg0);

    func_80055FF4_main(arg1, temp, arg2, arg3);
    return temp;
}

HuSprite_Unk84_Unk00_Struct *func_800560B8_main(HuSprite_Unk84_Struct **arg0, u16 arg1) {
    return &(*arg0)->unk00[arg1];
}

HuSprite_Unk84_Unk00_Struct *func_800560D8_main(s16 arg0, u16 arg1) {
    return &D_800C9530_main[arg0]->unk00[arg1];
}

HuSprite_Unk84_Unk00_Struct *func_80056108_main(HuSprAnm *arg0) {
    return &arg0->unk00->unk00[arg0->unk14];
}

void *func_80056128_main(HuSprite_Unk84_Struct **arg0, u16 arg1) {
    HuSprite_Unk84_Unk00_Struct *entry = &(*arg0)->unk00[arg1];

    return entry->unk00;
}

void *func_8005614C_main(s16 arg0, u16 arg1) {
    HuSprite_Unk84_Unk00_Struct *entry = &D_800C9530_main[arg0]->unk00[arg1];

    return entry->unk00;
}

void func_80056180_main(HuSprite_Unk84_Struct **arg0, u16 arg1, void *arg2) {
    HuSprite_Unk84_Unk00_Struct *entry = &(*arg0)->unk00[arg1];

    func_80019C00_main(entry->unk00);
    entry->unk00 = arg2;
}

void func_800561D0_main(s16 arg0, u16 arg1, void *arg2) {
    HuSprite_Unk84_Unk00_Struct *entry = &D_800C9530_main[arg0]->unk00[arg1];

    func_80019C00_main(entry->unk00);
    entry->unk00 = arg2;
}

void *func_80056230_main(HuSprAnm *arg0) {
    HuSprite_Unk84_Unk00_Struct *entry = &arg0->unk00->unk00[arg0->unk14];

    return entry->unk00;
}

void *func_80056254_main(HuSprite_Unk84_Struct **arg0) {
    return (*arg0)->unk0C;
}

void *func_80056260_main(s16 arg0) {
    return D_800C9530_main[arg0]->unk0C;
}

void func_8005627C_main(HuSprite_Unk84_Struct **arg0, void *arg1) {
    func_80019C00_main((*arg0)->unk0C);
    (*arg0)->unk0C = arg1;
}

void func_800562BC_main(s16 arg0, void *arg1) {
    func_80019C00_main(D_800C9530_main[arg0]->unk0C);
    D_800C9530_main[arg0]->unk0C = arg1;
}

s16 func_8005630C_main(HuSprAnm *arg0) {
    HuSprite_Unk84_Struct *desc = arg0->unk00;

    if (desc == NULL) {
        return -1;
    }
    if (arg0->unk06 == 1) {
        HuSprCelAnm *cel;
        HuSprCelFrame *frame;

        if (desc->unk04 == NULL) {
            return 0;
        }
        cel = &(*desc->unk04)[arg0->unk08];
        frame = &cel->unk04[arg0->unk0A];
        arg0->unk14 = frame->unk00;
        arg0->unk17 = frame->unk04;
        arg0->unk18 = frame->unk05;
        arg0->unk16 = frame->unk06;
    } else if (arg0->unk06 >= 2) {
        if (arg0->unk06 < 4) {
            arg0->unk14 = arg0->unk0A;
        }
    }
    return 0;
}

/* Steps a cel animation. */
void AnimateSprite(HuSprAnm* anm) {
    HuSprite_Unk84_Struct* anim;
    HuSprCelAnm* bank;
    HuSprCelFrame* key;
    s16 old;

    anim = anm->unk00;
    if (anim == NULL) {
        return;
    }
    anm->unk04 &= 0x80;
    switch (anm->unk06) {
        case 0:
            break;
        case 1:
            if (anim->unk04 == NULL) {
                break;
            }
            bank = &(*anim->unk04)[anm->unk08];
            key = &bank->unk04[anm->unk0A];
            anm->unk0C += anm->unk10;
            if ((s16)anm->unk0C > (s16)key->unk02) {
                anm->unk0C = 0.0f;
                anm->unk0A++;
                anm->unk04 |= 4;
                if (anm->unk0A >= bank->unk00) {
                    anm->unk06 = 0;
                    anm->unk04 |= 2;
                } else if ((s16)bank->unk04[anm->unk0A].unk02 < 0) {
                    anm->unk0A = 0;
                    anm->unk04 |= 8;
                }
            }
            anm->unk14 = key->unk00;
            anm->unk17 = key->unk04;
            anm->unk18 = key->unk05;
            anm->unk16 = key->unk06;
            anm->unk04 |= 1;
            break;
        case 2:
            old = anm->unk0A;
            anm->unk0C += anm->unk10;
            anm->unk0A = (s32)anm->unk0C + anm->unk0A;
            if (anm->unk0A != old) {
                anm->unk0C -= anm->unk0A - old;
                anm->unk04 |= 4;
            }
            if (anm->unk0A >= anm->unk00->unk10) {
                anm->unk0A = 0;
                anm->unk0C = 0.0f;
                anm->unk04 |= 8;
            }
            anm->unk14 = anm->unk0A;
            anm->unk04 |= 1;
            break;
        case 3:
            old = anm->unk0A;
            anm->unk0C += anm->unk10;
            anm->unk0A = (s32)anm->unk0C + anm->unk0A;
            if (anm->unk0A != old) {
                anm->unk0C -= anm->unk0A - old;
                anm->unk04 |= 8;
            }
            if (anm->unk0A < 0 || anm->unk0A >= anm->unk00->unk10) {
                anm->unk0A = (anm->unk10 < 0.0f) ? 1 : anm->unk00->unk10 - 2;
                anm->unk0C = 0.0f;
                anm->unk10 = -anm->unk10;
                anm->unk04 |= 8;
            }
            anm->unk14 = anm->unk0A;
            anm->unk04 |= 1;
            break;
    }
}

void func_80056650_main(HuSprite *sprite) {
    HuSprAnm *anm = &sprite->unk_68;

    func_80052E14_main(sprite);
    if (!(sprite->unk_68.unk04 & 0x80)) {
        if (func_8005630C_main(anm) == 0) {
            sprite->unk_68.unk04 |= 0x80;
        }
    } else {
        if (HmfPauseF == 0 || (sprite->unk_24 & 0x1000000)) {
            AnimateSprite(anm);
        }
    }
    sprite->unk_88 = anm->unk04;
    sprite->unk_0E = (u16)anm->unk06;
    sprite->unk_90 = (u16)anm->unk14;
    sprite->unk_93 = anm->unk17;
    sprite->unk_94 = anm->unk18;
    sprite->unk_92 = anm->unk16;
    sprite->unk_8A = (u16)anm->unk0A;
    sprite->unk_8C = anm->unk0C;
    sprite->unk_10 = anm->unk10;
    sprite->unk_18 = sprite->unk_50 * sprite->unk_60;
    sprite->unk_1C = sprite->unk_54 * sprite->unk_64;
    if (sprite->unk_98 != NULL) {
        func_800571C8_main((struct SprPalAnim *) &sprite->unk_98);
    }
}

/* Before drawing (MP2 func_80083748_84348, MP1 func_80068124): a sprite that is rotated, scaled or flagged for the
   textured-quad path counts the display-list space it needs (D_800D1FDC_main), or (flag 0x8000000)
   gets its own buffer. */
void func_80056758_main(HuSprite* sprite) {
    HuSprite_Unk84_Struct* anim;
    HuSprite_Unk84_Unk00_Struct* frame;
    s32 fmt = 0;
    s32 siz = 0;
    s32 w;
    u32 lines;
    s32 n;
    s32 diff;

    sprite->unk_24 = (u8)sprite->unk_92 ^ sprite->unk_5C;
    if (sprite->unk_84 != NULL && !(sprite->unk_24 & 0x8000)) {
        if (fabs(fmod(SPR_ROT(sprite), 360.0)) > 0.1f || (sprite->unk_24 & 0x3C0C00) ||
            (sprite->unk_24 & 0x30000) == 0x30000 || (sprite->unk_24 & 0x20000000)) {
            anim = sprite->unk_84;
            frame = &anim->unk00[sprite->unk_90];
            switch (anim->unk18 & 0x7FFF) {
                case 4:
                    fmt = 2;
                    siz = 0;
                    break;
                case 8:
                    fmt = 2;
                    siz = 1;
                    break;
                case 16:
                    fmt = 0;
                    siz = 2;
                    break;
                case 24:
                    fmt = 0;
                    siz = 3;
                    break;
            }
            w = (((frame->unk04 << siz) >> 4) << 4) >> siz;
            if (w < frame->unk04) {
                w += 16 >> siz;
            }
            switch (fmt) {
            case 2:
                if ((0x1000 >> siz) >= frame->unk06 * w) {
                    lines = frame->unk06;
                } else {
                    lines = (0x1000 >> siz) / w;
                }
                break;
            case 4:
                lines = frame->unk06;
                if (frame->unk06 * w > 0x1000) {
                    lines = 0x1000 / w;
                }
                break;
            default:
                if ((0x2000 >> siz) >= frame->unk06 * w) {
                    lines = frame->unk06;
                } else {
                    lines = (0x2000 >> siz) / w;
                }
                break;
            }
            n = frame->unk06 / lines;
            sprite->unk_24 |= 0x40000000;
            if (!(sprite->unk_24 & 0x8000000)) {
                if (!(sprite->unk_24 & 0x2000)) {
                    D_800D1FDC_main += (n + 2) << 5;
                } else {
                    D_800D1FDC_main += (n + 2) << 6;
                }
            } else {
                diff = sprite->unk_24 ^ SPR_LASTATTR(sprite);
                if (sprite->unk_124 == NULL || (diff & 0x40000000)) {
                    sprite->unk_24 |= 0x10000000;
                }
                if (sprite->unk_24 & 0x10000000) {
                    if (sprite->unk_128[SPR_BUFIDX(sprite)] != NULL) {
                        HuMemFree(sprite->unk_128[SPR_BUFIDX(sprite)]);
                        HuMemFree(sprite->unk_134[SPR_BUFIDX(sprite)]);
                        sprite->unk_128[SPR_BUFIDX(sprite)] = NULL;
                        sprite->unk_134[SPR_BUFIDX(sprite)] = NULL;
                    }
                    if (!(sprite->unk_24 & 0x2000)) {
                        sprite->unk_134[SPR_BUFIDX(sprite)] = HuMemAlloc((n + 2) << 5);
                    } else {
                        sprite->unk_134[SPR_BUFIDX(sprite)] = HuMemAlloc((n + 2) << 6);
                    }
                }
            }
        } else {
            sprite->unk_24 &= ~0x40000000;
            if (sprite->unk_24 & 0x8000000) {
                diff = sprite->unk_24 ^ SPR_LASTATTR(sprite);
                if (sprite->unk_124 == NULL || (diff & 0x40000000)) {
                    sprite->unk_24 |= 0x10000000;
                }
                if (sprite->unk_24 & 0x10000000) {
                    if (sprite->unk_128[SPR_BUFIDX(sprite)] != NULL) {
                        HuMemFree(sprite->unk_128[SPR_BUFIDX(sprite)]);
                        HuMemFree(sprite->unk_134[SPR_BUFIDX(sprite)]);
                        sprite->unk_128[SPR_BUFIDX(sprite)] = NULL;
                        sprite->unk_134[SPR_BUFIDX(sprite)] = NULL;
                    }
                }
            }
        }
        SPR_LASTATTR(sprite) = sprite->unk_24;
    }
}

void func_80056BAC_main(void) {
    s16 i;

    func_80052700_main();
    func_800557A0_main();
    func_80057158_main();
    for (i = 0; i < 3; i++) {
        if (D_800CE1B8_main[i] != NULL) {
            HuMemFree(D_800CE1B8_main[i]);
        }
    }
}

void func_80056C28_main(void) {
    f32 mf[4][4];
    Mtx m1;
    Mtx m2;

    fmod(0.0, 0.0);
    func_8007DFE0_main(mf, 0.0f, 0.0f, 0.0f);
    guMtxCatL(&m1, &m2, &m1);
}

u16 func_80056C74_main(u8 **arg0) {
    u8 *p = *arg0;
    u16 val = (p[0] << 8) + p[1];

    *arg0 = p + 2;
    return val;
}

u32 func_80056C98_main(u8 **arg0) {
    u8 *p = *arg0;
    u32 val = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];

    *arg0 = p + 4;
    return val;
}

void func_80056CD0_main(void) {
    s16 i;

    D_800D554E_main = 0;
    for (i = 0; i < 0x100; i++) {
        D_800D0A50_main[i] = NULL;
    }
}

/* Loads a palette-animation file into a free slot (MP2 func_80083D08_84908). */
s16 func_80056D18_main(u8* data) {
    u8* p;
    HuSprAnmDesc* desc;
    SprPalGroup* grp;
    SprPalFrame* frame;
    SprPalEntry* e;
    s32 i;
    s32 j;
    s32 k;
    s32 slot;
    u8* base = data;

    for (i = 0; i < 256; i++) {
        if (D_800D0A50_main[i] == NULL) {
            break;
        }
    }
    if (i == 256) {
        return -1;
    }
    slot = i;
    desc = HuMemAlloc(sizeof(HuSprAnmDesc));
    desc->unk00 = func_80056C74_main(&data);
    desc->unk02 = func_80056C74_main(&data);
    desc->unk04 = HuMemAlloc(desc->unk02 * 4);
    for (j = 0; j < desc->unk02; j++) {
        desc->unk04[j] = (HuSprAnmEntry*)(grp = HuMemAlloc(sizeof(SprPalGroup)));
        p = base + func_80056C98_main(&data);
        grp->count = func_80056C74_main(&p);
        if (grp->count != 0) {
            grp->nframes = func_80056C74_main(&p);
            grp->frames = HuMemAlloc(grp->nframes * 4);
            for (k = 0; k < grp->nframes; k++) {
                frame = HuMemAlloc(sizeof(SprPalFrame));
                grp->frames[k] = frame;
                frame->dur = func_80056C74_main(&p);
                e = HuMemAlloc(grp->count * 4);
                frame->entries = e;
                for (i = 0; i < grp->count; i++, e++) {
                    e->idx = func_80056C74_main(&p);
                    e->color = func_80056C74_main(&p);
                }
            }
        }
    }
    desc->unk08 = func_80056C74_main(&data);
    desc->unk0C = HuMemAlloc(desc->unk08 * 2);
    for (i = 0; i < desc->unk08; i++) {
        ((u16*)desc->unk0C)[i] = func_80056C74_main(&data);
    }
    D_800D0A50_main[slot] = desc;
    D_800D554E_main++;
    return slot;
}

void func_80056F80_main(s16 arg0) {
    HuSprAnmDesc *desc = D_800D0A50_main[arg0];
    s32 i;

    for (i = 0; i < desc->unk02; i++) {
        HuSprAnmEntry *group = desc->unk04[i];

        if (group->unk00 != 0) {
            s32 j;

            for (j = 0; j < group->unk02; j++) {
                HuSprAnmEntry *cel = group->unk04[j];

                HuMemFree(cel->unk04);
                HuMemFree(cel);
            }
            HuMemFree(group->unk04);
        }
        HuMemFree(group);
    }
    HuMemFree(desc->unk04);
    HuMemFree(desc->unk0C);
    HuMemFree(desc);
    D_800D0A50_main[arg0] = NULL;
    D_800D554E_main--;
}

void func_800570A8_main(s16 group, s16 member, s16 arg2) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];
    s32 i;

    sprite->unk_98 = D_800D0A50_main[arg2];
    sprite->unk_FC.f = 1.0f;
    for (i = 0; i < 0x10; i++) {
        sprite->unk_9C[i] = 0xFFFF;
        sprite->unk_BC[i] = 0;
    }
    sprite->unk_104 = 0;
}

void func_8005712C_main(s16 group, s16 member, s32 arg2) {
    HuSprGrpData[group]->members[member]->unk_FC.i = arg2;
}

void func_80057158_main(void) {
    s16 i;

    for (i = 0; i < 0x100; i++) {
        if (D_800D0A50_main[i] != NULL) {
            func_80056F80_main(i);
        }
    }
}

/* Steps a sprite's palette animation; when a frame changes, rebuilds the palette in the next of
   three buffers (MP2 func_800841B8_84DB8). */
// register allocation, as in MP2 (masked 0, raw 6): the frame pointer shares v0 with dur where
// retail loads it into v1 (three places).
#ifdef NON_MATCHING
void func_800571C8_main(SprPalAnim* pa) {
    HuSprAnmDesc* desc;
    SprPalGroup* grp;
    SprPalEntry* e;
    s32 changed;
    s32 i;
    s32 j;
    s32 dur;

    changed = 0;
    desc = pa->desc;
    for (i = 0; i < desc->unk02; i++) {
        grp = (SprPalGroup*)desc->unk04[i];
        if (grp->count != 0) {
            pa->timer[i] -= pa->speed;
            do {
                if (pa->timer[i] <= 0.0f) {
                    pa->frame[i]++;
                    if (pa->frame[i] >= grp->nframes) {
                        pa->frame[i] = 0;
                        dur = (*grp->frames)->dur;
                    } else if ((dur = grp->frames[pa->frame[i]]->dur) <= 0) {
                        pa->frame[i] = 0;
                        dur = (*grp->frames)->dur;
                    }
                    pa->timer[i] = dur + pa->timer[i];
                    changed = 1;
                }
            } while (pa->timer[i] < 0.0f);
        }
    }
    if (changed) {
        if (pa->bufs[pa->bufIdx] == NULL) {
            pa->bufs[pa->bufIdx] = HuMemAlloc(desc->unk08 * 2);
        }
        pa->cur = pa->bufs[pa->bufIdx];
        bcopy(desc->unk0C, pa->cur, desc->unk08 * 2);
        pa->bufIdx++;
        if (pa->bufIdx >= 3) {
            pa->bufIdx = 0;
        }
        for (j = 0; j < desc->unk02; j++) {
            grp = (SprPalGroup*)desc->unk04[j];
            if (grp->count != 0) {
                e = grp->frames[pa->frame[j]]->entries;
                for (i = 0; i < grp->count; i++, e++) {
                    pa->cur[e->idx] = e->color;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/sprman", func_800571C8_main);
#endif
