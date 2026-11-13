#include "overlays/minigame.h"
#include "game/data.h"
#include "game/hmfman.h"
#include "game/gamework_data.h"
#include "include_asm.h"

typedef func_800E1BA8_minigame_ObjData MgWork;
typedef func_800E1BA8_minigame_UnkE8_ObjData MgMotion;

extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
/* D_800CCF58_main's entries (common_structs.h's D_800CCF58_main_Struct, which this unit cannot
   include: it pulls in functions.us.h's u8 func_80017AD8_main). */
typedef struct {
    /* 0x00 */ char unk00[2];
    /* 0x02 */ s16 unk02; /* end frame */
    /* 0x04 */ char unk04[0x14];
} MgMotionInfo; // Size 0x18

extern MgMotionInfo* D_800CCF58_main; /* per motion */
extern s32 D_800EB820_minigame[][7]; /* per character: motion keys */
extern u16 D_800EC288_minigame; /* while set, blinking does not stop */

s16 func_8000B13C_main(s32 file);
s16 func_80017AD8_main(s32 id); /* 14EA0.c; functions.us.h (not included here) says u8 */
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2); /* hmfman.c defines (s16, u8, s8) */
f32 func_8001F358_main(s16 arg0);
void func_8001F038_main(void* model, u16 arg1); /* HmfModelM* (hmfman.c) */
void func_80017954_main(s16, s16, s16, s16);

void func_800E4BA4_minigame(u8 mdl);
void func_800E4C2C_minigame(omObjData* obj);
void func_800E4D9C_minigame(omObjData* obj);
void func_800E561C_minigame(omObjData* obj, u8 flags);
void func_800E5638_minigame(MgMotionReq* req, u16 flags, u16 motion, u16 speed, s16 arg4);
s32 func_800E567C_minigame(MgWork* w, u16 motion);
s32 func_800E5798_minigame(omObjData* obj, u16 motion);
void func_800E58F8_minigame(omObjData* obj, s32 a, s32 b);
s16 func_800E5A98_minigame(omObjData* obj, s32 id);

/* The requested motion (its slot). */
u16 func_800E4A80_minigame(omObjData* obj) {
    return ((MgWork*)obj->data)->unkD8.motion & 0x3FFF;
}

/* The current motion's class as a flag (1 when idle), also kept in unk5C. */
s32 func_800E4A90_minigame(omObjData* obj) {
    MgWork* w = obj->data;
    s32 flags;
    u16 mot;

    if (w->unkD0 == 0xFFFF) {
        return 1;
    } else {
        switch (mot = func_800E4A80_minigame(obj)) {
            case 0:
            case 11:
            case 24:
                flags = 2;
                break;
            case 16:
                flags = 0x20000;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                flags = 4;
                break;
            case 25:
            case 27:
                flags = 8;
                break;
            case 26:
                flags = 0x10;
                break;
            case 6:
                flags = 0x20;
                break;
            case 20:
                flags = 0x80;
                break;
            case 5:
                flags = 0x40;
                break;
            case 7:
                flags = 0x100;
                break;
            case 8:
                flags = 0x200;
                break;
            case 21:
                flags = 0x10000;
                break;
            case 18:
            case 19:
            case 28:
            case 30:
            case 31:
            case 33:
            case 34:
                flags = 0x8000;
                break;
            case 9:
            case 12:
            case 29:
                flags = 0x400;
                break;
            case 10:
            case 23:
                flags = 0x800;
                break;
            case 13:
            case 14:
            case 15:
                flags = 0x1000;
                break;
            case 17:
                flags = 0x2000;
                break;
            case 32:
                flags = 0x4000;
                break;
            case 35:
                flags = 0x40000;
                break;
            case 36:
                flags = 0x80000;
                break;
            case 37:
                flags = 0x100000;
                break;
            default:
                /* motion 22 gives 0; any motion past 37 gives 0x200000 */
                flags = (mot >= 38) ? 0x200000 : 0;
                break;
        }
        w->unk5C = flags;
    }
    return flags;
}

/* Hides model mdl once its motion has played to the end. */
void func_800E4BA4_minigame(u8 mdl) {
    f32 cur;

    if (mdl != 0) {
        cur = HmfModelData[mdl].unk40;
        if (D_800CCF58_main[HmfModelData[mdl].unk02].unk02 <= cur) {
            func_8001C258_main(mdl, 4, 4);
        }
    }
}

/* Effect models 3-8. */
void func_800E4C2C_minigame(omObjData* obj) {
    s32 i;

    i = 3;
loop:
    if (i < obj->mdlcnt) {
        func_800E4BA4_minigame(obj->model[i++]);
        if (i < 9) {
            goto loop;
        }
    }
}

/* Shows effect model idx at (x, y, z) turned by (a, b), restarting its motion once it ended. */
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b) {
    u8 mdl = obj->model[idx];
    f32 cur;

    if (obj->mdlcnt > idx) {
        if (mdl != 0) {
            cur = HmfModelData[mdl].unk40;
            if (D_800CCF58_main[HmfModelData[mdl].unk02].unk02 <= cur) {
                if (HmfModelData[mdl].hmf->unk98 != NULL) {
                    HmfModelData[mdl].hmf->unk98->unk08 = 0;
                }
                func_8001C6A8_main(mdl, 0.0f);
            }
            func_8001C258_main(mdl, 4, 0);
            Hu3DModelPosSet(mdl, x, y, z);
            Hu3DModelRotSet(mdl, a, b, 0.0f);
        }
    }
}
// NON_MATCHING: register allocation (masked 13), as MP2 func_800192E4_19EE4: retail keeps obj in a3,
// the motion table in a0 and a copy of flip in a1 for the second arm. Tried s16/u16/u8 flip.
#ifdef NON_MATCHING
/* Shows motion 22 (flipped with the request's flag 1). */
void func_800E4D9C_minigame(omObjData* obj) {
    MgWork* w = obj->data;
    s16* motion = obj->motion;
    s32 flip = (w->unkD8.flags & 1) * 2;

    if (w->unkE8[22].unk00 & 4) {
        func_8001EED8_main(obj->model[0], motion[22] & 0x3FFF, flip);
    } else {
        func_8001EED8_main(obj->model[0], HmfModelData[obj->motion[22] & 0x3FFF].unk02, flip);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E4D9C_minigame);
#endif

/* Starts the pending motion request, or steps the current motion once it reached its end. */
void func_800E4E30_minigame(omObjData* obj) {
    u16 mdl = obj->model[0];
    MgWork* w = obj->data;
    MgMotionReq* req;
    s16 mot;
    s16 flip;
    f32 t;
    u16 spd;
    s32 chr;
    MgMotion* e;

    if (w->unkD6 != 0) {
        chr = GwPlayer[w->unk59].chr;
        flip = 0;
        if (w->unkD2 != 0) {
            req = &w->unkD8;
            if (req->flags & 4) {
                mot = obj->motion[req->motion] & 0x3FFF;
                spd = (w->unkB8 = func_8001F358_main(mot)) / 5.0f;
            } else {
                mot = HmfModelData[obj->motion[req->motion] & 0x3FFF].unk02;
                spd = (w->unkB8 = D_800CCF58_main[HmfModelData[obj->motion[req->motion] & 0x3FFF].unk02].unk02) / 5.0f;
            }
            if (req->flags & 1) {
                flip = 2;
            }
            if (req->unk06 >= 0) {
                func_80017954_main(w->unk5A, w->unk5B, chr, req->unk06);
            }
            func_8001C624_main(mdl, mot, 0, spd, flip);
            HmfModelData[mdl].unk54 = req->speed;
            if (w->unk50 & 0x100) {
                func_800E4D9C_minigame(obj);
            }
        }
        w->unkD6 = 0;
    } else {
        e = &w->unkE8[func_800E4A80_minigame(obj)];
        if (!(e->unk00 & 1)) {
            t = func_8001C7D0_main(mdl);
            if (t == -1.0f) {
                t = HmfModelData[mdl].unk40;
            }
            if (w->unkB8 <= t) {
                w->unkD0++;
                if (w->unkD2 <= w->unkD0) {
                    w->unkD2 = 0;
                    w->unkD0 = 0xFFFF;
                }
            }
        }
    }
}

/* Squash/stretch (flags 1, 2, 4), the idle stretch, and blinking. */
void func_800E5138_minigame(omObjData* obj) {
    MgWork* w = obj->data;
    u16 lim1;
    u16 lim2;
    f32 sy;
    f32 sxz;
    f32 t;
    s32 off;
    u16 prev;

    if (w->unk50 & 7) {
        w->unkA8.timer += 2;
        lim1 = 60;
        if (w->unk50 & 2) {
            lim2 = 106;
            sy = 0.6f;
            sxz = w->unkAC * 1.4f;
        } else {
            lim1 = 120;
            lim2 = 166;
            sy = 0.1f;
            sxz = w->unkAC * 1.6f;
            if (w->unkA8.timer >= 120) {
                if (w->unk50 & 1) {
                    w->unk50 = (w->unk50 & ~1) | 4;
                }
            }
        }
        if (w->unkA8.timer < lim2) {
            if (w->unkA8.timer <= lim1) {
                obj->scale.x = (obj->scale.z = sxz);
                obj->scale.y = sy;
            } else if (w->unkA8.timer <= (lim1 + 10)) {
                t = w->unkA8.timer - lim1;
                obj->scale.y = (t * 0.05f) + 0.2;
                obj->scale.z = (obj->scale.x = 1.8 - (t * 0.08f));
            } else if (w->unkA8.timer <= (lim1 + 20)) {
                t = w->unkA8.timer - (lim1 + 10);
                obj->scale.y = 0.9 - (t * 0.05f);
                obj->scale.z = (obj->scale.x = (t * 0.05f) + 1.0);
            } else if (w->unkA8.timer <= (lim1 + 30)) {
                t = w->unkA8.timer - (lim1 + 20);
                obj->scale.y = (t * 0.05f) + 0.7;
                obj->scale.z = (obj->scale.x = 1.4 - (t * 0.04f));
            } else if (w->unkA8.timer <= (lim1 + 38)) {
                t = w->unkA8.timer - (lim1 + 30);
                obj->scale.y = 1.3 - (t * 0.1f);
                obj->scale.z = (obj->scale.x = (t * 0.02f) + 1.0);
            } else {
                t = w->unkA8.timer - (lim1 + 38);
                obj->scale.y = (t * 0.1f) + 0.3;
                obj->scale.z = (obj->scale.x = 1.1 - (t * 0.01f));
            }
        } else {
            obj->scale.x = (obj->scale.y = (obj->scale.z = 1.0f));
            w->unk50 &= ~7;
            w->unkA8.timer = 0;
        }
    } else if (w->unk8C != 65536.0f) {
        if (w->unk38 == 1000.0f) {
            if (obj->scale.y <= 0.5f) {
                func_800E561C_minigame(obj, 1);
            } else {
                obj->scale.y = w->unkB0;
                obj->scale.x = (obj->scale.z = (1.0f - w->unkB0) * 2.0f + 1.0f);
            }
        }
    } else {
        obj->scale.x = (obj->scale.y = (obj->scale.z = 1.0f));
        w->unkB0 = 1.0f;
    }
    if (w->unkBE != 0) {
        prev = w->unkBE;
        w->unkBE--;
        if (w->unkBE == 0) {
            if (D_800EC288_minigame != 0) {
                w->unkBE = prev;
            } else {
                w->unkC2 = 1;
            }
        }
        prev = ((w->unkC2 & 1) == 0) * 4;
        func_8001C258_main(obj->model[0], 4, off = prev);
        if (off != 0) {
            func_8001F038_main(&HmfModelData[obj->model[0]], 2);
        }
        w->unkC2 = (w->unkC2 + 1) & 3;
    }
    func_800E4C2C_minigame(obj);
}

void func_800E561C_minigame(omObjData* obj, u8 flags) {
    MgWork* w = obj->data;

    w->unk50 |= flags;
    w->unkA8.timer = 0;
}

void func_800E5638_minigame(MgMotionReq* req, u16 flags, u16 motion, u16 speed, s16 arg4) {
    req->flags = flags;
    req->motion = motion;
    req->unk08 = 0;
    req->speed = speed;
    req->unk06 = arg4;
}

s32 func_800E5664_minigame(omObjData* obj, u16 motion) {
    return ((MgWork*)obj->data)->unkD8.motion == motion;
}

s32 func_800E567C_minigame(MgWork* w, u16 motion) {
    return w->unkD8.motion == motion;
}

/* Starts `motion` unless the current one may not be interrupted; 1 if started. */
s32 func_800E5690_minigame(omObjData* obj, u16 motion) {
    MgWork* w = obj->data;
    MgMotion* e;
    s32 flags;
    s32 speed;
    u16 unk04;

    if (w->unk52 == 0) {
        /* MP1's and MP2's shape: both arms are the same */
        if (obj || obj->data) {
            e = &w->unkE8[func_800E4A80_minigame(obj)];
        } else {
            e = &w->unkE8[func_800E4A80_minigame(obj)];
        }
        if (w->unkD0 == 0xFFFF || (!(e->unk00 & 2) && !func_800E567C_minigame(w, motion))) {
            e = &w->unkE8[motion];
            if ((u16)obj->motion[motion] != 0xFFFF) {
                flags = e->unk00;
                speed = e->unk02;
                unk04 = e->unk04;
                w->unkD0 = 0;
                w->unkD2 = 1;
                func_800E5638_minigame(&w->unkD8, flags, motion, speed, unk04);
                w->unkD6 = 1;
                return 1;
            }
        }
    }
    return 0;
}

/* Starts `motion` unconditionally (unless locked or absent). */
s32 func_800E5798_minigame(omObjData* obj, u16 motion) {
    MgWork* w = obj->data;
    MgMotion* e;
    s32 flags;
    s32 speed;
    u16 unk04;

    if (w->unk52 != 0 || (e = &w->unkE8[motion], (u16)obj->motion[motion] == 0xFFFF)) {
        return 0;
    }
    flags = e->unk00;
    speed = e->unk02;
    unk04 = e->unk04;
    w->unkD0 = 0;
    w->unkD2 = 1;
    func_800E5638_minigame(&w->unkD8, flags, motion, speed, unk04);
    w->unkD6 = 1;
    return 1;
}

/* Starts `motion`, then `next` from motion slot 22. */
s32 func_800E5848_minigame(omObjData* obj, u16 motion, u16 next) {
    MgWork* w = obj->data;

    if (func_800E5798_minigame(obj, motion) == 1) {
        func_800E58F8_minigame(obj, 22, next);
        w->unk50 |= 0x100;
        return 1;
    }
    return 0;
}

void func_800E58B4_minigame(omObjData* obj, s32 src, s32 dst) {
    obj->motion[dst] = obj->motion[src];
}

void func_800E58D4_minigame(omObjData* obj, s32 idx, u16 flags, u16 speed) {
    MgWork* w = obj->data;
    MgMotion* e = &w->unkE8[idx];

    e->unk00 = flags;
    e->unk02 = speed;
}

/* Swaps motion slots a and b with their table entries. */
void func_800E58F8_minigame(omObjData* obj, s32 a, s32 b) {
    MgWork* w = obj->data;
    s32 tmp;
    MgMotion* ea;
    MgMotion* eb;
    u16 flags;
    u16 speed;
    u16 unk04;

    tmp = obj->motion[a];
    obj->motion[a] = obj->motion[b];
    obj->motion[b] = tmp;
    ea = &w->unkE8[a];
    eb = &w->unkE8[b];
    speed = ea->unk02;
    flags = ea->unk00;
    unk04 = ea->unk04;
    ea->unk02 = eb->unk02;
    ea->unk00 = eb->unk00;
    ea->unk04 = eb->unk04;
    eb->unk02 = speed;
    eb->unk00 = flags;
    eb->unk04 = unk04;
}

/* Loads motion file `file` into slot idx. */
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed) {
    s16 mot;
    MgWork* w;
    MgMotion* e;

    mot = func_8000B13C_main(file);
    if (mot >= 0) {
        w = obj->data;
        obj->motion[idx] = mot;
        e = &w->unkE8[idx];
        e->unk00 = flags;
        e->unk02 = speed;
    }
}

void func_800E5A00_minigame(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4) {
    func_800E1BA8_minigame_ObjData *temp_a1;
    func_800E1BA8_minigame_UnkE8_ObjData *temp_v0_2;
    s16 temp_v0;

    temp_v0 = func_8001F1FC_main(DataRead(arg2), 0x18);
    if (temp_v0 < 0) {
        return;
    }
    temp_a1 = (func_800E1BA8_minigame_ObjData *)arg0->data;
    arg0->motion[arg1] = temp_v0;
    temp_v0_2 = &temp_a1->unkE8[arg1];
    temp_v0_2->unk00 = arg3 | 4;
    temp_v0_2->unk02 = arg4;
}

/* The motion already loaded for key `id`, else func_80017AD8_main(id). */
s16 func_800E5A98_minigame(omObjData* obj, s32 id) {
    MgWork* w = obj->data;
    s32 i;

    for (i = 0; i < obj->mtncnt; i++) {
        if (w->unkE8[i].unk08 == id) {
            return w->unkE8[i].unk04;
        }
    }
    return func_80017AD8_main(id);
}

/* func_800E5C18_minigame's twin for a motion loaded through func_8000B13C_main. */
void func_800E5B08_minigame(omObjData* obj, u16 slot, s32 file, u16 flags, u16 speed, s32 arg5) {
    s16 mot = func_8000B13C_main(file);
    MgWork* w;
    MgMotion* e;
    s32 chr;
    s32 key;

    if (mot >= 0) {
        w = obj->data;
        obj->motion[slot] = mot;
        e = &w->unkE8[slot];
        e->unk00 = flags;
        e->unk02 = speed;
        chr = GwPlayer[w->unk59].chr;
        key = D_800EB820_minigame[chr][(s16)arg5] | D_800A178C_main[chr][0];
        e->unk04 = func_800E5A98_minigame(obj, key);
        e->unk08 = key;
    }
}

/* Loads motion file `file` into slot `slot` with the character's motion key (D_800EB820_minigame). */
void func_800E5C18_minigame(omObjData* obj, u16 slot, s32 file, s32 flags, u16 speed, s32 arg5) {
    s16 mot = func_8001F1FC_main(DataRead(file), 0x18);
    MgWork* w;
    MgMotion* e;
    s32 chr;
    s32 key;

    if (mot >= 0) {
        w = obj->data;
        obj->motion[slot] = mot;
        e = &w->unkE8[slot];
        e->unk00 = flags | 4;
        e->unk02 = speed;
        chr = GwPlayer[w->unk59].chr;
        key = D_800EB820_minigame[chr][(s16)arg5] | D_800A178C_main[chr][0];
        e->unk04 = func_800E5A98_minigame(obj, key);
        e->unk08 = key;
    }
}
