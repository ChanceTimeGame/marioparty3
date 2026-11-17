#include "mgresultdealer.h"

#ifdef NON_MATCHING
/* masked 0 at the right count when func_80017AD8_main returns s16 (include/functions.us.h says u8; see
   src/14EA0.c and ~/repos/mp3-wt/k2A.header.patch): with u8 the three stores gain an andi */
/* Game Guy's process: the player, the slot, the hand, the table and the three coin piles */
void func_801065D0_mgresultdealer(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 8, 5, -1, NULL);
    D_8010A250_mgresultdealer.obj = obj;
    chr = GwPlayer[D_8010A266_mgresultdealer[0]].chr;
    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C8A8_main(obj->model[0], 1);
    obj->model[1] = func_8000B108_main(0x83, 0x2B9);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C258_main(obj->model[1], 4, 4);
    Hu3DModelPosSet(obj->model[1], 0.0f, 140.0f, 0.0f);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = func_8000B108_main(0x190003, 0x2B9);
    func_8001C814_main(obj->model[2], 2, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    Hu3DModelPosSet(obj->model[2], 0.0f, 400.0f, -35.0f);
    func_8001C8A8_main(obj->model[2], 2);
    obj->model[3] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 0.0f, -5.0f, -35.0f);
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    func_8001C8A8_main(obj->model[3], 1);
    obj->model[4] = func_8000B108_main(0x190006, 0x2B9);
    obj->model[5] = func_8000B108_main(0x190007, 0x2B9);
    obj->model[6] = func_8000B108_main(0x190008, 0x2B9);
    func_8001C8A8_main(obj->model[4], 2);
    func_8001C8A8_main(obj->model[5], 2);
    func_8001C8A8_main(obj->model[6], 2);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8001C258_main(obj->model[5], 4, 4);
    func_8001C258_main(obj->model[6], 4, 4);
    D_80109A64_mgresultdealer[0] = func_80017790_main(obj->model[0], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80109A64_mgresultdealer[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80109A64_mgresultdealer[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80109A64_mgresultdealer[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA6));
    func_8001C514_main(obj->model[0]);
    func_80017954_main(obj->model[0], 2, GwPlayer[D_8010A266_mgresultdealer[0]].chr, D_80109A64_mgresultdealer[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, D_801099A8_mgresultdealer[chr]));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x25));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -35.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80106D94_mgresultdealer);
    D_8010A250_mgresultdealer.func = func_80106A50_mgresultdealer;
    while (1) {
        D_8010A250_mgresultdealer.func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4ECDE0", func_801065D0_mgresultdealer);
#endif

/* the hand falls onto the slot */
void func_80106A50_mgresultdealer(omObjData *obj) {
    if (D_801098E0_mgresultdealer != 0) {
        D_801098E4_mgresultdealer.y -= D_80109A60_mgresultdealer;
        D_80109A60_mgresultdealer += 0.98f;
        D_801098F0_mgresultdealer.x += 30.0f;
        if (D_801098E4_mgresultdealer.y <= 180.0f) {
            func_8001C258_main(obj->model[1], 4, 0);
            D_801098E4_mgresultdealer.y = 180.0f;
            D_80109A60_mgresultdealer = -10.0f;
            D_801098E2_mgresultdealer = 1;
            HuAudFXPlay(0x515);
            HuAudFXPlay(0x518);
            D_8010A250_mgresultdealer.func = func_80106B94_mgresultdealer;
        }
        Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y, D_801098E4_mgresultdealer.z);
        Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y, D_801098F0_mgresultdealer.z);
    }
}

/* it bounces off */
void func_80106B94_mgresultdealer(omObjData *obj) {
    D_801098E4_mgresultdealer.y -= D_80109A60_mgresultdealer;
    D_80109A60_mgresultdealer += 0.98f;
    D_801098E4_mgresultdealer.x += 5.0f;
    D_801098E4_mgresultdealer.z -= 5.0f;
    D_801098F0_mgresultdealer.x -= 5.0f;
    D_801098F0_mgresultdealer.y -= 5.0f;
    if (D_801098E4_mgresultdealer.y <= 20.0f) {
        D_801098E4_mgresultdealer.y = 20.0f;
        func_8001C258_main(obj->model[1], 4, 4);
        D_80109A60_mgresultdealer = -2.0f;
        D_8010A250_mgresultdealer.func = func_80106CC8_mgresultdealer;
    }
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y, D_801098E4_mgresultdealer.z);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y, D_801098F0_mgresultdealer.z);
}

/* and comes to rest */
void func_80106CC8_mgresultdealer(omObjData *obj) {
    D_801098E4_mgresultdealer.y -= D_80109A60_mgresultdealer;
    D_80109A60_mgresultdealer += 0.98f;
    if (D_801098E4_mgresultdealer.y <= 0.0f) {
        D_801098E4_mgresultdealer.y = 0.0f;
        D_801098E0_mgresultdealer = 0;
        D_8010A250_mgresultdealer.func = func_80106A50_mgresultdealer;
    }
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y, D_801098E4_mgresultdealer.z);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y, D_801098F0_mgresultdealer.z);
}

void func_80106D94_mgresultdealer(void) {
}

/* drop the hand */
void func_80106D9C_mgresultdealer(void) {
    omObjData *obj;

    obj = D_8010A250_mgresultdealer.obj;
    D_801098E0_mgresultdealer = 1;
    D_801098E1_mgresultdealer = 0;
    D_801098E2_mgresultdealer = 0;
    D_801098E4_mgresultdealer.x = 0.0f;
    D_801098E4_mgresultdealer.y = 400.0f;
    D_801098E4_mgresultdealer.z = -55.0f;
    D_801098F0_mgresultdealer.x = 160.0f;
    D_801098F0_mgresultdealer.y = 20.0f;
    D_801098F0_mgresultdealer.z = 0.0f;
    D_80109A60_mgresultdealer = 0.0f;
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y, D_801098E4_mgresultdealer.z);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y, D_801098F0_mgresultdealer.z);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 0);
}

s8 func_80106EA0_mgresultdealer(void) {
    return D_801098E2_mgresultdealer;
}

void func_80106EAC_mgresultdealer(void) {
    D_8010A250_mgresultdealer.func = func_80106EC0_mgresultdealer;
}

void func_80106EC0_mgresultdealer(omObjData *obj) {
    func_80106EEC_mgresultdealer();
    D_8010A250_mgresultdealer.func = func_80106A50_mgresultdealer;
}

/* each character's motion for the win */
const s32 D_801099A8_mgresultdealer[8] = { 0x36, 0x37, 0x3A, 0x37, 0x36, 0x37, 0x36, 0x37 };

/* four confetti models, scattered by the vertex effect */
void func_80106EEC_mgresultdealer(void) {
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = func_8000B108_main(D_801098FC_mgresultdealer[i], 0x2A9);
        D_801099F8_mgresultdealer[i] = model;
        func_8003302C_main(HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        func_8001C448_main(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, NULL, func_801072A8_mgresultdealer);
        func_8001C8A8_main(model, 2);
    }
    omAddObj(0xA, 0xA, 0xA, -1, func_8010705C_mgresultdealer);
}

void func_8010705C_mgresultdealer(omObjData *obj) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (!((D_8010990C_mgresultdealer + i) & 7)) {
            func_801070EC_mgresultdealer(D_801099F8_mgresultdealer[i]);
        }
    }
    D_8010990C_mgresultdealer++;
}

/* launch the first idle confetti piece */
void func_801070EC_mgresultdealer(s16 model) {
    DealerFxPart *part;
    s16 count;
    s16 i;

    count = ((DealerHmfData *)HmfModelData[model].hmf)->unk1A;
    part = ((DealerFxWork *)HmfModelData[model].unkBC)->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->pos.y <= 0.0f) {
            part->pos.x = 2.0f * (100.0f - (rand8() % 200));
            part->pos.y = 500.0f;
            part->pos.z = ((rand8() * 125) >> 5) - 500;
            part->dir.x = (f32)((s32)((u32)(rand8() * 5) >> 7) - 5) / 2.0f;
            part->dir.y = 0.0f;
            part->dir.z = (f32)((s32)((u32)(rand8() * 5) >> 7) - 5) / 2.0f;
            part->scale = 3.0f;
            return;
        }
    }
}

/* the effect's update hook: the pieces fall until they reach the floor */
void func_801072A8_mgresultdealer(s16 model) {
    DealerHmfData *hmf;
    DealerFxWork *work;
    DealerFxPart *part;
    u16 count;
    s16 i;

    hmf = (DealerHmfData *)HmfModelData[model].hmf;
    work = (DealerFxWork *)HmfModelData[model].unkBC;
    count = hmf->unk1A;
    if (work->unk02 == 0) {
        work->unk04 &= ~4;
        part = work->parts;
        for (i = 0; i < (s16)count; i++, part++) {
            part->scale = part->vel.x = part->vel.y = part->vel.z = part->pos.x = part->pos.y = part->pos.z = 0.0f;
            part->speed = 1.0f;
        }
        work->unk02++;
    }
    part = work->parts;
    for (i = 0; i < (s16)count; i++, part++) {
        if (part->pos.y > 0.0f) {
            part->pos.x += part->dir.x;
            part->pos.y += part->dir.y - 8.0f;
            part->pos.z += part->dir.z;
        } else {
            part->scale = 0.0f;
        }
    }
}

void func_801073F4_mgresultdealer(void) {
    func_80017954_main(D_8010A250_mgresultdealer.obj->model[0], 2, GwPlayer[D_8010A266_mgresultdealer[0]].chr,
                       D_80109A64_mgresultdealer[2]);
}

void func_80107448_mgresultdealer(void) {
    func_80017954_main(D_8010A250_mgresultdealer.obj->model[0], 2, GwPlayer[D_8010A266_mgresultdealer[0]].chr,
                       D_80109A64_mgresultdealer[3]);
}
