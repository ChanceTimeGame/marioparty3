#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"

// bg A: The Beat Goes On

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct BgCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} BgCtrl; /* size 0x28 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);

extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];

/* An entry of D_800CBB60_main (src/14EA0.c unk_800ECDE0) */
typedef struct BgSprModel {
    /* 0x00 */ u16 unk00; /* model */
    /* 0x02 */ u16 unk02; /* bank */
    /* 0x04 */ s16 unk04; /* step */
    /* 0x06 */ s16 unk06; /* animation */
    /* 0x08 */ char unk08[0x18];
    /* 0x20 */ u8* unk20;
} BgSprModel; /* size 0x24 */

/* src/14EA0.c SprBankStep, SprBankAnim, SprBank (D_800D408C_main) */
typedef struct BgSprBankStep {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ char unk_04[4];
} BgSprBankStep; /* size 8 */

typedef struct BgSprBankAnim {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ BgSprBankStep* unk_04;
} BgSprBankAnim; /* size 8 */

typedef struct BgSprBank {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ BgSprBankAnim* unk_10;
    /* 0x14 */ u16* unk_14;
} BgSprBank; /* size 0x18 */

extern BgSprBank* D_800D408C_main;

/* omObjData::data of a drum */
typedef struct BgDrum {
    /* 0x00 */ Vec unk00; /* sprite position */
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ s8 unk10;
    /* 0x11 */ char unk11[3];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ BgSprModel* unk18;
    /* 0x1C */ s8 unk1C; /* drum index */
    /* 0x1D */ char unk1D[3];
} BgDrum; /* size 0x20 */

extern BgSprModel* D_800CBB60_main;
u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
u16 func_80014618_main(s16 index, u16 arg1);
void func_80014714_main(s16 index, u16 arg1);
s16 HmfAnimRead(HmfData* arg0, s32 arg1, char* arg2);

// LOCAL
void func_80105C68_the_beat_goes_on(BgCtrl* ctrl);
void func_80105CDC_the_beat_goes_on(void);
void func_80105E0C_the_beat_goes_on(f32 div);
void func_80105F60_the_beat_goes_on(f32 div);
void func_801060B0_the_beat_goes_on(f32 div);
void func_80106204_the_beat_goes_on(f32 div);
void func_80106358_the_beat_goes_on(omObjData* obj);
void func_80106708_the_beat_goes_on(omObjData* obj);
void func_80107504_the_beat_goes_on(omObjData* obj);
void func_80108324_the_beat_goes_on(omObjData* obj);
void func_8010B058_the_beat_goes_on(omObjData* obj);
void func_8010B17C_the_beat_goes_on(omObjData* obj);
void func_80106E40_the_beat_goes_on(omObjData* obj);

extern s32 D_8010C2E4_the_beat_goes_on;
extern s32 D_8010C2E8_the_beat_goes_on;
extern s8 D_8010C2EC_the_beat_goes_on;

extern s16 D_8010C460_the_beat_goes_on;
extern s16 D_8010C462_the_beat_goes_on;
extern s16 D_8010C464_the_beat_goes_on;
extern s16 D_8010C466_the_beat_goes_on; /* drums made; D_8010C467 is its low byte */
extern u16 D_8010C468_the_beat_goes_on;
extern s16 D_8010C2F0_the_beat_goes_on[8][2]; /* sprite frame origin */
extern BgCtrl D_8010C478_the_beat_goes_on;
extern omObjData* D_8010C4E0_the_beat_goes_on;
extern omObjData* D_8010C4E4_the_beat_goes_on;
extern s8 D_8010C4EA_the_beat_goes_on;
extern s16 D_8010C4EC_the_beat_goes_on[4];
extern s16 D_8010C4F4_the_beat_goes_on;

void func_801059A0_the_beat_goes_on(void) {
    omObjData* obj;
    s32 i;
    s16 mdl;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CDC_the_beat_goes_on();
    func_80105C68_the_beat_goes_on(&D_8010C478_the_beat_goes_on);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010C478_the_beat_goes_on);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80106358_the_beat_goes_on), 0xA0);
    omSetStatBit(omAddObj(0, 1, 0, -1, func_8010B058_the_beat_goes_on), 0xA0);
    D_8010C4E0_the_beat_goes_on = omAddObj(0, 4, 5, -1, func_80107504_the_beat_goes_on);
    mdl = func_8000B108_main(0x41000A, 0x819);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            D_8010C4EC_the_beat_goes_on[i] = mdl;
        } else {
            D_8010C4EC_the_beat_goes_on[i] = Hu3DModelLink(mdl);
        }
        func_8001C258_main(D_8010C4EC_the_beat_goes_on[i], 4, 4);
    }
    obj = omAddObj(1, 0, 0, -1, func_8010B17C_the_beat_goes_on);
    D_8010C4E4_the_beat_goes_on = obj;
    omSetStatBit(obj, 0xA0);
    D_8010C4EA_the_beat_goes_on = (u32)(rand8() * 3) >> 5;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(2, 7, 10, -1, func_80108324_the_beat_goes_on);
    }
    for (i = 0; i < 5; i++) {
        omSetStatBit(omAddObj(3, 4, 2, -1, func_80106708_the_beat_goes_on), 0xA0);
    }
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    WipeCreateIn(0xFF, 16);
}

void func_80105C68_the_beat_goes_on(BgCtrl* ctrl) {
    s32 i;

    ctrl->unk00 = 0;
    ctrl->unk01 = 0;
    ctrl->unk02 = 2;
    ctrl->unk03 = 0;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 0;
    ctrl->unk1C = 64;
    ctrl->unk1E = -1;
    ctrl->unk20 = 0;
    ctrl->unk22 = -1;
    ctrl->unk24 = 150;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

void func_80105CDC_the_beat_goes_on(void) {
    f32 zero;
    s32 cam;

    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 140.0f;
    CRot.x = -40.0f;
    zero = Center.x;
    CRot.z = zero;
    CRot.y = zero;
    CZoom = 1060.0f;
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, zero, zero, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 30.0f, 80.0f, 8000.0f);
}

void func_80105E0C_the_beat_goes_on(f32 div) {
    f32 zoom = 1500.0f;
    f32 cz = -500.0f;
    f32 rx = -20.0f;
    Vec pos;
    Vec2f scr;

    CZoom += zoom / div;
    if (CZoom > 2200.0f) {
        CZoom = 2200.0f;
    }
    Center.z += cz / div;
    if (Center.z < 380.0f) {
        Center.z = 380.0f;
    }
    CRot.x += rx / div;
    if (CRot.x < -30.0f) {
        CRot.x = -30.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &scr);
    func_80054904_main(D_8010C4F4_the_beat_goes_on, 0, 160, scr.y + -50.0f);
}

void func_80105F60_the_beat_goes_on(f32 div) {
    f32 zoom = -1500.0f;
    f32 cz = 500.0f;
    f32 rx = 20.0f;
    Vec pos;
    Vec2f scr;

    CZoom += zoom / div;
    if (CZoom < 700.0f) {
        CZoom = 700.0f;
    }
    Center.z += cz / div;
    if (Center.z > 880.0f) {
        Center.z = 880.0f;
    }
    CRot.x += rx / div;
    if (CRot.x > -10.0f) {
        CRot.x = -10.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &scr);
    func_80054904_main(D_8010C4F4_the_beat_goes_on, 0, 160, scr.y + -50.0f);
}

void func_801060B0_the_beat_goes_on(f32 div) {
    f32 zoom = 1140.0f;
    f32 cz = 240.0f;
    f32 rx = 10.0f;
    Vec pos;
    Vec2f scr;

    CZoom += zoom / div;
    if (CZoom > 2200.0f) {
        CZoom = 2200.0f;
    }
    Center.z += cz / div;
    if (Center.z > 380.0f) {
        Center.z = 380.0f;
    }
    CRot.x += rx / div;
    if (CRot.x > -30.0f) {
        CRot.x = -30.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &scr);
    func_80054904_main(D_8010C4F4_the_beat_goes_on, 0, 160, scr.y + -50.0f);
}

void func_80106204_the_beat_goes_on(f32 div) {
    f32 zoom = -1140.0f;
    f32 cz = -240.0f;
    f32 rx = -10.0f;
    Vec pos;
    Vec2f scr;

    CZoom += zoom / div;
    if (CZoom < 1060.0f) {
        CZoom = 1060.0f;
    }
    Center.z += cz / div;
    if (Center.z < 140.0f) {
        Center.z = 140.0f;
    }
    CRot.x += rx / div;
    if (CRot.x < -40.0f) {
        CRot.x = -40.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &scr);
    func_80054904_main(D_8010C4F4_the_beat_goes_on, 0, 160, scr.y + -50.0f);
}

void func_80106358_the_beat_goes_on(omObjData* obj) {
    omObjData* pl;
    s32 i;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010C2EC_the_beat_goes_on == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010C2EC_the_beat_goes_on = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                if (func_800E6E9C_minigame() == 16) {
                    HuAudSeqPlay(0x3F);
                    HuAudFXPlay(0x40B);
                } else if (func_800E6E9C_minigame() >= 27) {
                    func_801060B0_the_beat_goes_on(40.0f);
                }
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                if (D_8010C2E8_the_beat_goes_on == 0) {
                    func_8004AB0C_main(30);
                    if (D_8010C478_the_beat_goes_on.unk06 == 0) {
                        pl = D_800EC598_minigame[D_8010C478_the_beat_goes_on.unk18[0]];
                        func_8001C258_main(pl->model[3], 4, 4);
                        func_8001C258_main(pl->model[4], 4, 4);
                        func_8001C258_main(pl->model[5], 4, 4);
                    }
                } else if (D_8010C2E8_the_beat_goes_on == 30) {
                    if (D_8010C478_the_beat_goes_on.unk06 == 4) {
                        for (i = 0; i < 4; i++) {
                            pl = D_800EC598_minigame[i];
                            if (pl->work[0] == 10) {
                                func_8001C258_main(pl->model[6], 4, 4);
                            } else {
                                func_800E4C88_minigame(pl, 6, pl->trans.x, -50.0f, pl->trans.z + 50.0f, 45.0f, 0.0f);
                                func_8001C258_main(pl->model[3], 4, 4);
                                func_8001C258_main(pl->model[4], 4, 4);
                                func_8001C258_main(pl->model[5], 4, 4);
                            }
                        }
                    }
                }
                D_8010C2E8_the_beat_goes_on++;
                break;
            case 4:
                if (func_800E6E9C_minigame() == 1) {
                    switch (D_8010C478_the_beat_goes_on.unk06) {
                        case 0:
                            GMesCreate(0x16, GwPlayer[D_8010C478_the_beat_goes_on.unk18[0]].chr);
                            HuAudSeqPlay(0x65);
                            break;
                        case 4:
                            GMesCreate(0x20);
                            HuAudSeqPlay(0x6C);
                            break;
                    }
                    D_8010C478_the_beat_goes_on.unk06 = 9;
                }
                break;
            case 5:
                if (D_8010C2E4_the_beat_goes_on == 0) {
                    WipeCreateOut(0, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010C2E4_the_beat_goes_on++;
                break;
        }
    }
}

#ifdef NON_MATCHING
/* masked 37: the sprite id ternaries convert to s16 in each branch (retail: once at the join) */
void func_80106708_the_beat_goes_on(omObjData* obj) {
    BgDrum* w;
    s16 id;
    s16 mdl;

    obj->data = HuMemAllocTag(sizeof(BgDrum), 0x7918);
    memset(obj->data, 0, sizeof(BgDrum));
    w = obj->data;
    w->unk1C = D_8010C466_the_beat_goes_on;
    if (w->unk1C == 4) {
        w->unk10 = 0;
    } else {
        if (w->unk1C == 0) {
            w->unk10 = 20;
        } else {
            w->unk10 = rand8() % 20;
        }
    }
    w->unk14 = 0;
    obj->scale.z = 3.0f;
    obj->scale.y = 3.0f;
    obj->scale.x = 3.0f;
    id = (D_8010C466_the_beat_goes_on == 0) ? (D_8010C462_the_beat_goes_on = SprModelRead(0x410001, 0, 16))
                                             : func_80014618_main(D_8010C462_the_beat_goes_on, 16);
    func_80014714_main(id, D_8010C466_the_beat_goes_on & 7);
    w->unk18 = &D_800CBB60_main[id];
    obj->model[1] = w->unk18->unk00;
    obj->trans.x = sindf(D_8010C466_the_beat_goes_on * 45.0f - 90.0f) * 160.0f;
    obj->trans.y = 40.0f;
    obj->trans.z = cosdf(D_8010C466_the_beat_goes_on * 45.0f - 90.0f) * 160.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    id = (D_8010C466_the_beat_goes_on == 0) ? (D_8010C460_the_beat_goes_on = SprModelRead(0x410000, 0, 16))
                                             : func_80014618_main(D_8010C460_the_beat_goes_on, 16);
    obj->model[0] = D_800CBB60_main[id].unk00;
    func_8001C258_main(obj->model[0], 4, 4);
    id = (D_8010C466_the_beat_goes_on == 0) ? (D_8010C464_the_beat_goes_on = SprModelRead(0x410002, 0, 16))
                                             : func_80014618_main(D_8010C464_the_beat_goes_on, 16);
    obj->model[2] = D_800CBB60_main[id].unk00;
    func_8001C258_main(obj->model[2], 4, 4);
    mdl = obj->model[3] = func_8000B108_main(0x410003, 0xAA9);
    if (D_8010C466_the_beat_goes_on == 0) {
        D_8010C468_the_beat_goes_on = HmfAnimRead(HmfModelData[mdl].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        func_80032694_main(HmfModelData[mdl].hmf, D_8010C468_the_beat_goes_on, 0, "c201n_00_DEF");
        func_80032694_main(HmfModelData[obj->model[3]].hmf, D_8010C468_the_beat_goes_on, 0, "c201n_00_DEF");
    }
    func_8001C448_main(mdl);
    func_8001C514_main(mdl);
    Hu3DModelScaleSet(mdl, 0.6f, 0.6f, 0.6f);
    Hu3DModelPosSet(mdl, (D_8010C466_the_beat_goes_on - 4) * 25 * obj->scale.x, 0.0f, 0.0f);
    func_8000B460_main(obj, 0, 0x410003);
    func_8000B460_main(obj, 1, 0x410004);
    obj->func = func_80106E40_the_beat_goes_on;
    D_8010C466_the_beat_goes_on++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106708_the_beat_goes_on);
#endif

#ifdef NON_MATCHING
/* masked 3: one hazard nop after the cosdf(CRot.x) delay slot */
/* Keeps a drum's sprite facing the camera. */
void func_80106BE0_the_beat_goes_on(omObjData* obj) {
    BgDrum* w = obj->data;
    BgSprModel* spr = w->unk18;
    u16 mdl = spr->unk00;
    s32 frame;
    BgSprBankAnim* anim;
    f32 x;
    f32 y;
    f32 px;
    f32 py;
    f32 pz;
    f32 z;

    obj->rot.x = CRot.x;
    obj->rot.y = CRot.y;
    obj->rot.z = CRot.z;
    Hu3DModelRotSet(mdl, obj->rot.x, obj->rot.y, obj->rot.z);
    anim = &D_800D408C_main[spr->unk02].unk_10[spr->unk06];
    frame = anim->unk_04[spr->unk04].unk_00;
    x = D_8010C2F0_the_beat_goes_on[frame][0] - 16;
    y = 16 - D_8010C2F0_the_beat_goes_on[frame][1];
    z = 0.0f;
    px = x * cosdf(CRot.y) + sindf(CRot.y) * z;
    py = y * cosdf(CRot.x) - sindf(CRot.x) * z;
    pz = y * sindf(CRot.x) + sindf(CRot.x) * z - x * sindf(CRot.y) + cosdf(CRot.y) * z;
    px *= obj->scale.x;
    py *= obj->scale.y;
    pz *= obj->scale.z;
    px += obj->trans.x;
    py += obj->trans.y;
    pz += obj->trans.z;
    Hu3DModelPosSet(obj->model[3], px, py, pz);
    w->unk00.x = px;
    w->unk00.y = py;
    w->unk00.z = pz;
    Hu3DModelRotSet(obj->model[3], CRot.x, CRot.y, CRot.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106BE0_the_beat_goes_on);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106E40_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80107504_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010775C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_801080DC_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108198_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108324_the_beat_goes_on);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", D_8010C3B8_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108810_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A5FC_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A88C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A94C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010AD60_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010AF10_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B058_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B0E0_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B17C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B6DC_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010C0F4_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010C14C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010C1A4_the_beat_goes_on);
