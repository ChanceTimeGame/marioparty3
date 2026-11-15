#include "common.h"
#include "ovl_81.h"

// duel n1: Duel Mode's copy of ovl_80 EAB00 (choice menu) and EC3B0 (vector helpers)
f32 atan2df(f32, f32);
void HuVecNormalize3F(Vec *);
f32 acosdf(f32);
f32 HuVecDot3F(Vec *, Vec *);

UnkBoard2 *func_800D6B70_name_81(s32 arg0);
UnkEA790Struct *func_800D6C6C_name_81(void);
void func_800D6D2C_name_81(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2);
UnkBoard2 *func_800D6EC8_name_81(UnkEA790Struct *arg0, s16 arg1);
s16 func_800EBA50_name_81(s16 arg0, f32 arg1);
void func_800EB708_name_81(Vec *arg0, Vec *arg1, Vec *arg2);
SpaceData *MBDMasuGet(s16 arg0);
s32 func_800D7250_name_81(UnkEA790Struct *arg0, s32 arg1);
f32 func_800D7CEC_name_81(Vec *vec_1, Vec *vec_2);
void func_800D7568_name_81(UnkBoard2 *arg0, Vec *arg1, Vec *arg2, f32 arg3);

void func_800D6EE0_name_81(void) {
    s32 mesg;
    s32 ret;
    UnkEA790Struct *work;
    Vec *scale;
    f32 scaleX;
    f32 scaleZ;
    f32 speed;
    f32 angle;
    s16 timer;
    s16 sel;
    s16 delay;
    s32 i;

    timer = -1;
    work = HuPrcCurrentGet()->user_data;
    sel = work->unk_0C;
    angle = 0.0f;
    delay = 0;

    while (timer != 0) {
        HuPrcVSleep();

        if (timer < 0) {
            if (delay == 0) {
                ret = osRecvMesg(&work->unk10, (OSMesg *)&mesg, 0);
                if (ret == -1) {
                    mesg = ret;
                }
                if (work->unk_00 & 1) {
                    delay = 8;
                }
            } else {
                mesg = -1;
                delay--;
            }

            switch (mesg) {
            case -1:
                break;
            case -2:
                work->unk_0C++;
                if (work->unk_0C >= work->unk_02) {
                    work->unk_0C = 0;
                }
                break;
            case -3:
                work->unk_0C--;
                if (work->unk_0C < 0) {
                    work->unk_0C = work->unk_02 - 1;
                }
                break;
            case -4:
                if (work->unk_0C >= 0) {
                    HuAudFXPlay(3);
                    mbCameraBtnF = 0;
                    D_800D51F8_main = 0;
                    timer = 30;
                }
                break;
            case -5:
                HuAudFXPlay(4);
                work->unk_0C = -1;
                timer = 0;
                break;
            case -6:
                work->unk_0C = -1;
                break;
            default:
                if (mesg < work->unk_02) {
                    work->unk_0C = mesg;
                }
                break;
            }

            if (sel != work->unk_0C) {
                HuAudFXPlay(1);
                if (sel >= 0) {
                    HuVecCopyXYZ(&func_800D6EC8_name_81(work, sel)->obj->scale, 1.0f, 1.0f, 1.0f);
                    angle = 0.0f;
                }
                sel = work->unk_0C;
            }
        }

        if (sel >= 0) {
            f32 temp;
            if (timer >= 0) {
                speed = 50.0f;
            } else {
                speed = 25.0f;
            }
            angle += speed;
            temp = 360.0f;
            if (angle > temp) {
                angle -= temp;
            }
            scaleZ = (cosdf(angle) * 0.3f) + 1.2f;
            scaleX = (cosdf(angle) * 0.2f) + 1.2f;
            HuVecCopyXYZ(&func_800D6EC8_name_81(work, sel)->obj->scale, scaleX, 1.0f, scaleZ);
        }

        if (timer > 0) {
            timer--;
            scaleZ = timer * (1.0f / 30.0f);
            for (i = 0; i < work->unk_02; i++) {
                if (i != sel) {
                    scale = &func_800D6EC8_name_81(work, i)->obj->scale;
                    HuVecMulScalar(scale, scaleZ, scale);
                }
            }
        }
    }
    omDelPrcObj(NULL);
}

s32 func_800D7250_name_81(UnkEA790Struct* arg0, s32 arg1) {
    if (arg0->proc != NULL) {
        return osSendMesg(&arg0->unk10, (void* ) arg1, 0);
    }
    return - 1;
}

void func_800D7280_name_81(void) {
    Vec stick;
    Vec diff;
    UnkEA790Struct *work;
    GW_PLAYER *player;
    s32 sel;
    s32 i;
    s16 run;

    run = 1;
    work = HuPrcCurrentGet()->user_data;
    player = work->player;
    sel = work->unk_0C;

    while (run) {
        HuPrcVSleep();

        stick.x = D_800CBB6E_main[work->unkE];
        stick.z = D_800D20A1_main[work->unkE];
        stick.z = -stick.z;
        stick.y = 0.0f;

        if (func_800EBA50_name_81(work->unkE, 40.0f) != 0) {
            for (i = 0; i < work->unk_02; i++) {
                HuVecSubtract(&diff,
                              &func_800D6EC8_name_81(work, i)->obj->coords,
                              &player->player_obj->coords);
                diff.y = 0.0f;
                if (func_800D7CEC_name_81(&stick, &diff) <= 38.0f) {
                    if (sel != i) {
                        sel = i;
                        func_800D7250_name_81(work, sel);
                    }
                    break;
                }
            }
        }

        if ((D_800C9520_main[work->unkE] & 0x8000) && (sel >= 0)) {
            sel = -4;
            func_800D7250_name_81(work, sel);
            run = 0;
        }
    }
    omDelPrcObj(NULL);
}


s32 func_800D742C_name_81(UnkEA790Struct* arg0, s16 playerNo, s32 arg2) {
    GW_PLAYER* player;
    Process* proc;

    if (arg0->proc == NULL) {
        proc = omAddPrcObj(func_800D6EE0_name_81, 0xEFFF, 0x1000, 0);
        arg0->proc = proc;
        proc->user_data = arg0;
        osCreateMesgQueue(&arg0->unk10, &arg0->unk28, 0x10);
        arg0->unk_00 = arg2 | arg0->unk_00;
        player = MBDGetPlayerStruct(playerNo);
        if (player->stat & 1) {
            arg0->unk_00 |= 1;
            func_800D7250_name_81(arg0, -1);
        } else {
            arg0->unkE = player->pad;
            omAddPrcObj(func_800D7280_name_81, 0xEFFF, 0x1000, 0)->user_data = arg0;
        }
        return player->stat & 1;
    }
    return -1;
}

s32 func_800D7518_name_81(UnkEA790Struct* arg0) {
    if (arg0->proc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), arg0->proc);
        HuPrcChildWait();
        arg0->proc = NULL;
    }
    return arg0->unk_0C;
}

void func_800D7568_name_81(UnkBoard2* arg0, Vec* arg1, Vec* arg2, f32 arg3) {
    Vec sp10;

    func_800EB708_name_81(arg1, arg2, &sp10);
    HuVecCopy3F(&arg0->obj->rot, &sp10);
    HuVecMulScalar(&sp10, arg3, &sp10);
    HuVecAdd(&arg0->obj->coords, &sp10, arg1);
}

UnkEA790Struct* func_800D75E8_name_81(s16 arg0, s16* arg1, s32 arg2) {
    GW_PLAYER* player;
    UnkBoard2* temp_s0;
    UnkEA790Struct* temp_v0;

    player = MBDGetPlayerStruct(arg0);
    temp_v0 = func_800D6C6C_name_81();
    temp_v0->player = player;
    for (; *arg1 >= 0; arg1++) {
        temp_s0 = func_800D6B70_name_81(arg2);
        func_800D7568_name_81(temp_s0, &player->player_obj->coords, &MBDMasuGet(*arg1)->coords, 12.0f);
        func_800D6D2C_name_81(temp_v0, temp_s0, 0);
    }
    
    return temp_v0;
}

UnkEA790Struct* func_800D76A0_name_81(s16 arg0, s16* arg1) {
    return func_800D75E8_name_81(arg0, arg1, 0);
}

/* Retail linked the vector helpers below from their own file (ovl_80's EC3B0), so their start is
 * padded to 16 bytes. */
#ifndef NON_MATCHING
__asm__(".section .text\n    .align 4\n");
#endif

f32 func_800D76D0_name_81(Vec *arg0) {
    f32 temp_f16;

    if (arg0->x != 0.0f || arg0->z != 0.0f) {
        if (arg0->x == 0.0f) {
            if (0.0f < arg0->z) {
                return 0.0f;
            }
            return 180.0f;
        }

        if (arg0->z == 0.0f) {
            if (0.0f < arg0->x) {
                return 90.0f;
            }
            return 270.0f;
        }

        temp_f16 = atan2df(arg0->z, arg0->x);

        if (arg0->z < 0.0f) {
            temp_f16 = 90.0f - temp_f16;
        } else {
            temp_f16 = 90.0f - temp_f16;
            if (temp_f16 < 0.0f) {
                temp_f16 += 360.0f;
            }
        }
        return temp_f16;
    }

    return -1.0f;
}

void func_800D7828_name_81(Vec *vec) {
    if ((vec->x == 0.0f) && (vec->y == 0.0f) && (vec->z == 0.0f)) {
        vec->z = 1.0f;
    }

    HuVecNormalize3F(vec);
}

void func_800D7898_name_81(Vec *arg0, f32 arg1) {
    Vec sp10;

    sp10.y = arg0->y;
    sp10.z = arg0->z;

    arg0->y = ((cosdf(arg1) * sp10.y) - (sindf(arg1) * sp10.z));
    arg0->z = ((cosdf(arg1) * sp10.z) + (sindf(arg1) * sp10.y));
}

void func_800D7934_name_81(Vec *arg0, f32 arg1) {
    Vec sp10;

    sp10.x = arg0->x;
    sp10.z = arg0->z;

    arg0->x = ((cosdf(arg1) * sp10.x) + (sindf(arg1) * sp10.z));
    arg0->z = ((cosdf(arg1) * sp10.z) - (sindf(arg1) * sp10.x));
}

void func_800D79D0_name_81(Vec *arg0, f32 arg1) {
    Vec sp10;

    sp10.x = arg0->x;
    sp10.y = arg0->y;

    arg0->x = ((cosdf(arg1) * sp10.x) - (sindf(arg1) * sp10.y));
    arg0->y = ((cosdf(arg1) * sp10.y) + (sindf(arg1) * sp10.x));
}


void func_800D7A6C_name_81(Vec* arg0, Vec* arg1, f32 arg2) {
    Vec origPos;
    f32 temp_f2; //should be fs4
    f32 temp_f3; //should be fs1
    f32 temp_f4; //should be fs2
    f32 temp_f5; //should be fs3
    f32 temp_f0;
    
    // Store original vector
    origPos.x = arg0->x;
    origPos.y = arg0->y;
    origPos.z = arg0->z;
    
    // Normalize the rotation axis
    func_800D7828_name_81(arg1);

    arg0->x = ((arg1->x * arg1->x + (1.0f - arg1->x * arg1->x) * cosdf(arg2)) * origPos.x) +
              ((arg1->x * arg1->y * (1.0f - cosdf(arg2)) - sindf(arg2) * arg1->z) * origPos.y) +
              ((arg1->x * arg1->z * (1.0f - cosdf(arg2)) + sindf(arg2) * arg1->y) * origPos.z);

    arg0->y = ((arg1->x * arg1->y * (1.0f - cosdf(arg2)) + sindf(arg2) * arg1->z) * origPos.x) +
              ((arg1->y * arg1->y + (1.0f - arg1->y * arg1->y) * cosdf(arg2)) * origPos.y) +
              ((arg1->y * arg1->z * (1.0f -  cosdf(arg2)) - sindf(arg2) * arg1->x) * origPos.z);
    
    arg0->z = ((arg1->x * arg1->z * (1.0f - cosdf(arg2)) - sindf(arg2) * arg1->y) * origPos.x) +
              ((arg1->y * arg1->z * (1.0f - cosdf(arg2)) + sindf(arg2) * arg1->x) * origPos.y) +
              ((arg1->z * arg1->z + (1.0f - arg1->z * arg1->z) * cosdf(arg2)) * origPos.z);
}

f32 func_800D7CEC_name_81(Vec *vec_1, Vec *vec_2) {
    f32 length;
    f32 dot;

    dot = HuVecDot3F(vec_1, vec_2);
    length = HuVecGetLength3F(vec_1) * HuVecGetLength3F(vec_2);
    if (length != 0.0f) {
        return acosdf(dot / length);
    }
}