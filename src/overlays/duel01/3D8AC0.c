#include "common.h"
#include "duel01.h"

void func_801059D0_duel01(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel01(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80119470_duel01 = func_800E1824_name_81(0, 0xA0, 1);
    D_80119474_duel01 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80119478_duel01 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011947C_duel01 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel01(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80119470_duel01);
    func_800E1854_name_81(D_80119474_duel01);
    func_800E1854_name_81(D_80119478_duel01);
    func_800E1854_name_81(D_8011947C_duel01);
}

void func_80105B64_duel01(void) {
    GwSystem.current_board_index = 0;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105B9C_duel01(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x241);
    func_800E9F4C_name_81(0x1C, &sp10, &sp11);
    func_800ECD0C_name_81(0, sp10, sp11);
    func_800E9F4C_name_81(0x1B, &sp10, &sp11);
    func_800ECD0C_name_81(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105C64_duel01(Vec *arg0, Vec *arg1, Vec *arg2) { // duel b1: Vec* (was s32, s32, unkStruct01*)
    f32 temp_f20;

    func_800EB708_name_81(arg0, arg1, arg2);
    temp_f20 = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(temp_f20);
    arg2->z = cosdf(temp_f20);
}

// duel b1
void func_80105CC0_duel01(void) {
    Vec pos;
    Vec2f pos2D;
    unkStruct02 *work;
    f32 x;
    f32 y;
    f32 z;
    B1UnkBoard4 *spr;
    void *data;
    f32 height;
    s32 i;

    work = HuPrcCurrentGet()->user_data;
    x = work->unk_00.x;
    y = work->unk_00.y;
    z = work->unk_00.z;
    HuPrcSleep(5);
    HuVecCopyXYZ(&pos, x, y, z);
    MBDCamera3Dto2D(&pos, &pos2D);
    spr = func_800F4528_name_81(1, 0);
    data = DataRead(0x1301EC);
    *spr->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(spr->unk_0A, 0, *spr->unk_0C, 0);
    HuSprPriSet(spr->unk_0A, 0, 0x2010);
    HuSprAttrSet(spr->unk_0A, 0, 0);
    func_80054904_main(spr->unk_0A, 0, pos2D.x, pos2D.y);
    HuAudFXPlay(0x202);
    height = 20.0f;
    for (i = 0; i < 20; i++) {
        func_80054904_main(spr->unk_0A, 0, pos2D.x, pos2D.y - fabs(sindf(i * 20) * height));
        height -= 1.0f;
        if (height < 0.0f) {
            height = 0.0f;
        }
        HuPrcVSleep();
    }
    func_800F4584_name_81(spr);
    omDelPrcObj(NULL);
}

void *func_80105EB0_duel01(unkStruct04 *arg0) {
    Process *process;
    unkStruct02 *temp_v0_2;

    process = omAddPrcObj(&func_80105CC0_duel01, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00.x = arg0->unk_0C.x;
    temp_v0_2->unk_00.y = arg0->unk_0C.y;
    temp_v0_2->unk_00.z = arg0->unk_0C.z;
    return process;
}

// duel b1
void func_80105F20_duel01(void) {
    Vec dest;
    Vec start;
    Process *process;
    B1ThwompPrc *work;
    GW_PLAYER *player;
    Object *obj;
    s32 wait;
    s32 delay;

    process = HuPrcCurrentGet();
    work = HuPrcCurrentGet()->user_data;
    player = work->player;
    obj = work->obj;
    delay = work->delay;
    wait = work->wait;
    delay -= 5;
    if (delay > 0) {
        HuPrcSleep(delay);
    }
    func_80105EB0_duel01((unkStruct04 *)obj);
    HuVecSubtract(&dest, &obj->coords, &player->player_obj->coords);
    if ((D_80105620_name_81 == 3) | (D_80105620_name_81 == 1)) {
        func_800D7934_name_81(&dest, -90.0f);
    } else {
        func_800D7934_name_81(&dest, 90.0f);
    }
    HuVecAdd(&dest, &dest, &obj->coords);
    HuVecCopy3F(&start, &obj->coords);
    func_800FB0B8_name_81(obj, 3, 0);
    D_80101994_name_81++;
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 2.0f));
    HuPrcChildWait();
    HuPrcSleep(wait);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &start, &obj->coords, 2.0f));
    func_8001C814_main(obj->omObj1->model[0], 0, 4);
    HuPrcChildWait();
    func_800EFB00_name_81(obj);
    func_800D90D0_name_81(obj, -1, 2);
    D_80101994_name_81--;
    omDelPrcObj(NULL);
}

// duel b1
Process *func_801060D0_duel01(GW_PLAYER *player, Object *obj, s32 delay, s32 wait) {
    Process *process;
    B1ThwompPrc *work;

    process = omAddPrcObj(func_80105F20_duel01, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(B1ThwompPrc));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->wait = wait;
    return process;
}

// duel b1
void func_8010615C_duel01(Object *obj, Object *target, GW_PLAYER *player, Vec *dest, Vec *start, f32 dist) {
    Vec ofs;
    f32 angle;

    HuVecCopy3F(start, &obj->coords);
    if (target != NULL) {
        HuVecCopy3F(dest, &target->coords);
    } else {
        HuVecCopy3F(dest, &player->player_obj->coords);
    }
    func_800EB708_name_81(&obj->coords, dest, &obj->rot);
    angle = func_800D76D0_name_81(&obj->rot) + 180.0f;
    ofs.x = sindf(angle) * dist;
    ofs.y = 0.0f;
    ofs.z = cosdf(angle) * dist;
    HuVecAdd(dest, dest, &ofs);
}

void func_80106240_duel01(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

// duel b1: arg0/arg1 typed (were s32, unkStruct05*)
Process *func_80106260_duel01(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) { // duel b1: returns the camera move (was void)
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
    return process;
}

// duel b1: typed; b7: the frame count is the caller's fourth argument, passed through in $a3
Process *func_801062C0_duel01(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 frames) {
    Process *process;

    if (arg2 & 9) {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, frames);
    } else {
        process = func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, frames);
    }
    return process;
}

// duel b1
void func_80106308_duel01(void) {
    Vec2f base;
    Vec2f pos;
    unkStruct06 *work;
    s32 amp;
    s32 step;
    f32 ampf;
    f32 half;

    work = HuPrcCurrentGet()->user_data;
    amp = work->unk_00;
    step = work->unk_04;
    MBDCameraPos2DGet(&base);
    func_800FC888_name_81(0);
    while (amp >= 0) {
        pos.x = func_800EFE20_name_81(ampf = amp) + base.x - (half = amp / 2);
        pos.y = func_800EFE20_name_81(ampf) + base.y - half;
        MBDCameraPos2DSet(&pos);
        amp -= step;
        HuPrcVSleep();
        pos.x = func_800EFE20_name_81(ampf) + base.x - half;
        pos.y = func_800EFE20_name_81(ampf) + base.y - half;
        MBDCameraPos2DSet(&pos);
        HuPrcVSleep();
    }
    func_800FC888_name_81(4);
    omDelPrcObj(NULL);
}

Process *func_8010645C_duel01(s32 arg0, s32 arg1) {
    Process *process;
    unkStruct06 *temp_v0_2;

    process = omAddPrcObj(&func_80106308_duel01, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct06));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    return process;
}

// duel b1
void func_801064C8_duel01(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *obj;

    player = MBDGetPlayerStruct(playerIndex);
    switch (mode) {
    case 0:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            obj = func_800D8010_name_81(0x28, 0);
            D_80119480_duel01 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            obj = func_800D8010_name_81(0x28, 0);
            D_80119484_duel01 = obj;
            HuVecCopy3F(&obj->coords, &partner->coords);
            HuVecCopy3F(&obj->rot, &partner->rot);
            func_800D8F0C_name_81(partner);
        }
        break;
    case 1:
        if (player->stats.partners.frontID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 0);
            func_800D8F3C_name_81(D_80119480_duel01);
            func_800D8E88_name_81(partner);
        }
        if (player->stats.partners.backID == 3) {
            partner = MBDGetPlayerPartnerRef(playerIndex, 1);
            func_800D8F3C_name_81(D_80119484_duel01);
            func_800D8E88_name_81(partner);
        }
        break;
    case 2:
        switch (D_80105620_name_81) {
        case 1:
        case 3:
            if (player->stats.partners.frontID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 0);
                obj = func_800D8010_name_81(0x28, 0);
            D_80119480_duel01 = obj;
                HuVecCopy3F(&obj->coords, &partner->coords);
                HuVecCopy3F(&obj->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            break;
        case 0:
        case 2:
            if (player->stats.partners.backID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 1);
                obj = func_800D8010_name_81(0x28, 0);
            D_80119484_duel01 = obj;
                HuVecCopy3F(&obj->coords, &partner->coords);
                HuVecCopy3F(&obj->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            break;
        }
        break;
    case 3:
        switch (D_80105620_name_81) {
        case 1:
        case 3:
            if (player->stats.partners.frontID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 0);
                func_800D8F3C_name_81(D_80119480_duel01);
                func_800D8E88_name_81(partner);
            }
            break;
        case 0:
        case 2:
            if (player->stats.partners.backID == 3) {
                partner = MBDGetPlayerPartnerRef(playerIndex, 1);
                func_800D8F3C_name_81(D_80119484_duel01);
                func_800D8E88_name_81(partner);
            }
            break;
        }
        break;
    }
}

void *func_80106740_duel01(s32 arg0) {
    Object *obj;

    obj = func_800D8010_name_81(arg0 & 0xFF, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0x1800);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    return obj;
}

void func_801067D4_duel01(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0); // duel b1: was ()
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

// duel b1: a partner charges at the target (level 1: with a stand-in model, level 2: spinning with a second effect model)
void func_80106828_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec diff;
    Process *spinPrc[2];
    Vec mid;
    Process *process;
    GW_PLAYER *player;
    HmfModel *mdl;
    Object *effect;
    Object *standIn;
    Object *effect2;
    f32 angle;
    f32 speed;
    s32 model;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    spinPrc[0] = NULL;
    spinPrc[1] = NULL;
    standIn = NULL;
    effect2 = NULL;
    model = -1;
    func_800FAD04_name_81(0);
    if (level == 1) {
        standIn = func_80106740_duel01(0x45);
    }
    effect = func_800D8010_name_81(D_80118710_duel01[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        effect2 = func_800D8010_name_81(0x56, 0);
        func_800D8944_name_81(effect2);
        func_800D8F0C_name_81(effect2);
    }
    func_80106240_duel01();
    HuAudFXPlay(0x25A);
    func_800FAE18_name_81(partner, 0, 0);
    func_800EFABC_name_81(partner);
    func_800FAE18_name_81(partner, 1, 2);
    if (level == 2) {
        HuAudFXPlay(0x1D6);
        angle = 0.0f;
        for (speed = 0.0f; speed <= 30.0f; speed += 2.0f) {
            HuPrcVSleep();
            angle += speed;
            B1_MODEL_ROTY(partner, angle, mdl);
        }
        spinPrc[0] = func_800D9668_name_81(partner, angle, 30.0f, -1);
        HuVecCopy3F(&effect2->coords, &partner->coords);
        func_800D8E88_name_81(effect2);
        spinPrc[1] = func_800D9668_name_81(effect2, 0.0f, 30.0f, -1);
        HuPrcSleep(20);
    }
    func_8010615C_duel01(partner, target, player, &dest, &start, 6.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    HuVecSubtract(&diff, &partner->coords, &dest);
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
    if (level == 2) {
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect2->coords, &dest, &effect2->coords, 3.0f));
    }
    func_80106260_duel01(target, player, flags, 3.0f);
    if (flags & 8) {
        func_801060D0_duel01(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
    } else {
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
        if (level == 1) {
            func_801067D4_duel01(standIn, &partner->coords);
        }
        if (flags & 1) {
            HuVecAdd(&mid, &target->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105C64_duel01(&target->coords, &standIn->coords, &standIn->rot);
                func_801067D4_duel01(standIn, &target->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80118E60_duel01);
                func_800DD2DC_name_81(model, &mid);
            }
        } else {
            HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
            HuVecMulScalar(&mid, 0.5f, &mid);
            func_800DCE40_name_81(0x4A, &mid, NULL, 2.0f);
            if (level == 1) {
                func_80105C64_duel01(&player->player_obj->coords, &standIn->coords, &standIn->rot);
                func_801067D4_duel01(standIn, &player->player_obj->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80118E60_duel01);
                func_800DD2DC_name_81(model, &mid);
            }
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &start, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &start, &effect->coords, 3.0f));
    if (level == 2) {
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect2->coords, &start, &effect2->coords, 3.0f));
    }
    HuPrcChildWait();
    func_800D8F0C_name_81(effect);
    if (spinPrc[0] != NULL) {
        omDelPrcObj(spinPrc[0]);
    }
    if (level == 2) {
        if (spinPrc[1] != NULL) {
            omDelPrcObj(spinPrc[1]);
        }
        func_800D8F0C_name_81(effect2);
    }
    B1_MODEL_ROTY(partner, 0.0f, mdl);
    func_800FAE18_name_81(partner, 0, 0);
    func_8001C814_main(partner->omObj1->model[0], 0, 4);
    func_8001C6A8_main(partner->omObj1->model[0], 1000.0f);
    func_800EFB00_name_81(partner);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(effect);
    if (level == 1) {
        func_800D8F3C_name_81(standIn);
    } else {
        func_800D8F3C_name_81(effect2);
        if (model != -1) {
            while (func_800DD3B4_name_81(model) == 0) {
                HuPrcVSleep();
            }
            func_800DD2BC_name_81(model);
        }
    }
    func_800FADB4_name_81();
}

// duel b1: a partner jumps on the target (level 2: spinning, with a second effect model)
void func_80107188_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    s32 standInIds[2];
    Vec mid;
    Vec *midp;
    Process *process;
    Object *standIn;
    GW_PLAYER *player;
    HmfModel *mdl;
    Object *effect;
    Object *effect2;
    Process *spinPrc;
    s32 i;
    f32 speed;
    f32 jumpSpeed;
    f32 jumpGravity;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    effect2 = NULL;
    standInIds[0] = 0x48;
    standInIds[1] = 0x49;
    spinPrc = NULL;
    standIn = func_80106740_duel01(standInIds[level - 1]);
    effect = func_800D8010_name_81(D_80118710_duel01[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        effect2 = func_800D8010_name_81(0x56, 0);
        func_800D8944_name_81(effect2);
        func_800D8F0C_name_81(effect2);
    }
    func_800FAD04_name_81(1);
    func_800D90D0_name_81(partner, 0, 2);
    func_8010615C_duel01(partner, target, player, &dest, &start, 7.0f);
    func_80106240_duel01();
    func_80106260_duel01(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
    HuPrcChildWait();
    func_800D8F0C_name_81(effect);
    if (level == 2) {
        HuVecCopy3F(&effect2->coords, &partner->coords);
        func_800D8E88_name_81(effect2);
        spinPrc = func_800D9668_name_81(effect2, 0.0f, 30.0f, -1);
        jumpSpeed = 3.0f;
        jumpGravity = -0.375f;
        func_800EF7C8_name_81(effect2, jumpSpeed, jumpGravity);
        func_800D8E88_name_81(effect);
        func_800EF7C8_name_81(effect, jumpSpeed, jumpGravity);
    }
    func_800FAE18_name_81(partner, 0, 2);
    speed = level + 1.0f;
    func_800EF7C8_name_81(partner, speed, -speed / 8.0f);
    if (level == 2) {
        for (i = 0; i < 8; i++) {
            B1_MODEL_ROTY(partner, i * 45.0f, mdl);
            HuPrcVSleep();
        }
        B1_MODEL_ROTY(partner, 0.0f, mdl);
    } else {
        HuPrcSleep(8);
    }
    partner->velocity.z = 0.0f;
    func_800FAE18_name_81(partner, 1, 0);
    if (level == 2) {
        if (spinPrc != NULL) {
            omDelPrcObj(spinPrc);
        }
        func_800D8F0C_name_81(effect2);
        func_800D8F0C_name_81(effect);
    }
    if (flags & 8) {
        func_801060D0_duel01(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        func_801067D4_duel01(standIn, &partner->coords);
        HuAudFXPlay(0x25B);
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        mid.y += partner->velocity.x;
        func_801067D4_duel01(standIn, midp);
        if (level == 2) {
            func_800DCE40_name_81(0x4B, &mid, NULL, 2.0f);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    func_800EFABC_name_81(partner);
    partner->velocity.z = -(level + 1.0f) / 8.0f;
    func_800EF800_name_81(partner);
    func_800EB708_name_81(&partner->coords, &start, &partner->rot);
    func_800D90D0_name_81(partner, 0, 2);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
    func_800D8E88_name_81(effect);
    func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
    HuVecCopy3F(&effect->coords, &partner->coords);
    func_800EB708_name_81(&effect->coords, &start, &effect->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &start, &effect->coords, 3.0f));
    HuPrcChildWait();
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(standIn);
    func_800D8F3C_name_81(effect);
    if (level == 2) {
        func_800D8F3C_name_81(effect2);
    }
    func_800FADB4_name_81();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E60_duel01);

// duel b1: a partner swings a hooked item at the target
// decomp-permuter
void func_801079B8_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level)
{
  Vec dest;
  Vec start;
  s32 standInIds[2];
  s32 effectIds[2];
  Vec mid;
  Vec *midp;
  Process *process;
  GW_PLAYER *player;
  Object *effect;
  Object *standIn;
  Object *hook;
  player = MBDGetPlayerStruct(targetIndex);
  process = HuPrcCurrentGet();
  standInIds[0] = 0x54;
  standInIds[1] = 0x55;
  effectIds[0] = 0x4E;
  effectIds[1] = 0x4A;
  func_800FAD04_name_81(2);
  standIn = func_80106740_duel01(standInIds[level - 1]);
  effect = func_800D8010_name_81(D_80118710_duel01[level - 1] & 0xFF, 0);
  func_8001C8E4_main(effect->omObj1->model[0], 0);
  func_8001C448_main(effect->omObj1->model[0]);
  func_800D8944_name_81(effect);
  func_800D8F0C_name_81(effect);
  hook = func_800D8010_name_81(0x3F, 0);
  func_800D8F0C_name_81(hook);
  func_800F0378_name_81(partner, "item_hook", hook->omObj1->model[0]);
  func_800D90D0_name_81(partner, 0, 2);
  func_8010615C_duel01(partner, target, player, &dest, &start, 6.0f);
  func_80106240_duel01();
  func_80106260_duel01(target, player, flags, 3.0f);
  HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
  func_800D8E88_name_81(effect);
  func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
  HuVecCopy3F(&effect->coords, &partner->coords);
  func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
  HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 3.0f));
  HuPrcChildWait();
  func_800D8F0C_name_81(effect);
  func_800D8E88_name_81(hook);
  if (level == 2)
  {
    func_800FAE18_name_81(partner, 0, 0);
    HuAudFXPlay(0x1D8);
    HuPrcSleep(6);
    func_8001C814_main(partner->omObj1->model[0], 0, 4);
    func_800EFB00_name_81(partner);
    func_800FAE18_name_81(partner, 0, 0);
    HuAudFXPlay(0x1D8);
    HuPrcSleep(6);
    func_8001C814_main(partner->omObj1->model[0], 0, 4);
    func_800EFB00_name_81(partner);
  }
  func_800FAE18_name_81(partner, 0, 0);
  HuAudFXPlay(0x1D8);
  if (flags & 8)
  {
    func_801060D0_duel01(player, target, 0, 20);
  }
  else
  {
    HuPrcSleep(9);
    HuAudFXPlay(0x1D7);
 do { if (level == 2) { HuAudFXPlay(0x1F2); } midp = &mid; if (flags & 1) { HuVecAdd(midp, &target->coords, &partner->coords); } else { HuVecAdd(midp, &player->player_obj->coords, &partner->coords); } HuVecMulScalar(midp, 0.5f, midp); func_800EB804_name_81(standIn); func_801067D4_duel01(standIn, midp); func_800DCE40_name_81(effectIds[level - 1], &mid, 0, 2.0f); func_800FAC1C_name_81(&D_80105540_name_81); } while (0);
    if (flags & 1)
    {
      func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
    }
    if (flags & 2)
    {
      func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
    }
  }
  func_800EFABC_name_81(partner);
  func_800D8F0C_name_81(hook);
  func_800EB708_name_81(&partner->coords, &start, &partner->rot);
  func_800D90D0_name_81(partner, 0, 2);
  HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
  func_800D8E88_name_81(effect);
  func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
  HuVecCopy3F(&effect->coords, &partner->coords);
  func_800EB708_name_81(&effect->coords, &start, &effect->rot);
  HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &start, &effect->coords, 3.0f));
  HuPrcChildWait();
  func_800D90D0_name_81(partner, -1, 2);
  func_800ED214_name_81(playerIndex);
  func_800D8F3C_name_81(hook);
  func_800D8F3C_name_81(standIn);
  func_800D8F3C_name_81(effect);
  func_800FADB4_name_81();
}

// duel b1: a partner throws itself at the target (or straight at the player) and explodes
void func_80107EBC_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec ofs;
    s32 standInIds[2];
    Vec mid;
    Object *blast;
    GW_PLAYER *player;
    Object *standIn;
    Object *effect;
    Object *orig;
    Process *process;
    f32 angle;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    blast = NULL;
    standInIds[0] = 0x4F;
    standInIds[1] = 0x52;
    standIn = func_80106740_duel01(standInIds[level - 1]);
    HuVecCopyXYZ(&standIn->scale, 2.0f, 2.0f, 2.0f);
    if (level == 2) {
        HuPrcVSleep();
        blast = func_80106740_duel01(0x5B);
        HuPrcVSleep();
    }
    effect = func_800D8010_name_81(D_80118710_duel01[level - 1] & 0xFF, 0);
    func_8001C8E4_main(effect->omObj1->model[0], 0);
    func_8001C448_main(effect->omObj1->model[0]);
    func_800D8944_name_81(effect);
    func_800D8F0C_name_81(effect);
    func_800FAD04_name_81(3);
    if (level == 2) {
        func_800D8F0C_name_81(partner);
        orig = partner;
        partner = func_800D8010_name_81(0x27, 0);
        HuVecCopy3F(&partner->coords, &orig->coords);
        HuVecCopy3F(&partner->rot, &orig->rot);
    }
    func_800FAE98_name_81(partner, 0, 0, 5, 2);
    HuAudFXPlay(0x1DC);
    HuPrcSleep(20);
    func_80106240_duel01();
    func_80106260_duel01(target, player, flags, 2.0f);
    if (target != NULL) {
        HuVecCopy3F(&dest, &target->coords);
        func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
        angle = func_800D76D0_name_81(&partner->rot) + 180.0f;
        ofs.x = sindf(angle) * 9.0f;
        ofs.y = 0.0f;
        ofs.z = cosdf(angle) * 9.0f;
        HuVecAdd(&dest, &dest, &ofs);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 2.0f));
        func_800D8E88_name_81(effect);
        func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
        HuVecCopy3F(&effect->coords, &partner->coords);
        func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 2.0f));
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
        HuAudFXPlay(0x256);
        HuVecCopy3F(&dest, &player->player_obj->coords);
        func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
        func_800EF7C8_name_81(partner, 7.5f, -0.825f);
        HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 15));
        HuPrcChildWait();
    } else {
        HuVecCopy3F(&dest, &player->player_obj->coords);
        func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
        angle = func_800D76D0_name_81(&partner->rot) + 180.0f;
        ofs.x = sindf(angle) * 6.0f / 2.0f;
        ofs.y = 0.0f;
        ofs.z = cosdf(angle) * 6.0f / 2.0f;
        HuVecAdd(&dest, &dest, &ofs);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 2.0f));
        func_800D8E88_name_81(effect);
        func_8001C6A8_main(effect->omObj1->model[0], 0.0f);
        HuVecCopy3F(&effect->coords, &partner->coords);
        func_800EB708_name_81(&effect->coords, &dest, &effect->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&effect->coords, &dest, &effect->coords, 2.0f));
        HuAudFXPlay(0x256);
        HuPrcChildWait();
        func_800D8F0C_name_81(effect);
    }
    func_800D8F0C_name_81(partner);
    partner->coords.y += partner->velocity.x;
    HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
    HuVecMulScalar(&mid, 0.5f, &mid);
    if (level == 2) {
        func_801067D4_duel01(blast, &partner->coords);
        func_8001C92C_main(blast->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        func_801067D4_duel01(standIn, &mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (level == 1) {
        func_801067D4_duel01(standIn, &mid);
        HuAudFXPlay(0x1DD);
    } else {
        HuAudFXPlay(0x1DE);
    }
    MBDBackTPLvlSet(0xFF);
    HuPrcVSleep();
    MBDBackTPLvlSet(0x40);
    func_800FAC1C_name_81(&D_80105540_name_81);
    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
    HuPrcSleep(30);
    if (level == 2) {
        func_800D8F3C_name_81(partner);
        func_800D8F3C_name_81(blast);
    }
    func_800D8F3C_name_81(effect);
    func_800D8F3C_name_81(standIn);
    func_800FADB4_name_81();
}

// duel b1
void func_801084A4_duel01(s32 playerIndex, s32 arg1, Object *partner, Object *target, s32 arg4, s32 count) {
    func_800FAD04_name_81(5);
    if (count == 2) {
        HuAudFXPlay(0x25D);
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
    }
    HuAudFXPlay(0x25D);
    func_800FAE18_name_81(partner, 0, 0);
    func_800EFABC_name_81(partner);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800FADB4_name_81();
}

// duel b1: a partner rears up and slams down on the target (level 2: three slams, then a wobble)
#ifdef NON_MATCHING // duel b1: masked 0; float registers of the final squash loop ($f20/$f22/$f24) rotated
void func_80108550_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec diff;
    GW_PLAYER *player;
    Process *process;
    Object *standIn;
    Object *dust;
    HmfModel *mdl;
    s32 model;
    s32 i;
    f32 amp;
    f32 height;
    f32 scale;
    f32 angle;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    model = -1;
    if (target == NULL) {
        HuPrcSleep(20);
        return;
    }
    standIn = func_80106740_duel01(0x55);
    func_8010615C_duel01(partner, target, player, &dest, &start, 9.0f);
    for (height = 0.0f; height <= 20.0f; height += 2.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    func_80106240_duel01();
    func_80106260_duel01(target, player, flags, 3.0f);
    B1_MODEL_ROTX(partner, 20.0f, mdl);
    HuVecSubtract(&diff, &dest, &partner->coords);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
    for (i = 20; i > 0; i--) {
        B1_MODEL_ROTX(partner, i, mdl);
        HuPrcVSleep();
    }
    B1_MODEL_ROTX(partner, 0.0f, mdl);
    HuPrcSleep(5);
    for (height = 20.0f; height >= 0.0f; height -= 10.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    func_800DCB04_name_81(0x5A, 1, &partner->coords, 1.0f, 0);
    HuAudFXPlay(0x1E7);
    HuAudFXPlay(0x1E8);
    HuPrcSleep(10);
    if (target != NULL) {
        HuPrcSleep(10);
        for (height = 0.0f; height <= 24.0f; height += 2.0f) {
            partner->velocity.x = height;
            HuPrcVSleep();
        }
        HuVecCopy3F(&dest, &target->coords);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
        HuPrcChildWait();
        HuPrcSleep(10);
        if (flags & 8) {
            if (level == 1) {
                func_801060D0_duel01(player, target, 0, 55);
            } else {
                func_801060D0_duel01(player, target, 0, 120);
            }
            for (height = 24.0f; height >= 0.0f; height -= 8.0f) {
                partner->velocity.x = height;
                HuPrcVSleep();
            }
            if (level == 1) {
                HuAudFXPlay(0x1E7);
                HuAudFXPlay(0x1E8);
            } else {
                HuAudFXPlay(0x1E9);
            }
            func_800DCB04_name_81(0x5A, 1, &partner->coords, 1.0f, 0);
        } else {
            for (height = 24.0f; height >= 0.0f; height -= 8.0f) {
                scale = height / 24.0f;
                partner->velocity.x = height;
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                if (scale < 0.1f) {
                    scale = 0.1f;
                }
                HuVecCopyXYZ(&target->scale, 1.0f, scale, 1.0f);
                HuPrcVSleep();
            }
            HuAudFXPlay((level == 1) ? 0x1F3 : 0x1E9);
            HuVecCopyXYZ(&target->scale, 1.0f, 0.1f, 1.0f);
            func_801064C8_duel01(targetIndex, 2);
            if (level == 1) {
                func_800EB804_name_81(standIn);
                func_801067D4_duel01(standIn, &target->coords);
                func_800DCE40_name_81(0x47, &target->coords, NULL, 1.0f);
            } else {
                dust = func_800D8010_name_81(0x5A, 0);
                func_800D974C_name_81(dust);
                HuVecCopy3F(&dust->coords, &partner->coords);
                model = func_800DD1E0_name_81(0xB0023, D_80118E60_duel01);
                func_800DD2DC_name_81(model, &partner->coords);
            }
        }
        if (level == 1) {
            func_8010645C_duel01(10, 1);
            HuPrcSleep(40);
        } else {
            HuPrcChildLink(process, func_8010645C_duel01(5, 2));
            HuPrcChildWait();
            for (i = 0; i < 3; i++) {
                for (height = 0.0f; height < 9.0f; height += 3.0f) {
                    partner->velocity.x = height;
                    HuPrcVSleep();
                }
                for (; height >= 0.0f; height -= 4.5f) {
                    partner->velocity.x = height;
                    HuPrcVSleep();
                }
                if (i == 2) {
                    HuAudFXPlay(0x1F3);
                    func_800EB804_name_81(standIn);
                    func_801067D4_duel01(standIn, &partner->coords);
                    func_800DCE40_name_81(0x47, &partner->coords, NULL, 1.0f);
                } else {
                    HuAudFXPlay(0x1E9);
                    dust = func_800D8010_name_81(0x5A, 0);
                    func_800D974C_name_81(dust);
                    HuVecCopy3F(&dust->coords, &partner->coords);
                }
                HuPrcChildLink(process, func_8010645C_duel01(5, 2));
                HuPrcChildWait();
            }
            angle = func_800D76D0_name_81(&partner->rot);
            for (i = 0; i < 30; i++) {
                partner->rot.x = sindf(angle + sindf(i * 60) * (30 - i));
                partner->rot.z = cosdf(angle + sindf(i * 60) * (30 - i));
                HuPrcVSleep();
            }
            partner->rot.x = sindf(angle);
            partner->rot.z = cosdf(angle);
            HuPrcSleep(10);
        }
    }
    for (height = 0.0f; height <= 24.0f; height += 2.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    B1_MODEL_ROTX(partner, 20.0f, mdl);
    HuVecSubtract(&diff, &start, &partner->coords);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &start, &partner->coords, 20));
    for (i = 20; i > 0; i--) {
        B1_MODEL_ROTX(partner, i, mdl);
        HuPrcVSleep();
    }
    B1_MODEL_ROTX(partner, 0.0f, mdl);
    HuPrcSleep(5);
    for (height = 24.0f; height >= 0.0f; height -= 6.0f) {
        partner->velocity.x = height;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x1E7);
    HuAudFXPlay(0x1E8);
    func_800DCB04_name_81(0x5A, 1, &partner->coords, 1.0f, 0);
    func_800ED214_name_81(playerIndex);
    if (target != NULL && !(flags & 8)) {
        func_801064C8_duel01(targetIndex, 3);
        amp = 1.0f;
        for (i = 0; i < 1080; i += 54) {
            HuVecCopyXYZ(&target->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            amp -= 0.025f;
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&target->scale, 1.0f, 1.0f, 1.0f);
        func_800FAC1C_name_81(&D_80105540_name_81);
        func_800FAB68_name_81(target, -1, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
    }
    func_800D8F3C_name_81(standIn);
    if (model != -1) {
        while (func_800DD3B4_name_81(model) == 0) {
            HuPrcVSleep();
        }
        func_800DD2BC_name_81(model);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80108550_duel01);
#endif

// duel b1: a partner drifts into the target and fades out (and back in)
void func_80109404_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec diff;
    Vec pos;
    GW_PLAYER *player;
    Process *process;
    s32 frames;
    s32 i;
    f32 scale;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    HuAudFXPlay(0x1F4);
    func_800D90D0_name_81(partner, 0, 2);
    func_8010615C_duel01(partner, target, player, &dest, &start, 0.0f);
    HuVecSubtract(&diff, &partner->coords, &dest);
    func_80106240_duel01();
    func_80106260_duel01(target, player, flags, 3.0f);
    dest.y -= 5.0f;
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 3.0f));
    frames = HuVecGetLength3F(&diff) / 3.0f;
    partner->flags |= 1;
    if (flags & 8) {
        func_801060D0_duel01(player, target, HuVecGetLength3F(&diff) / 3.0f, 20);
        for (i = 0; i < frames; i++) {
            func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 128) / frames);
            scale = 2.0f * i / frames + 1.0f;
            HuVecCopyXYZ(&partner->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        for (i = 128; i >= 0; i -= 10) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
    } else {
        for (i = 0; i < frames; i++) {
            func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 128) / 10);
            scale = 2.0f * i / frames + 1.0f;
            HuVecCopyXYZ(&partner->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopy3F(&pos, &partner->coords);
        pos.y += 10.0f;
        func_800DCE40_name_81(0x44, &pos, NULL, 1.0f);
        HuPrcSleep(10);
        func_800DCE40_name_81(0x44, &pos, NULL, 1.0f);
        HuPrcSleep(12);
        for (i = 128; i >= 0; i -= 10) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_8010554C_name_81 & 8, D_8010571C_name_81);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_8010554C_name_81 & 1, -1);
        }
    }
    if (!(D_80105718_name_81 & 0x10)) {
        func_800ED214_name_81(playerIndex);
        HuVecCopyXYZ(&partner->scale, 1.0f, 1.0f, 1.0f);
        for (i = 0; i < 256; i += 10) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF);
    }
}

// duel b1: a partner vanishes and reappears beside the target to strike (level 2: two blinks around the camera
// focus first); flag 0x10 in the level picks the fade-through attack instead
void func_80109888_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    Vec near;
    Vec dir;
    Vec mid;
    GW_PLAYER *player;
    Process *process;
    s32 seNo;
    s32 i;
    f32 baseAngle;
    s32 angle;
    Vec *midp;

    player = MBDGetPlayerStruct(targetIndex);
    process = HuPrcCurrentGet();
    seNo = -1;
    if (level & 0x10) {
        func_80109404_duel01(playerIndex, targetIndex, partner, target, flags, 1);
        return;
    }
    level &= ~0x10;
    func_800D90D0_name_81(partner, 0, 2);
    func_8010615C_duel01(partner, target, player, &near, &start, 6.0f);
    func_8010615C_duel01(partner, target, player, &dest, &start, 8.0f);
    func_80106240_duel01();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 255) / 10);
        func_8001F9E4_main(partner->omObj2->model[0], 0xFF - (i * 255) / 10);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0);
    func_8001F9E4_main(partner->omObj2->model[0], 0);
    HuPrcChildLink(process, func_80106260_duel01(target, player, flags, 3.0f));
    HuPrcChildWait();
    if (level == 2) {
        seNo = HuAudFXPlay(0x1DF);
        func_800EB708_name_81(&D_80105540_name_81, &partner->coords, &dir);
        baseAngle = func_800D76D0_name_81(&dir);
        angle = baseAngle + 90.0f;
        HuVecCopyXYZ(&partner->coords, D_80105540_name_81.x + sindf(angle) * 8.0f, D_80105540_name_81.y,
                     D_80105540_name_81.z + cosdf(angle) * 8.0f);
        func_800EB708_name_81(&partner->coords, &D_80105540_name_81, &partner->rot);
        for (i = 0; i <= 128; i += 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
        func_8001F9E4_main(partner->omObj2->model[0], 0);
        HuPrcVSleep();
        angle = baseAngle + -90.0f;
        HuVecCopyXYZ(&partner->coords, D_80105540_name_81.x + sindf(angle) * 8.0f, D_80105540_name_81.y,
                     D_80105540_name_81.z + cosdf(angle) * 8.0f);
        func_800EB708_name_81(&partner->coords, &D_80105540_name_81, &partner->rot);
        for (i = 0; i <= 128; i += 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            func_8001F9E4_main(partner->omObj1->model[0], i);
            func_8001F9E4_main(partner->omObj2->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(partner->omObj1->model[0], 0);
        func_8001F9E4_main(partner->omObj2->model[0], 0);
        HuPrcVSleep();
    }
    HuVecCopy3F(&partner->coords, &dest);
    func_800EB708_name_81(&partner->coords, &D_80105540_name_81, &partner->rot);
    for (i = 0; i < 255; i += 10) {
        func_8001F9E4_main(partner->omObj1->model[0], i);
        func_8001F9E4_main(partner->omObj2->model[0], i);
        HuPrcVSleep();
        if (i == 160) {
            if (seNo != -1) {
                HuAudFXStop((s16)seNo);
            }
            HuAudFXPlay(0x257);
        }
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0xFF);
    func_8001F9E4_main(partner->omObj2->model[0], 0xFF);
    HuPrcSleep((level == 1) ? 10 : 3);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &near, &partner->coords, 3));
    if (flags & 8) {
        if (level == 1) {
            func_801060D0_duel01(player, target, 0, 20);
        } else {
            func_801060D0_duel01(player, target, 0, 40);
        }
        HuPrcChildWait();
        if (level == 2) {
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
            HuPrcChildWait();
            HuPrcSleep(5);
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &near, &partner->coords, 3));
            HuPrcChildWait();
        }
    } else {
        HuPrcChildWait();
        midp = &mid;
        if (flags & 1) {
            HuVecAdd(midp, &target->coords, &partner->coords);
        } else {
            HuVecAdd(midp, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(midp, 0.5f, midp);
        mid.y += 3.0f;
        func_800DCE40_name_81(0x59, &mid, NULL, 1.0f);
        HuAudFXPlay(0x1E0);
        if (level == 2) {
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
            HuPrcChildWait();
            HuPrcSleep(5);
            HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &near, &partner->coords, 3));
            HuPrcChildWait();
            func_800DCE40_name_81(0x59, &mid, NULL, 1.0f);
            HuAudFXPlay(0x1E0);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &dest, &partner->coords, 10));
    HuPrcChildWait();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(partner->omObj1->model[0], 0xFF - (i * 255) / 10);
        func_8001F9E4_main(partner->omObj2->model[0], 0xFF - (i * 255) / 10);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0);
    func_8001F9E4_main(partner->omObj2->model[0], 0);
    func_800ED214_name_81(playerIndex);
    for (i = 0; i < 256; i += 10) {
        func_8001F9E4_main(partner->omObj1->model[0], i);
        func_8001F9E4_main(partner->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(partner->omObj1->model[0], 0xFF);
    func_8001F9E4_main(partner->omObj2->model[0], 0xFF);
}

// duel b2: local types and prototypes for func_8010A210..func_8010DB2C
#include "mallocblock.h"
typedef void (*DuelB2PartnerFunc)(s32, s32, Object *, Object *, s32, s32);

/* Sixteen sprite-billboard puffs (func_8010AFB4 creates, func_8010B130 moves). */
typedef struct DuelB2Puffs {
    /* 0x000 */ Vec pos[16];
    /* 0x0C0 */ Vec vel[16];
    /* 0x180 */ s16 active[16];
    /* 0x1A0 */ s16 spr[16];
    /* 0x1C0 */ s16 model[16];
    /* 0x1E0 */ s16 delay;
    /* 0x1E4 */ f32 life[16];
    /* 0x224 */ f32 scale[16];
} DuelB2Puffs; // sizeof 0x264

typedef struct DuelB2SprModel {
    /* 0x00 */ u16 model;
    /* 0x02 */ char unk_02[0x22];
} DuelB2SprModel; // sizeof 0x24

extern DuelB2SprModel *D_800CBB60_main;
extern Object *D_80119488_duel01;
extern omObjData *D_8011948C_duel01;
extern s32 D_80118718_duel01[];
extern f32 D_8011872C_duel01;
extern Object *D_80119490_duel01;

/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct DuelB2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 rotY;
} DuelB2HmfPart;

void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void *func_8001D33C_main(s16 model, char *name);

extern s32 D_80118710_duel01[];
extern s32 D_80105550_name_81;
extern s32 D_80105558_name_81;
extern s32 D_80105718_name_81;
extern s32 D_8010571C_name_81;
extern char D_80118E60_duel01[];

void func_800D90D0_name_81(Object *, s16, u16);
Process *func_800DCE40_name_81(s32 type, Vec *pos, Vec *vel, f32 scale);
s32 func_800DD1E0_name_81(s32 data, char *name);
void func_800DD2BC_name_81(s32 model); // defined with s16 model
void func_800DD2DC_name_81(s32 model, Vec *pos); // defined with s16 model
s32 func_800DD3B4_name_81(s32 model);
void func_800EB804_name_81(Object *obj);
void func_800ED214_name_81(s32 playerIndex);
void func_800EFABC_name_81(Object *);
Process *func_800FAB68_name_81(Object *obj, s32 amount, s32 motion, s32 flags, s32 seNo);
void func_800FAC1C_name_81(Vec *arg0);
void func_800FAD04_name_81(s32 arg0);
void func_800FADB4_name_81(void);
Process *func_800EC36C_name_81(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
void func_800FAE98_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_800FC888_name_81(s32 arg0);
void MBDBackTPLvlSet(u8 arg0);
Object *func_800D8B18_name_81(Object *obj);
void func_800EF7C8_name_81(Object *obj, f32 arg1, f32 arg2);
s32 func_800EF7D4_name_81(Object *obj);
s32 func_800EFE20_name_81(f32 arg0);
Process *func_800DCC8C_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed);
void func_800D918C_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void func_8010AAB0_duel01(Object *obj, s32 create);
void func_8010AD48_duel01(Object *obj);
void func_8010AFB4_duel01(void);
s16 func_8010B480_duel01(void);
void func_8010B4C0_duel01(void);
void func_8010B528_duel01(void);
void func_8010B53C_duel01(void);
void func_800FAE18_name_81(Object *arg0, s16 arg1, s16 arg2);
Process *func_801060D0_duel01(GW_PLAYER *player, Object *target, s32 arg2, s32 arg3);
void func_8010615C_duel01(Object *partner, Object *target, GW_PLAYER *player, Vec *arg3, Vec *arg4, f32 arg5);

u16 func_80014618_main(s16 index, u16 arg1);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
void func_80014850_main(s16 index);
void func_80016638_main(s32 index);
void func_800166D0_main(void);
void func_800D7828_name_81(Vec *vec);
void func_800D8F3C_name_81(Object *arg0);
void func_800FAC94_name_81(DuelB2PartnerFunc *arg0, DuelB2PartnerFunc *arg1);
void func_800EA7D4_name_81(void);
void func_800EA97C_name_81(void);
void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2); // defined with two parameters in E3CD0.c
void func_800EA46C_name_81(event_table_entry *arg0);
void func_800FC5A8_name_81(process_func arg0);
void func_800FC59C_name_81(s32 arg0);
void func_800FF640_name_81(u32 arg0);

void func_80106828_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80107188_duel01(s32, s32, Object *, Object *, s32, s32);
void func_801079B8_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80107EBC_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80109888_duel01(s32, s32, Object *, Object *, s32, s32);
void func_801084A4_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010CE68_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010D424_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010BCD4_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80108550_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010A210_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010B54C_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010B130_duel01(omObjData *obj);
void func_8010DCA8_duel01(void);
void func_8010DD3C_duel01(void);
void func_8010E348_duel01(void);
void func_8010EA74_duel01(void);
void func_8011390C_duel01(void);
s32 func_80118328_duel01(void);
extern event_table_entry D_80118914_duel01[];
extern event_table_entry D_80118DEC_duel01[];

#ifdef NON_MATCHING
// duel b2: masked 24 of 655: register choice around the &sp98/&sp78 arguments of HuVecSubtract (retail recomputes them per arm); logic checked block by block.
void func_8010A210_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec sp18;
    Vec sp28;
    Object *parts[16];
    Vec sp78;
    Vec sp88;
    Vec sp98;
    GW_PLAYER *player;
    Process *process;
    Object *obj;
    Object *extra2;
    Object *extra1;
    s32 i;
    s32 count;
    Vec *vel;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    extra2 = NULL;
    func_800FAD04_name_81(0xA);
    if (variant == 2) {
        extra2 = func_80106740_duel01(0x51);
        HuVecCopyXYZ(&extra2->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    extra1 = func_80106740_duel01(0x4C);
    HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
    HuPrcVSleep();
    if (target != NULL) {
        HuVecCopy3F(&sp18, &target->coords);
    } else {
        HuVecCopy3F(&sp18, &player->player_obj->coords);
    }
    func_800EB708_name_81(&partner->coords, &sp18, &partner->rot);
    obj = func_800D8010_name_81(0x57, 0);
    func_800D8F0C_name_81(obj);
    HuVecCopy3F(&obj->coords, &partner->coords);
    obj->coords.y += 5.0f;
    sp18.y += 5.0f;
    if (variant == 2) {
        HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
        for (i = 0; i < 16; i++) {
            parts[i] = func_800D8B18_name_81(obj);
            HuVecCopy3F(&parts[i]->coords, &obj->coords);
            func_800D8F0C_name_81(parts[i]);
            HuVecCopyXYZ(&parts[i]->scale, 0.5f, 0.5f, 0.5f);
        }
    }
    func_800FAE18_name_81(partner, 0, 0);
    HuPrcSleep(0x14);
    func_800D8E88_name_81(obj);
    func_800EF7C8_name_81(obj, 3.0f, -0.18f);
    HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &sp18, &obj->coords, 0x1E));
    if (variant == 2) {
        for (i = 0; i < 16; i++) {
            HuVecCopy3F(&sp28, &sp18);
            sp28.x += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            sp28.y += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            sp28.z += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            func_800EF7C8_name_81(parts[i], 3.0f, -0.18f);
            HuPrcChildLink(process, func_800EBF2C_name_81(&parts[i]->coords, &sp28, &parts[i]->coords, 0x1E));
        }
    }
    HuAudFXPlay(0x1E1);
    func_80106240_duel01();
    func_801062C0_duel01(target, player, flags, 0x1E);
    if (flags & 8) {
        HuVecCopy3F(&sp78, &target->coords);
        sp78.y += 5.0f;
        func_801060D0_duel01(player, target, 0x19, 0x28);
        if (variant == 1) {
            HuPrcSleep(0x20);
        } else {
            HuPrcSleep(0x14);
            func_800D8F0C_name_81(obj);
            HuVecCopy3F(&sp88, &obj->coords);
            sp88.y += obj->velocity.x;
            HuVecSubtract(&sp98, &target->coords, &sp88);
            HuVecMulScalar(&sp98, 0.05f, &sp98);
            func_800DCC8C_name_81(0x4E, &sp88, &sp98, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                func_800D8E88_name_81(parts[i]);
                parts[i]->velocity.z = func_800EFE20_name_81(100.0f) / 1000.0f + -0.18f - 0.05f;
                parts[i]->velocity.y += func_800EFE20_name_81(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
            HuPrcChildWait();
        }
        func_801067D4_duel01(extra1, &sp78);
        if (variant == 2) {
            func_801067D4_duel01(extra2, &sp78);
        }
    } else {
        if (variant != 1) {
            HuPrcSleep(0x14);
            func_800D8F0C_name_81(obj);
            HuVecCopy3F(&sp78, &obj->coords);
            sp78.y += obj->velocity.x;
            vel = &sp98;
            if (flags & 1) {
                HuVecSubtract(vel, &target->coords, &sp78);
            } else {
                HuVecSubtract(vel, &player->player_obj->coords, &sp78);
            }
            HuVecMulScalar(vel, 0.05f, vel);
            func_800DCC8C_name_81(0x4E, &sp78, vel, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                func_800D8E88_name_81(parts[i]);
                parts[i]->velocity.z = func_800EFE20_name_81(100.0f) / 1000.0f + -0.18f - 0.05f;
                parts[i]->velocity.y += func_800EFE20_name_81(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
        }
        HuPrcChildWait();
        if (flags & 1) {
            HuVecCopy3F(&sp78, &target->coords);
        } else {
            HuVecCopy3F(&sp78, &player->player_obj->coords);
        }
        sp78.y += 5.0f;
        func_801067D4_duel01(extra1, &sp78);
        if (variant == 2) {
            func_801067D4_duel01(extra2, &sp78);
        }
        func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    if (variant == 2) {
        while (TRUE) {
            count = 0;
            for (i = 0; i < 16; i++) {
                if (func_800EF7D4_name_81(parts[i]) == 0) {
                    count++;
                    func_800D8F0C_name_81(parts[i]);
                }
            }
            if (i == count) {
                break;
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 16; i++) {
            func_800D8F3C_name_81(parts[i]);
        }
    }
    func_800D8F3C_name_81(obj);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(arg0);
    HuPrcSleep(0x1E);
    func_800D8F3C_name_81(extra1);
    if (variant == 2) {
        func_800D8F3C_name_81(extra2);
    }
    func_800FADB4_name_81();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010A210_duel01);
#endif

/* A smoke puff (model 0x21) grows over obj; with create, model 8 (D_80119488) is made, then hidden at obj's place. */
void func_8010AAB0_duel01(Object *obj, s32 create) {
    Object *puff;
    f32 rot;
    f32 scale;

    if (create != 0) {
        D_80119488_duel01 = func_800D8010_name_81(8, D_80118718_duel01);
        func_800D8944_name_81(D_80119488_duel01);
        func_800D8F0C_name_81(D_80119488_duel01);
    } else {
        HuPrcSleep(3);
    }
    puff = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(puff->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(puff->omObj1->model[0], 0x800);
    func_8001C448_main(puff->omObj1->model[0]);
    HuVecCopy3F(&puff->coords, &obj->coords);
    puff->coords.y += 5.0f;
    HuAudFXPlay(0x1E3);
    rot = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale += 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    if (create != 0) {
        HuVecCopy3F(&D_80119488_duel01->coords, &obj->coords);
        HuVecCopy3F(&D_80119488_duel01->rot, &obj->rot);
        func_800D8E88_name_81(D_80119488_duel01);
        func_800D8F0C_name_81(obj);
    }
    for (; scale >= 1.0f; scale -= 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

/* Smoke puff over D_80119488: obj takes its place and hides, and that model is freed. */
void func_8010AD48_duel01(Object *obj) {
    Object *puff;
    f32 rot;
    f32 scale;

    puff = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(puff->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(puff->omObj1->model[0], 0x800);
    func_8001C448_main(puff->omObj1->model[0]);
    HuVecCopy3F(&puff->coords, &D_80119488_duel01->coords);
    puff->coords.y += 5.0f;
    if (GwSystem.current_board_index == 6) {
        HuAudFXPlay(0x1E3);
    }
    rot = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale += 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    HuVecCopy3F(&obj->coords, &D_80119488_duel01->coords);
    HuVecCopy3F(&obj->rot, &D_80119488_duel01->rot);
    func_800D8F3C_name_81(D_80119488_duel01);
    func_800D8E88_name_81(obj);
    obj->flags &= ~1;
    for (; scale >= 1.0f; scale -= 1.0) {
        HuVecCopyXYZ(&puff->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[puff->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(puff);
}

void func_8010AFB4_duel01(void) {
    DuelB2Puffs *puffs;
    void *data;
    s32 i;

    func_800142A0_main(0x1A);
    D_8011948C_duel01 = omAddObj(0x1F4, 0, 0, -1, func_8010B130_duel01);
    puffs = D_8011948C_duel01->data = HuMemAllocTag(sizeof(DuelB2Puffs), 0x7918);
    data = DataRead(0xB0047);
    for (i = 0; i < 16; i++) {
        if (i == 0) {
            puffs->spr[0] = HmfSprModelCreate(data, 0x1A0D, 8);
        } else {
            puffs->spr[i] = func_80014618_main(puffs->spr[0], 8);
        }
        func_800146DC_main(puffs->spr[i], 6, 0x180);
        puffs->model[i] = D_800CBB60_main[puffs->spr[i]].model;
        func_800147FC_main(puffs->spr[i], 0xFF, 0x40, 8);
        func_80014794_main(puffs->spr[i], 0xC8);
        func_8001C2FC_main(puffs->model[i], 0x70000000, 0x70000000);
    }
    DataClose(data);
    for (i = 0; i < 16; i++) {
        puffs->active[i] = 0;
    }
    D_8011948C_duel01->work[0] = 0;
    puffs->delay = 0;
}

void func_8010B130_duel01(omObjData *obj) {
    DuelB2Puffs *puffs = obj->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (puffs->active[i] != 0) {
            puffs->pos[i].x += puffs->vel[i].x;
            puffs->pos[i].y += puffs->vel[i].y;
            puffs->pos[i].z += puffs->vel[i].z;
            if (puffs->pos[i].y < 0.0f) {
                puffs->pos[i].y = 0.0f;
            }
            Hu3DModelPosSet(puffs->model[i], puffs->pos[i].x, puffs->pos[i].y, puffs->pos[i].z);
            puffs->life[i] -= 2.0f;
            if (puffs->life[i] <= 0.0f) {
                puffs->active[i] = 0;
                func_8001C258_main(puffs->model[i], 4, 4);
                func_800146DC_main(puffs->spr[i], 0, 0x80);
            }
            puffs->scale[i] += 0.02f;
            if (puffs->scale[i] >= 3.0f) {
                puffs->scale[i] = 3.0f;
            }
            Hu3DModelScaleSet(puffs->model[i], puffs->scale[i], puffs->scale[i], puffs->scale[i]);
        }
    }
    if (obj->work[0] == 1) {
        if (puffs->delay == 0) {
            for (i = 0; i < 16; i++) {
                if (puffs->active[i] == 0) {
                    break;
                }
            }
            if (i != 16) {
                puffs->active[i] = 1;
                puffs->delay = 1;
                puffs->vel[i].x = D_80119488_duel01->rot.x;
                puffs->vel[i].y = -0.8f;
                puffs->vel[i].z = D_80119488_duel01->rot.z;
                func_800D7828_name_81(&puffs->vel[i]);
                puffs->vel[i].x = 2.0f * puffs->vel[i].x;
                puffs->vel[i].y = 2.0f * puffs->vel[i].y;
                puffs->vel[i].z = 2.0f * puffs->vel[i].z;
                puffs->pos[i].x = D_80119488_duel01->rot.x * 10.0f + D_80119488_duel01->coords.x;
                puffs->pos[i].z = D_80119488_duel01->rot.z * 10.0f + D_80119488_duel01->coords.z;
                puffs->pos[i].y = D_80119488_duel01->coords.y + 6.0f;
                puffs->life[i] = 15.0f;
                puffs->scale[i] = 0.1f;
                func_8001C258_main(puffs->model[i], 4, 0);
                func_80014850_main(puffs->spr[i]);
                Hu3DModelPosSet(puffs->model[i], puffs->pos[i].x, puffs->pos[i].y, puffs->pos[i].z);
                Hu3DModelScaleSet(puffs->model[i], puffs->scale[i], puffs->scale[i], puffs->scale[i]);
                func_8001C8A8_main(puffs->model[i], 1);
            }
        } else {
            puffs->delay--;
        }
    }
}

s16 func_8010B480_duel01(void) {
    DuelB2Puffs *puffs = D_8011948C_duel01->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (puffs->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B4C0_duel01(void) {
    DuelB2Puffs *puffs = D_8011948C_duel01->data;
    s32 i;

    for (i = 0; i < 16; i++) {
        func_80016638_main(puffs->spr[i]);
    }
    omDelObj(D_8011948C_duel01);
    func_800166D0_main();
}

void func_8010B528_duel01(void) {
    D_8011948C_duel01->work[0] = 1;
}

void func_8010B53C_duel01(void) {
    D_8011948C_duel01->work[0] = 0;
}

void func_8010B54C_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec sp18;
    Vec sp28;
    Vec offset;
    Vec sp48;
    Vec sp58;
    GW_PLAYER *player;
    Process *process;
    Object *obj;
    f32 angle;
    f32 speed;
    f32 scale;
    Vec *mid;
    s32 effect;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effect = -1;
    func_800FAD04_name_81(0xB);
    if (flags != 0) {
        obj = func_800D8010_name_81(D_80118710_duel01[variant - 1], 0);
        func_8001C8E4_main(obj->omObj1->model[0], 0);
        func_8001C448_main(obj->omObj1->model[0]);
        func_800D8944_name_81(obj);
        func_800D8F0C_name_81(obj);
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
        func_8010AAB0_duel01(partner, 1);
        HuAudFXPlay(0x29C);
        func_800D90D0_name_81(D_80119488_duel01, 0, 2);
        HuVecCopy3F(&sp28, &D_80119488_duel01->coords);
        HuVecCopy3F(&sp48, &D_80119488_duel01->rot);
        if (target != NULL) {
            HuVecCopy3F(&sp18, &target->coords);
        } else {
            HuVecCopy3F(&sp18, &player->player_obj->coords);
        }
        func_800EB708_name_81(&D_80119488_duel01->coords, &sp18, &D_80119488_duel01->rot);
        angle = func_800D76D0_name_81(&D_80119488_duel01->rot) + 180.0f;
        if (variant == 1) {
            offset.x = sindf(angle) * (scale = 6.0f) * (speed = 2.5f);
        } else {
            offset.x = sindf(angle) * (scale = 6.0f) * (speed = 3.0f);
        }
        offset.y = 0.0f;
        offset.z = cosdf(angle) * scale * speed;
        HuVecAdd(&sp18, &sp18, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&D_80119488_duel01->coords, &sp18, &D_80119488_duel01->coords, 0.5f));
        func_80106240_duel01();
        func_80106260_duel01(target, player, flags, 0.8f);
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &D_80119488_duel01->coords);
        func_800EB708_name_81(&obj->coords, &sp18, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp18, &obj->coords, 0.5f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 1) {
            func_800D90D0_name_81(D_80119488_duel01, 3, 0);
            if (flags & 8) {
                func_801060D0_duel01(player, target, 0, 0x32);
            } else {
                HuPrcSleep(8);
                mid = &sp58;
                if (flags & 1) {
                    HuVecAdd(mid, &target->coords, &D_80119488_duel01->coords);
                } else {
                    HuVecAdd(mid, &player->player_obj->coords, &D_80119488_duel01->coords);
                }
                HuVecMulScalar(mid, 0.5f, mid);
                sp58.y += 5.0f;
                effect = func_800DD1E0_name_81(0xB0025, D_80118E60_duel01);
                func_800DD2DC_name_81(effect, &sp58);
                func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
                if (flags & 1) {
                    func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
                    HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
                }
                if (flags & 2) {
                    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
                    if (!(flags & 1)) {
                        HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
                    }
                }
            }
            func_800EFABC_name_81(D_80119488_duel01);
            func_800D90D0_name_81(D_80119488_duel01, -1, 2);
            HuPrcSleep(0x14);
        } else {
            func_800D90D0_name_81(D_80119488_duel01, 1, 0);
            HuPrcSleep(0x1E);
            func_8010AFB4_duel01();
            func_8010B528_duel01();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                func_801060D0_duel01(player, target, 0, 0x32);
            }
            func_800EFABC_name_81(D_80119488_duel01);
            func_800D90D0_name_81(D_80119488_duel01, 2, 2);
            if (!(flags & 8)) {
                func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
                if (flags & 1) {
                    func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
                }
                if (flags & 2) {
                    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
                }
            }
            HuPrcSleep(0x1E);
            func_8010B53C_duel01();
            while (func_8010B480_duel01() != 0) {
                HuPrcVSleep();
            }
            func_800D918C_name_81(D_80119488_duel01, -1, 0, 5, 2);
            HuPrcSleep(0xA);
            func_8010B4C0_duel01();
        }
        func_8010AD48_duel01(partner);
        func_800EB708_name_81(&partner->coords, &sp28, &partner->rot);
        func_800D90D0_name_81(partner, 0, 2);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &sp28, &partner->coords, 3.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &sp28, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp28, &obj->coords, 3.0f));
        HuPrcChildWait();
        func_800D90D0_name_81(partner, -1, 2);
        func_800ED214_name_81(arg0);
        func_800D8F3C_name_81(obj);
        if (variant == 1) {
            if (effect != -1) {
                while (func_800DD3B4_name_81(effect) == 0) {
                    HuPrcVSleep();
                }
                func_800DD2BC_name_81(effect);
            }
        }
    } else {
        func_800FAE18_name_81(partner, 0, 0);
        func_800EFABC_name_81(partner);
        func_8010AAB0_duel01(partner, 0);
        HuAudFXPlay(0x2A0);
        func_80105EB0_duel01((unkStruct04 *)partner);
        HuPrcSleep(0xA);
        func_800FAE18_name_81(partner, 1, 0);
        func_800EFABC_name_81(partner);
        func_800D90D0_name_81(partner, -1, 2);
    }
    func_800FADB4_name_81();
}

// duel b6
Process *func_800DCE10_name_81(s32 type, Vec *pos, Vec *vel, f32 scale, s32 delay);

/* Partner attack (level 1: a charge that knocks the player and partners down; otherwise a ground pound that squashes them). */
void func_8010BCD4_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec dest;
    Vec start;
    Vec diff;
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);
    Process *process = HuPrcCurrentGet();
    Object *front = NULL;
    Object *back = NULL;
    s32 frontNo = -1;
    s32 backNo = -1;
    s32 hitTime[3] = { -1, -1, -1 };
    Process *spinPrc[3] = { NULL, NULL, NULL };
    Vec pos;
    Object *obj;
    HmfModel *mdl;
    s32 i;
    f32 scale;
    f32 amp;

    func_800FAD04_name_81(8);
    obj = func_800D8010_name_81(D_80118710_duel01[variant - 1] & 0xFF, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    HuVecCopy3F(&start, &partner->coords);
    HuVecCopy3F(&dest, &player->player_obj->coords);
    func_800EB708_name_81(&partner->coords, &dest, &partner->rot);
    HuVecSubtract(&diff, &partner->coords, &player->player_obj->coords);
    hitTime[0] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
    if (hitTime[0] < 0) {
        hitTime[0] = 0;
    }
    if (player->stats.partners.frontID != -1) {
        front = MBDGetPlayerPartnerRef(playerNo, 0);
        frontNo = GwPlayer[playerNo].stats.partners.frontID;
        HuVecSubtract(&diff, &partner->coords, &front->coords);
        hitTime[1] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
        if (hitTime[1] < 0) {
            hitTime[1] = 0;
        }
    }
    if (player->stats.partners.backID != -1) {
        back = MBDGetPlayerPartnerRef(playerNo, 1);
        backNo = GwPlayer[playerNo].stats.partners.backID;
        HuVecSubtract(&diff, &partner->coords, &back->coords);
        hitTime[2] = HuVecGetLength3F(&diff) / 7.0f - 1.0f;
        if (hitTime[2] < 0) {
            hitTime[2] = 0;
        }
    }
    func_80106240_duel01();
    func_80106260_duel01(target, player, 0, 7.0f);
    if (variant == 1) {
        func_800FAE18_name_81(partner, 0, 2);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 7.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &dest, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 7.0f));
        for (i = 0; ; i++) {
            if (i == hitTime[0]) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1E5);
                spinPrc[0] = func_800D9668_name_81(player->player_obj, func_800D76D0_name_81(&player->player_obj->rot), 50.0f, -1);
                func_800EF7C8_name_81(player->player_obj, 7.0f, -0.4f);
                hitTime[0] = -1;
                HuVecCopy3F(&pos, &player->player_obj->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (i == hitTime[1]) {
                HuAudFXPlay((D_80105718_name_81 & 2) ? 0x1CE : 0x1E5);
                spinPrc[1] = func_800D9668_name_81(front, func_800D76D0_name_81(&front->rot), 50.0f, -1);
                func_800EF7C8_name_81(front, 7.0f, -0.4f);
                hitTime[1] = -1;
                HuVecCopy3F(&pos, &front->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (i == hitTime[2]) {
                HuAudFXPlay((D_80105718_name_81 & 4) ? 0x1CE : 0x1E5);
                spinPrc[2] = func_800D9668_name_81(back, func_800D76D0_name_81(&back->rot), 50.0f, -1);
                func_800EF7C8_name_81(back, 7.0f, -0.4f);
                hitTime[2] = -1;
                HuVecCopy3F(&pos, &back->coords);
                pos.y += 5.0f;
                func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
            }
            if (HuPrcChildGet(process) == 0) {
                break;
            }
            HuPrcVSleep();
        }
        if (hitTime[0] != -1) {
            spinPrc[0] = func_800D9668_name_81(player->player_obj, func_800D76D0_name_81(&player->player_obj->rot), 50.0f, -1);
            func_800EF7C8_name_81(player->player_obj, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &player->player_obj->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        if (hitTime[1] != -1) {
            spinPrc[1] = func_800D9668_name_81(front, func_800D76D0_name_81(&front->rot), 50.0f, -1);
            func_800EF7C8_name_81(front, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &front->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        if (hitTime[2] != -1) {
            spinPrc[2] = func_800D9668_name_81(back, func_800D76D0_name_81(&back->rot), 50.0f, -1);
            func_800EF7C8_name_81(back, 7.0f, -0.4f);
            HuVecCopy3F(&pos, &back->coords);
            pos.y += 5.0f;
            func_800DCE40_name_81(0x4A, &pos, NULL, 1.5f);
        }
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &start, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &start, &obj->coords, 3.0f));
        HuPrcChildWait();
        func_800D90D0_name_81(partner, -1, 2);
        func_800ED214_name_81(arg0);
        func_800D8F3C_name_81(obj);
        while (TRUE) {
            if (spinPrc[0] != NULL && func_800EF7D4_name_81(player->player_obj) == 0) {
                B1_MODEL_ROTY(player->player_obj, 0.0f, mdl);
                omDelPrcObj(spinPrc[0]);
                spinPrc[0] = NULL;
            }
            if (spinPrc[1] != NULL && func_800EF7D4_name_81(front) == 0) {
                B1_MODEL_ROTY(front, 0.0f, mdl);
                omDelPrcObj(spinPrc[1]);
                spinPrc[1] = NULL;
            }
            if (spinPrc[2] != NULL && func_800EF7D4_name_81(back) == 0) {
                B1_MODEL_ROTY(back, 0.0f, mdl);
                omDelPrcObj(spinPrc[2]);
                spinPrc[2] = NULL;
            }
            if (spinPrc[0] == NULL && spinPrc[1] == NULL && spinPrc[2] == NULL) {
                break;
            }
            HuPrcVSleep();
        }
    } else {
        dest.y = 20.0f;
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &dest, &partner->coords, 7.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &dest, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &dest, &obj->coords, 7.0f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        partner->velocity.x = partner->coords.y;
        partner->coords.y = 0.0f;
        HuPrcSleep(10);
        HuAudFXPlay(0x1E6);
        for (i = 0; i < 20; i++) {
            f32 grow = i / 10.0f + 1.0f;
            HuVecCopyXYZ(&partner->scale, grow, grow, grow);
            HuPrcVSleep();
        }
        HuPrcSleep(10);
        if (front != NULL) {
            func_800DCE10_name_81(0x4C, &front->coords, NULL, 2.0f, 4);
        }
        if (back != NULL) {
            func_800DCE10_name_81(0x4C, &back->coords, NULL, 2.0f, 4);
        }
        func_800DCE10_name_81(0x51, &player->player_obj->coords, NULL, 3.0f, 4);
        func_800EF7C8_name_81(partner, -1.0f, -2.0f);
        player->stat |= 4;
        for (i = 0; i < 6; i++) {
            scale = (10 - i) * 0.9f / 10.0f + 0.1f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuVecCopyXYZ(&player->player_obj->scale, 1.0f, scale, 1.0f);
            if (front != NULL) {
                HuVecCopyXYZ(&front->scale, 1.0f, scale, 1.0f);
            }
            if (back != NULL) {
                HuVecCopyXYZ(&back->scale, 1.0f, scale, 1.0f);
            }
            HuPrcVSleep();
        }
        func_801064C8_duel01(playerNo, 0);
        func_800EF800_name_81(partner);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, func_8010645C_duel01(10, 1));
        HuPrcChildWait();
        HuPrcSleep(10);
        for (i = 20; i >= 0; i -= 2) {
            f32 grow = i / 10.0f + 1.0f;
            HuVecCopyXYZ(&partner->scale, grow, grow, grow);
            HuPrcVSleep();
        }
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &start, &partner->coords, 3.0f));
        func_800D8E88_name_81(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        func_800EB708_name_81(&obj->coords, &start, &obj->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &start, &obj->coords, 3.0f));
        HuPrcChildWait();
        func_800D90D0_name_81(partner, -1, 2);
        func_800ED214_name_81(arg0);
        func_800D8F3C_name_81(obj);
        func_801064C8_duel01(playerNo, 1);
        amp = 1.0f;
        for (i = 0; i < 1080; i += 54) {
            HuVecCopyXYZ(&player->player_obj->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            if (front != NULL) {
                HuVecCopyXYZ(&front->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            }
            if (back != NULL) {
                HuVecCopyXYZ(&back->scale, 1.0f, sindf(i) * amp + 1.0f, 1.0f);
            }
            amp -= 0.025f;
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
        if (front != NULL) {
            HuVecCopyXYZ(&front->scale, 1.0f, 1.0f, 1.0f);
        }
        if (back != NULL) {
            HuVecCopyXYZ(&back->scale, 1.0f, 1.0f, 1.0f);
        }
        player->stat &= ~4;
    }
    func_800FAC1C_name_81(&D_80105540_name_81);
    if (flags & 0x20) {
        func_800FAB68_name_81(player->player_obj, 4, 3, D_80105718_name_81 & 1, -1);
        if (front != NULL) {
            func_800FAB68_name_81(front, 4, 1, D_80105718_name_81 & 2, frontNo);
        }
        if (back != NULL) {
            func_800FAB68_name_81(back, 4, 1, D_80105718_name_81 & 4, backNo);
        }
    } else if (flags & 0x10) {
        func_800FAB68_name_81(player->player_obj, 2, 3, D_80105718_name_81 & 1, -1);
        if (front != NULL) {
            func_800FAB68_name_81(front, 2, 1, D_80105718_name_81 & 2, frontNo);
        }
        if (back != NULL) {
            func_800FAB68_name_81(back, 2, 1, D_80105718_name_81 & 4, backNo);
        }
    } else {
        func_800FAB68_name_81(player->player_obj, 1, 3, D_80105718_name_81 & 1, -1);
        if (front != NULL) {
            func_800FAB68_name_81(front, 1, 1, D_80105718_name_81 & 2, frontNo);
        }
        if (back != NULL) {
            func_800FAB68_name_81(back, 1, 1, D_80105718_name_81 & 4, backNo);
        }
    }
    func_800FADB4_name_81();
}

void func_8010CE68_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Vec sp18;
    Vec sp28;
    s32 effects[2];
    GW_PLAYER *player;
    Process *process;
    Object *obj;
    Object *obj2;
    Object *extra1;
    Object *extra2;
    s32 i;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effects[0] = 0x4D;
    effects[1] = 0x53;
    obj2 = NULL;
    extra1 = NULL;
    extra2 = NULL;
    func_800FAD04_name_81(6);
    if (variant == 2) {
        extra1 = func_80106740_duel01(0x4C);
        HuPrcVSleep();
        extra2 = func_80106740_duel01(0x53);
        HuPrcVSleep();
    }
    if (target != NULL) {
        HuVecCopy3F(&sp18, &target->coords);
    } else {
        HuVecCopy3F(&sp18, &player->player_obj->coords);
    }
    func_800EB708_name_81(&partner->coords, &sp18, &partner->rot);
    obj = func_800D8010_name_81(0x58, 0);
    func_800D8F0C_name_81(obj);
    HuPrcVSleep();
    if (variant == 2) {
        obj2 = func_800D8010_name_81(0x53, 0);
        func_800D8F0C_name_81(obj2);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A3);
    func_800FAE98_name_81(partner, variant - 1, 0, 5, 2);
    if (variant == 1) {
        HuPrcSleep(7);
    } else {
        HuPrcSleep(0xF);
    }
    func_800D8E88_name_81(obj);
    HuVecCopy3F(&obj->coords, &partner->coords);
    obj->velocity.x = 5.0f;
    func_800D8F0C_name_81(obj);
    func_80106240_duel01();
    func_800D8E88_name_81(obj);
    HuPrcChildLink(process, func_800EC36C_name_81(&obj->coords, &sp18, &obj->coords, 4.0f));
    HuPrcChildLink(process, func_80106260_duel01(target, player, flags, 4.0f));
    HuVecCopy3F(&sp28, &partner->rot);
    func_800D7828_name_81(&sp28);
    HuVecMulScalar(&sp28, 6.0f, &sp28);
    HuVecAdd(&sp28, &sp28, &obj->coords);
    sp28.y += 5.0f;
    func_800DCE40_name_81(0x4E, &sp28, NULL, 0.5f);
    if (variant == 2) {
        func_800D8E88_name_81(obj2);
        func_8001C258_main(obj2->omObj1->model[0], 0x180, 0);
        func_8001C8E4_main(obj2->omObj1->model[0], 0x800);
        HuVecCopy3F(&obj2->coords, &obj->coords);
        obj2->velocity.x = 5.0f;
        HuPrcChildLink(process, func_800EC36C_name_81(&obj2->coords, &sp18, &obj2->coords, 4.0f));
        HuAudFXPlay(0x1DA);
    } else {
        HuAudFXPlay(0x1D9);
    }
    if (flags & 8) {
        func_801060D0_duel01(player, target, 0, 0x14);
        HuPrcChildWait();
        func_800FC888_name_81(3);
        func_800D8F0C_name_81(obj);
        if (variant == 2) {
            func_800D8F0C_name_81(obj2);
        }
    } else {
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 2) {
            func_800D8F0C_name_81(obj2);
        }
        if (flags & 1) {
            HuVecCopy3F(&sp28, &target->coords);
        } else {
            HuVecCopy3F(&sp28, &player->player_obj->coords);
        }
        sp28.y += obj->velocity.x;
        if (variant == 1) {
            func_800DCE40_name_81(effects[0], &sp28, NULL, 2.0f);
        } else {
            func_801067D4_duel01(extra1, &sp28);
            HuVecCopyXYZ(&extra1->scale, 2.0f, 2.0f, 2.0f);
            func_801067D4_duel01(extra2, &sp28);
            HuVecCopyXYZ(&extra2->scale, 2.0f, 2.0f, 2.0f);
        }
        func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            if (variant == 2) {
                if (D_80105718_name_81 & 8) {
                    HuAudFXPlay(0x1EF);
                } else {
                    HuAudFXPlay(0x1EE);
                }
            } else {
                if (D_80105718_name_81 & 8) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (variant == 2) {
                if (!(flags & 1)) {
                    if (D_80105718_name_81 & 1) {
                        HuAudFXPlay(0x1EF);
                    } else {
                        HuAudFXPlay(0x1EE);
                    }
                }
            } else if (!(flags & 1)) {
                if (D_80105718_name_81 & 1) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (variant == 2) {
            for (i = 0; i < 3; i++) {
                MBDBackTPLvlSet(0xFF);
                HuPrcVSleep();
                MBDBackTPLvlSet(0x40);
                HuPrcVSleep();
            }
        }
    }
    func_800D8F3C_name_81(obj);
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(arg0);
    if (variant == 2) {
        HuPrcSleep(0x1E);
        func_800D8F3C_name_81(extra1);
        func_800D8F3C_name_81(extra2);
        func_800D8F3C_name_81(obj2);
    }
    func_800FADB4_name_81();
}

void func_8010D424_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    Object *obj;
    Vec sp18;
    Vec sp28;
    Vec sp38;
    GW_PLAYER *player;
    Process *process;
    Object *extra;
    s32 effect;
    Vec *partnerPos;
    Vec *mid;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effect = -1;
    extra = NULL;
    if (variant == 1) {
        extra = func_80106740_duel01(0x45);
    }
    obj = func_800D8010_name_81(D_80118710_duel01[variant - 1], 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    partnerPos = &partner->coords;
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(partner, 0, 2);
    func_8010615C_duel01(partner, target, player, &sp18, &sp28, 7.5f);
    func_80106240_duel01();
    func_80106260_duel01(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(partnerPos, &sp18, partnerPos, 3.0f));
    func_800D8E88_name_81(obj);
    func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
    HuVecCopy3F(&obj->coords, partnerPos);
    func_800EB708_name_81(&obj->coords, &sp18, &obj->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp18, &obj->coords, 3.0f));
    HuPrcChildWait();
    func_800D8F0C_name_81(obj);
    if (variant == 1) {
        func_800FAE18_name_81(partner, 0, 2);
    } else {
        func_800FAE18_name_81(partner, 1, 0);
    }
    if (flags & 8) {
        if (variant == 2) {
            HuPrcSleep(10);
        }
        func_801060D0_duel01(player, target, 0, 0x1E);
        if (variant == 1) {
            HuPrcSleep(0x1E);
        } else {
            func_800EFABC_name_81(partner);
        }
    } else {
        HuPrcSleep(variant == 1 ? 10 : 0x11);
        mid = &sp38;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &partner->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        sp38.y += 5.0f;
        if (variant == 1) {
            func_800DCE40_name_81(0x4B, &sp38, NULL, 2.0f);
            func_800EB804_name_81(extra);
            func_801067D4_duel01(extra, &sp38);
        } else {
            effect = func_800DD1E0_name_81(0xB0024, D_80118E60_duel01);
            func_800DD2DC_name_81(effect, &sp38);
            HuAudFXPlay(0x1DB);
            HuAudFXPlay(0x1F1);
        }
        func_800FAC1C_name_81((Vec *)&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
        if (variant == 2) {
            func_800EFABC_name_81(partner);
        } else {
            HuPrcSleep(10);
        }
    }
    func_800EB708_name_81(&partner->coords, &sp28, &partner->rot);
    func_800D90D0_name_81(partner, 0, 2);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &sp28, &partner->coords, 3.0f));
    func_800D8E88_name_81(obj);
    func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
    HuVecCopy3F(&obj->coords, &partner->coords);
    func_800EB708_name_81(&obj->coords, &sp28, &obj->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &sp28, &obj->coords, 3.0f));
    HuPrcChildWait();
    func_800D90D0_name_81(partner, -1, 2);
    func_800ED214_name_81(arg0);
    func_800D8F3C_name_81(obj);
    if (variant == 2) {
        if (effect != -1) {
            while (func_800DD3B4_name_81(effect) == 0) {
                HuPrcVSleep();
            }
            func_800DD2BC_name_81(effect);
        }
    } else {
        func_800D8F3C_name_81(extra);
    }
    func_800FADB4_name_81();
}

void func_8010D95C_duel01(void) {
    DuelB2PartnerFunc funcs1[12] = {
        func_80106828_duel01, func_80107188_duel01, func_801079B8_duel01, func_80107EBC_duel01,
        func_80109888_duel01, func_801084A4_duel01, func_8010CE68_duel01, func_8010D424_duel01,
        func_8010BCD4_duel01, func_80108550_duel01, func_8010A210_duel01, func_8010B54C_duel01,
    };
    DuelB2PartnerFunc funcs2[12] = {
        NULL, NULL, NULL, NULL, func_80109888_duel01, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(funcs1, funcs2);
}

void func_8010D9F4_duel01(void) {
    omInitObjMan(0xA0, 0x50);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    func_800FC260_name_81(0x18, 0x241, 0);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    func_8010DCA8_duel01();
    func_8010DD3C_duel01();
    func_8010E348_duel01();
    func_8010EA74_duel01();
    func_8010D95C_duel01();
}

// entrypoint 2
void func_8010DA84_duel01(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9F4_duel01();
    func_800EA46C_name_81(D_80118914_duel01);
    func_800EA46C_name_81(D_80118DEC_duel01);
    func_800FC5A8_name_81(func_8011390C_duel01);
    func_800FC59C_name_81((s32)func_80118328_duel01);
    func_800FF640_name_81(0);
}

// entrypoint 3
void func_8010DB00_duel01(void) {
    Hu3DCamInit(1);
    func_8010D9F4_duel01();
    func_800FF640_name_81(1);
}

/* Process: spins the "neji" (screw) part of D_80119490's model forever. */
void func_8010DB2C_duel01(void) {
    DuelB2HmfPart *part;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], HmfModelData[D_80119490_duel01->omObj1->model[0]].unk02, "neji", 0x4C, 0x46);
        part = func_8001D33C_main(D_80119490_duel01->omObj1->model[0], "neji");
        angle += D_8011872C_duel01;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        part->rotY = angle;
        HuPrcVSleep();
    }
}

// duel b3: declarations for func_8010DC04_duel01..func_80110C3C_duel01
SpaceData *MBDMasuGet(s16 spaceIdx);
void func_8010DB2C_duel01(void);
void func_8010DC04_duel01(void);
void func_8010DDEC_duel01(void);
void func_8010E1B4_duel01(void);
void func_8010E3F8_duel01(void);
void func_8010E7C0_duel01(void);

/* The bell model part func_8001D33C_main returns: only its +0x14 float is used here. */
typedef struct Duel01Part {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} Duel01Part;

extern char D_80118F18_duel01[]; /* "bell" (rodata; func_80111DFC_duel01 uses it too) */
extern s32 D_80118730_duel01[];
extern s16 D_80118740_duel01;
extern s16 D_80118742_duel01;
extern s16 D_80118748_duel01;
extern s16 D_8011874A_duel01;
extern s16 D_80118750_duel01[2];
extern s16 D_80118754_duel01[2][2];
extern Process *D_80118744_duel01;
extern Process *D_8011874C_duel01;
extern Process *D_80119494_duel01;
extern Object *D_80119498_duel01;
extern f32 D_8011949C_duel01;
extern Object *D_801194A0_duel01;
extern f32 D_801194A4_duel01;
extern s32 D_8011875C_duel01;
extern Object *D_801194A8_duel01;
extern Object *D_801194AC_duel01[2];

/* A weighted choice: an entry is taken when a roll of 100 falls under its chance; value -1 ends a list. */
typedef struct Duel01Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel01Weight;

extern s8 D_80118760_duel01[]; /* value, chance pairs */
extern Duel01Weight *D_8011885C_duel01[8]; /* per character */
extern s32 D_8011889C_duel01;
extern s32 D_80118894_duel01;

typedef B1UnkBoard4 Duel01SprGrp; /* ovl_81's sprite group (UnkBoard4 there) */
s32 func_800F37B8_name_81(s16 playerIndex);
void func_800E0310_name_81(u8 *output, s32 count);
extern u16 D_800C9520_main[];
s32 func_8010EDA0_duel01(void);
void func_8010EFBC_duel01(void);
void func_8010F12C_duel01(void);
void func_8010DF68_duel01(Vec *pos);
void func_8010E008_duel01(void);
void func_8010E2CC_duel01(void);
void func_8010E2F8_duel01(void);
void func_8010E574_duel01(Vec *pos);
void func_8010E614_duel01(void);
void func_8010E8D8_duel01(void);
void func_8010E904_duel01(void);
void func_800EB140_name_81(s32 arg0, s32 arg1);
void func_800EB7BC_name_81(Vec *out);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
void func_800EF800_name_81(Object *obj);
Object *func_800F8050_name_81(s32 partnerID);
void func_800FC8DC_name_81(Object *arg0);
extern s32 D_8011887C_duel01[2][3]; /* per player: three space ids (splat labels 7E/82/86 are low halves) */
extern Object *D_80118898_duel01;

void func_8010DC04_duel01(void) {
    s16 model = D_80119490_duel01->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80118F18_duel01, 0x4C, 0x46);
    ((Duel01Part *)func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010DCA8_duel01(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, D_80118730_duel01);
    func_800D8944_name_81(obj);
    D_80119490_duel01 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x1D)->coords);
    func_8010DC04_duel01();
    D_80119494_duel01 = omAddPrcObj(func_8010DB2C_duel01, 0xA, 0, 0);
    omPrcSetStatBit(D_80119494_duel01, 0xA0);
}

void func_8010DD3C_duel01(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_80119498_duel01 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80118740_duel01);
    to = MBDMasuGet(D_80118742_duel01);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010DDEC_duel01(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_8011949C_duel01;
        sincosdf(rot, &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF68_duel01(Vec *pos) {
    Process *process;
    s32 *angle;

    D_8011949C_duel01 = 10.0f;
    process = omAddPrcObj(func_8010DDEC_duel01, 0xA, 0, 0x40);
    D_80118744_duel01 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80119498_duel01->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E008_duel01(void) {
    HmfModel *mdl;

    if (D_80118744_duel01 != NULL) {
        while (D_8011949C_duel01 >= 0.0f) {
            D_8011949C_duel01 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80118744_duel01);
        sincosdf(0.0f, &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}


INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F18_duel01);

void func_8010E1B4_duel01(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80119498_duel01->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80119498_duel01->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80119498_duel01);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80119498_duel01->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80119498_duel01->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2CC_duel01(void) {
    omAddPrcObj(func_8010E1B4_duel01, 0xA, 0, 0);
}

void func_8010E2F8_duel01(void) {
    func_8001C814_main(D_80119498_duel01->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80119498_duel01->omObj1->model[0], 1.0f);
}

void func_8010E348_duel01(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_801194A0_duel01 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80118748_duel01);
    to = MBDMasuGet(D_8011874A_duel01);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010E3F8_duel01(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_801194A4_duel01;
        sincosdf(rot, &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E574_duel01(Vec *pos) {
    Process *process;
    s32 *angle;

    D_801194A4_duel01 = 10.0f;
    process = omAddPrcObj(func_8010E3F8_duel01, 0xA, 0, 0x40);
    D_8011874C_duel01 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_801194A0_duel01->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E614_duel01(void) {
    HmfModel *mdl;

    if (D_8011874C_duel01 != NULL) {
        while (D_801194A4_duel01 >= 0.0f) {
            D_801194A4_duel01 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_8011874C_duel01);
        sincosdf(0.0f, &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010E7C0_duel01(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_801194A0_duel01->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_801194A0_duel01->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801194A0_duel01);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_801194A0_duel01->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_801194A0_duel01->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8D8_duel01(void) {
    omAddPrcObj(func_8010E7C0_duel01, 0xA, 0, 0);
}

void func_8010E904_duel01(void) {
    func_8001C814_main(D_801194A0_duel01->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_801194A0_duel01->omObj1->model[0], 1.0f);
}

void func_8010E954_duel01(s16 no) {
    s32 pad[2]; /* retail's frame is 8 bytes larger */
    Object *obj;
    SpaceData *from;

    if (D_801194AC_duel01[no] == NULL) {
        if (D_801194A8_duel01 == NULL) {
            obj = func_800D8010_name_81(0x2D, 0);
            func_800D8944_name_81(obj);
            D_801194A8_duel01 = obj;
        } else {
            obj = func_800D8B18_name_81(D_801194A8_duel01);
        }
        D_801194AC_duel01[no] = obj;
        obj->flags |= 2;
        func_8001C814_main(obj->omObj1->model[0], 2, 1);
        HuVecCopy3F(&obj->coords, &MBDMasuGet(D_80118750_duel01[no])->coords);
        from = MBDMasuGet(D_80118754_duel01[no][0]);
        func_800EB708_name_81(&from->coords, &MBDMasuGet(D_80118754_duel01[no][1])->coords,
                              &obj->rot);
    }
}

void func_8010EA74_duel01(void) {
    s32 i;

    D_801194A8_duel01 = NULL;
    for (i = 0; i < 2; i++) {
        D_801194AC_duel01[i] = NULL;
        func_8010E954_duel01(i);
    }
}

void func_8010EAD4_duel01(s32 no) {
    if (D_8011875C_duel01 == 0) {
        HuAudFXPlay(0x1C4);
    }
    D_8011875C_duel01 = 1;
    func_8001C814_main(D_801194AC_duel01[no]->omObj1->model[0], 5, 0);
    HuPrcSleep(10);
}

void func_8010EB44_duel01(s32 no) {
    func_8001C814_main(D_801194AC_duel01[no]->omObj1->model[0], 1, 4);
    D_8011875C_duel01 = 0;
}

// referent (masked 20-23): retail reads GwSystem.current_player_index as a scalar global; with a scalar extern
// only register allocation remains (masked 17); with the struct field our GCC keeps its address in s0
#ifdef NON_MATCHING
s32 func_8010EB88_duel01(void) {
    GW_PLAYER *rival;
    s32 chance;
    s32 dist;

    rival = MBDGetPlayerStruct((s8)(GwSystem.current_player_index ^ 1));
    chance = (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
    if (mbWalkNum < 4) {
        if (GwSystem.current_player_index == 0) {
            if (rival->clink == 0) {
                dist = rival->cidx - 8;
                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            }
        } else if (rival->clink == 1) {
            dist = rival->cidx - 8;
            if (dist == mbWalkNum) {
                chance = 0;
            }
            if (dist < mbWalkNum) {
                chance += 20;
            }
        }
    }
    return chance;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB88_duel01);
#endif

s32 func_8010EC78_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 tbl[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };
    s32 prize = player->stats.prize.gamblePrize;

    if (prize == -1) {
        return 0;
    }
    return tbl[prize];
}

s32 func_8010ED20_duel01(s32 no) {
    s16 tbl[12] = { 70, 10, 50, 20, 30, 90, 10, 10, 20, 80, 60, 30 };

    return tbl[no];
}

s32 func_8010EDA0_duel01(void) {
    GW_PLAYER *player;
    s32 result;
    s32 roll;
    s32 i;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    result = -1;
    roll = func_800EFE20_name_81(10.0f);
    switch (player->cpu_difficulty) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            /* Both prize bytes (gamblePrize, duelNo) unset, read as one big-endian word. */
            if ((*(u32 *)&player->stats.prize.gamblePrize & 0xFFFF0000) != 0xFFFF0000) {
                if (roll < 6) {
                    if (player->stats.prize.gamblePrize != -1) {
                        result = player->stats.prize.gamblePrize;
                    }
                    if (player->stats.prize.duelNo != -1) {
                        result = player->stats.prize.duelNo;
                    }
                    break;
                }
                if (roll < 8) {
                    for (i = 0; D_80118760_duel01[i * 2] != -1; i++) {
                        if (D_80118760_duel01[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    result = D_80118760_duel01[i * 2];
                    break;
                }
            }
            for (i = 0; D_8011885C_duel01[player->chr][i].value != -1; i++) {
                if (D_8011885C_duel01[player->chr][i].chance > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            result = D_8011885C_duel01[player->chr][i].value;
            break;
    }
    if (result == -1) {
        result = func_800EFE20_name_81(12.0f);
    }
    if (result < 0 || result >= 12) {
        result = 0;
    }
    return result;
}

// float constants: retail keeps 64.0f and 3.0f out of registers (loop hoisting), frame 8 bytes larger (masked 24)
#ifdef NON_MATCHING
void func_8010EFBC_duel01(void) {
    s32 *data;
    f32 angle1;
    f32 angle2;
    s32 win;
    s16 r;
    s16 g;
    s16 b;

    r = 0x43;
    data = HuPrcCurrentGet()->user_data;
    angle2 = 0.0f;
    angle1 = 90.0f;
    win = *data;
    func_8005FBF8_main(*data, 0x43, 0x80, 1);
    while (TRUE) {
        if (D_8011889C_duel01 != 0) {
            g = sindf(angle1) * 128.0f;
            if (g < 0) {
                g = -g;
            }
            angle1 += 6.0f;
            if (angle1 > 360.0f) {
                angle1 -= 360.0f;
            }
            b = sindf(angle2) * 64.0f;
            if (b < 0) {
                b = -b;
            }
            angle2 += 3.0f;
            if (angle2 > 360.0f) {
                angle2 -= 360.0f;
            }
            func_8005FBF8_main(win, (u8)r, (u8)g, (u8)b);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EFBC_duel01);
#endif

void func_8010F12C_duel01(void) {
    s16 pos[3][2] = { { 160, -80 }, { 160, -160 }, { 160, -80 } };
    s32 files[6] = { 0x13011C, 0x13011F, 0x13011E, 0x13011D, 0x130120, 0x13011E }; /* [player * 3 + i] */
    u8 order[32];
    s32 player;
    s32 msg;
    s16 win;
    Process *proc;
    s32 kind;
    s32 cpuChoice;
    s32 cpuCount;
    s32 wait;
    s32 n;
    s32 i;
    s32 *data;
    void *file;
    Duel01SprGrp *grp;
    u8 last;

    player = *(s32 *)HuPrcCurrentGet()->user_data;
    proc = NULL;
    cpuChoice = -1;
    mbItemBtnF = 0;
    if (player == 0) {
        kind = (u8)GwSystem.playerIndexVisitingBowser;
    } else {
        kind = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    win = func_8005A968_main(60, -160, 200, 160, 0, 0);
    func_8005FBF8_main(win, 0x43, 5, 1);
    func_8005BEE0_main(win, 0xC0);
    if (kind == 2) {
        proc = omAddPrcObj(func_8010EFBC_duel01, 0xA, 0, 0x40);
        data = HuMemMemoryAlloc(proc->heap, 0x10);
        proc->user_data = data;
        *data = win;
    }
    grp = func_800F4528_name_81(3, 0);
    for (i = 0; i < 3; i++) {
        file = DataRead(files[player * 3 + i]);
        grp->unk_0C[i] = func_80055810_main(file);
        func_80055024_main(grp->unk_0A, i, grp->unk_0C[i], 0);
        HuSprPriSet(grp->unk_0A, i, i + 1);
        HuSprAttrSet(grp->unk_0A, i, 0);
        func_80054904_main(grp->unk_0A, i, pos[i][0], pos[i][1]);
        DataClose(file);
        if (i == 2) {
            func_80055140_main(grp->unk_0A, 2, func_800EFE20_name_81(12.0f), 0);
        }
    }
    for (wait = 90; wait < 180; wait += 15) {
        for (i = 0; i < 3; i++) {
            func_80054904_main(grp->unk_0A, i, pos[i][0], (pos[i][1] + 215) + sindf(wait) * -200.0f);
        }
        func_8005BA90_main(win, 60, sindf(wait) * -200.0f + 55.0f);
        HuPrcVSleep();
    }
    for (wait = 0; wait < 180; wait += 20) {
        for (i = 0; i < 3; i++) {
            func_80054904_main(grp->unk_0A, i, pos[i][0], (pos[i][1] + 215) + sindf(wait) * -50.0f);
        }
        func_8005BA90_main(win, 60, sindf(wait) * -50.0f + 55.0f);
        HuPrcVSleep();
    }
    for (wait = 0; wait < 180; wait += 20) {
        for (i = 0; i < 3; i++) {
            func_80054904_main(grp->unk_0A, i, pos[i][0], (pos[i][1] + 215) + sindf(wait) * -30.0f);
        }
        func_8005BA90_main(win, 60, sindf(wait) * -30.0f + 55.0f);
        HuPrcVSleep();
    }
    if (func_800F37B8_name_81(CUR_PLAYER) != 0) {
        cpuCount = func_800EFE20_name_81(10.0f) + 10;
        cpuChoice = func_8010EDA0_duel01();
        if (kind == 2 && cpuChoice != -1) {
            cpuCount = 5;
        }
    } else {
        cpuCount = -1;
    }
    msg = func_800E1824_name_81(0x13, 0xB9, 0);
    D_8011889C_duel01 = 1;
    last = 0xFF;
    n = 11;
    do {
        func_800E0310_name_81(order, n);
        if (last == order[0]) {
            last = order[n];
            order[n] = order[0];
            order[0] = last;
            last = 0xFF;
        }
        for (i = 0; i <= n; i++) {
            HuAudFXPlay(0x1C8);
            last = order[i];
            func_80055140_main(grp->unk_0A, 2, order[i], 0);
            func_800550F4_main(grp->unk_0A, 2, 1);
            wait = (kind == 2) ? 15 : 1;
            while (TRUE) {
                if (cpuCount > 0) {
                    if (kind != 2 || cpuChoice == -1 || cpuChoice == order[i]) {
                        if (--cpuCount == 0) {
                            break;
                        }
                    }
                } else if (D_800C9520_main[GwPlayer[player].pad] & 0x8000) {
                    break;
                }
                HuPrcVSleep();
                if (--wait == 0) {
                    break;
                }
            }
            if (wait != 0) {
                break;
            }
        }
    } while (i == n + 1);
    {
        s32 sfx[12] = { 0x25A, 0x25B, 0x298, 0x256, 0x257, 0x25D, 0x2A3, 0x2A4, 0x2A2, 0x1E7, 0x2A5, 0x2A0 };

        HuAudFXPlay(sfx[order[i]]);
    }
    D_8011889C_duel01 = 0;
    if (player == 0) {
        if (kind == 2) {
            GwSystem.playerIndexVisitingBowser &= 0xFF00;
        } else {
            GwSystem.playerIndexVisitingBowser++;
        }
    } else if (kind == 2) {
        GwSystem.playerIndexVisitingBowser &= 0xFF;
    } else {
        GwSystem.playerIndexVisitingBowser += 0x100;
    }
    HuPrcSleep(30);
    D_80118894_duel01 = order[i];
    func_800E1854_name_81(msg);
    if (proc != NULL) {
        omDelPrcObj(proc);
    }
    func_800F4584_name_81(grp);
    func_8005F364_main(win);
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

// register allocation (the -1, walk target and partner/bell registers) and one branch-likely (masked 14)
#ifdef NON_MATCHING
s32 func_8010F99C_duel01(s32 no) {
    Vec dir;
    Vec cam;
    Vec target;
    Object *fx[4];
    Vec unused; /* retail's frame has 0x18 bytes here and 8 after offs */
    s32 pad[2];
    SpaceData *start;
    SpaceData *goal;
    GW_PLAYER *player;
    Vec *pos;
    Object *partner;
    Object *bell;
    Process *proc;
    s32 *data;
    s32 i;
    s32 kind;

    start = MBDMasuGet(D_8011887C_duel01[no][1]);
    goal = MBDMasuGet(D_8011887C_duel01[no][2]);
    player = MBDGetPlayerStruct(no);
    if (no == 0) {
        kind = (u8)GwSystem.playerIndexVisitingBowser;
    } else {
        kind = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    if (kind == 2) {
        func_800EB140_name_81(0x16, 0x1F07);
    }
    HuVecCopy3F(&cam, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&target, &start->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 3.0f));
    func_800F3880_name_81(-1, 0, 2);
    func_800EB708_name_81(&player->player_obj->coords, &start->coords,
                          &player->player_obj->rot);
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EC1E4_name_81(&player->player_obj->coords, &start->coords, &player->player_obj->coords, 3.0f));
    HuPrcChildWait();
    func_800EB708_name_81(&player->player_obj->coords, &goal->coords,
                          &player->player_obj->rot);
    func_800F3880_name_81(-1, 7, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x1C9);
    if (no == 0) {
        func_8010DF68_duel01(&player->player_obj->coords);
    } else {
        func_8010E574_duel01(&player->player_obj->coords);
    }
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    D_80118894_duel01 = -1;
    proc = omAddPrcObj(func_8010F12C_duel01, 0xA, 0, 0x40);
    data = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = data;
    *data = no;
    pos = &MBDMasuGet(D_8011887C_duel01[no][0])->coords;
    func_800EB708_name_81(&player->player_obj->coords, pos, &player->player_obj->rot);
    func_800F3880_name_81(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&player->player_obj->coords, pos, &player->player_obj->coords, 2.0f));
    HuPrcChildWait();
    func_800F3880_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&dir);
    func_800EBC60_name_81(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    if (D_80118894_duel01 == -1) {
        do {
            HuPrcVSleep();
        } while (D_80118894_duel01 == -1);
    }
    HuVecCopy3F(&target, &goal->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &target, &cam, 2.0f));
    HuPrcChildWait();
    if (no == 0) {
        func_8010E008_duel01();
    } else {
        func_8010E614_duel01();
    }
    bell = func_800D8010_name_81(0x35, 0);
    func_800D8F0C_name_81(bell);
    partner = func_800F8050_name_81(D_80118894_duel01);
    HuVecCopy3F(&partner->coords, &goal->coords);
    partner->coords.y += 26.0f;
    func_800D8F0C_name_81(partner);
    HuAudFXPlay(0x1CA);
    if (no == 0) {
        func_8010E2CC_duel01();
    } else {
        func_8010E8D8_duel01();
    }
    HuPrcSleep(20);
    {
        Vec offs[4] = { { 4.0f, 4.0f, -4.0f }, { -4.0f, -2.0f, -4.0f }, { 4.0f, 0.0f, 4.0f }, { -4.0f, 2.0f, 4.0f } };
        s32 pad2[2];

        for (i = 0; i < 4; i++) {
            fx[i] = func_800D8B18_name_81(bell);
            func_8001C8E4_main(fx[i]->omObj1->model[0], 0x800);
            func_8001C258_main(fx[i]->omObj1->model[0], 0x180, 0);
            func_8001C814_main(fx[i]->omObj1->model[0], 2, 0);
            HuVecCopy3F(&fx[i]->coords, &goal->coords);
            fx[i]->velocity.x = 26.0f;
            fx[i]->coords.x += offs[i].x;
            fx[i]->coords.y += offs[i].y;
            fx[i]->coords.z += offs[i].z;
            if (i == 3) {
                func_800D8E88_name_81(partner);
            }
            HuPrcSleep(4);
        }
    }
    HuPrcSleep(25);
    for (i = 0; i < 4; i++) {
        func_800D8F3C_name_81(fx[i]);
    }
    func_800D8F3C_name_81(bell);
    func_800FC888_name_81(5);
    func_800FC8DC_name_81(partner);
    pos = &MBDMasuGet(D_8011887C_duel01[no][1])->coords;
    func_800EB708_name_81(&partner->coords, pos, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    func_800EF7C8_name_81(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&partner->coords, pos, &partner->coords, 20));
    HuPrcChildWait();
    func_800EF800_name_81(partner);
    if (no == 0) {
        func_8010E2F8_duel01();
    } else {
        func_8010E904_duel01();
    }
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&cam);
    HuVecCopy3F(&cam, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&cam, &player->player_obj->coords, &cam, 2.0f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
    D_80118898_duel01 = partner;
    return D_80118894_duel01;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FB4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F99C_duel01);
#endif

// duel b7
typedef struct DuelPadMask {
    u8 mask[4];
} DuelPadMask;
typedef struct DuelChoiceTbl {
    s16 choice[4];
} DuelChoiceTbl;
extern const DuelPadMask D_80118FE4_duel01;
extern const DuelChoiceTbl D_80118FE8_duel01;
extern s16 D_8010555C_name_81;
void func_800FB524_name_81(s32);
void func_800EB1D8_name_81(s32 arg0, s32 arg1);
s32 func_800EED50_name_81(void);
s32 func_8010EB88_duel01(void);
s32 func_8010F99C_duel01(s32 no);
typedef struct DuelB7VecTbl {
    Vec v[3];
} DuelB7VecTbl;
extern const DuelB7VecTbl D_80118FF0_duel01; /* smoke puff offsets around a partner leaving */
extern s32 D_80101A1C_name_81[];             /* partner name messages, by partner id */
void func_800EAFC4_name_81(s32 mess);
void func_800EE0D0_name_81(s32 arg0);
void func_800F85A4_name_81(s32 playerIndex, s32 frontOrBackIndex);
void func_800F8358_name_81(s32 playerIndex);
void func_800F57B0_name_81(s32 playerNo);
void func_800F5E2C_name_81(s32 playerNo);
void func_800ECF1C_name_81(s32 playerNo, Vec *front, Vec *back);
void func_800ED118_name_81(s32 playerNo, Vec *front, Vec *back);
void func_800F8418_name_81(s32 playerIndex, s32 partnerID, s32 frontOrBackIndex);
void func_800F821C_name_81(s32 playerIndex, s32 partnerNo);
s32 func_800F89D0_name_81(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, s16 arg3);
void func_800F5BB4_name_81(s32 playerIndex);
void func_800F5EB0_name_81(s32 playerIndex);
void func_800F7BB4_name_81(s32 playerNo, s32 set);
void func_800F7D94_name_81(s32 playerNo, s32 set);
void func_800FBDD4_name_81(void);

/* The partner pipe space: with no partners the player gets one from the roulette; otherwise the player
   (or the CPU) picks the front or back partner to send away and gets a new one in its place. A matching
   pair of partners then powers both up (or, for ids 5 and 9, costs them). */
void func_80110068_duel01(s32 no) {
    Vec pos;
    DuelPadMask padMask;
    DuelChoiceTbl choice;
    DuelB7VecTbl ofs;
    Vec frontPos;
    Vec backPos;
    Vec frontRot;
    Vec backRot;
    GW_PLAYER *player;
    Object *partner;
    s32 i;
    s16 partnerID;
    s16 result;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    padMask = D_80118FE4_duel01;
    choice = D_80118FE8_duel01;
    func_800DB3E0_name_81(no);
    func_800F38DC_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&pos);
    func_800EBC60_name_81(&player->player_obj->rot, &pos, &player->player_obj->rot, 8);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuPrcChildWait();
    if ((player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2)
        || (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2)) {
        func_800EAFC4_name_81(0x1F00);
        Duel_PowerDownPartners(no);
    }
    func_800EDD50_name_81(&MBDMasuGet(D_8011887C_duel01[no][0])->coords);
    func_800EE0D0_name_81(0);
    func_800EDF48_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F01);
    func_800F3880_name_81(-1, 6, 0);
    func_800E14D8_name_81(no, 10);
    func_800F7378_name_81(no, 10);
    HuPrcSleep(30);
    func_800F3880_name_81(-1, -1, 2);
    if ((*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        func_800EB140_name_81(0x16, 0x1F04);
        partnerID = func_8010F99C_duel01(no);
    loop1:
        func_800EB1D8_name_81(0x16, 0x1F05);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (func_8010EB88_duel01() >= func_800EFE20_name_81(100.0f)
                || func_8010ED20_duel01(partnerID) >= func_800EFE20_name_81(100.0f)) {
                choice.choice[GwPlayer[no].pad] = 0x400;
                func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            }
            choice.choice[GwPlayer[no].pad] = -0x8000;
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        result = func_8005E1D8_main(D_8010555C_name_81, 0, 1);
        choice.choice[GwPlayer[no].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (result == 2) {
            func_801059D0_duel01();
            goto loop1;
        }
        if (result == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(no);
            mbItemBtnF = 1;
            goto loop1;
        }
    } else {
        func_800EB140_name_81(0x16, 0x1F02);
    loop2:
        func_800EB1D8_name_81(0x16, 0x1F03);
        if (func_800F37B8_name_81(no) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[no].pad]);
            choice.choice[GwPlayer[no].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (player->stats.partners.backID == -1 || func_8010EC78_duel01() >= func_800EFE20_name_81(100.0f)) {
                choice.choice[GwPlayer[no].pad] = 0x400;
                func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            }
            choice.choice[GwPlayer[no].pad] = -0x8000;
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        result = func_8005E1D8_main(D_8010555C_name_81, 0, 1);
        choice.choice[GwPlayer[no].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (result == 2) {
            func_801059D0_duel01();
            goto loop2;
        }
        if (result == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(no);
            mbItemBtnF = 1;
            goto loop2;
        }
        partner = MBDGetPlayerPartnerRef(no, result);
        if (partner != NULL) {
            HuVecCopy3F(&pos, &partner->coords);
            pos.y += 2.0f;
            ofs = D_80118FF0_duel01;
            for (i = 0; i < 3; i++) {
                HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[i], 3.0f));
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            func_800D8F0C_name_81(partner);
            HuPrcChildWait();
            func_800F85A4_name_81(no, result);
            func_800F8358_name_81(no);
            func_800F57B0_name_81(no);
            func_800F5E2C_name_81(no);
        }
        partnerID = func_8010F99C_duel01(no);
    }
    func_800ECF1C_name_81(no, &frontPos, &backPos);
    func_800ED118_name_81(no, &frontRot, &backRot);
    func_800D918C_name_81(D_80118898_duel01, 0, 0, 5, 2);
    if (GwSystem.current_board_index == 2) {
        func_800EF7C8_name_81(D_80118898_duel01, 2.0f, -0.2f);
    }
    if (result == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        func_800EB708_name_81(&D_80118898_duel01->coords, &frontPos, &D_80118898_duel01->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80118898_duel01->coords, &frontPos, &D_80118898_duel01->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80118898_duel01->rot, &frontRot, &D_80118898_duel01->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        func_800EB708_name_81(&D_80118898_duel01->coords, &backPos, &D_80118898_duel01->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80118898_duel01->coords, &backPos, &D_80118898_duel01->coords, 3.0f));
        HuPrcChildWait();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80118898_duel01->rot, &backRot, &D_80118898_duel01->rot, 7));
    }
    HuPrcChildWait();
    func_800D8F3C_name_81(D_80118898_duel01);
    func_800F8418_name_81(no, partnerID, result);
    func_800F821C_name_81(no, result);
    func_800F89D0_name_81(no, 0, -1, 2);
    func_800F89D0_name_81(no, 1, -1, 2);
    func_800ED214_name_81(no);
    func_800F5BB4_name_81(no);
    func_800F5EB0_name_81(no);
    if (player->stats.partners.frontID == player->stats.partners.backID) {
        switch (player->stats.partners.frontID) {
        case 5:
        case 9:
            func_800EB49C_name_81(0x16, 0x1F09, D_80101A1C_name_81[player->stats.partners.frontID], 0, 0, 0, 0);
            func_800EB58C_name_81();
            func_800EB58C_name_81();
            func_800EB58C_name_81();
            func_800EB278_name_81();
            func_800EB29C_name_81();
            player->stats.partners.frontCost--;
            player->stats.partners.backCost--;
            HuAudFXPlay(0x205);
            func_800F7BB4_name_81(no, 1);
            func_800F7D94_name_81(no, 1);
            break;
        default:
            func_800EB49C_name_81(0x16, 0x1F08, D_80101A1C_name_81[player->stats.partners.frontID], 0, 0, 0, 0);
            func_800EB58C_name_81();
            func_800EB278_name_81();
            func_800EB29C_name_81();
            player->stats.partners.frontPower++;
            player->stats.partners.backPower++;
            HuAudFXPlay(0x205);
            func_800F7BB4_name_81(no, 0);
            func_800F7D94_name_81(no, 0);
            break;
        }
        /* board flag: player 1 or 2 has a matching pair */
        if (no == 0) {
            GWBoardFlagSet(0x12);
        } else {
            GWBoardFlagSet(0x13);
        }
    }
    func_800FBDD4_name_81();
    func_800EB140_name_81(0x16, 0x1F06);
    func_800EDF78_name_81();
    func_800EE468_name_81(0);
    func_800EDDBC_name_81();
    func_800DADA0_name_81(no);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
}

void func_80110B7C_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(0);
    }
}

void func_80110BD8_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(1);
    }
}







INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE8_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FF0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119010_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119014_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801190FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801191E4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801192CC_duel01);

// duel b7
extern u8 D_80119014_duel01[]; /* window strings: the starting partner choices (SJIS) */
extern u8 D_801190FC_duel01[];
extern u8 D_801191E4_duel01[];
extern u8 D_801192CC_duel01[];
void func_8008A120_main(f32 *mtx, f32 angle); // defined with Matrix4f (f32[4][4])
void func_800F8108_name_81(s32 playerIndex);
void func_800F82EC_name_81(s32 playerIndex);
void func_800EADBC_name_81(s32, u32, u32, u32, u32, u32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);

/* Window selection of one starting partner; retail reads the current player's pad even for player 2's picks. */
#define DUEL_B7_PICK(win, mess, cur, padMask, choice, buf, result, last)                                         \
    win = func_80061188_main(-1, 0x50, 0x50, 0xA0, 0x69, 0);                                                     \
    func_8005B63C_main(win, 0x40, 0x40);                                                                         \
    func_80061388_main(win);                                                                                     \
    func_8005FBA4_main(buf, mess);                                                                               \
    func_8005B43C_main(win, (s32)buf, -1, -1);                                                                   \
    while (func_8005E0C0_main(win) != 0) {                                                                       \
        HuPrcVSleep();                                                                                           \
    }                                                                                                            \
    if (func_800F37B8_name_81(cur) == 0) {                                                                       \
        func_8005FE54_main(win, padMask.mask[GwPlayer[cur].pad]);                                                \
        choice.choice[GwPlayer[cur].pad] = -1;                                                                   \
        func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);              \
    } else {                                                                                                     \
        if (GwPlayer[cur].chr == 5) {                                                                            \
            choice.choice[GwPlayer[cur].pad] = 0x400;                                                            \
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81()); \
        }                                                                                                        \
        choice.choice[GwPlayer[cur].pad] = -0x8000;                                                              \
        func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81()); \
        func_8005B63C_main(win, 2, 2);                                                                           \
    }                                                                                                            \
    result = (s16)func_8005E1D8_main(win, 0, last);                                                                 \
    func_80061A5C_main(win, 0);                                                                                  \
    func_8005F364_main(win)

#ifdef NON_MATCHING // duel b7: masked 0 but for register allocation: one extra callee-saved register ($s8), so every $s register is one higher
/* Turn start: on the first turn both players pick their starting partners; partner 6 may hand over 2-4
   coins; from the second turn the player pays the partners' upkeep, or loses them when short of coins. */
void func_80110C3C_duel01(void) {
    u8 buf[0x200];
    DuelPadMask padMask;
    DuelChoiceTbl choice;
    Vec dir;
    Vec rot;
    Vec camPos;
    char str[8];
    Vec puffPos;
    Vec pos;
    DuelB7VecTbl ofs;
    s32 cur;
    GW_PLAYER *player;
    Object *partner;
    Object *coin;
    s16 win;
    s32 front;
    s32 back;
    s32 count;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    f32 scale;
    s32 cost;
    s32 coins;

    cur = GwSystem.current_player_index;
    player = MBDGetPlayerStruct(cur);
    padMask = D_80118FE4_duel01;
    choice = D_80118FE8_duel01;
    if (cur == 0 && GwSystem.current_turn == 1 && (*(u32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
        DUEL_B7_PICK(win, D_80119014_duel01, cur, padMask, choice, buf, front, 1);
        DUEL_B7_PICK(win, D_801190FC_duel01, cur, padMask, choice, buf, back, 1);
        func_800F8418_name_81(cur, front, 0);
        func_800F8418_name_81(cur, back, 1);
        func_800F8108_name_81(cur);
        func_800ED214_name_81(cur);
        func_800F5BB4_name_81(cur);
        func_800F5EB0_name_81(cur);
        if (D_800D5546_main[0] & 0x1000) {
            Duel_PowerUpPartners(cur);
        }
        DUEL_B7_PICK(win, D_801191E4_duel01, cur, padMask, choice, buf, front, 0);
        DUEL_B7_PICK(win, D_801192CC_duel01, cur, padMask, choice, buf, back, 0);
        func_800F8418_name_81(1, front, 0);
        func_800F8418_name_81(1, back, 1);
        func_800F8108_name_81(1);
        func_800ED214_name_81(1);
        func_800F5BB4_name_81(1);
        func_800F5EB0_name_81(1);
        if (D_800D5546_main[0] & 0x1000) {
            Duel_PowerUpPartners(1);
        }
    }
    if ((player->stats.partners.frontID == 6 || player->stats.partners.backID == 6) && func_800EFE20_name_81(100.0f) < 34) {
        count = func_800EFE20_name_81(3.0f) + 2;
        func_800FAD04_name_81(6);
        if (player->stats.partners.backID == 6) {
            partner = MBDGetPlayerPartnerRef(cur, 1);
        } else {
            partner = MBDGetPlayerPartnerRef(cur, 0);
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
        HuPrcChildWait();
        HuVecCopy3F(&camPos, &player->player_obj->coords);
        func_800FC888_name_81(4);
        func_800FC8C4_name_81(&camPos);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&camPos, &partner->coords, &camPos, 2.0f));
        HuPrcChildWait();
        func_800EB708_name_81(&partner->coords, &player->player_obj->coords, &dir);
        HuVecCopy3F(&rot, &partner->rot);
        func_800EBC60_name_81(&partner->rot, &dir, &partner->rot, 8);
        HuPrcSleep(8);
        for (i = 0; i < 31; i += 5) {
            func_8008A120_main(HmfModelData[partner->omObj1->model[0]].mtx, -i);
            partner->velocity.x += 1.0f;
            HuPrcVSleep();
        }
        func_800FAE98_name_81(partner, 2, 0, 5, 2);
        coin = NULL;
        for (i = 0; i < count; i++) {
            if (coin != NULL) {
                for (j = 6; j < 12; j++) {
                    scale = j / 6.0f + 0.5f;
                    if (scale > 1.0f) {
                        scale = 1.0f;
                    }
                    HuVecCopyXYZ(&coin->scale, scale, scale, scale);
                    func_8008A2A0_main(HmfModelData[coin->omObj1->model[0]].mtx, j * 40);
                    HuPrcVSleep();
                }
            } else {
                HuPrcSleep(3);
                HuVecCopy3F(&puffPos, &partner->coords);
                puffPos.y += 12.0f;
                func_800DCE40_name_81(0x4E, &puffPos, NULL, 1.0f);
                HuPrcSleep(1);
            }
            if (coin != NULL) {
                func_800F7378_name_81(cur, 1);
                func_800D8F3C_name_81(coin);
                HuVecCopy3F(&puffPos, &partner->coords);
                puffPos.y += 12.0f;
                func_800DCE40_name_81(0x4E, &puffPos, NULL, 1.0f);
            }
            coin = func_800D8010_name_81(0x1C, NULL);
            coin->velocity.x = 13.0f;
            HuVecCopy3F(&coin->coords, &partner->coords);
            HuVecCopyXYZ(&coin->scale, 0.0f, 0.0f, 0.0f);
            func_800EF7C8_name_81(coin, 2.0f, -0.2f);
            func_800EBF2C_name_81(&coin->coords, &player->player_obj->coords, &coin->coords, 10);
            HuAudFXPlay(0x200);
            for (k = 0; k < 6; k++) {
                scale = k / 6.0f;
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                HuVecCopyXYZ(&coin->scale, scale, scale, scale);
                func_8008A2A0_main(HmfModelData[coin->omObj1->model[0]].mtx, k * 40);
                HuPrcVSleep();
            }
        }
        for (l = 6; l < 12; l++) {
            scale = l / 6.0f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuVecCopyXYZ(&coin->scale, scale, scale, scale);
            func_8008A2A0_main(HmfModelData[coin->omObj1->model[0]].mtx, l * 40);
            HuPrcVSleep();
        }
        func_800F7378_name_81(cur, 1);
        func_800D8F3C_name_81(coin);
        func_800D90D0_name_81(partner, -1, 2);
        for (i = 30; i >= 0; i -= 10) {
            func_8008A120_main(HmfModelData[partner->omObj1->model[0]].mtx, -i);
            partner->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        partner->velocity.x = 0.0f;
        func_800EBC60_name_81(&partner->rot, &rot, &partner->rot, 4);
        HuPrcSleep(4);
        func_800FADB4_name_81();
        sprintf(str, "%d", count);
        func_800EADBC_name_81(0x4F0C, (u32)str, 0, 0, 0, 0);
        func_800EAF70_name_81(cur);
        func_800EAF94_name_81();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&camPos, &player->player_obj->coords, &camPos, 2.0f));
        HuPrcChildWait();
        func_800FC888_name_81(1);
    }
    if (GwSystem.current_turn != 1) {
        cost = func_800F8980_name_81(cur);
        coins = GwPlayer[cur].coin;
        if (coins < cost) {
            func_800E14D8_name_81(cur, -coins);
            func_800F7378_name_81(cur, -coins);
            HuPrcSleep(30);
            for (i = 0; i < 2; i++) {
                partner = MBDGetPlayerPartnerRef(cur, i);
                if (partner != NULL) {
                    HuVecCopy3F(&pos, &partner->coords);
                    pos.y += 2.0f;
                    ofs = D_80118FF0_duel01;
                    for (j = 0; j < 3; j++) {
                        HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &ofs.v[j], 3.0f));
                    }
                    func_800D8F0C_name_81(partner);
                }
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            HuPrcChildWait();
            func_800F85A4_name_81(cur, 0);
            func_800F85A4_name_81(cur, 1);
            func_800F82EC_name_81(cur);
            func_800F57B0_name_81(cur);
            func_800F5E2C_name_81(cur);
            func_800EAFC4_name_81(0x1E01);
            return;
        }
        if (cost != 0) {
            func_800E14D8_name_81(cur, -cost);
            func_800F7378_name_81(cur, -cost);
            HuPrcSleep(30);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110C3C_duel01);
#endif

void func_80111DFC_duel01(void) {
    Vec pos;
    char buf[8];
    GW_PLAYER *player;
    SpaceData *space;
    DuelB4HmfPart *part;
    f32 ofs;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    space = MBDMasuGet(0x1D);
    func_800DB3E0_name_81(system->current_player_index);
    func_800F38DC_name_81(-1, -1, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuVecCopy3F(&pos, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &space->coords, &pos, 4.0f));
    func_800D90D0_name_81(D_80119490_duel01, 2, 0);
    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0],
                       HmfModelData[D_80119490_duel01->omObj1->model[0]].unk02, D_80118F18_duel01, 0x4C, 0x46);
    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], D_80119490_duel01->omObj1->motion[2],
                       D_80118F18_duel01, 0x4C, 0x46);
    i = 0;
    ((DuelB4HmfPart *)func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
    while (!(func_800D9234_name_81(D_80119490_duel01) & 1)) {
        if (++i == 8) {
            HuAudFXPlay(0x1C5);
        }
        HuPrcVSleep();
    }
    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0],
                       HmfModelData[D_80119490_duel01->omObj1->model[0]].unk02, D_80118F18_duel01, 0x4C, 0x46);
    part = func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01);
    part->unk_14 = (GwSystem.bank_coins - 5) * 60;
    HuAudFXPlay(0x1C7);
    for (ofs = 0.0f; ofs >= -60.0f; ofs -= 4.0f) {
        part->unk_14 = (GwSystem.bank_coins - 5) * 60 + ofs;
        HuPrcVSleep();
    }
    HuPrcChildWait();
    if (GwSystem.bank_coins != 0) {
        GwSystem.bank_coins--;
    }
    func_8010DC04_duel01();
    D_8011872C_duel01 = 12.0f;
    if (GwSystem.bank_coins != 0) {
        HuAudFXPlay(0x207);
        func_800D918C_name_81(D_80119490_duel01, 0, 0, 5, 2);
        func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], D_80119490_duel01->omObj1->motion[0],
                           D_80118F18_duel01, 0x4C, 0x46);
        func_8001C92C_main(D_80119490_duel01->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(0x18);
        func_800D90D0_name_81(D_80119490_duel01, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        func_800D918C_name_81(D_80119490_duel01, 1, 0, 5, 2);
        func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], D_80119490_duel01->omObj1->motion[1],
                           D_80118F18_duel01, 0x4C, 0x46);
        func_8001C92C_main(D_80119490_duel01->omObj1->model[0], 1.0f);
        func_8010DC04_duel01();
        func_800F74E4_name_81(-1);
        func_800EEC40_name_81(&pos);
        if (system->current_turn < 11) {
            sprintf(buf, "20");
        } else if (system->current_turn >= 20) {
            sprintf(buf, "40");
        } else {
            sprintf(buf, "30");
        }
        HuAudFXPlay(0x2A7);
        func_800EB49C_name_81(0x15, 0x1F30, (s32)buf, 0, 0, 0, 0);
        func_800EB58C_name_81();
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80118414_duel01();
        D_80100F44_name_81 = D_80119490_duel01;
        func_800FD620_name_81();
        HuPrcSleep(-1);
    }
    D_8011872C_duel01 = 3.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &player->player_obj->coords, &pos, 4.0f));
    func_800DADA0_name_81(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
}

// duel b4: the current player's partner effect: restore the player's star field (duel HP) to 5
void func_801123E8_duel01(void) {
    GW_PLAYER *player;
    void *win;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FF);
    win = func_800FFC2C_name_81(-1, 3, 5);
    func_800EE74C_name_81(3);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    func_8004ACE0_main(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    GwPlayer[GwSystem.current_player_index].star = 5;
}

void func_801124D8_duel01(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

// duel b4: lose up to 10 coins
void func_80112514_duel01(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 coins = GwPlayer[system->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(system->current_player_index, -coins);
    func_800F7378_name_81(system->current_player_index, -coins);
    HuPrcSleep(30);
}

// duel b4: gain 10 coins
void func_80112590_duel01(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 10);
    func_800F7378_name_81(system->current_player_index, 10);
    HuPrcSleep(30);
}

// duel b4: warp the current player to their start space
void func_801125CC_duel01(void) {
    s8 link;
    s8 idx;
    s8 backLink = -1;
    s8 backIdx = -1;

    func_800E9F4C_name_81(MBDGetCurrentPlayerIndex() == 0 ? 0x1C : 0x1B, &link, &idx);
    func_80118320_duel01(&backLink, &backIdx);
    func_800E24AC_name_81(link, idx, backLink, backIdx);
    func_800ED214_name_81(GwSystem.current_player_index);
    func_80110068_duel01(MBDGetCurrentPlayerIndex());
}

// duel b4: swap space: a growing spin swaps the two players' places
void func_8011264C_duel01(void) {
    void *win[2];
    GW_PLAYER *player;
    Object *obj;
    f32 rot;
    f32 scale;
    s32 cur;
    s32 other;

    cur = MBDGetCurrentPlayerIndex();
    other = (cur + 1) & 1;
    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1F9);
    win[0] = func_800FFC2C_name_81(0, 3, 5);
    win[1] = func_800FFC2C_name_81(1, 3, 5);
    rot = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800EA898_name_81(other, cur);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    for (; scale >= 1.0f; scale -= 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win[0]);
    func_800FFCCC_name_81(win[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB49C_name_81(0x16, 0x1F2B, D_80101200_name_81[GwPlayer[GwSystem.current_player_index ^ 1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    func_8004ACE0_main(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
}

// duel b4: partner power-up space: each partner flashes and gains power
void func_801129C8_duel01(void) {
    Object *partner[2];
    GW_PLAYER *player;
    void *win;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    win = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(0);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partner[0] = NULL;
    partner[1] = NULL;
    if (player->stats.prize.gamblePrize != -1) {
        partner[0] = func_800D8010_name_81(0x38, 0);
        func_800D8944_name_81(partner[0]);
        HuVecCopy3F(&partner[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
        func_8001C814_main(partner[0]->omObj1->model[0], 2, 0);
    }
    if (player->stats.prize.duelNo != -1) {
        partner[1] = func_800D8010_name_81(0x38, 0);
        func_800D8944_name_81(partner[1]);
        HuVecCopy3F(&partner[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
        func_8001C814_main(partner[1]->omObj1->model[0], 2, 0);
    }
    HuAudFXPlay(0x1FA);
    if (partner[0] != NULL) {
        func_800EFABC_name_81(partner[0]);
        func_800D8F3C_name_81(partner[0]);
    }
    if (partner[1] != NULL) {
        func_800EFABC_name_81(partner[1]);
        func_800D8F3C_name_81(partner[1]);
    }
    Duel_PowerUpPartners(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(0));
    HuPrcChildWait();
    func_800EDDBC_name_81();
}

// duel b4: partner power-down space
void func_80112BB4_duel01(void) {
    Object *partner[2];
    GW_PLAYER *player;
    void *win;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FB);
    win = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(4);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partner[0] = NULL;
    partner[1] = NULL;
    if (player->stats.prize.gamblePrize != -1) {
        partner[0] = func_800D8010_name_81(0x3A, 0);
        func_800D8944_name_81(partner[0]);
        HuVecCopy3F(&partner[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
        func_8001C814_main(partner[0]->omObj1->model[0], 2, 0);
    }
    if (player->stats.prize.duelNo != -1) {
        partner[1] = func_800D8010_name_81(0x3A, 0);
        func_800D8944_name_81(partner[1]);
        HuVecCopy3F(&partner[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
        func_8001C814_main(partner[1]->omObj1->model[0], 2, 0);
    }
    if (partner[0] != NULL) {
        func_800EFABC_name_81(partner[0]);
        func_800D8F3C_name_81(partner[0]);
    }
    if (partner[1] != NULL) {
        func_800EFABC_name_81(partner[1]);
        func_800D8F3C_name_81(partner[1]);
    }
    Duel_PowerDownPartners(system->current_player_index);
    HuAudFXPlay(0x1FC);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(1));
    HuPrcChildWait();
    func_800EDDBC_name_81();
}

// duel b4: spin the partner's model about Y by ang * 10 degrees (the model matrix is rebuilt as a pure Y rotation)
#define B4_PARTNER_SPIN(obj, vel, ang)                                                                         \
    {                                                                                                          \
        HmfModel *mdl;                                                                                         \
        (obj)->velocity.x = (vel);                                                                             \
        sincosdf((ang) * 10.0f, &HmfModelData[(obj)->omObj1->model[0]].mtx[8],                                 \
                 &HmfModelData[(obj)->omObj1->model[0]].mtx[10]);                                              \
        HmfModelData[(obj)->omObj1->model[0]].mtx[2] = -HmfModelData[(obj)->omObj1->model[0]].mtx[8];         \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[0] = mdl->mtx[10];                                                                            \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[1] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[6] = mdl->mtx[7] = mdl->mtx[9] = mdl->mtx[11] =     \
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;                                                 \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[5] = mdl->mtx[15] = 1.0f;                                                                     \
    }

// duel b4: partner swap space: both partners spin, swap front and back, and spin back
void func_80112DA0_duel01(void) {
    GW_PLAYER *player;
    Object *obj;
    void *win;
    f32 angle;
    s32 cur;

    player = MBDGetPlayerStruct(-1);
    cur = MBDGetCurrentPlayerIndex();
    func_800DD41C_name_81(&player->player_obj->coords);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuAudFXPlay(0x1FD);
    func_800DD554_name_81();
    win = func_800FFC2C_name_81(-1, 1, 5);
    for (angle = 0.0f; angle < 120.0f; angle += 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    Duel_SwapPartnerPositions(cur);
    func_800DD564_name_81();
    for (angle = 120.0f; angle > 0.0f; angle -= 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win);
    /* angle is 0 here: the loop steps from 120 by 5 */
    if (player->stats.prize.gamblePrize != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 0);
        B4_PARTNER_SPIN(obj, 0.0f, angle);
    }
    if (player->stats.prize.duelNo != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 1);
        B4_PARTNER_SPIN(obj, 0.0f, angle);
    }
    func_800DD570_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2C);
    func_800EDF78_name_81();
    func_800EE468_name_81(1);
    func_800EDDBC_name_81();
}

// duel b4: partner downgrade space (the mirror of the swap space's spin)
void func_801135D8_duel01(void) {
    void *win[2];
    GW_PLAYER *player;
    Object *obj;
    f32 rot;
    f32 scale;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1FB);
    func_800EE74C_name_81(4);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x22, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1FE);
    win[0] = func_800FFC2C_name_81(0, 2, 5);
    win[1] = func_800FFC2C_name_81(1, 2, 5);
    rot = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800EA8DC_name_81();
    func_800EA97C_name_81();
    for (; scale >= 1.0f; scale -= 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win[0]);
    func_800FFCCC_name_81(win[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2D);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    CharFXPlay(0x286, GwPlayer[GwSystem.current_player_index].chr);
    func_800F3880_name_81(-1, 5, 0);
    func_800EFABC_name_81(player->player_obj);
}

// duel b4: gain 20 coins
void func_801138D0_duel01(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 20);
    func_800F7378_name_81(system->current_player_index, 20);
    HuPrcSleep(30);
}

// duel b4: the event roulette's result: a banner drops in and bounces, then the chosen space event runs
void func_8011390C_duel01(void) {
    DuelB4SprGrp *grp;
    void *data;
    s32 i;
    s32 y;

    mbItemBtnF = 0;
    func_800F74E4_name_81(-1);
    HuAudFXPlay(0x204);
    grp = func_800F4528_name_81(2, 2);
    data = DataRead(0x130103);
    grp->unk_0C[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp->unk_0A, 0, grp->unk_0C[0], 0);
    HuSprPriSet(grp->unk_0A, 0, 1);
    HuSprAttrSet(grp->unk_0A, 0, 0x1000);
    func_80054904_main(grp->unk_0A, 0, 160, -32);
    func_800555E8_main(grp->unk_0A, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    grp->unk_0C[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp->unk_0A, 1, grp->unk_0C[1], 0);
    HuSprPriSet(grp->unk_0A, 1, 2);
    HuSprAttrSet(grp->unk_0A, 1, 0x1000);
    func_80054904_main(grp->unk_0A, 1, 0, 0);
    func_800555E8_main(grp->unk_0A, 0, 16, 12, 304, 228);
    func_80055420_main(grp->unk_0A, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        func_80054904_main(grp->unk_0A, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        func_80054904_main(grp->unk_0A, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        func_80054904_main(grp->unk_0A, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    func_80054904_main(grp->unk_0A, 0, 160, 120);
    for (y = 0, i = 0; i < 9; i++) {
        y += i * 2;
        func_80054904_main(grp->unk_0A, 0, 160, 120 - y);
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800E0924_name_81());
    HuPrcChildWait();
    func_800F4584_name_81(grp);
    func_800F75EC_name_81(-1);
    D_801188E4_duel01[GwSystem.minigame_index]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
// duel b4: logic checked branch by branch against the asm; masked ~240: operand load order and register choice in the repeated power-vs-HP tests (759 vs 779 instructions)
// duel b4: COM decision for the current player against the opponent, from the opponent's position (clink, cidx)
// relative to the roll (mbWalkNum); compares partner power with HP. me/opp partner fields are PartnerStats.
s32 func_80113CAC_duel01(void) {
    DuelSpaceTbl dist;
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 n;
    s32 m;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    dist = D_801193E8_duel01;
    switch (opp->clink) {
        case 0:
            if (opp->cidx == walk - 6) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return FALSE;
                }
                if (func_800F8980_name_81(cur) == 0) {
                    n = 100;
                } else {
                    n = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
                }
                if (n < 4) {
                    return FALSE;
                }
                return me->stats.partners.frontPower != 0;
            }
            if (opp->cidx < walk - 6) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return FALSE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 10) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return TRUE;
                    }
                    return me->stats.partners.backPower < hp + me->stats.partners.backHp;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID != 10) {
                        return FALSE;
                    }
                    return opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star;
                }
                return FALSE;
            }
            if (walk == 6) {
                if (func_800F8980_name_81(cur) == 0) {
                    n = 100;
                    m = 100;
                } else {
                    n = GwPlayer[cur].coin / func_800F8980_name_81(cur);
                    m = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
                }
                if (n == 0) {
                    return FALSE;
                }
                if (m > 0) {
                    return TRUE;
                }
                if (func_800EFE20_name_81(100.0f) < 50) {
                    return TRUE;
                }
                return FALSE;
            }
            if (walk != 1) {
                return FALSE;
            }
            if (opp->cidx >= 6) {
                if (me->stats.partners.backID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.backID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.backID == 10) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.backHp + opp->star)) {
                        return FALSE;
                    }
                } else if (opp->stats.partners.frontHp + opp->star < me->stats.partners.backPower) {
                    return FALSE;
                }
                if (opp->stats.partners.frontID != 4) {
                    return FALSE;
                }
                return !(me->stats.partners.backPower < me->star + me->stats.partners.backHp);
            }
            if (opp->stats.partners.frontPower == 0) {
                return FALSE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 100;
            } else {
                n = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
            }
            return n >= 4;
        case 1:
            if (opp->cidx == walk - 1) {
                if (me->stats.partners.frontID == 3) {
                    return FALSE;
                }
                if (opp->stats.partners.backID != 4) {
                    return FALSE;
                }
                if (me->stats.partners.frontPower < me->star + me->stats.partners.frontHp) {
                    return FALSE;
                }
                return me->stats.partners.frontPower < opp->stats.partners.backHp + opp->star;
            }
            if (opp->cidx < walk - 1) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return TRUE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 7) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return FALSE;
                    }
                    return !(me->stats.partners.backPower < hp + me->stats.partners.backHp);
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return !(opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star);
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return TRUE;
                    }
                    return FALSE;
                }
                return FALSE;
            }
            if (walk == 1) {
                return FALSE;
            }
            if (opp->cidx < 8) {
                return FALSE;
            }
            if (opp->stats.partners.frontPower == 0) {
                return FALSE;
            }
            if (walk != 6) {
                return FALSE;
            }
            if (opp->stats.partners.frontID != 4) {
                return TRUE;
            }
            return me->stats.partners.backPower < me->stats.partners.backHp + me->star;
        case 2:
            if ((opp->rev & 1) || opp->nlink == 0) {
                if (dist.idx[walk] < opp->cidx) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    if (!(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                } else if (!(me->stats.partners.frontPower < opp->star + opp->stats.partners.backHp)) {
                    return TRUE;
                }
                if (opp->stats.partners.frontID == 4) {
                    if (me->stats.partners.frontPower < me->star + me->stats.partners.frontHp) {
                        return TRUE;
                    }
                    return !(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star);
                }
                if (me->stats.partners.frontPower != 0) {
                    return TRUE;
                }
                if (opp->stats.partners.frontPower != 0) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3) {
                    return TRUE;
                }
                return FALSE;
            }
            if (dist.idx[walk] < opp->cidx) {
                if (walk == 2 && me->stats.partners.frontPoweredUp != walk) {
                    if (func_800F8980_name_81(cur) == 0) {
                        n = 100;
                    } else {
                        n = (GwPlayer[cur].coin - 5) / (func_800F8980_name_81(cur) * 2);
                    }
                } else {
                    if (func_800F8980_name_81(cur) == 0) {
                        n = 100;
                    } else {
                        n = (GwPlayer[cur].coin - 5) / (func_800F8980_name_81(cur) * 2);
                    }
                }
                if (n < 4) {
                    return FALSE;
                }
                return me->stats.partners.frontPower != 0;
            }
            if (me->stats.partners.frontID == 8 && opp->star < 2) {
                return TRUE;
            }
            if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                return TRUE;
            }
            if (me->stats.partners.frontID == 10) {
                if (!(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star)) {
                    return TRUE;
                }
            } else if (!(me->stats.partners.frontPower < opp->star + opp->stats.partners.backHp)) {
                return TRUE;
            }
            if (opp->stats.partners.backID == 4) {
                return FALSE;
            }
            if (walk == 6) {
                return TRUE;
            }
            if (opp->cidx == dist.idx[walk]) {
                return !(me->stats.partners.frontPower == 0 && walk == 1);
            }
            if (opp->stats.partners.frontID == 8 && me->star < 2) {
                return FALSE;
            }
            if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                return FALSE;
            }
            if (opp->stats.partners.frontID == 10) {
                if (opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star) {
                    return FALSE;
                }
            } else if (opp->stats.partners.frontPower < me->star + me->stats.partners.backHp) {
                return FALSE;
            }
            return FALSE;
    }
    return FALSE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80113CAC_duel01);
#endif

// duel b7
u8 func_800FD498_name_81(void); /* defined s32 in ovl_81; the callers here read it as u8 */

#ifdef NON_MATCHING
// duel b7: m2c-derived, block order differs from retail (masked ~1450 of 1147). Logic checked by running retail
// and this build in a MIPS interpreter on 15000 random player/board states: same result and call sequence on all,
// covering every reachable retail instruction (the walk == 7 block is dead in retail too).
// COM decision mirroring func_80113CAC_duel01: whether the current player should act against the opponent.
s32 func_801147FC_duel01(void) {
    GW_PLAYER *me;
    DuelSpaceTbl dist;
    GW_PLAYER *opp;
    SpaceData *temp_a0_3;
    s16 temp_s0;
    s16 cur;
    s32 temp_s1;
    s32 walk;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_v0;
    s32 var_v0_10;
    s32 var_v0_11;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_4;
    s8 temp_a0_5;
    s8 temp_v0_2;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 temp_v1_3;
    s8 temp_v1_4;
    s8 temp_v1_5;
    s8 var_a1;
    s8 var_a1_2;
    s8 var_v0_3;
    s8 var_v0_8;
    s8 var_v0_9;
    s8 var_v1;
    u8 temp_s0_2;
    u8 temp_s0_3;

    cur = MBDGetCurrentPlayerIndex();
    temp_s0 = MBDGetCurrentPlayerIndex() ^ 1;
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct((s32) temp_s0);
    walk = mbWalkNum;
    dist = D_801193E8_duel01;
    temp_v1 = opp->clink;
    if (temp_v1 != 1) {
        if (temp_v1 >= 2) {
            if (temp_v1 != 2) {
                return 1;
            }
            if ((opp->rev & 1) || (opp->nlink == 0)) {
                if (dist.idx[walk] >= opp->cidx) {
                    var_v0 = 1;
                    if (opp->stats.partners.frontID == 4) {
                        temp_a0_2 = me->stats.partners.frontPower;
                        if (temp_a0_2 >= (me->star + me->stats.partners.frontHp)) {
                            return temp_a0_2 >= (opp->stats.partners.frontHp + opp->star);
                        }
                        goto block_236;
                    }
                    return var_v0;
                }
                if (opp->stats.partners.frontID == 8) {
                    var_v0 = 0;
                    if (me->star >= 2) {
                        goto block_172;
                    }
                    return var_v0;
                }
block_172:
                if (((opp->stats.partners.frontID != 3) || (var_v0 = 0, ((opp->stats.partners.frontPoweredUp < me->star) != 0))) && ((opp->stats.partners.frontID != 0xA) || (var_v0 = 0, ((opp->stats.partners.frontPower < (me->stats.partners.backHp + me->star)) != 0))) && ((temp_v1_2 = me->stats.partners.frontHp, ((temp_v1_2 < opp->stats.partners.frontPower) == 0)) || (var_v0 = 0, ((me->stats.partners.backHp < temp_v1_2) != 0)))) {
                    var_v0 = 1;
                    if (func_800EFE20_name_81(100.0f) >= 0x32) {
                        return 0;
                    }
                }
                return var_v0;
            }
            if (dist.idx[walk] < opp->cidx) {
                if ((walk == 2) && (me->stats.partners.frontPoweredUp != walk)) {
                    var_s1_2 = 0x64;
                    if (func_800F8980_name_81(cur) != 0) {
                        var_s1_3 = GwPlayer[cur].coin - 5;
                        var_v0_6 = func_800F8980_name_81(cur) * 2;
                        goto block_198;
                    }
                    goto block_199;
                }
                if (walk == 3) {
                    goto block_186;
                }
                temp_a0_3 = MBDMasuGet(0x13);
                if (walk == 1) {
                    if ((temp_a0_3->space_type - 0xB) == GwPlayer[cur].chr) {
                        var_s1_2 = 0x64;
                        if (func_800F8980_name_81(cur) != 0) {
                            temp_s0_2 = func_800FD498_name_81();
                            var_s1_3 = GwPlayer[cur].coin + (temp_s0_2 - 5);
                            var_v0_6 = func_800F8980_name_81(cur) * 2;
                            goto block_198;
                        }
                    } else if (temp_a0_3->space_type == 6) {
                        var_s1_2 = 0x64;
                        if (func_800F8980_name_81(cur) != 0) {
                            goto block_197;
                        }
                    } else {
                        var_s1_2 = 0x64;
                        if (func_800F8980_name_81(cur) != 0) {
                            temp_s0_3 = func_800FD498_name_81();
                            var_s1_3 = GwPlayer[cur].coin - (temp_s0_3 + 5);
                            var_v0_6 = func_800F8980_name_81(cur) * 2;
                            goto block_198;
                        }
                    }
                } else {
                    var_s1_2 = 0x64;
                    if (func_800F8980_name_81(cur) != 0) {
block_197:
                        var_v0_6 = func_800F8980_name_81(cur);
                        var_s1_3 = GwPlayer[cur].coin - 5;
                        goto block_198;
                    }
                }
                goto block_199;
            }
            if (me->stats.partners.frontID == 8) {
                var_v0 = 1;
                if (opp->star >= 2) {
                    goto block_203;
                }
                return var_v0;
            }
block_203:
            if ((me->stats.partners.frontID != 3) || (var_v0 = 1, ((me->stats.partners.frontPoweredUp < opp->star) != 0))) {
                if (me->stats.partners.frontID == 0xA) {
                    if (me->stats.partners.frontPower >= (opp->stats.partners.frontHp + opp->star)) {
                        return 1;
                    }
                    goto block_209;
                }
                var_v0 = 1;
                if (me->stats.partners.frontPower < (opp->star + opp->stats.partners.backHp)) {
block_209:
                    if (opp->stats.partners.backID == 4) {
                        if (me->stats.partners.frontPower >= (me->stats.partners.frontHp + me->star)) {
                            return 0;
                        }
                        temp_s1 = me->stats.partners.frontHp - me->stats.partners.frontPower;
                        var_v0_5 = (me->star + me->stats.partners.backHp) - (-(temp_s1 < 1) & temp_s1);
                        goto block_214;
                    }
                    var_s1_4 = 0x64;
                    if (func_800F8980_name_81(cur) != 0) {
                        var_s1_4 = (s32) (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
                    }
                    var_v0 = 1;
                    if (!((walk == 6) & (var_s1_4 >= 2))) {
                        if (opp->cidx != dist.idx[walk]) {
                            if (opp->stats.partners.frontID == 8) {
                                var_v0 = 0;
                                if (me->star >= 2) {
                                    goto block_226;
                                }
                                return var_v0;
                            }
block_226:
                            if ((opp->stats.partners.frontID != 3) || (var_v0 = 0, ((opp->stats.partners.frontPoweredUp < me->star) != 0))) {
                                if (opp->stats.partners.frontID == 0xA) {
                                    var_v0_7 = me->stats.partners.frontHp + me->star;
                                } else {
                                    var_v0_7 = me->star + me->stats.partners.backHp;
                                }
                                if (opp->stats.partners.frontPower >= var_v0_7) {
                                    return 0;
                                }
                                var_v0 = 1;
                                if (me->stats.partners.frontPower == 0) {
                                    return opp->stats.partners.frontPower == 0;
                                }
                                return var_v0;
                            }
                            return var_v0;
                        }
                        var_v0_4 = me->stats.partners.frontPower == 0;
                        var_v1_3 = walk == 1;
                        goto block_222;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            return var_v0;
        }
        if (temp_v1 != 0) {
            return 1;
        }
        if (opp->cidx == (walk - 6)) {
            var_v0 = 1;
            if (opp->stats.partners.backID == 4) {
                var_v1 = me->stats.partners.frontPower;
                var_v0_2 = me->star + me->stats.partners.frontHp;
                goto block_148;
            }
            return var_v0;
        }
        if (opp->cidx < (walk - 6)) {
            var_a1 = me->star;
            if (me->stats.partners.frontID == 8) {
                var_v0 = 1;
                if (opp->star >= 2) {
                    goto block_15;
                }
                return var_v0;
            }
block_15:
            if ((me->stats.partners.frontID != 3) || (var_v0 = 1, ((me->stats.partners.frontPoweredUp < opp->star) != 0))) {
                if (me->stats.partners.frontID == 0xA) {
                    var_v0_8 = opp->stats.partners.frontHp;
                } else {
                    var_v0_8 = opp->stats.partners.backHp;
                }
                if (me->stats.partners.frontPower < (var_v0_8 + opp->star)) {
                    if (opp->stats.partners.backID == 4) {
                        var_v0 = 0;
                        if (me->stats.partners.frontPower < (me->star + me->stats.partners.frontHp)) {
                            temp_a0_4 = me->stats.partners.frontPower;
                            temp_v1_3 = me->stats.partners.frontHp;
                            if (temp_v1_3 < temp_a0_4) {
                                var_a1 -= temp_a0_4 - temp_v1_3;
                            }
                            goto block_26;
                        }
                        return var_v0;
                    }
block_26:
                    if (walk == 0xA) {
                        if (me->stats.partners.backPower < (opp->stats.partners.frontHp + opp->star)) {
                            var_v0 = 1;
                            if (opp->stats.partners.frontID == 4) {
                                return me->stats.partners.backPower < (var_a1 + me->stats.partners.backHp);
                            }
                            return var_v0;
                        }
                        goto block_236;
                    }
                    if (((GwSystem.current_turn != GwSystem.total_turns) | (cur == 0)) != 0) {
                        if (opp->stats.partners.frontID == 8) {
                            var_v0 = 0;
                            if (me->star >= 2) {
                                goto block_34;
                            }
                            return var_v0;
                        }
block_34:
                        if ((opp->stats.partners.frontID != 3) || (var_v0 = 0, ((opp->stats.partners.frontPoweredUp < me->star) != 0))) {
                            if (opp->stats.partners.frontID == 0xA) {
                                var_v0_5 = me->stats.partners.frontHp + me->star;
block_214:
                                return opp->stats.partners.frontPower < var_v0_5;
                            }
                            var_v0 = 0;
                            if ((me->stats.partners.backHp + me->star) >= opp->stats.partners.frontPower) {
                                goto block_39;
                            }
                            return var_v0;
                        }
                        return var_v0;
                    }
block_39:
                    var_v0 = 1;
                    if (me->stats.partners.frontPower == 0) {
                        var_v0 = 1;
                        if (me->stats.partners.backID != 4) {
                            return 0;
                        }
                    }
                    return var_v0;
                }
                goto block_236;
            }
            return var_v0;
        }
        if (walk == 1) {
            if (opp->cidx >= 6) {
                if (me->stats.partners.backID == 8) {
                    var_v0 = 0;
                    if (opp->star >= 2) {
                        goto block_47;
                    }
                    return var_v0;
                }
block_47:
                if ((me->stats.partners.backID != 3) || (var_v0 = 0, ((me->stats.partners.frontPoweredUp < opp->star) != 0))) {
                    if (me->stats.partners.backID == 0xA) {
                        if (me->stats.partners.backPower >= (opp->stats.partners.backHp + opp->star)) {
                            goto block_51;
                        }
                        goto block_55;
                    }
                    if ((opp->stats.partners.frontHp + opp->star) < me->stats.partners.backPower) {
                        return 0;
                    }
block_55:
                    var_v0 = 0;
                    if (opp->stats.partners.frontID == 4) {
                        var_v0_3 = me->stats.partners.backPower;
                        var_v1_2 = me->star + me->stats.partners.backHp;
                        goto block_126;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            if (opp->stats.partners.frontPower != 0) {
                if (opp->stats.partners.frontID == 8) {
                    var_v0 = 1;
                    if (me->star >= 2) {
                        goto block_61;
                    }
                    return var_v0;
                }
block_61:
                if ((opp->stats.partners.frontID != 3) || (var_v0 = 1, ((opp->stats.partners.frontPoweredUp < me->star) != 0))) {
                    if (opp->stats.partners.frontID == 0xA) {
                        if (opp->stats.partners.frontPower >= (me->stats.partners.frontHp + me->star)) {
                            return 1;
                        }
                        goto block_68;
                    }
                    var_v0 = 0;
                    if (me->stats.partners.backHp < opp->stats.partners.frontPower) {
                        if (opp->stats.partners.frontPower < (me->stats.partners.backHp + me->star)) {
block_68:
                            return (MBDMasuGet(0x13)->space_type - 0xB) == GwPlayer[cur].chr;
                        }
block_236:
                        var_v0 = 1;
                        return var_v0;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            goto block_51;
        }
        var_v0 = 1;
        if ((u32) (walk - 6) >= 2U) {
            if (walk == 3) {
                goto block_186;
            }
            if (walk == 2 && me->stats.partners.frontPoweredUp != walk) {
                {
                    var_s1_2 = 0x64;
                    if (func_800F8980_name_81(cur) != 0) {
                        var_s1_3 = GwPlayer[cur].coin - 5;
                        var_v0_6 = func_800F8980_name_81(cur) * 2;
block_198:
                        var_s1_2 = var_s1_3 / var_v0_6;
                    }
block_199:
                    return var_s1_2 >= 2;
                }
            }
            if (walk == 7) { /* never true here: walk 6 and 7 returned above */
                {
                    var_s1_5 = 0x64;
                    if (func_800F8980_name_81(cur) != 0) {
                        var_s1_5 = (s16) GwPlayer[cur].coin / func_800F8980_name_81(cur);
                    }
                    if ((me->stats.partners.frontPower == 0) || (var_v0 = 0, (((me->stats.partners.backHp != 0) & (var_s1_5 >= 4)) == 0))) {
                        if (opp->stats.partners.frontID == 8) {
                            var_v0 = 1;
                            if (me->star >= 2) {
                                goto block_83;
                            }
                            return var_v0;
                        }
block_83:
                        if ((opp->stats.partners.frontID != 3) || (var_v0 = 1, ((opp->stats.partners.frontPoweredUp < me->star) != 0))) {
                            if (opp->stats.partners.frontID == 0xA) {
                                if (opp->stats.partners.frontPower >= (me->stats.partners.frontHp + me->star)) {
                                    return 1;
                                }
                                goto block_89;
                            }
                            var_v0 = 1;
                            if (opp->stats.partners.frontPower < (me->stats.partners.backHp + me->star)) {
                                goto block_89;
                            }
                            return var_v0;
                        }
                        return var_v0;
                    }
                    return var_v0;
                }
            }
            {
block_89:
                var_s1_6 = 0x64;
                if (func_800F8980_name_81(cur) == 0) {
                    var_v1_4 = 0x64;
                } else {
                    var_s1_6 = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
                    var_v1_4 = GwPlayer[cur].coin / func_800F8980_name_81(cur);
                }
                var_v0_4 = var_s1_6 < 2;
                var_v1_3 = var_v1_4 >= 2;
block_222:
                return (var_v0_4 & var_v1_3) == 0;
            }
        } else {
            return var_v0;
        }
    } else {
        if (opp->cidx == (walk - 1)) {
            if (me->stats.partners.frontID != 3) {
                if (opp->stats.partners.backID == 4) {
                    temp_a0 = me->stats.partners.frontPower;
                    if (temp_a0 >= (me->star + me->stats.partners.frontHp)) {
                        return temp_a0 < (opp->stats.partners.backHp + opp->star);
                    }
                }
                return (me->stats.partners.frontPower == 0) & (walk != 6);
            }
            goto block_51;
        }
        if (opp->cidx < (walk - 1)) {
            var_a1_2 = me->star;
            if (me->stats.partners.frontID == 8) {
                var_v0 = 0;
                if (opp->star >= 2) {
                    goto block_103;
                }
                return var_v0;
            }
block_103:
            if ((me->stats.partners.frontID != 3) || (var_v0 = 0, ((me->stats.partners.frontPoweredUp < opp->star) != 0))) {
                if (me->stats.partners.frontID == 0xA) {
                    var_v0_9 = opp->stats.partners.frontHp;
                } else {
                    var_v0_9 = opp->stats.partners.backHp;
                }
                if (me->stats.partners.frontPower < (var_v0_9 + opp->star)) {
                    if (opp->stats.partners.backID == 4) {
                        var_v0 = 1;
                        if (me->stats.partners.frontPower < (me->star + me->stats.partners.frontHp)) {
                            temp_a0_5 = me->stats.partners.frontPower;
                            temp_v1_4 = me->stats.partners.frontHp;
                            if (temp_v1_4 < temp_a0_5) {
                                var_a1_2 -= temp_a0_5 - temp_v1_4;
                            }
                            goto block_114;
                        }
                        return var_v0;
                    }
block_114:
                    if (walk == 7) {
                        if (me->stats.partners.backPower < (opp->stats.partners.frontHp + opp->star)) {
                            var_v0 = 0;
                            if (opp->stats.partners.frontID == 4) {
                                var_v0_3 = me->stats.partners.backPower;
                                var_v1_2 = var_a1_2 + me->stats.partners.backHp;
                                goto block_126;
                            }
                            return var_v0;
                        }
                        goto block_51;
                    }
                    if (((GwSystem.current_turn != GwSystem.total_turns) | (cur == 0)) != 0) {
                        if (opp->stats.partners.frontID == 8) {
                            var_v0 = 1;
                            if (me->star >= 2) {
                                goto block_122;
                            }
                            return var_v0;
                        }
block_122:
                        if ((opp->stats.partners.frontID != 3) || (var_v0 = 1, ((opp->stats.partners.frontPoweredUp < me->star) != 0))) {
                            if (opp->stats.partners.frontID == 0xA) {
                                var_v1_2 = me->stats.partners.frontHp + me->star;
                                var_v0_3 = opp->stats.partners.frontPower;
block_126:
                                return var_v0_3 >= var_v1_2;
                            }
                            var_v0 = 1;
                            if ((me->stats.partners.backHp + me->star) >= opp->stats.partners.frontPower) {
                                goto block_128;
                            }
                            return var_v0;
                        }
                        return var_v0;
                    }
block_128:
                    temp_v0_2 = me->stats.partners.frontID;
                    var_v0 = 0;
                    if (((temp_v0_2 == 3) | (temp_v0_2 == 8)) == 0) {
                        if (me->stats.partners.frontID == 0xA) {
                            if (me->stats.partners.frontPower < opp->stats.partners.frontHp) {
                                var_v0_10 = opp->stats.partners.frontPower < opp->stats.partners.backHp;
                                goto block_132;
                            }
                            goto block_136;
                        }
                        temp_v1_5 = opp->stats.partners.backHp;
                        if (me->stats.partners.frontPower < temp_v1_5) {
                            var_v0_10 = opp->stats.partners.frontPower < temp_v1_5;
block_132:
                            if (var_v0_10 == 0) {
                                return 1;
                            }
                            goto block_136;
                        }
block_136:
                        var_v0 = 0;
                        if (me->stats.partners.frontPower == 0) {
                            var_v0 = 0;
                            if (me->stats.partners.backID != 4) {
                                return 1;
                            }
                        }
                        return var_v0;
                    }
                    return var_v0;
                }
block_51:
                return 0;
            }
            return var_v0;
        }
        var_v0 = 0;
        if (walk != 1) {
            if (opp->cidx >= 8) {
                if ((opp->stats.partners.frontID == 3) || (opp->stats.partners.frontPower != 0)) {
                    if (walk != 6) {
                        return 0;
                    }
                    var_v0 = 1;
                    if (opp->stats.partners.frontID == 4) {
                        var_v1 = me->stats.partners.backPower;
                        var_v0_2 = me->stats.partners.backHp + me->star;
block_148:
                        return var_v1 < var_v0_2;
                    }
                    return var_v0;
                }
                if (walk != 3) {
                    if ((walk == 2) && (me->stats.partners.frontPoweredUp != walk)) {
                        var_s1 = 0x64;
                        if (func_800F8980_name_81(cur) != 0) {
                            var_s1_7 = GwPlayer[cur].coin - 5;
                            var_v0_11 = func_800F8980_name_81(cur) * 2;
                            goto block_156;
                        }
                    } else {
                        var_s1 = 0x64;
                        if (func_800F8980_name_81(cur) != 0) {
                            var_v0_11 = func_800F8980_name_81(cur);
                            var_s1_7 = GwPlayer[cur].coin - 5;
block_156:
                            var_s1 = var_s1_7 / var_v0_11;
                        }
                    }
                    return var_s1 > 0;
                }
block_186:
                return func_800EFE20_name_81(100.0f) < 0x32;
            }
            if (opp->cidx < 5) {
                return 0;
            }
            return (u32) (walk - 9) < 2U;
        }
        return var_v0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801147FC_duel01);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801193E8_duel01);

// duel b5
extern const DuelSpaceTbl D_80119410_duel01;
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
void func_800E27D4_name_81(s16 playerIndex, Vec *pos, Vec *frontPos, Vec *backPos);
UnkEA790Struct *func_800D76A0_name_81(s16 arg0, s16 *arg1);
s32 func_800D742C_name_81(UnkEA790Struct *arg0, s16 playerNo, s32 arg2);
s32 func_800D7250_name_81(UnkEA790Struct *arg0, s32 arg1);
s32 func_800D7518_name_81(UnkEA790Struct *arg0);
void func_800D6CA0_name_81(void *arg0);
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *arg0);
void func_800ECDE8_name_81(void);
void func_800ECE10_name_81(void);
Process *func_800ED70C_name_81(s32 playerNo, s32 hop);
Process *func_800EDC6C_name_81(s32 playerNo, s32 hop);
void func_8010EAD4_duel01(s32);
void func_8010EB44_duel01(s32);
extern DecisionTreeNonLeafNode D_80118CF0_duel01[];
extern s16 D_80118DE4_duel01[];
extern DecisionTreeNonLeafNode D_80118AEC_duel01[];
extern DecisionTreeNonLeafNode D_80118CC0_duel01[];
extern s16 D_8010555C_name_81;
extern s16 mbItemBtnF;
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800E14D8_name_81(s32 player, s32 coins);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EBDDC_name_81(s16 playerNo, s32 arg1, s16 spaceIdx);
void func_800ECD88_name_81(s16 playerNo, s16 link, s16 idx);
void func_800ED788_name_81(s32 playerNo);
void func_800F7378_name_81(s32 playerIndex, s32 coinAmount);
void func_800FB524_name_81(s32 playerNo);
s32 func_800F8980_name_81(s32 playerIndex); // ovl_81 defines it with a void * (stored as process user_data)

// duel b5: masked 17, raw 19 (retail reloads cidx and the table entry after the equality test, no CSE of sp+walk); H1 tried: one `==` || `>=` return (masked 26), nested if/return 0 (masked 16, 120 instr).
#ifdef NON_MATCHING
s32 func_80115850_duel01(void) {
    DuelSpaceTbl spaceIdx;
    GW_PLAYER *cur;
    GW_PLAYER *other;
    s32 otherNo;
    s32 walk;
    s32 chance;

    otherNo = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    cur = MBDGetPlayerStruct(CUR_PLAYER);
    other = MBDGetPlayerStruct(otherNo);
    walk = mbWalkNum;
    spaceIdx = D_801193E8_duel01;
    if ((other->rev & 1) || other->nlink == 0) {
        if (other->cidx == spaceIdx.idx[walk]) {
            goto yes;
        }
        return spaceIdx.idx[walk] >= other->cidx;
    }
    if (!(other->cidx < spaceIdx.idx[walk])) {
        return 1;
    }
    if (!(other->stats.partners.frontPower < cur->star + cur->stats.partners.backHp)) {
        return 0;
    }
    if (other->stats.partners.frontPower < cur->stats.partners.frontPower) {
        return 1;
    }
    if (cur->stats.partners.frontPower == 0) {
        return 0;
    }
    switch (GwPlayer[MBDGetCurrentPlayerIndex()].chr) {
    case 4:
    case 5:
    case 6:
        chance = func_800EFE20_name_81(100.0f) < 80;
        break;
    case 0:
    case 3:
    case 7:
        chance = func_800EFE20_name_81(100.0f) < 50;
        break;
    default:
        chance = func_800EFE20_name_81(100.0f) < 20;
        break;
    }
    if (!chance) {
        return 0;
    }
yes:
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80115850_duel01);
#endif

// duel b5: COM decision: which route-3 gate to take (m2c structure; logic checked against the asm)
#ifdef NON_MATCHING
s32 func_801159F8_duel01(void) {
    DuelSpaceTbl spaceIdx;
    GW_PLAYER *cur;
    GW_PLAYER *other;
    s16 otherNo;
    s16 playerNo;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_v0;
    s32 var_v0_3;
    s32 var_v1;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_3;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 var_a1;
    s8 var_v0_2;
    s8 var_v0_4;
    s8 var_v0_5;
    s8 var_v0_6;

    playerNo = MBDGetCurrentPlayerIndex();
    otherNo = MBDGetCurrentPlayerIndex() ^ 1;
    cur = MBDGetPlayerStruct(CUR_PLAYER);
    other = MBDGetPlayerStruct(otherNo);
    spaceIdx = D_80119410_duel01;
    temp_v1 = other->clink;
    if (temp_v1 != 1) {
        if (temp_v1 >= 2) {
            if (temp_v1 != 2) {
                return 0;
            }
            if (!(other->rev & 1) && (other->nlink != 0)) {
                var_v0 = 0;
                if (other->cidx >= spaceIdx.idx[mbWalkNum]) {
                    if (cur->stats.partners.frontID == 8) {
                        var_v0 = 1;
                        if (other->star >= 2) {
                            goto block_114;
                        }
                        return var_v0;
                    }
block_114:
                    if ((cur->stats.partners.frontID != 3) || (var_v0 = 1, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                        if (cur->stats.partners.frontID == 0xA) {
                            if (cur->stats.partners.frontPower >= (other->stats.partners.frontHp + other->star)) {
                                goto block_118;
                            }
                            goto block_120;
                        }
                        var_v0 = 1;
                        if (cur->stats.partners.frontPower < (other->star + other->stats.partners.backHp)) {
block_120:
                            if (other->stats.partners.frontID == 4) {
                                temp_a0_2 = cur->stats.partners.frontPower;
                                if (temp_a0_2 < (cur->star + cur->stats.partners.frontHp)) {
                                    return 1;
                                }
                                return temp_a0_2 >= (other->stats.partners.frontHp + other->star);
                            }
                            var_v0 = 1;
                            if (cur->stats.partners.frontPower == 0) {
                                var_v0 = 1;
                                if (other->stats.partners.frontPower == 0) {
                                    var_v0 = 1;
                                    if (cur->stats.partners.frontID != 3) {
                                        return 0;
                                    }
                                }
                            }
                            return var_v0;
                        }
                        return var_v0;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            if (other->cidx < spaceIdx.idx[mbWalkNum]) {
                if ((mbWalkNum == 4) && (cur->stats.partners.frontPoweredUp != 2)) {
                    var_s0_3 = 0x64;
                    if (func_800F8980_name_81(playerNo) != 0) {
                        goto block_135;
                    }
                } else {
                    var_s0_3 = 0x64;
                    if (func_800F8980_name_81(playerNo) != 0) {
block_135:
                        var_s0_4 = GwPlayer[playerNo].coin - 5;
                        var_v0_3 = func_800F8980_name_81(playerNo) * 2;
                        goto block_136;
                    }
                }
                goto block_137;
            }
            if (cur->stats.partners.frontID == 8) {
                var_v0 = 1;
                if (other->star >= 2) {
                    goto block_142;
                }
                return var_v0;
            }
block_142:
            if ((cur->stats.partners.frontID != 3) || (var_v0 = 1, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                if (cur->stats.partners.frontID == 0xA) {
                    if (cur->stats.partners.frontPower >= (other->stats.partners.frontHp + other->star)) {
                        return 1;
                    }
                    goto block_148;
                }
                var_v0 = 1;
                if (cur->stats.partners.frontPower < (other->star + other->stats.partners.backHp)) {
block_148:
                    if (other->stats.partners.backID != 4) {
                        if (mbWalkNum != 6) {
                            if (other->cidx != spaceIdx.idx[mbWalkNum]) {
                                if (other->stats.partners.frontID == 8) {
                                    var_v0 = 0;
                                    if (cur->star >= 2) {
                                        goto block_157;
                                    }
                                    return var_v0;
                                }
block_157:
                                if ((other->stats.partners.frontID != 3) || (var_v0 = 0, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                                    if (other->stats.partners.frontID == 0xA) {
                                        return 0;
                                    }
                                    goto block_162;
                                }
                                return var_v0;
                            }
                            return ((cur->stats.partners.frontPower == 0) & (mbWalkNum == 1)) == 0;
                        }
                        goto block_118;
                    }
                    goto block_162;
                }
                return var_v0;
            }
            return var_v0;
        }
        if (temp_v1 != 0) {
            return 0;
        }
        if (other->cidx == (mbWalkNum - 1)) {
            if (cur->stats.partners.frontID != 3) {
                var_v0 = 0;
                if (other->stats.partners.backID == 4) {
                    temp_a0 = cur->stats.partners.frontPower;
                    if (temp_a0 >= (cur->star + cur->stats.partners.frontHp)) {
                        return temp_a0 < (other->stats.partners.backHp + other->star);
                    }
                    goto block_162;
                }
                return var_v0;
            }
            goto block_162;
        }
        if (other->cidx < (mbWalkNum - 1)) {
            var_a1 = cur->star;
            if (cur->stats.partners.frontID == 8) {
                var_v0 = 0;
                if (other->star >= 2) {
                    goto block_75;
                }
                return var_v0;
            }
block_75:
            if ((cur->stats.partners.frontID != 3) || (var_v0 = 0, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                if (cur->stats.partners.frontID == 0xA) {
                    var_v0_4 = other->stats.partners.frontHp;
                } else {
                    var_v0_4 = other->stats.partners.backHp;
                }
                if (cur->stats.partners.frontPower < (var_v0_4 + other->star)) {
                    if (other->stats.partners.backID == 4) {
                        var_v0 = 1;
                        if (cur->stats.partners.frontPower < (cur->star + cur->stats.partners.frontHp)) {
                            temp_a0_3 = cur->stats.partners.frontPower;
                            temp_v1_2 = cur->stats.partners.frontHp;
                            if (temp_v1_2 < temp_a0_3) {
                                var_a1 -= temp_a0_3 - temp_v1_2;
                            }
                            goto block_86;
                        }
                        return var_v0;
                    }
block_86:
                    if (mbWalkNum == 5) {
                        var_v0 = 0;
                        if ((cur->stats.partners.backPower < (other->stats.partners.frontHp + other->star)) && (other->stats.partners.frontID == 4)) {
                            var_v0_2 = cur->stats.partners.backPower;
                            var_v1 = var_a1 + cur->stats.partners.backHp;
                            goto block_98;
                        }
                        return var_v0;
                    }
                    if (((GwSystem.current_turn != GwSystem.total_turns) | (playerNo == 0)) != 0) {
                        if (other->stats.partners.frontID == 8) {
                            var_v0 = 1;
                            if (cur->star >= 2) {
                                goto block_94;
                            }
                            return var_v0;
                        }
block_94:
                        if ((other->stats.partners.frontID != 3) || (var_v0 = 1, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                            if (other->stats.partners.frontID == 0xA) {
                                var_v1 = cur->stats.partners.frontHp + cur->star;
                                var_v0_2 = other->stats.partners.frontPower;
                                goto block_98;
                            }
                            var_v0 = 1;
                            if ((cur->stats.partners.backHp + cur->star) >= other->stats.partners.frontPower) {
                                return 0;
                            }
                            return var_v0;
                        }
                        return var_v0;
                    }
                    goto block_162;
                }
                goto block_162;
            }
            return var_v0;
        }
        var_v0 = 0;
        if (mbWalkNum != 1) {
            var_v0 = 0;
            if (other->cidx >= 8) {
                if (((other->stats.partners.frontID == 3) || (other->stats.partners.frontPower != 0)) && (mbWalkNum == 6)) {
                    var_v0 = 1;
                    if (other->stats.partners.frontID == 4) {
                        return cur->stats.partners.backPower < (cur->stats.partners.backHp + cur->star);
                    }
                    return var_v0;
                }
                goto block_162;
            }
        }
        return var_v0;
    }
    if (other->cidx == (mbWalkNum - 6)) {
        if (cur->stats.partners.frontID == 8) {
            var_v0 = 1;
            if (other->star >= 2) {
                goto block_12;
            }
            return var_v0;
        }
block_12:
        if ((cur->stats.partners.frontID != 3) || (var_v0 = 1, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
            if (cur->stats.partners.frontID == 0xA) {
                var_v0_5 = other->stats.partners.frontHp;
            } else {
                var_v0_5 = other->stats.partners.backHp;
            }
            if (cur->stats.partners.frontPower < (var_v0_5 + other->star)) {
                if ((other->stats.partners.backID != 4) || (var_v0 = 0, ((cur->stats.partners.frontPower < (cur->star + cur->stats.partners.frontHp)) != 0))) {
                    if (func_800F8980_name_81(playerNo) == 0) {
                        var_s0_3 = 0x64;
                    } else {
                        var_v0_3 = func_800F8980_name_81(playerNo);
                        var_s0_4 = GwPlayer[playerNo].coin - 5;
block_136:
                        var_s0_3 = var_s0_4 / var_v0_3;
                    }
block_137:
                    var_v0 = 0;
                    if (var_s0_3 >= 4) {
                        return cur->stats.partners.frontPower != 0;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            goto block_118;
        }
        return var_v0;
    }
    if (other->cidx < (mbWalkNum - 6)) {
        if (cur->stats.partners.frontID == 8) {
            var_v0 = 1;
            if (other->star >= 2) {
                goto block_28;
            }
            return var_v0;
        }
block_28:
        if ((cur->stats.partners.frontID != 3) || (var_v0 = 1, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
            if (cur->stats.partners.frontID == 0xA) {
                var_v0_6 = other->stats.partners.frontHp;
            } else {
                var_v0_6 = other->stats.partners.backHp;
            }
            if (cur->stats.partners.frontPower < (var_v0_6 + other->star)) {
                if ((other->stats.partners.backID != 4) || (var_v0 = 0, ((cur->stats.partners.frontPower < (cur->star + cur->stats.partners.frontHp)) != 0))) {
                    if (((GwSystem.current_turn != GwSystem.total_turns) | (playerNo == 0)) != 0) {
                        if (other->stats.partners.frontID == 8) {
                            var_v0 = 0;
                            if (cur->star >= 2) {
                                goto block_40;
                            }
                            return var_v0;
                        }
block_40:
                        if ((other->stats.partners.frontID != 3) || (var_v0 = 0, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                            if (other->stats.partners.frontID == 0xA) {
                                return other->stats.partners.frontPower < (cur->stats.partners.frontHp + cur->star);
                            }
                            goto block_162;
                        }
                        return var_v0;
                    }
                    goto block_162;
                }
                return var_v0;
            }
block_118:
            return 1;
        }
        return var_v0;
    }
    if (mbWalkNum == 6) {
        var_s0_2 = 0x64;
        if (func_800F8980_name_81(playerNo) != 0) {
            var_s0_2 = (s32) (GwPlayer[playerNo].coin - 5) / func_800F8980_name_81(playerNo);
        }
        var_v0 = 0;
        if (func_800EFE20_name_81(100.0f) < 0x1E) {
            return var_s0_2 > 0;
        }
        return var_v0;
    }
    var_v0 = 0;
    if (mbWalkNum == 1) {
        if (other->cidx >= 6) {
            if (cur->stats.partners.backID == 8) {
                var_v0 = 0;
                if (other->star >= 2) {
                    goto block_54;
                }
                return var_v0;
            }
block_54:
            if ((cur->stats.partners.backID != 3) || (var_v0 = 0, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                if (cur->stats.partners.backID == 0xA) {
                    if (cur->stats.partners.backPower >= (other->stats.partners.backHp + other->star)) {
                        return 0;
                    }
                    goto block_60;
                }
                if ((other->stats.partners.frontHp + other->star) >= cur->stats.partners.backPower) {
block_60:
                    var_v0 = 0;
                    if (other->stats.partners.frontID == 4) {
                        var_v0_2 = cur->stats.partners.backPower;
                        var_v1 = cur->star + cur->stats.partners.backHp;
block_98:
                        return var_v0_2 >= var_v1;
                    }
                    return var_v0;
                }
block_162:
                var_v0 = 0;
                return var_v0;
            }
            return var_v0;
        }
        var_v0 = 0;
        if (other->stats.partners.frontPower != 0) {
            var_s0 = 0x64;
            if (func_800F8980_name_81(playerNo) != 0) {
                var_s0 = (s32) (GwPlayer[playerNo].coin - 5) / func_800F8980_name_81(playerNo);
            }
            return var_s0 >= 4;
        }
        return var_v0;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801159F8_duel01);
#endif

// duel b5: COM decision (m2c structure; logic checked against the asm)
#ifdef NON_MATCHING
s32 func_80116484_duel01(void) {
    DuelSpaceTbl spaceIdx;
    GW_PLAYER *cur;
    GW_PLAYER *other;
    SpaceData *temp_a0_3;
    s16 otherNo;
    s16 playerNo;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s1;
    s32 walk;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_v0;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_4;
    s8 temp_v0_2;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 temp_v1_3;
    s8 temp_v1_4;
    s8 var_a1;
    s8 var_v0_10;
    s8 var_v0_2;
    s8 var_v0_7;

    playerNo = MBDGetCurrentPlayerIndex();
    otherNo = MBDGetCurrentPlayerIndex() ^ 1;
    cur = MBDGetPlayerStruct(CUR_PLAYER);
    other = MBDGetPlayerStruct(otherNo);
    walk = mbWalkNum;
    spaceIdx = D_80119410_duel01;
    temp_v1 = other->clink;
    if (temp_v1 != 1) {
        if (temp_v1 >= 2) {
            if (temp_v1 != 2) {
                return 1;
            }
            if (!(other->rev & 1) && (other->nlink != 0)) {
                if (other->cidx >= spaceIdx.idx[walk]) {
                    var_v0 = 1;
                    if (other->stats.partners.frontID == 4) {
                        temp_a0_2 = cur->stats.partners.frontPower;
                        if (temp_a0_2 < (cur->star + cur->stats.partners.frontHp)) {
                            return 1;
                        }
                        return temp_a0_2 >= (other->stats.partners.frontHp + other->star);
                    }
                    return var_v0;
                }
                if (other->stats.partners.frontID == 8) {
                    var_v0 = 0;
                    if (cur->star >= 2) {
                        goto block_169;
                    }
                    return var_v0;
                }
block_169:
                if (((other->stats.partners.frontID != 3) || (var_v0 = 0, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) && ((other->stats.partners.frontID != 0xA) || (var_v0 = 0, ((other->stats.partners.frontPower < (cur->stats.partners.backHp + cur->star)) != 0))) && ((temp_v1_2 = cur->stats.partners.frontHp, ((temp_v1_2 < other->stats.partners.frontPower) == 0)) || (var_v0 = 0, ((cur->stats.partners.backHp < temp_v1_2) != 0)))) {
                    var_v0 = 1;
                    if (func_800EFE20_name_81(100.0f) >= 0x32) {
                        return 0;
                    }
                }
                return var_v0;
            }
            if (other->cidx < spaceIdx.idx[walk]) {
                if ((walk == 4) && (cur->stats.partners.frontPoweredUp != 2)) {
                    var_s1 = 0x64;
                    if (func_800F8980_name_81(playerNo) != 0) {
                        var_s1_3 = GwPlayer[playerNo].coin - 5;
                        var_v0_5 = func_800F8980_name_81(playerNo) * 2;
                        goto block_195;
                    }
                    goto block_196;
                }
                if (walk == 3) {
                    goto block_183;
                }
                temp_a0_3 = MBDMasuGet(0xF);
                if (walk == 1) {
                    if ((temp_a0_3->space_type - 0xB) == GwPlayer[playerNo].chr) {
                        var_s1 = 0x64;
                        if (func_800F8980_name_81(playerNo) != 0) {
                            temp_s0_2 = func_800FD498_name_81();
                            var_s1_3 = GwPlayer[playerNo].coin + (temp_s0_2 - 5);
                            var_v0_5 = func_800F8980_name_81(playerNo) * 2;
                            goto block_195;
                        }
                    } else if (temp_a0_3->space_type == 6) {
                        var_s1 = 0x64;
                        if (func_800F8980_name_81(playerNo) != 0) {
                            goto block_194;
                        }
                    } else {
                        var_s1 = 0x64;
                        if (func_800F8980_name_81(playerNo) != 0) {
                            temp_s0_3 = func_800FD498_name_81();
                            var_s1_3 = GwPlayer[playerNo].coin - (temp_s0_3 + 5);
                            var_v0_5 = func_800F8980_name_81(playerNo) * 2;
                            goto block_195;
                        }
                    }
                } else {
                    var_s1 = 0x64;
                    if (func_800F8980_name_81(playerNo) != 0) {
block_194:
                        var_v0_5 = func_800F8980_name_81(playerNo);
                        var_s1_3 = GwPlayer[playerNo].coin - 5;
                        goto block_195;
                    }
                }
                goto block_196;
            }
            if (cur->stats.partners.frontID == 8) {
                var_v0 = 1;
                if (other->star >= 2) {
                    goto block_200;
                }
                return var_v0;
            }
block_200:
            if ((cur->stats.partners.frontID != 3) || (var_v0 = 1, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                if (cur->stats.partners.frontID == 0xA) {
                    if (cur->stats.partners.frontPower >= (other->stats.partners.frontHp + other->star)) {
                        return 1;
                    }
                    goto block_206;
                }
                var_v0 = 1;
                if (cur->stats.partners.frontPower < (other->star + other->stats.partners.backHp)) {
block_206:
                    if (other->stats.partners.backID == 4) {
                        if (cur->stats.partners.frontPower >= (cur->stats.partners.frontHp + cur->star)) {
                            return 0;
                        }
                        temp_s1 = cur->stats.partners.frontHp - cur->stats.partners.frontPower;
                        var_v0_4 = (cur->star + cur->stats.partners.backHp) - (-(temp_s1 < 1) & temp_s1);
                        goto block_211;
                    }
                    var_s1_4 = 0x64;
                    if (func_800F8980_name_81(playerNo) != 0) {
                        var_s1_4 = (s32) (GwPlayer[playerNo].coin - 5) / func_800F8980_name_81(playerNo);
                    }
                    var_v0 = 1;
                    if (!((walk == 6) & (var_s1_4 >= 2))) {
                        if (other->cidx != spaceIdx.idx[walk]) {
                            if (other->stats.partners.frontID == 8) {
                                var_v0 = 0;
                                if (cur->star >= 2) {
                                    goto block_223;
                                }
                                return var_v0;
                            }
block_223:
                            if ((other->stats.partners.frontID != 3) || (var_v0 = 0, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                                if (other->stats.partners.frontID == 0xA) {
                                    var_v0_6 = cur->stats.partners.frontHp + cur->star;
                                } else {
                                    var_v0_6 = cur->star + cur->stats.partners.backHp;
                                }
                                if (other->stats.partners.frontPower >= var_v0_6) {
                                    return 0;
                                }
                                var_v0 = 1;
                                if (cur->stats.partners.frontPower == 0) {
                                    var_v0 = other->stats.partners.frontPower == 0;
                                }
                                return var_v0;
                            }
                            return var_v0;
                        }
                        var_v0_3 = cur->stats.partners.frontPower == 0;
                        var_v1_2 = walk == 1;
                        goto block_219;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            return var_v0;
        }
        if (temp_v1 != 0) {
            return 1;
        }
        if (other->cidx == (walk - 1)) {
            if (cur->stats.partners.frontID != 3) {
                if (other->stats.partners.backID == 4) {
                    temp_a0 = cur->stats.partners.frontPower;
                    if (temp_a0 >= (cur->star + cur->stats.partners.frontHp)) {
                        return temp_a0 < (other->stats.partners.backHp + other->star);
                    }
                }
                return (cur->stats.partners.frontPower == 0) & (walk != 6);
            }
            goto block_45;
        }
        if (other->cidx < (walk - 1)) {
            var_a1 = cur->star;
            if (cur->stats.partners.frontID == 8) {
                var_v0 = 0;
                if (other->star >= 2) {
                    goto block_99;
                }
                return var_v0;
            }
block_99:
            if ((cur->stats.partners.frontID != 3) || (var_v0 = 0, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                if (cur->stats.partners.frontID == 0xA) {
                    var_v0_7 = other->stats.partners.frontHp;
                } else {
                    var_v0_7 = other->stats.partners.backHp;
                }
                if (cur->stats.partners.frontPower < (var_v0_7 + other->star)) {
                    if (other->stats.partners.backID == 4) {
                        var_v0 = 1;
                        if (cur->stats.partners.frontPower < (cur->star + cur->stats.partners.frontHp)) {
                            temp_a0_4 = cur->stats.partners.frontPower;
                            temp_v1_3 = cur->stats.partners.frontHp;
                            if (temp_v1_3 < temp_a0_4) {
                                var_a1 -= temp_a0_4 - temp_v1_3;
                            }
                            goto block_110;
                        }
                        return var_v0;
                    }
block_110:
                    if (walk == 5) {
                        if (cur->stats.partners.backPower < (other->stats.partners.frontHp + other->star)) {
                            var_v0 = 0;
                            if (other->stats.partners.frontID == 4) {
                                var_v0_2 = cur->stats.partners.backPower;
                                var_v1 = var_a1 + cur->stats.partners.backHp;
                                goto block_122;
                            }
                            return var_v0;
                        }
                        goto block_45;
                    }
                    if (((GwSystem.current_turn != GwSystem.total_turns) | (playerNo == 0)) != 0) {
                        if (other->stats.partners.frontID == 8) {
                            var_v0 = 1;
                            if (cur->star >= 2) {
                                goto block_118;
                            }
                            return var_v0;
                        }
block_118:
                        if ((other->stats.partners.frontID != 3) || (var_v0 = 1, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                            if (other->stats.partners.frontID == 0xA) {
                                var_v1 = cur->stats.partners.frontHp + cur->star;
                                var_v0_2 = other->stats.partners.frontPower;
                                goto block_122;
                            }
                            var_v0 = 1;
                            if ((cur->stats.partners.backHp + cur->star) >= other->stats.partners.frontPower) {
                                goto block_124;
                            }
                            return var_v0;
                        }
                        return var_v0;
                    }
block_124:
                    temp_v0_2 = cur->stats.partners.frontID;
                    var_v0 = 0;
                    if (((temp_v0_2 == 3) | (temp_v0_2 == 8)) == 0) {
                        if (cur->stats.partners.frontID == 0xA) {
                            if (cur->stats.partners.frontPower < other->stats.partners.frontHp) {
                                var_v0_8 = other->stats.partners.frontPower < other->stats.partners.backHp;
                                goto block_128;
                            }
                            goto block_132;
                        }
                        temp_v1_4 = other->stats.partners.backHp;
                        if (cur->stats.partners.frontPower < temp_v1_4) {
                            var_v0_8 = other->stats.partners.frontPower < temp_v1_4;
block_128:
                            if (var_v0_8 == 0) {
                                return 1;
                            }
                            goto block_132;
                        }
block_132:
                        var_v0 = 0;
                        if (cur->stats.partners.frontPower == 0) {
                            var_v0 = 0;
                            if (cur->stats.partners.backID != 4) {
                                return 1;
                            }
                        }
                        return var_v0;
                    }
                    return var_v0;
                }
                goto block_45;
            }
            return var_v0;
        }
        var_v0 = 0;
        if (walk != 1) {
            if (other->cidx >= 8) {
                if (other->stats.partners.frontPower != 0) {
                    var_v0 = 0;
                    if (walk == 6) {
                        if (other->stats.partners.frontID == 4) {
                            if (cur->stats.partners.backPower >= (cur->stats.partners.backHp + cur->star)) {
                                return 0;
                            }
                            goto block_143;
                        }
block_143:
                        return cur->stats.partners.backPower != 0;
                    }
                    return var_v0;
                }
                if (walk != 3) {
                    if ((walk == 2) && (cur->stats.partners.frontPoweredUp != walk)) {
                        var_s1_2 = 0x64;
                        if (func_800F8980_name_81(playerNo) != 0) {
                            var_s1_5 = GwPlayer[playerNo].coin - 5;
                            var_v0_9 = func_800F8980_name_81(playerNo) * 2;
                            goto block_151;
                        }
                    } else {
                        var_s1_2 = 0x64;
                        if (func_800F8980_name_81(playerNo) != 0) {
                            var_v0_9 = func_800F8980_name_81(playerNo);
                            var_s1_5 = GwPlayer[playerNo].coin - 5;
block_151:
                            var_s1_2 = var_s1_5 / var_v0_9;
                        }
                    }
                    return var_s1_2 > 0;
                }
                goto block_183;
            }
            if (other->cidx < 5) {
                return 0;
            }
            return (u32) (walk - 9) < 2U;
        }
        return var_v0;
    }
    if (other->cidx == (walk - 6)) {
        var_v0 = 1;
        if (other->stats.partners.backID == 4) {
            return cur->stats.partners.frontPower < (cur->star + cur->stats.partners.frontHp);
        }
        return var_v0;
    }
    if (other->cidx < (walk - 6)) {
        if (cur->stats.partners.frontID == 8) {
            var_v0 = 1;
            if (other->star >= 2) {
                goto block_15;
            }
            return var_v0;
        }
block_15:
        if ((cur->stats.partners.frontID != 3) || (var_v0 = 1, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
            if (cur->stats.partners.frontID == 0xA) {
                var_v0_10 = other->stats.partners.frontHp;
            } else {
                var_v0_10 = other->stats.partners.backHp;
            }
            if (cur->stats.partners.frontPower >= (var_v0_10 + other->star)) {
                return 1;
            }
            if ((other->stats.partners.backID != 4) || (var_v0 = 0, ((cur->stats.partners.frontPower < (cur->star + cur->stats.partners.frontHp)) != 0))) {
                if (((GwSystem.current_turn != GwSystem.total_turns) | (playerNo == 0)) != 0) {
                    if (other->stats.partners.frontID == 8) {
                        var_v0 = 0;
                        if (cur->star >= 2) {
                            goto block_28;
                        }
                        return var_v0;
                    }
block_28:
                    if ((other->stats.partners.frontID != 3) || (var_v0 = 0, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                        if (other->stats.partners.frontID == 0xA) {
                            var_v0_4 = cur->stats.partners.frontHp + cur->star;
block_211:
                            return other->stats.partners.frontPower < var_v0_4;
                        }
                        var_v0 = 0;
                        if ((cur->stats.partners.backHp + cur->star) >= other->stats.partners.frontPower) {
                            goto block_33;
                        }
                        return var_v0;
                    }
                    return var_v0;
                }
block_33:
                var_v0 = 1;
                if (cur->stats.partners.frontPower == 0) {
                    var_v0 = 1;
                    if (cur->stats.partners.backID != 4) {
                        return 0;
                    }
                }
                return var_v0;
            }
            return var_v0;
        }
        return var_v0;
    }
    switch (walk) {                              /* irregular */
    case 1:
        if (other->cidx >= 6) {
            if (cur->stats.partners.backID == 8) {
                var_v0 = 0;
                if (other->star >= 2) {
                    goto block_41;
                }
                return var_v0;
            }
block_41:
            if ((cur->stats.partners.backID != 3) || (var_v0 = 0, ((cur->stats.partners.frontPoweredUp < other->star) != 0))) {
                if (cur->stats.partners.backID == 0xA) {
                    if (cur->stats.partners.backPower >= (other->stats.partners.backHp + other->star)) {
                        goto block_45;
                    }
                    goto block_49;
                }
                if ((other->stats.partners.frontHp + other->star) < cur->stats.partners.backPower) {
                    return 0;
                }
block_49:
                var_v0 = 0;
                if (other->stats.partners.frontID == 4) {
                    var_v0_2 = cur->stats.partners.backPower;
                    var_v1 = cur->star + cur->stats.partners.backHp;
block_122:
                    return var_v0_2 >= var_v1;
                }
                return var_v0;
            }
            return var_v0;
        }
        if (other->stats.partners.frontPower != 0) {
            if (other->stats.partners.frontID == 8) {
                var_v0 = 1;
                if (cur->star >= 2) {
                    goto block_55;
                }
                return var_v0;
            }
block_55:
            if ((other->stats.partners.frontID != 3) || (var_v0 = 1, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                if (other->stats.partners.frontID == 0xA) {
                    if (other->stats.partners.frontPower >= (cur->stats.partners.frontHp + cur->star)) {
                        return 1;
                    }
                    goto block_64;
                }
                var_v0 = 0;
                if (cur->stats.partners.backHp < other->stats.partners.frontPower) {
                    if (other->stats.partners.frontPower >= (cur->stats.partners.backHp + cur->star)) {
                        return 1;
                    }
block_64:
                    return (MBDMasuGet(0xF)->space_type - 0xB) == GwPlayer[playerNo].chr;
                }
                return var_v0;
            }
            return var_v0;
        }
    case 6:
block_45:
        return 0;
    case 4:
        if (cur->stats.partners.frontPoweredUp != 2) {
            var_s1 = 0x64;
            if (func_800F8980_name_81(playerNo) != 0) {
                var_s1_3 = GwPlayer[playerNo].coin - 5;
                var_v0_5 = func_800F8980_name_81(playerNo) * 2;
block_195:
                var_s1 = var_s1_3 / var_v0_5;
            }
block_196:
            return var_s1 >= 2;
        }
        if (walk == 5) {
        case 5:
            var_s1_6 = 0x64;
            if (func_800F8980_name_81(playerNo) != 0) {
                var_s1_6 = (s16) GwPlayer[playerNo].coin / func_800F8980_name_81(playerNo);
            }
            if ((cur->stats.partners.frontPower == 0) || (var_v0 = 0, (((cur->stats.partners.backHp != 0) & (var_s1_6 >= 4)) == 0))) {
                if (other->stats.partners.frontID == 8) {
                    var_v0 = 1;
                    if (cur->star >= 2) {
                        goto block_79;
                    }
                    return var_v0;
                }
block_79:
                if ((other->stats.partners.frontID != 3) || (var_v0 = 1, ((other->stats.partners.frontPoweredUp < cur->star) != 0))) {
                    if (other->stats.partners.frontID == 0xA) {
                        if (other->stats.partners.frontPower >= (cur->stats.partners.frontHp + cur->star)) {
                            return 1;
                        }
                        goto block_85;
                    }
                    var_v0 = 1;
                    if (other->stats.partners.frontPower < (cur->stats.partners.backHp + cur->star)) {
                        goto block_85;
                    }
                    return var_v0;
                }
                return var_v0;
            }
            return var_v0;
        }
    default:
block_85:
        var_s1_7 = 0x64;
        if (func_800F8980_name_81(playerNo) == 0) {
            var_v1_3 = 0x64;
        } else {
            temp_s0_4 = playerNo * 0x38;
            var_s1_7 = (s32) (*(&GwPlayer->coin + temp_s0_4) - 5) / func_800F8980_name_81(playerNo);
            var_v1_3 = (s16) *(&GwPlayer->coin + temp_s0_4) / func_800F8980_name_81(playerNo);
        }
        var_v0_3 = var_s1_7 < 2;
        var_v1_2 = var_v1_3 >= 2;
block_219:
        return (var_v0_3 & var_v1_2) == 0;
    case 3:
block_183:
        return func_800EFE20_name_81(100.0f) < 0x32;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80116484_duel01);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119410_duel01);

// duel b5: masked 13 (retail reloads the table entry after the equality test)
#ifdef NON_MATCHING
s32 func_80117480_duel01(void) {
    DuelSpaceTbl spaceIdx;
    GW_PLAYER *cur;
    GW_PLAYER *other;
    s32 otherNo;
    s32 walk;
    s32 chance;

    otherNo = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    cur = MBDGetPlayerStruct(CUR_PLAYER);
    other = MBDGetPlayerStruct(otherNo);
    walk = mbWalkNum;
    spaceIdx = D_80119410_duel01;
    if (!(other->rev & 1) && other->nlink != 0) {
        if (other->cidx != spaceIdx.idx[walk]) {
            return other->cidx >= spaceIdx.idx[walk];
        }
        goto yes;
    }
    if (!(spaceIdx.idx[walk] < other->cidx)) {
        return 1;
    }
    if (!(other->stats.partners.frontPower < cur->star + cur->stats.partners.backHp)) {
        return 0;
    }
    if (other->stats.partners.frontPower < cur->stats.partners.frontPower) {
        return 1;
    }
    if (cur->stats.partners.frontPower == 0) {
        return 0;
    }
    switch (GwPlayer[MBDGetCurrentPlayerIndex()].chr) {
    case 4:
    case 5:
    case 6:
        chance = func_800EFE20_name_81(100.0f) < 80;
        break;
    case 0:
    case 3:
    case 7:
        chance = func_800EFE20_name_81(100.0f) < 50;
        break;
    default:
        chance = func_800EFE20_name_81(100.0f) < 20;
        break;
    }
    if (!chance) {
        return 0;
    }
yes:
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117480_duel01);
#endif

void func_80117624_duel01(void) {
    DuelPadMask padMask;
    DuelChoiceTbl choice;
    s32 playerNo;
    GW_PLAYER *player;
    s32 space;
    s16 result;

    playerNo = MBDGetCurrentPlayerIndex();
    player = MBDGetPlayerStruct(CUR_PLAYER);
    space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);
    if (space == 1) {
        return;
    }
    if (space == 0x13) {
        func_800ECD88_name_81(-1, 1, 0);
        func_8010EB44_duel01(0);
        return;
    }
    func_800ECD88_name_81(-1, 1, 0);
    func_800F38DC_name_81(-1, -1, 2);
    func_800EBDDC_name_81(-1, 8, 0x23);
    HuPrcSleep(8);
    func_800DB3E0_name_81(playerNo);
    if (player->coin < 5) {
        func_800EB140_name_81(0x12, 0x2103);
    } else {
        padMask = D_80118FE4_duel01;
        choice = D_80118FE8_duel01;
    loop:
        func_800EB1D8_name_81(0x12, 0x2100);
        if (func_800F37B8_name_81(playerNo) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[playerNo].pad]);
            choice.choice[GwPlayer[playerNo].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (func_800D97B0_name_81(D_80118AEC_duel01) == 0) {
                choice.choice[GwPlayer[playerNo].pad] = 0x400;
                func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            }
            choice.choice[GwPlayer[playerNo].pad] = -0x8000;
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        result = func_8005E1D8_main(D_8010555C_name_81, 0, 1);
        choice.choice[GwPlayer[playerNo].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (result == 2) {
            func_801059D0_duel01();
            goto loop;
        }
        if (result == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(playerNo);
            mbItemBtnF = 1;
            goto loop;
        }
        if (result == 0) {
            func_800E14D8_name_81(playerNo, -5);
            func_800F7378_name_81(playerNo, -5);
            HuPrcSleep(30);
            func_800ECD88_name_81(-1, 2, 0);
            func_800ED788_name_81(playerNo);
            func_800EB140_name_81(0x12, 0x2101);
            func_8010EAD4_duel01(0);
        } else {
            func_800EB140_name_81(0x12, 0x2102);
        }
    }
    func_800DADA0_name_81(playerNo);
}

void func_801179AC_duel01(void) {
    DuelPadMask padMask;
    DuelChoiceTbl choice;
    s32 playerNo;
    GW_PLAYER *player;
    s32 space;
    s16 result;

    playerNo = MBDGetCurrentPlayerIndex();
    player = MBDGetPlayerStruct(CUR_PLAYER);
    space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);
    if (space == 0xD) {
        return;
    }
    if (space == 0xF) {
        func_800ECD88_name_81(-1, 0, 0);
        func_8010EB44_duel01(1);
        return;
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800ECD88_name_81(-1, 0, 0);
    func_800EBDDC_name_81(-1, 8, 0x20);
    HuPrcSleep(8);
    func_800DB3E0_name_81(playerNo);
    if (player->coin < 5) {
        func_800EB140_name_81(0x12, 0x2103);
    } else {
        padMask = D_80118FE4_duel01;
        choice = D_80118FE8_duel01;
    loop:
        func_800EB1D8_name_81(0x12, 0x2100);
        if (func_800F37B8_name_81(playerNo) == 0) {
            func_8005FE54_main(D_8010555C_name_81, padMask.mask[GwPlayer[playerNo].pad]);
            choice.choice[GwPlayer[playerNo].pad] = -1;
            func_8005F744_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3]);
        } else {
            if (func_800D97B0_name_81(D_80118CC0_duel01) == 0) {
                choice.choice[GwPlayer[playerNo].pad] = 0x400;
                func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            }
            choice.choice[GwPlayer[playerNo].pad] = -0x8000;
            func_8005F698_main(choice.choice[0], choice.choice[1], choice.choice[2], choice.choice[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        result = func_8005E1D8_main(D_8010555C_name_81, 0, 1);
        choice.choice[GwPlayer[playerNo].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (result == 2) {
            func_801059D0_duel01();
            goto loop;
        }
        if (result == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(playerNo);
            mbItemBtnF = 1;
            goto loop;
        }
        if (result == 0) {
            func_800E14D8_name_81(playerNo, -5);
            func_800F7378_name_81(playerNo, -5);
            HuPrcSleep(30);
            func_800ECD88_name_81(-1, 2, 5);
            func_800ECDE8_name_81();
            func_800ED788_name_81(playerNo);
            func_800EB140_name_81(0x12, 0x2101);
            func_8010EAD4_duel01(1);
        } else {
            func_800EB140_name_81(0x12, 0x2102);
        }
    }
    func_800DADA0_name_81(playerNo);
}

void func_80117D3C_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (space == MBDMasuLinkMasuIdGet(player->clink, player->cidx + 1)) {
        func_800E9F4C_name_81(0x21, &player->nlink, &player->nidx);
    }
}

void func_80117DDC_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (space == MBDMasuLinkMasuIdGet(player->clink, player->cidx + 1)) {
        func_800E9F4C_name_81(0x22, &player->nlink, &player->nidx);
    }
}

void func_80117E7C_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (MBDMasuLinkMasuIdGet(player->nlink, player->nidx) == 0x22) {
        func_8010EAD4_duel01(0);
    }
}

void func_80117ED8_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (player->rev & 1) {
        if (mbWalkNum != 0) {
            func_8010EAD4_duel01(0);
        }
    } else {
        func_8010EB44_duel01(0);
    }
    if (player->rev & 1) {
        func_800E9F4C_name_81(1, &player->nnlink, &player->nnidx);
    }
    if (space != 0x22) {
        if (space == MBDMasuLinkMasuIdGet(player->clink, player->cidx + 1)) {
            func_800E9F4C_name_81(0x22, &player->nlink, &player->nidx);
            func_800ECE10_name_81();
            return;
        }
        osSyncPrintf("route 3 start error\n");
        while (1) {
        }
    }
}

void func_80117FFC_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (MBDMasuLinkMasuIdGet(player->nlink, player->nidx) == 0x21) {
        func_8010EAD4_duel01(1);
    }
}

void func_80118058_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 space = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (player->rev & 1) {
        func_8010EB44_duel01(1);
    } else if (mbWalkNum != 0) {
        func_8010EAD4_duel01(1);
    }
    if (!(player->rev & 1)) {
        func_800E9F4C_name_81(0xD, &player->nnlink, &player->nnidx);
    }
    if (space != 0x21) {
        if (space == MBDMasuLinkMasuIdGet(player->clink, player->cidx - 1)) {
            func_800E9F4C_name_81(0x21, &player->nlink, &player->nidx);
            return;
        }
        osSyncPrintf("route 3 end error\n");
        while (1) {
        }
    }
}

void func_80118178_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(1, &player->nnlink, &player->nnidx);
    }
}

void func_801181C4_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x22, &player->nnlink, &player->nnidx);
    }
}

void func_80118210_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(0xD, &player->nnlink, &player->nnidx);
    }
}

void func_8011825C_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x21, &player->nnlink, &player->nnidx);
    }
}

void func_801182A8_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1)) {
        func_800E9F4C_name_81(0x21, &player->nnlink, &player->nnidx);
    }
}

void func_801182E4_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (player->rev & 1) {
        func_800E9F4C_name_81(0x22, &player->nnlink, &player->nnidx);
    }
}

void func_80118320_duel01(void) {
}

// control flow (66 vs 65, masked 13): retail keeps cur->nidx in a1 from the opening compare for the first
// rev&1 arm; ours reloads it (tried early returns, nested opening test)
#ifdef NON_MATCHING
s32 func_80118328_duel01(void) {
    GW_PLAYER *cur;
    GW_PLAYER *other;
    s32 curIdx;
    s32 otherIdx;
    s32 ret;

    curIdx = GwSystem.current_player_index;
    otherIdx = (curIdx + 1) & 1;
    cur = MBDGetPlayerStruct(curIdx);
    other = MBDGetPlayerStruct(otherIdx);
    if (cur->nlink == other->clink && cur->nidx == other->cidx) {
        if (cur->nlink == 2) {
            if (cur->rev & 1) {
                if (other->rev & 1) {
                    ret = 0;
                } else if (cur->nidx != 0 || other->nlink != 0) {
                    ret = 3;
                } else {
                    ret = 0;
                }
            } else if (other->rev & 1) {
                ret = 3;
            } else if (cur->nidx != 0 || other->nlink != 0) {
                ret = 0;
            } else {
                ret = 3;
            }
        } else if (cur->rev & 4) {
            ret = 1;
        } else {
            ret = 0;
        }
        return ret;
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118328_duel01);
#endif

void func_80118414_duel01(void) {
    s8 linkIdx[2]; // link, index
    Vec pos[3]; // center, front, back
    GW_PLAYER *player;
    SpaceData *space;
    s8 playerNo;

    playerNo = GwSystem.current_player_index ^ 1;
    player = MBDGetPlayerStruct(playerNo);
    func_800E9F4C_name_81(0x1E, &linkIdx[0], &linkIdx[1]);
    func_800ECD0C_name_81(playerNo, linkIdx[0], linkIdx[1]);
    player->rev = 0;
    player->nnlink = -2;
    player->nnidx = -2;
    space = MBDMasuGet(0x1E);
    HuVecAdd(&pos[0], &space->coords, &MBDMasuGet(0x1D)->coords);
    HuVecMulScalar(&pos[0], 0.5f, &pos[0]);
    HuVecCopy3F(&pos[1], &pos[0]);
    pos[1].x -= 12.0f;
    HuVecCopy3F(&pos[2], &pos[0]);
    pos[2].x += 12.0f;
    func_800E27D4_name_81(playerNo, &pos[0], &pos[1], &pos[2]);
}

void func_80118530_duel01(void) {
    GW_PLAYER *player;
    UnkEA790Struct *tree;
    Process *process;
    s32 result;
    s32 i;
    s32 count;
    s8 link;
    s8 idx;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (player->nnlink == -2 && player->nnidx == player->nnlink) {
        player->nnlink = -1;
        player->nnidx = -1;
        func_800F38DC_name_81(-1, -1, 2);
        HuPrcVSleep();
        func_80105A58_duel01();
        tree = func_800D76A0_name_81(GwSystem.current_player_index, D_80118DE4_duel01);
        func_800D742C_name_81(tree, GwSystem.current_player_index, 0);
        if (func_800F37B8_name_81(-1) != 0) {
            count = func_800D97B0_name_81(D_80118CF0_duel01);
            for (i = 0; i < count; i++) {
                func_800D7250_name_81(tree, -2);
            }
            func_800D7250_name_81(tree, -4);
        }
        result = func_800D7518_name_81(tree);
        func_800D6CA0_name_81(tree);
        func_80105B10_duel01();
        if (result != 0) {
            link = player->nlink;
            idx = player->nidx;
            player->nlink = player->blink;
            player->nidx = player->bidx;
            player->blink = link;
            player->bidx = idx;
            func_800ECDE8_name_81();
            process = func_800ED70C_name_81(GwSystem.current_player_index, 1);
            if (process != NULL) {
                HuPrcChildLink(HuPrcCurrentGet(), process);
            }
            process = func_800EDC6C_name_81(GwSystem.current_player_index, 0);
            if (process != NULL) {
                HuPrcChildLink(HuPrcCurrentGet(), process);
            }
            HuPrcChildWait();
        }
    }
}

// duel b5: functions the .data names (other forks' units still asm)
void func_80110C3C_duel01(void);
void func_80111DFC_duel01(void);
void func_801123E8_duel01(void);
void func_801124D8_duel01(void);
void func_80112514_duel01(void);
void func_80112590_duel01(void);
void func_801125CC_duel01(void);
void func_8011264C_duel01(void);
void func_801129C8_duel01(void);
void func_80112BB4_duel01(void);
void func_80112DA0_duel01(void);
void func_801135D8_duel01(void);
void func_801138D0_duel01(void);
s32 func_80113CAC_duel01(void);
s32 func_801147FC_duel01(void);
s32 func_80115850_duel01(void);
s32 func_801159F8_duel01(void);
s32 func_80116484_duel01(void);
s32 func_80117480_duel01(void);

/* .data */
// duel b5: the unit's .data (0x3EB800, 0x750 bytes)
s32 D_80118710_duel01[2] = { 0x37, 0x39 };
s32 D_80118718_duel01[5] = { 4, 0xA0035, 0xA003A, 0xA003B, 0xA003F }; /* count, then file ids */
f32 D_8011872C_duel01 = 3.0f;
s32 D_80118730_duel01[4] = { 3, 0xA011D, 0xA011E, 0xA0121 }; /* count, then file ids */
s16 D_80118740_duel01 = 0x25; /* bell object: from space id */
s16 D_80118742_duel01 = 0x24; /* to */
Process *D_80118744_duel01 = NULL;
s16 D_80118748_duel01 = 0x26; /* second object: from space id */
s16 D_8011874A_duel01 = 0x1F; /* to */
Process *D_8011874C_duel01 = NULL;
s16 D_80118750_duel01[2] = { 0x23, 0x20 }; /* per object: start space id */
s16 D_80118754_duel01[2][2] = { { 0x13, 0x22 }, { 0xF, 0x21 } }; /* per object: from, to space ids */
s32 D_8011875C_duel01 = 0;
s8 D_80118760_duel01[13 * 2] = { /* value, chance pairs (D_80118761_duel01 = [1]) */
    7, 30, 6, 30, 4, 30, 1, 30, 11, 30, 8, 20, 3, 20,
    10, 20, 0, 20, 2, 20, 9, 20, 5, 20, -1, -1,
};
Duel01Weight D_8011877C_duel01[14] = {
    { 0, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_80118798_duel01[14] = {
    { 1, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_801187B4_duel01[14] = {
    { 2, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_801187D0_duel01[14] = {
    { 4, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_801187EC_duel01[14] = {
    { 3, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_80118808_duel01[14] = {
    { 5, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_80118824_duel01[14] = {
    { 7, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight D_80118840_duel01[14] = {
    { 6, 50 }, { 7, 20 }, { 6, 20 }, { 4, 20 }, { 1, 20 }, { 11, 20 }, { 8, 10 },
    { 3, 10 }, { 10, 10 }, { 0, 10 }, { 2, 10 }, { 9, 10 }, { 5, 10 }, { -1, -1 },
};
Duel01Weight *D_8011885C_duel01[8] = {
    D_8011877C_duel01, D_80118798_duel01, D_801187B4_duel01, D_801187D0_duel01,
    D_801187EC_duel01, D_80118808_duel01, D_80118824_duel01, D_80118840_duel01,
};
/* the asm reads the low halves: D_8011887E/82/86_duel01 = (s16 *)&[0..2] + 1 */
s32 D_8011887C_duel01[2][3] = { { 0x1C, 0x24, 0x25 }, { 0x1B, 0x1F, 0x26 } };
s32 D_80118894_duel01 = -1;
Object *D_80118898_duel01 = NULL;
s32 D_8011889C_duel01 = 0;
event_list_entry D_801188A0_duel01[2] = {
    { 1, 1, func_80110B7C_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_801188B0_duel01[2] = {
    { 1, 1, func_80110BD8_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_801188C0_duel01[2] = {
    { 7, 1, func_80110C3C_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_801188D0_duel01[3] = {
    { 1, 1, func_80111DFC_duel01 },
    { 8, 1, func_80118530_duel01 },
    { 0, 0, NULL },
};
/* indexed from 1: the asm addresses it as D_801188E4_duel01 (= this - 4) */
void (*D_801188E8_duel01[11])(void) = {
    func_801123E8_duel01, func_801124D8_duel01, func_80112514_duel01, func_80112590_duel01,
    func_801125CC_duel01, func_8011264C_duel01, func_801129C8_duel01, func_80112BB4_duel01,
    func_80112DA0_duel01, func_801135D8_duel01, func_801138D0_duel01,
};
event_table_entry D_80118914_duel01[5] = {
    { 28, D_801188A0_duel01 },
    { 27, D_801188B0_duel01 },
    { -5, D_801188C0_duel01 },
    { 30, D_801188D0_duel01 },
    { -1, NULL },
};
DecisionTreeNonLeafNode D_8011893C_duel01[2] = {
    { 0x5, { .func = func_80113CAC_duel01 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80118954_duel01[3] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_8011893C_duel01 } },
    { 0x5, { .func = func_801147FC_duel01 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80118978_duel01[3] = {
    { 0x2, { .data = 0x00000020 }, { .data = 0x1B56AD5A } },
    { 0x2, { .data = 0x00000001 }, { .data = 0x08D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_8011899C_duel01[4] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x0001050B }, { .data = 0x0B56AD5A } },
    { 0xF, { .data = 0x00000004 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_801189CC_duel01[2] = {
    { 0x5, { .func = func_80115850_duel01 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_801189E4_duel01[8] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80118978_duel01 } },
    { 0x2, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0x2, { .data = 0x00000020 }, { .data = 0x1B56AD5A } },
    { 0x7, { .data = 0x00000007 }, { .node_data = D_8011899C_duel01 } },
    { 0xB, { .data = 0x00020005 }, { .node_data = D_801189CC_duel01 } },
    { 0xB, { .data = 0x0001050B }, { .data = 0x0B56AD5A } },
    { 0xF, { .data = 0x00000004 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80118A44_duel01[3] = {
    { 0x2, { .data = 0x0000001F }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0A142850 } },
};
DecisionTreeNonLeafNode D_80118A68_duel01[3] = {
    { 0x17, { .data = 0x00000020 }, { .data = 0x1A142850 } },
    { 0x17, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_80118A8C_duel01[3] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1A142850 } },
    { 0xF, { .data = 0x00000003 }, { .data = 0x18D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80118AB0_duel01[5] = {
    { 0x15, { .data = 0x00000001 }, { .node_data = D_80118A44_duel01 } },
    { 0x7, { .data = 0x00000006 }, { .node_data = D_80118A8C_duel01 } },
    { 0xB, { .data = 0x00020005 }, { .node_data = D_80118A68_duel01 } },
    { 0xF, { .data = 0x00000003 }, { .data = 0x18D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80118AEC_duel01[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80118954_duel01 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_801189E4_duel01 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80118AB0_duel01 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_80118B1C_duel01[2] = {
    { 0x5, { .func = func_801159F8_duel01 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80118B34_duel01[3] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80118B1C_duel01 } },
    { 0x5, { .func = func_80116484_duel01 }, { .data = 0x1C993264 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
DecisionTreeNonLeafNode D_80118B58_duel01[3] = {
    { 0x2, { .data = 0x00000020 }, { .data = 0x1B56AD5A } },
    { 0x2, { .data = 0x00000001 }, { .data = 0x08D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80118B7C_duel01[4] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1B56AD5A } },
    { 0xB, { .data = 0x0000050B }, { .data = 0x0B56AD5A } },
    { 0xF, { .data = 0x00000004 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80118BAC_duel01[2] = {
    { 0x5, { .func = func_80117480_duel01 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0B56AD5A } },
};
DecisionTreeNonLeafNode D_80118BC4_duel01[7] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80118B58_duel01 } },
    { 0x2, { .data = 0x00000001 }, { .data = 0x0B56AD5A } },
    { 0x7, { .data = 0x00000006 }, { .node_data = D_80118B7C_duel01 } },
    { 0xB, { .data = 0x00020005 }, { .node_data = D_80118BAC_duel01 } },
    { 0xB, { .data = 0x0000050B }, { .data = 0x0B56AD5A } },
    { 0xF, { .data = 0x00000004 }, { .data = 0x1B56AD5A } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80118C18_duel01[3] = {
    { 0x2, { .data = 0x0000001F }, { .data = 0x0A142850 } },
    { 0xB, { .data = 0x00020005 }, { .data = 0x1A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x0A142850 } },
};
DecisionTreeNonLeafNode D_80118C3C_duel01[3] = {
    { 0x17, { .data = 0x00000020 }, { .data = 0x1A142850 } },
    { 0x17, { .data = 0x00000001 }, { .data = 0x0A142850 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_80118C60_duel01[3] = {
    { 0xB, { .data = 0x00020005 }, { .data = 0x1A142850 } },
    { 0xF, { .data = 0x00000003 }, { .data = 0x18D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x08D1A346 } },
};
DecisionTreeNonLeafNode D_80118C84_duel01[5] = {
    { 0x15, { .data = 0x00000000 }, { .node_data = D_80118C18_duel01 } },
    { 0x7, { .data = 0x00000006 }, { .node_data = D_80118C60_duel01 } },
    { 0xB, { .data = 0x00020005 }, { .node_data = D_80118C3C_duel01 } },
    { 0xF, { .data = 0x00000003 }, { .data = 0x18D1A346 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x078F1E3C } },
};
DecisionTreeNonLeafNode D_80118CC0_duel01[4] = {
    { 0x16, { .data = 0x00000003 }, { .node_data = D_80118B34_duel01 } },
    { 0x16, { .data = 0x00000002 }, { .node_data = D_80118BC4_duel01 } },
    { 0x16, { .data = 0x00000001 }, { .node_data = D_80118C84_duel01 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_80118CF0_duel01[3] = {
    { 0x15, { .data = 0x00000000 }, { .data = 0x0C97ED50 } },
    { 0x15, { .data = 0x00000001 }, { .data = 0x1C97ED50 } },
    { 0x0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
event_list_entry D_80118D14_duel01[2] = {
    { 1, 1, func_80117624_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D24_duel01[2] = {
    { 1, 1, func_801179AC_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D34_duel01[2] = {
    { 1, 1, func_80117D3C_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D44_duel01[2] = {
    { 1, 1, func_80117DDC_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D54_duel01[3] = {
    { 1, 1, func_80117ED8_duel01 },
    { 8, 1, func_80117E7C_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D6C_duel01[3] = {
    { 1, 1, func_80118058_duel01 },
    { 8, 1, func_80117FFC_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D84_duel01[2] = {
    { 1, 1, func_80118178_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118D94_duel01[2] = {
    { 1, 1, func_801181C4_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118DA4_duel01[2] = {
    { 1, 1, func_80118210_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118DB4_duel01[2] = {
    { 1, 1, func_8011825C_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118DC4_duel01[2] = {
    { 1, 1, func_801182A8_duel01 },
    { 0, 0, NULL },
};
event_list_entry D_80118DD4_duel01[2] = {
    { 1, 1, func_801182E4_duel01 },
    { 0, 0, NULL },
};
s16 D_80118DE4_duel01[3] = { 0x10, 0x11, -1 };
event_table_entry D_80118DEC_duel01[13] = {
    { 34, D_80118D14_duel01 },
    { 33, D_80118D24_duel01 },
    { 13, D_80118D34_duel01 },
    { 1, D_80118D44_duel01 },
    { 19, D_80118D54_duel01 },
    { 15, D_80118D6C_duel01 },
    { 26, D_80118D84_duel01 },
    { 2, D_80118D94_duel01 },
    { 12, D_80118DA4_duel01 },
    { 14, D_80118DB4_duel01 },
    { 16, D_80118DC4_duel01 },
    { 18, D_80118DD4_duel01 },
    { -1, NULL },
};
