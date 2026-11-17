#include "mgresultdealer.h"

void func_801059A0_mgresultdealer(void) {
    omObjData *obj;
    s16 n;
    s16 grp;
    s16 i;

    n = 0;
    for (grp = 0; grp < 4; grp++) {
        for (i = 0; i < 4; i++) {
            if (grp == GwPlayer[i].group) {
                D_8010A266_mgresultdealer[n] = i;
                n++;
                if (n >= 4) {
                    break;
                }
            }
        }
        if (n >= 4) {
            break;
        }
    }
    func_800142A0_main(0x64);
    omInitObjMan(0x1E, 0x28);
    func_8000B690_main(2);
    for (grp = 0; grp < 2; grp++) {
        ScissorSet(grp, 0.0f, 0.0f, 320.0f, 240.0f);
        ViewportSet(grp, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCamSetPerspective(grp, 30.0f, 80.0f, 8000.0f);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 2;
    D_8010A264_mgresultdealer = GwPlayer[D_8010A266_mgresultdealer[0]].gameCoin;
    D_8010A258_mgresultdealer = GwPlayer[D_8010A266_mgresultdealer[0]].bonusCoin;
    omAddPrcObj(func_801065D0_mgresultdealer, 0x1001, 0x2000, 0);
    omAddPrcObj(func_801074A0_mgresultdealer, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80108040_mgresultdealer, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80108570_mgresultdealer, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, func_80105C88_mgresultdealer);
    omAddObj(0, 0, 0, -1, func_80106234_mgresultdealer);
    func_801062B4_mgresultdealer();
    func_801061C8_mgresultdealer();
    WipeCreateIn(0xFF, 0x10);
}

/* the main sequence */
void func_80105C88_mgresultdealer(omObjData *arg0) {
    omObjData *obj;
    f32 time;
    s32 state;

    obj = D_8010A250_mgresultdealer.obj;
    state = D_801098C0_mgresultdealer;
    switch (state) {
    case 0:
        if (D_8010A264_mgresultdealer * D_8010A258_mgresultdealer > 0) {
            HuAudSeqPlay(0x46);
        } else {
            HuAudSeqPlay(0x47);
        }
        D_801098CC_mgresultdealer = 0;
        state++;
        break;
    case 1:
        state += !(++D_801098CC_mgresultdealer < 0x15);
        break;
    case 2:
        state++;
        func_801090B4_mgresultdealer();
        break;
    case 3:
        state += func_801090E8_mgresultdealer() != 0;
        break;
    case 4:
        if (func_80109478_mgresultdealer() == 1) {
            D_801098CC_mgresultdealer = 0;
            state++;
        }
        break;
    case 5:
        state += func_801090F4_mgresultdealer() != 0;
        break;
    case 6:
        if (++D_801098CC_mgresultdealer > 0) {
            state++;
            if (D_8010A264_mgresultdealer * D_8010A258_mgresultdealer <= 0) {
                state = 11;
            }
        }
        break;
    case 7:
        state++;
        func_80107E44_mgresultdealer(D_8010A264_mgresultdealer * D_8010A258_mgresultdealer);
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[3]].unk02, 0, 0x1E, 2);
        break;
    case 8:
        state += func_80108034_mgresultdealer() == 1;
        break;
    case 9:
        func_801073F4_mgresultdealer();
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, 0, 0x1E, 0);
        func_8004ACE0_main(0x274, D_8010A266_mgresultdealer[0]);
        HuAudFXPlay(0x516);
        if (D_8010A264_mgresultdealer * D_8010A258_mgresultdealer >= 100) {
            func_8001C258_main(obj->model[4], 4, 0);
            func_8001C258_main(obj->model[5], 4, 0);
            func_8001C258_main(obj->model[6], 4, 0);
        } else if (D_8010A264_mgresultdealer * D_8010A258_mgresultdealer >= 50) {
            func_8001C258_main(obj->model[4], 4, 0);
            func_8001C258_main(obj->model[6], 4, 0);
        } else {
            func_8001C258_main(obj->model[5], 4, 0);
        }
        state++;
        func_80106EAC_mgresultdealer();
        break;
    case 10:
        time = HmfModelData[obj->model[0]].unk40;
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= time) {
            D_801098CC_mgresultdealer = 0;
            state = 15;
        }
        break;
    case 11:
        state++;
        func_80108260_mgresultdealer();
        break;
    case 12:
        if (func_8010829C_mgresultdealer() == 1) {
            state++;
            func_80106D9C_mgresultdealer();
        }
        break;
    case 13:
        if (func_80106EA0_mgresultdealer() == 1) {
            if (!(GwPlayer[D_8010A266_mgresultdealer[0]].stat & 1)) {
                omVibrate(D_8010A266_mgresultdealer[0], 0x14, 0, 0x14);
            }
            state++;
            func_80107448_mgresultdealer();
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 0x1E, 0);
            func_8004ACE0_main(0x26B, D_8010A266_mgresultdealer[0]);
        }
        break;
    case 14:
        time = HmfModelData[obj->model[0]].unk40;
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= time) {
            D_801098CC_mgresultdealer = 0;
            state++;
        }
        break;
    case 15:
        state += !(++D_801098CC_mgresultdealer < 0xF);
        break;
    case 16:
        D_8010A264_mgresultdealer = 0;
        D_8010A258_mgresultdealer = 0;
        WipeCreateOut(0, 0x14);
        HuAudSeqFadeOut(0x1E);
        func_8004AB0C_main(0x1E);
        state++;
        break;
    case 17:
        if (WipeStatGet() == 0) {
            func_80037258_main();
            omOvlReturnEx(1);
        }
        break;
    }
    D_801098C0_mgresultdealer = state;
}

/* the stage model, whose camera the screen uses */
void func_801061C8_mgresultdealer(void) {
    s16 model;

    model = func_8000B108_main(0x190002, 0x2002B9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_80019828_main(model, 2);
    func_80013320_main(model, 0);
    func_8010630C_mgresultdealer(model);
}

/* START (D_800D530C_main) leaves at once */
void func_80106234_mgresultdealer(omObjData *arg0) {
    if (D_800D530C_main == 1) {
        if (D_801098D0_mgresultdealer == 0) {
            WipeCreateOut(0, 0x14);
            D_801098D0_mgresultdealer = 1;
        } else if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(0x1E);
            func_8004AB0C_main(0x1E);
            func_80037258_main();
            omOvlReturnEx(1);
        }
    }
}

void func_801062B4_mgresultdealer(void) {
    u16 spr;

    spr = InitEspriteSlot(func_8000B838_main(0x190000), 0, 0);
    func_8000BBD4_main(spr, 0xA0, 0x78);
    func_8000BC48_main(spr, 0x4000);
}

/* point every camera along the model file's camera */
void func_8010630C_mgresultdealer(s16 model) {
    f32 mtx[4][4];
    f32 x;
    DealerHmfCam *cam;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 angle;
    s8 i;

    cam = ((DealerHmfData *)HmfModelData[model].hmf)->cam;
    dx = cam->eye.x - cam->at.x;
    dy = cam->eye.y - cam->at.y;
    dz = cam->eye.z - cam->at.z;
    CZoom = HuSqrtf(dx * dx + dy * dy + dz * dz);
    angle = atan2df(dz, dx);
    CRot.y = -(angle - 90.0f);
    angle = -angle;
    mtx[0][0] = mtx[2][2] = cosdf(angle);
    mtx[2][0] = -sindf(angle);
    mtx[0][2] = sindf(angle);
    mtx[1][1] = mtx[3][3] = 1.0f;
    mtx[1][0] = mtx[3][0] = mtx[0][1] = mtx[2][1] = mtx[3][1] = mtx[1][2] = mtx[3][2] = mtx[0][3] = mtx[1][3] =
        mtx[2][3] = 0.0f;
    x = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    CRot.x = -atan2df(dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1], x);
    CRot.z = 0.0f;
    if (CZoom > 32000.0f) {
        CZoom = 32000.0f;
    }
    Center.x = cam->at.x;
    Center.y = cam->at.y;
    Center.z = cam->at.z;
    for (i = 0; i < 4; i++) {
        CRotM[i] = CRot;
        CenterM[i] = Center;
        CZoomM[i] = CZoom;
        Hu3DCamSetPerspective(i, cam->fov, 80.0f, 8000.0f);
    }
}

/* .data (0x4F00D0) */
s8 D_801098C0_mgresultdealer = 0;
s32 D_801098C4_mgresultdealer = 0; /* unused */
s32 D_801098C8_mgresultdealer = 0; /* unused */
s32 D_801098CC_mgresultdealer = 0;
s8 D_801098D0_mgresultdealer = 0;
