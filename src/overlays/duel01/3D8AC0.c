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
#ifdef NON_MATCHING // duel b1: two extra nops after the sindf/cosdf calls
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010615C_duel01);
#endif

void func_80106240_duel01(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

// duel b1: arg0/arg1 typed (were s32, unkStruct05*)
void func_80106260_duel01(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

// duel b1: typed; retail passes func_800EBF2C_name_81 no frame count (its $a3 is left over)
void func_801062C0_duel01(Object *arg0, GW_PLAYER *arg1, s32 arg2) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81);
    }
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
#ifdef NON_MATCHING // duel b1: masked 14, &mid is kept in $s0 from before the HuVecAdd branch in retail
void func_80107188_duel01(s32 playerIndex, s32 targetIndex, Object *partner, Object *target, s32 flags, s32 level) {
    Vec dest;
    Vec start;
    s32 standInIds[2];
    Vec mid;
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
        if (flags & 1) {
            HuVecAdd(&mid, &target->coords, &partner->coords);
        } else {
            HuVecAdd(&mid, &player->player_obj->coords, &partner->coords);
        }
        HuVecMulScalar(&mid, 0.5f, &mid);
        mid.y += partner->velocity.x;
        func_801067D4_duel01(standIn, &mid);
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107188_duel01);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E60_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801079B8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107EBC_duel01);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80108550_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109404_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109888_duel01);

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
/* duel01.h declares func_800D8E88_name_81(void); it takes the Object (ovl_81.h). */
typedef void (*DuelB2ObjFunc)(Object *);
/* Correct types of ovl_81 functions that duel01.h declares wrongly (see ovl_81.h); called through these. */
typedef Object *(*DuelB2ModelCreateFunc)(u8 id, s32 *motions);           // func_800D8010_name_81
typedef Process *(*DuelB2MoveFunc)(Vec *, Vec *, Vec *, f32);             // func_800EC1E4_name_81
typedef void (*DuelB2DirFunc)(Vec *, Vec *, Vec *);                       // func_800EB708_name_81
/* func_80106260_duel01 is defined void, but retail returns func_800EC1E4's process and callers use it. */
typedef Process *(*DuelB2Move2Func)(Object *, GW_PLAYER *, s32, f32);    // func_80106260_duel01
typedef Process *(*DuelB2JumpFunc)(Vec *, Vec *, Vec *, s32);             // func_800EBF2C_name_81
/* func_801062C0_duel01 is defined with an unused f32 last parameter; retail passes the int 30. */
typedef Process *(*DuelB2Jump2Func)(Object *, GW_PLAYER *, s32, s32);    // func_801062C0_duel01

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
void func_80118328_duel01(void);
extern event_table_entry D_80118914_duel01[];
extern event_table_entry D_80118DEC_duel01[];

#ifdef NON_MATCHING
// duel b2: masked 24 of 655: register choice around the &sp98/&sp78 arguments of HuVecSubtract (retail recomputes them per arm); logic checked block by block.
void func_8010A210_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    DuelB2DirFunc dir = (DuelB2DirFunc)(void (*)(void))func_800EB708_name_81;
    DuelB2JumpFunc jump = (DuelB2JumpFunc)(void (*)(void))func_800EBF2C_name_81;
    DuelB2Jump2Func jump2 = (DuelB2Jump2Func)(void (*)(void))func_801062C0_duel01;
    DuelB2ObjFunc objHide = (DuelB2ObjFunc)func_800D8E88_name_81;
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
    dir(&partner->coords, &sp18, &partner->rot);
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
    objHide(obj);
    func_800EF7C8_name_81(obj, 3.0f, -0.18f);
    HuPrcChildLink(process, jump(&obj->coords, &sp18, &obj->coords, 0x1E));
    if (variant == 2) {
        for (i = 0; i < 16; i++) {
            HuVecCopy3F(&sp28, &sp18);
            sp28.x += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            sp28.y += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            sp28.z += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            func_800EF7C8_name_81(parts[i], 3.0f, -0.18f);
            HuPrcChildLink(process, jump(&parts[i]->coords, &sp28, &parts[i]->coords, 0x1E));
        }
    }
    HuAudFXPlay(0x1E1);
    func_80106240_duel01();
    jump2(target, player, flags, 0x1E); // host: func_801062C0_duel01 must take an s32 here
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
                objHide(parts[i]);
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
                objHide(parts[i]);
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
    DuelB2ObjFunc objHide = (DuelB2ObjFunc)func_800D8E88_name_81;
    Object *puff;
    f32 rot;
    f32 scale;

    if (create != 0) {
        D_80119488_duel01 = func_800D8010_name_81(8, (s32)D_80118718_duel01); // host: pointer through s32 (duel01.h prototype)
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
        objHide(D_80119488_duel01);
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
    DuelB2ObjFunc objHide = (DuelB2ObjFunc)func_800D8E88_name_81;
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
    objHide(obj);
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

#ifdef NON_MATCHING
// duel b2: masked 78 of 649: func_800EB708 is called through a correctly typed local pointer (duel01.h has it wrong) and GCC keeps it in $s8 (jalr), which shifts the allocation; logic checked block by block.
void func_8010B54C_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    DuelB2ModelCreateFunc modelCreate = (DuelB2ModelCreateFunc)(void (*)(void))func_800D8010_name_81;
    DuelB2MoveFunc move = (DuelB2MoveFunc)(void (*)(void))func_800EC1E4_name_81;
    DuelB2DirFunc dir = (DuelB2DirFunc)(void (*)(void))func_800EB708_name_81;
    DuelB2ObjFunc objHide = (DuelB2ObjFunc)func_800D8E88_name_81;
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
    s32 effect;

    player = MBDGetPlayerStruct(playerNo);
    process = HuPrcCurrentGet();
    effect = -1;
    func_800FAD04_name_81(0xB);
    if (flags != 0) {
        obj = modelCreate(D_80118710_duel01[variant - 1], 0);
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
        HuVecCopy3F(&sp18, (target != NULL) ? &target->coords : &player->player_obj->coords);
        dir(&D_80119488_duel01->coords, &sp18, &D_80119488_duel01->rot);
        angle = func_800D76D0_name_81(&D_80119488_duel01->rot) + 180.0f;
        if (variant == 1) {
            speed = 2.5f;
        } else {
            speed = 3.0f;
        }
        offset.x = sindf(angle) * 6.0f * speed;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 6.0f * speed;
        HuVecAdd(&sp18, &sp18, &offset);
        HuPrcChildLink(process, move(&D_80119488_duel01->coords, &sp18, &D_80119488_duel01->coords, 0.5f));
        func_80106240_duel01();
        func_80106260_duel01((s32)target, (unkStruct05 *)player, flags, 0.8f); // host: pointer through s32
        objHide(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &D_80119488_duel01->coords);
        dir(&obj->coords, &sp18, &obj->rot);
        HuPrcChildLink(process, move(&obj->coords, &sp18, &obj->coords, 0.5f));
        HuPrcChildWait();
        func_800D8F0C_name_81(obj);
        if (variant == 1) {
            func_800D90D0_name_81(D_80119488_duel01, 3, 0);
            if (flags & 8) {
                func_801060D0_duel01(player, target, 0, 0x32);
            } else {
                HuPrcSleep(8);
                HuVecAdd(&sp58, (flags & 1) ? &target->coords : &player->player_obj->coords, &D_80119488_duel01->coords);
                HuVecMulScalar(&sp58, 0.5f, &sp58);
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
        dir(&partner->coords, &sp28, &partner->rot);
        func_800D90D0_name_81(partner, 0, 2);
        HuPrcChildLink(process, move(&partner->coords, &sp28, &partner->coords, 3.0f));
        objHide(obj);
        func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
        HuVecCopy3F(&obj->coords, &partner->coords);
        dir(&obj->coords, &sp28, &obj->rot);
        HuPrcChildLink(process, move(&obj->coords, &sp28, &obj->coords, 3.0f));
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B54C_duel01);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010BCD4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E98_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EA4_duel01);

#ifdef NON_MATCHING
// duel b2: masked 84 of 463: register/stack allocation (retail frame 8 bytes larger, 5.0f kept in $f20, extra1/extra2 slots swapped); logic checked block by block.
void func_8010CE68_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    DuelB2ObjFunc objHide = (DuelB2ObjFunc)func_800D8E88_name_81;
    DuelB2DirFunc dir = (DuelB2DirFunc)(void (*)(void))func_800EB708_name_81;
    DuelB2Move2Func move2 = (DuelB2Move2Func)(void (*)(void))func_80106260_duel01;
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
    HuVecCopy3F(&sp18, (target != NULL) ? &target->coords : &player->player_obj->coords);
    dir(&partner->coords, &sp18, &partner->rot);
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
    HuPrcSleep(variant == 1 ? 7 : 0xF);
    objHide(obj);
    HuVecCopy3F(&obj->coords, &partner->coords);
    obj->velocity.x = 5.0f;
    func_800D8F0C_name_81(obj);
    func_80106240_duel01();
    objHide(obj);
    HuPrcChildLink(process, func_800EC36C_name_81(&obj->coords, &sp18, &obj->coords, 4.0f));
    HuPrcChildLink(process, move2(target, player, flags, 4.0f)); // host: func_80106260_duel01 returns void
    HuVecCopy3F(&sp28, &partner->rot);
    func_800D7828_name_81(&sp28);
    HuVecMulScalar(&sp28, 6.0f, &sp28);
    HuVecAdd(&sp28, &sp28, &obj->coords);
    sp28.y += 5.0f;
    func_800DCE40_name_81(0x4E, &sp28, NULL, 0.5f);
    if (variant != 2) {
        HuAudFXPlay(0x1D9);
    } else {
        objHide(obj2);
        func_8001C258_main(obj2->omObj1->model[0], 0x180, 0);
        func_8001C8E4_main(obj2->omObj1->model[0], 0x800);
        HuVecCopy3F(&obj2->coords, &obj->coords);
        obj2->velocity.x = 5.0f;
        HuPrcChildLink(process, func_800EC36C_name_81(&obj2->coords, &sp18, &obj2->coords, 4.0f));
        HuAudFXPlay(0x1DA);
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
        HuVecCopy3F(&sp28, (flags & 1) ? &target->coords : &player->player_obj->coords);
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
                HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1EF : 0x1EE);
            } else {
                HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
            }
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (variant == 2) {
                if (!(flags & 1)) {
                    HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1EF : 0x1EE);
                }
            } else if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010CE68_duel01);
#endif

#ifdef NON_MATCHING
// duel b2: masked 0, raw 28: partner and obj swap s3/s4.
void func_8010D424_duel01(s32 arg0, s32 playerNo, Object *partner, Object *target, s32 flags, s32 variant) {
    DuelB2ModelCreateFunc modelCreate = (DuelB2ModelCreateFunc)(void (*)(void))func_800D8010_name_81;
    DuelB2MoveFunc move = (DuelB2MoveFunc)(void (*)(void))func_800EC1E4_name_81;
    DuelB2DirFunc dir = (DuelB2DirFunc)(void (*)(void))func_800EB708_name_81;
    DuelB2ObjFunc objHide = (DuelB2ObjFunc)func_800D8E88_name_81;
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
    obj = modelCreate(D_80118710_duel01[variant - 1], 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    partnerPos = &partner->coords;
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(partner, 0, 2);
    func_8010615C_duel01(partner, target, player, &sp18, &sp28, 7.5f);
    func_80106240_duel01();
    func_80106260_duel01((s32)target, (unkStruct05 *)player, flags, 3.0f); // host: pointer through s32
    HuPrcChildLink(process, move(partnerPos, &sp18, partnerPos, 3.0f));
    objHide(partner);
    func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
    HuVecCopy3F(&obj->coords, partnerPos);
    dir(&obj->coords, &sp18, &obj->rot);
    HuPrcChildLink(process, move(&obj->coords, &sp18, &obj->coords, 3.0f));
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
    dir(&partner->coords, &sp28, &partner->rot);
    func_800D90D0_name_81(partner, 0, 2);
    HuPrcChildLink(process, move(&partner->coords, &sp28, &partner->coords, 3.0f));
    objHide(partner);
    func_8001C6A8_main(obj->omObj1->model[0], 0.0f);
    HuVecCopy3F(&obj->coords, &partner->coords);
    dir(&obj->coords, &sp28, &obj->rot);
    HuPrcChildLink(process, move(&obj->coords, &sp28, &obj->coords, 3.0f));
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D424_duel01);
#endif

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

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DC04_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DCA8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DD3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DDEC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DF68_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E008_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F18_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E1B4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E2CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E2F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E348_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E3F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E574_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E614_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E7C0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E8D8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E904_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E954_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EA74_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EAD4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB44_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB88_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EC78_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010ED20_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EDA0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EFBC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F12C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F99C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110068_duel01);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F30_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F48_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F60_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F6C_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F84_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FB4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE8_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FF0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119010_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119014_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801190FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801191E4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801192CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110C3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80111DFC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801123E8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801124D8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112514_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112590_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801125CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011264C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801129C8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112BB4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112DA0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801135D8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801138D0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011390C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80113CAC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801147FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801193E8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80115850_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801159F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80116484_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119410_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117480_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117624_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801179AC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117D3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117DDC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117E7C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117ED8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117FFC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118058_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118178_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801181C4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011825C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801182A8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801182E4_duel01);

void func_80118320_duel01(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118328_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118414_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118530_duel01);
