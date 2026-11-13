#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfman.h"

/* Minigame player actions: each one first offers the minigame an override hook in the player's
   work block (hook returns 1 = handled), then does the default (MP2 src/B6E0.c). */

typedef func_800E1BA8_minigame_ObjData MgWork;

// EXTERN

f32 func_800202A8_main(f32 angle);
int abs(int);
double fabs(double); /* the GCC builtin (abs.d) */
void func_800DFE44_minigame(omObjData* obj);
void func_800DFF3C_minigame(omObjData* obj, f32 x, f32 y, f32 z);

// LOCAL

extern f32 D_800EB744_minigame; /* jump speed */
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern u8 D_800EB739_minigame;

void func_800E19FC_minigame(MgWork* work, s8 state);
void func_800E23E0_minigame(omObjData* obj);
void func_800E2CA4_minigame(omObjData* obj, f32 arg1);
void func_800E2E98_minigame(omObjData* obj);
f32 func_800E2ED4_minigame(f32 x1, f32 z1, f32 x2, f32 z2);
void func_800E3628_minigame(s16 model, Vec* normal);
void func_800E4C88_minigame(omObjData* obj, s32 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_800E561C_minigame(omObjData* obj, s32 flags);

void func_800E3928_minigame(omObjData* obj, MgWork* work);
void func_800E3EA4_minigame(omObjData* obj, MgWork* work);

void func_800E3820_minigame(omObjData* obj, MgWork* work) {
    if (work->unk50 & 0x40) {
        if (work->unk38 == 1000.0f && (work->unk104[10] == NULL || work->unk104[10](obj) != 1)) {
            func_800E5690_minigame(obj, 0x23);
        }
    } else {
        func_800E3928_minigame(obj, work);
    }
}

void func_800E38A4_minigame(omObjData* obj, MgWork* work) {
    if (work->unk50 & 0x40) {
        if (work->unk38 == 1000.0f && (work->unk104[11] == NULL || work->unk104[11](obj) != 1)) {
            func_800E5690_minigame(obj, 0x24);
        }
    } else {
        func_800E3EA4_minigame(obj, work);
    }
}

/* Jump. */
void func_800E3928_minigame(omObjData* obj, MgWork* work) {
    if (work->unk104[2] == NULL || work->unk104[2](obj) != 1) {
        if (work->unkB0 == 1.0f && func_800E5690_minigame(obj, 6) == 1) {
            work->unk38 = -D_800EB744_minigame;
            work->unk50 &= ~0x80;
            func_800E19FC_minigame(work, 3);
        }
    }
}

void func_800E39CC_minigame(omObjData* obj, MgWork* work, void* arg2, s16 x, s16 y) {
    if (work->unk104[3] == NULL || work->unk104[3](obj, arg2) != 1) {
        if (abs(x) < 8 && abs(y) < 8) {
            work->unk40 = D_800EB770_minigame;
            func_800E5690_minigame(obj, 0x15);
            func_800E19FC_minigame(work, 4);
            func_800E23E0_minigame(obj);
        } else {
            func_800E5690_minigame(obj, 1);
            work->unk40 = D_800EB764_minigame;
            func_800E19FC_minigame(work, 1);
        }
    }
}

void func_800E3AB8_minigame(omObjData* obj, MgWork* work) {
    s32 ret = func_800E5690_minigame(obj, 8);

    if (ret == 1 && (work->unk104[5] == NULL || work->unk104[5](obj) != ret)) {
        work->unk40 = D_800EB770_minigame;
        work->unk38 = -D_800EB744_minigame * 0.1f;
        if (work->unk50 & 0x10) {
            func_800E2CA4_minigame(obj, D_800EB76C_minigame * 0.6f);
        }
        func_800E19FC_minigame(work, 0xA);
    }
}

void func_800E3B98_minigame(omObjData* obj, MgWork* work, void* arg2, f32 x, f32 y, f32 z) {
    if (work->unk104[6] == NULL || work->unk104[6](obj, arg2) != 1) {
        work->unk38 = -D_800EB744_minigame * 0.6f;
        func_800E4C88_minigame(obj, 7, x, y, z, 0.0f, 0.0f);
        func_800E4C88_minigame(obj, 8, x, y, z, 0.0f, 0.0f);
        work->unk50 |= 0x80;
        func_800E19FC_minigame(work, 0xB);
        omVibrate(work->unk59, 0xA, 0, 0xA);
    }
}

void func_800E3CA0_minigame(omObjData* obj, MgWork* work, void* arg2, f32 x, f32 y, f32 z) {
    if (work->unk104[7] == NULL || work->unk104[7](obj, arg2) != 1) {
        func_800E5690_minigame(obj, 0x12);
        func_800E4C88_minigame(obj, 8, x, y, z, 0.0f, 0.0f);
        work->unk50 &= ~0x80;
    }
}

void func_800E3D3C_minigame(omObjData* obj, MgWork* work) {
    if (work->unk104[14] == NULL || work->unk104[14](obj) != 1) {
        if (work->unk50 & 0x10) {
            if (func_800E5690_minigame(obj, 0x14) == 1) {
                work->unk38 = -D_800EB744_minigame * 0.4f;
                func_800E2E98_minigame(obj);
                func_800E19FC_minigame(work, 0xC);
            }
        } else if (func_800E5690_minigame(obj, 7) == 1) {
            work->unk38 = -D_800EB744_minigame * 0.4f;
            func_800E19FC_minigame(work, 6);
        }
    }
}

void func_800E3E24_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgWork* work = obj->data;

    if (work->unk104[15] == NULL || work->unk104[15](obj) != 1) {
        func_800DFF3C_minigame(obj, x, y, z);
    }
}

void func_800E3EA4_minigame(omObjData* obj, MgWork* work) {
    if (work->unk104[8] == NULL || work->unk104[8](obj) != 1) {
        if (work->unk50 & 0x10) {
            if (func_800E5690_minigame(obj, 0x14) == 1) {
                func_800E2E98_minigame(obj);
                func_800E19FC_minigame(work, 0xC);
            }
        } else if (func_800E5690_minigame(obj, 5) == 1) {
            func_800E19FC_minigame(work, 5);
        }
    }
}

void func_800E3F44_minigame(omObjData* obj, s32 flags, f32 x, f32 y, f32 z) {
    MgWork* work = obj->data;

    if (work->unk104[9] == NULL || work->unk104[9](obj) != 1) {
        if (flags & 0x80) {
            func_800DFE44_minigame(obj);
        } else {
            func_800DFF3C_minigame(obj, x, y, z);
        }
    }
}

/* Punch: during motion frames 30-50, knocks down every other player within reach. */
void func_800E3FD8_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgWork* work = obj->data;
    omObjData* other;
    MgWork* otherWork;
    f32 time;
    f32 dx, dy, dz;
    s32 i;

    if (work->unk104[12] == NULL || work->unk104[12](obj, &x, &y, &z) != 1) {
        HmfModelData[obj->model[0]].unk06 = 0xFF;
        time = func_8001C7D0_main(obj->model[0]);
        if (time == -1.0f) {
            time = HmfModelData[obj->model[0]].unk40;
        }
        if ((time >= 30.0f) & (time <= 50.0f)) {
            x += sindf(work->unk3C) * (work->unk6C + work->unk48);
            z += cosdf(work->unk3C) * (work->unk6C + work->unk48);
            for (i = 0; i < D_800EC280_minigame; i++) {
                other = D_800EC598_minigame[i];
                otherWork = other->data;
                if (work != otherWork) {
                    dx = other->trans.x - x;
                    dy = other->trans.y - y;
                    dz = other->trans.z - z;
                    if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherWork->unk48 + work->unk70) {
                        func_800E561C_minigame(other, 1);
                        func_800E5690_minigame(other, 0);
                        func_800E4C88_minigame(obj, 7, x, y, z, 0.0f, 0.0f);
                    }
                }
            }
        }
    }
}

/* Sweep: during motion frames 10-25, the reach turns with the motion and pushes back every
   other player within it. */
void func_800E4248_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgWork* work = obj->data;
    omObjData* other;
    MgWork* otherWork;
    f32 time;
    f32 angle;
    f32 dx, dy, dz;
    s32 i;

    if (work->unk104[13] == NULL || work->unk104[13](obj, &x, &y, &z) != 1) {
        HmfModelData[obj->model[0]].unk06 = 0xFF;
        time = func_8001C7D0_main(obj->model[0]);
        if (time == -1.0f) {
            time = HmfModelData[obj->model[0]].unk40;
        }
        if ((time >= 10.0f) & (time <= 25.0f)) {
            angle = (work->unk3C - 90.0f) + (time - 10.0f) * 12.0f;
            x += sindf(angle) * (work->unk6C + work->unk48);
            z += cosdf(angle) * (work->unk6C + work->unk48);
            for (i = 0; i < D_800EC280_minigame; i++) {
                other = D_800EC598_minigame[i];
                otherWork = other->data;
                if (work != otherWork) {
                    dx = other->trans.x - x;
                    dy = other->trans.y - y;
                    dz = other->trans.z - z;
                    if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherWork->unk48 + work->unk70) {
                        func_800E5690_minigame(other, 0x25);
                        otherWork->unk40 = 2.0f * D_800EB760_minigame;
                        otherWork->unk3C = func_800202A8_main(atan2df(dx, dz) + 90.0f);
                        otherWork->unkC0 = 90;
                    }
                }
            }
        }
    }
}

s32 func_800E4510_minigame(omObjData* obj) {
    MgWork* work = obj->data;

    if (work->unk104[16] == NULL || work->unk104[16](obj) != 1) {
        return 1;
    }
    return 0;
}

/* obj hits other (dx, dz: the hit direction): other is knocked back, away from or along obj's
   facing depending on which side it was hit from. */
void func_800E454C_minigame(omObjData* obj, omObjData* other, f32 dx, f32 dz, u16 arg4) {
    MgWork* work = obj->data;
    MgWork* otherWork = other->data;
    f32 side;

    if (work->unk104[17] == NULL || work->unk104[17](obj) != 1) {
        if (!(otherWork->unk50 & 0x200)) {
            side = func_800E2ED4_minigame(sindf(otherWork->unk3C), cosdf(otherWork->unk3C), dx, dz);
            if (otherWork->unk50 & 0x10) {
                func_800E2CA4_minigame(other, D_800EB768_minigame);
            }
            if (side < 0.0f) {
                func_800E5690_minigame(other, 0x1E);
                if (otherWork->unk38 == 1000.0f) {
                    otherWork->unk40 = -D_800EB760_minigame;
                } else {
                    otherWork->unk40 = -D_800EB760_minigame;
                    otherWork->unk38 = -D_800EB744_minigame * 0.6f;
                }
                otherWork->unk3C = func_800202A8_main(work->unk3C + 180.0f);
            } else {
                func_800E5690_minigame(other, 0x1F);
                if (otherWork->unk38 == 1000.0f) {
                    otherWork->unk40 = D_800EB760_minigame;
                } else {
                    otherWork->unk40 = D_800EB760_minigame;
                    otherWork->unk38 = -D_800EB744_minigame * 0.6f;
                }
                otherWork->unk3C = work->unk3C;
            }
            func_800E4C88_minigame(obj, 6, other->trans.x, other->trans.y, other->trans.z, 0.0f,
                                   atan2df(dx, dz) + 180.0f);
            func_800E19FC_minigame(work, 8);
            omVibrate(work->unk59, 2, 3, 0xA);
            omVibrate(otherWork->unk59, 0x14, 0, 0x14);
        }
        work->unk54 = arg4;
        otherWork->unkC3 = work->unk59;
    }
}

/* Landing on ground at height `ground`. */
void func_800E47D8_minigame(omObjData* obj, f32 ground) {
    MgWork* work = obj->data;

    if (work->unk104[4] == NULL || work->unk104[4](obj, &ground) != 1) {
        if (work->unk38 == 1000.0f) {
            work->unkB0 = (work->unk8C - ground) / work->unk34;
        } else if (work->unk38 < 0.0f) {
            work->unk38 = D_800EB744_minigame * 0.1f;
        }
    }
}

/* The player's shadow (model 1): on the ground below (x, y, z), shrinking with the height, and
   flattened onto the ground's plane; hidden when there is no ground (-65536.0f). */
void func_800E4890_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 ground, Vec* normal) {
    MgWork* work = obj->data;
    f32 scale;

    if (work->unk104[18] == NULL || work->unk104[18](obj, &x, &y, &z, &ground, normal) != 1) {
        if (ground != -65536.0f) {
            if (y != ground) {
                if (D_800EB739_minigame == 1) {
                    ground += 2.0f;
                }
                Hu3DModelPosSet(obj->model[1], x, ground, z);
                ground = y - ground;
                if (ground > 200.0f) {
                    scale = 0.6f;
                } else {
                    scale = 1.0 - fabs(ground) / 500.0;
                }
                Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
            } else {
                if (D_800EB739_minigame == 1) {
                    ground += 2.0f;
                }
                Hu3DModelPosSet(obj->model[1], x, ground, z);
            }
            func_800E3628_minigame(obj->model[1], normal);
            func_8001C258_main(obj->model[1], 4, 0);
        } else {
            func_8001C258_main(obj->model[1], 4, 4);
        }
    }
}
