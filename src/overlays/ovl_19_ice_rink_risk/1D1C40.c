#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// ice rink A: Ice Rink Risk (4 players dodge sliding pucks on a rink)

typedef func_800E1BA8_minigame_ObjData MgWork;

typedef struct Vec4f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w; /* radius */
} Vec4f;

/* omObjData::data of a puck: the framework's item actor (minigame mgcol.h ColActorWork) */
typedef struct IrPuck {
    /* 0x00 */ u8 unk00[0x20];
    /* 0x20 */ char unk20[0x14];
    /* 0x34 */ f32 unk34; /* height */
    /* 0x38 */ f32 unk38; /* vertical speed; 1000.0f on the ground */
    /* 0x3C */ f32 unk3C; /* heading */
    /* 0x40 */ f32 unk40; /* speed */
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48; /* radius */
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53; /* ground object index */
    /* 0x54 */ u8 unk54;
    /* 0x55 */ char unk55;
    /* 0x56 */ u16 unk56; /* puck index */
    /* 0x58 */ char unk58[0x1C];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])();
    /* 0xA8 */ void* unkA8;
} IrPuck; /* size 0xAC */

/* omObjData::data of the rink (the framework's ground object, minigame mgcol.h GroundWork) */
typedef struct IrGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xF];
    /* 0x14 */ f32 unk14; /* top surface height */
    /* 0x18 */ char unk18[0x9C];
} IrGround; /* size 0xB4 */

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct IrCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result message: winners - 1, 4 none */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4]; /* winner player indices */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} IrCtrl;

/* A puck's last hit: by which puck, frames since, where. */
typedef struct IrHit {
    /* 0x00 */ s32 owner;
    /* 0x04 */ s32 timer;
    /* 0x08 */ Vec pos;
} IrHit; /* size 0x14 */

// main
s32 func_8000B638_main(void);
void func_8000BC48_main(u16 arg0, u16 arg1);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_80021BE0_main(s32* arg0, s32 n);
f32 func_800202A8_main(f32 angle);
s32 func_800202FC_main(Vec* v);
void func_8004B760_main(s32 prio, s32 sprId, void* draw, f32 fov, Vec* eye, Vec* at);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
f32 HuVecDot3F(Vec* a, Vec* b);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
f32 fabsf(f32);
omObjData* func_80045ED0_main(u32 arg0);

extern s32 D_800A178C_main[][6];
extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];
extern u8 D_800D6A90_main;

// minigame
void func_800DC7D8_minigame(omObjData* g, Vec4f* p);
void func_800DFCDC_minigame(f32 dx, f32 dz, f32 d);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E1404_minigame(omObjData* obj, f32 arg1, f32 arg2);
void func_800E1468_minigame(omObjData* obj);
void func_800E147C_minigame(omObjData* obj);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E17D4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E1804_minigame(void);
void func_800E28BC_minigame(f32 (*l2w)[4], f32 (*w2l)[4], Vec* p, omObjData* g);
void func_800E2B58_minigame(f32 (*m)[4], Vec* v);
void func_800E3568_minigame(MgWork* work, s32 slot, void* hook);
void func_800E3584_minigame(s16);
void func_800E3628_minigame(s16 mdl, Vec* n);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
s32 func_800E5798_minigame(omObjData* obj, u16 motion);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern f32 D_800EB720_minigame;
extern f32 D_800EB72C_minigame;
extern s16 D_800EB736_minigame;
extern f32 D_800EB73C_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB748_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB774_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame[];
extern f32 D_800EBE2C_minigame;
extern f32 D_800EBE30_minigame[4][4];
extern omObjData* D_800EBE70_minigame[];
extern s32 D_800EBEB0_minigame[]; /* minigame mgcol.h HitList */
extern f32 D_800EC240_minigame[4][4];
extern Vec D_800EC298_minigame[];
extern f32 D_800EC5D8_minigame;

// LOCAL

void func_80105E34_ice_rink_risk(omObjData* obj);
void func_80105E60_ice_rink_risk(void);
void func_80105EA4_ice_rink_risk(void);
void func_80105FAC_ice_rink_risk(omObjData* obj);
void func_80106198_ice_rink_risk(omObjData* obj);
void func_80106554_ice_rink_risk(omObjData* obj);
void func_80106710_ice_rink_risk(omObjData* obj, s32 arg1, s32 arg2, u16 arg3);
s32 func_80106A60_ice_rink_risk(omObjData* obj, omObjData* other);
void func_80106C54_ice_rink_risk(omObjData* obj);
s32 func_80106E20_ice_rink_risk(omObjData* obj);
s32 func_80106FC0_ice_rink_risk(omObjData* obj);
void func_80107590_ice_rink_risk(omObjData* obj);
void func_80107604_ice_rink_risk(omObjData* obj);
void func_80107678_ice_rink_risk(omObjData* obj);
void func_801076EC_ice_rink_risk(omObjData* obj);
void func_80107760_ice_rink_risk(omObjData* obj);
void func_8010796C_ice_rink_risk(omObjData* obj);
f32 func_80107CB4_ice_rink_risk(omObjData* obj, f32 x, f32 y, f32 z);
f32 func_80107D14_ice_rink_risk(omObjData* obj, Vec4f* p);
void func_80107DEC_ice_rink_risk(omObjData* obj, f32 x, f32 y, f32 z, f32 g, Vec* n);
f32 func_80107F24_ice_rink_risk(omObjData* obj, Vec4f* p, Vec* n);
void func_80107F58_ice_rink_risk(omObjData* obj, f32 x, f32 y, f32 z);
void func_80108134_ice_rink_risk(omObjData* obj, Vec4f* p);
void func_8010826C_ice_rink_risk(omObjData* obj);
void func_80108384_ice_rink_risk(omObjData* obj, f32 dx, f32 dz);

extern Vec D_80108550_ice_rink_risk[4];
extern Vec D_80108580_ice_rink_risk[4];
extern IrHit D_801085B0_ice_rink_risk[3];
extern s32 D_801085EC_ice_rink_risk[3];
extern s32 D_801085F8_ice_rink_risk;
extern s32 D_801085FC_ice_rink_risk[4];
extern IrCtrl D_8010860C_ice_rink_risk;
extern s32 D_80108634_ice_rink_risk;
extern s32 D_80108638_ice_rink_risk;
extern s32 D_8010863C_ice_rink_risk[4];
extern s32 D_8010864C_ice_rink_risk[4];
extern s8 D_8010865C_ice_rink_risk[4][2];
extern f32 D_80108664_ice_rink_risk[4];
extern f32 D_80108674_ice_rink_risk[4];
extern s32 D_80108684_ice_rink_risk;
extern f32 D_80108688_ice_rink_risk[10];

extern Vec D_801086D0_ice_rink_risk;
extern Vec D_801086DC_ice_rink_risk;
extern s32 D_801086E8_ice_rink_risk;
extern s32 D_801086EC_ice_rink_risk;
extern s32 D_801086F0_ice_rink_risk;
extern s32 D_801086F4_ice_rink_risk;

void func_801059A0_ice_rink_risk(void) {
    u8 cam;
    s16 sprId;

    Hu3DAnimInit(50);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 41.539f, 80.0f, 13000.0f);
    HmfLightDirSet(1, -79.0f, -10.0f, 89.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 10, 0, -1, func_80106554_ice_rink_risk);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107590_ice_rink_risk);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107604_ice_rink_risk);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107678_ice_rink_risk);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_801076EC_ice_rink_risk);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 4, 0, -1, func_80107760_ice_rink_risk);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 4, 0, -1, func_80107760_ice_rink_risk);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 4, 0, -1, func_80107760_ice_rink_risk);
    D_801086DC_ice_rink_risk.x = 0.0f;
    D_801086DC_ice_rink_risk.y = 18.995f;
    D_801086DC_ice_rink_risk.z = -31.245f;
    D_801086D0_ice_rink_risk.x = 0.0f;
    D_801086D0_ice_rink_risk.y = 1100.0f;
    D_801086D0_ice_rink_risk.z = 710.785f;
    sprId = InitEspriteSlot(func_8000B838_main(0x3A0003), 0, 1);
    func_8000BB54_main(sprId);
    func_8000BBD4_main(sprId, 160, 120);
    func_8000BC48_main(sprId, 0x4000);
    func_8004B760_main(100, sprId, NULL, 41.539f, &D_801086D0_ice_rink_risk, &D_801086DC_ice_rink_risk);
    CZoom *= 1.25f;
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010860C_ice_rink_risk);
    D_800EB930_minigame = 0x35;
    D_800EB932_minigame = 20;
}

void func_80105E34_ice_rink_risk(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

/* Release the next puck. */
void func_80105E60_ice_rink_risk(void) {
    D_801085EC_ice_rink_risk[D_801085F8_ice_rink_risk] = 1;
    D_801085F8_ice_rink_risk++;
    HuAudFXPlay(0x3D3);
}

/* Finish: stop the pucks where they are. */
void func_80105EA4_ice_rink_risk(void) {
    omObjData* obj;
    s32 i;

    for (i = 0; i < D_801085F8_ice_rink_risk; i++) {
        obj = D_800EBE70_minigame[i];
        func_8001C258_main(obj->model[2], 4, 0);
        func_8001C6A8_main(obj->model[2], 0.0f);
        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelScaleSet(obj->model[2], 1.2f, 1.2f, 1.2f);
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
        obj->func = NULL;
    }
    D_80108634_ice_rink_risk = 0;
}

/* Puck hit sparks (the rink's models 1-3). */
void func_80105FAC_ice_rink_risk(omObjData* obj) {
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < 3; i++) {
        if (D_801085B0_ice_rink_risk[i].timer == 0) {
            found = 0;
            for (j = 0; j < 3; j++) {
                if (j != i && D_801085B0_ice_rink_risk[j].owner == i) {
                    if (D_801085B0_ice_rink_risk[i].timer == D_801085B0_ice_rink_risk[j].timer) {
                        D_801085B0_ice_rink_risk[j].timer = 5;
                        D_801085B0_ice_rink_risk[j].owner = -1;
                    } else {
                        found = 1;
                    }
                }
            }
            if (found == 0) {
                func_8001C258_main(obj->model[i + 1], 4, 0);
                Hu3DModelPosSet(obj->model[i + 1], D_801085B0_ice_rink_risk[i].pos.x, D_801085B0_ice_rink_risk[i].pos.y,
                                D_801085B0_ice_rink_risk[i].pos.z);
                func_8001C6A8_main(obj->model[i + 1], 0.0f);
            }
            D_801085B0_ice_rink_risk[i].timer++;
        } else {
            D_801085B0_ice_rink_risk[i].timer++;
            if (D_801085B0_ice_rink_risk[i].timer >= 16) {
                D_801085B0_ice_rink_risk[i].owner = -1;
            }
        }
    }
}

/* The rink: runs the minigame's states. */
// masked 1 instruction: retail compares the alive flags against 1 kept in a register (xor), GCC 2.7.2 here
// emits xori; the rest follows from the one-instruction shift
#ifdef NON_MATCHING
void func_80106198_ice_rink_risk(omObjData* obj) {
    s32 i;
    s32 alive = 0;
    u16 timer;
    s32 n;
    MgWork* w;
    omObjData* player;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        for (i = 0; i < 4; i++) {
            if (D_801085FC_ice_rink_risk[i] == 1) {
                alive++;
            }
        }
        timer = func_800E6E9C_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                if (timer == 5) {
                    HuAudFXPlay(0x3D5);
                }
                break;
            case 2:
                func_80105FAC_ice_rink_risk(obj);
                switch (D_80108638_ice_rink_risk) {
                    case 0:
                    case 300:
                    case 600:
                        func_80105E60_ice_rink_risk();
                        break;
                }
                if (alive < 2) {
                    func_800E6F0C_minigame(3);
                }
                D_80108638_ice_rink_risk++;
                break;
            case 3:
                if (D_80108634_ice_rink_risk == 1) {
                    func_80105EA4_ice_rink_risk();
                }
                if (alive == 0) {
                    D_8010860C_ice_rink_risk.unk06 = 4;
                } else {
                    D_8010860C_ice_rink_risk.unk06 = alive - 1;
                    for (n = 0, i = 0; i < 4; i++) {
                        if (D_801085FC_ice_rink_risk[i] == 1) {
                            D_8010860C_ice_rink_risk.unk18[n++] = i;
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (D_801085FC_ice_rink_risk[i] == 1) {
                        ((MgWork*)D_800EC598_minigame[i]->data)->unk3C *= 0.8f;
                    }
                }
                break;
            case 4:
                if (D_800EB934_minigame[0] == 1) {
                    for (i = 0; i < 4; i++) {
                        if (D_801085FC_ice_rink_risk[i] == 1) {
                            player = D_800EC598_minigame[i];
                            w = player->data;
                            func_800E5798_minigame(player, 0xD);
                            GwPlayer[w->unk59].bonusCoin += 10;
                            func_80045ED0_main(D_800A178C_main[GwPlayer[w->unk59].chr][0] | 0x2F);
                        }
                    }
                }
                break;
            case 5:
                WipeCreateOut(0, 20);
                obj->func = func_80105E34_ice_rink_risk;
                break;
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
        }
        if (D_800D530C_main == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            obj->func = func_80105E34_ice_rink_risk;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106198_ice_rink_risk);
#endif

void func_80106554_ice_rink_risk(omObjData* obj) {
    IrGround* gw;

    D_800EB73C_minigame = 20.0f;
    obj->model[0] = func_8000B0A0_main(0x3A0001, 0x80019);
    obj->model[1] = func_8000B108_main(8, 0x88D);
    obj->model[2] = func_8000B108_main(8, 0x88D);
    obj->model[3] = func_8000B108_main(8, 0x88D);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(IrGround), 31000);
    memset(gw, 0, sizeof(IrGround));
    obj->func = func_80106198_ice_rink_risk;
    gw->unk03 = 1;
    func_800E147C_minigame(obj);
    func_800E1404_minigame(obj, 100.0f, 500.0f);
    func_800E1304_minigame(obj, 0.1f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 25.0f);
    func_800E1468_minigame(obj);
    gw->unk04 = 0;
    obj->scale.x = obj->scale.z = 1.25f;
    Hu3DModelScaleSet(obj->model[1], 0.75f, 0.75f, 0.75f);
    Hu3DModelScaleSet(obj->model[2], 0.75f, 0.75f, 0.75f);
    Hu3DModelScaleSet(obj->model[3], 0.75f, 0.75f, 0.75f);
    omSetStatBit(obj, 0xA0);
}

/* A player: models, motions and hooks. */
void func_80106710_ice_rink_risk(omObjData* obj, s32 arg1, s32 arg2, u16 arg3) {
    MgWork* w;
    s32 chr;

    func_800E1BA8_minigame(obj, arg1, arg2, arg3, 0xA99, 0xA99);
    w = obj->data;
    chr = GwPlayer[w->unk59].chr;
    obj->model[3] = func_8000B108_main(3, 0x88D);
    obj->model[4] = func_8000B108_main(4, 0x88D);
    obj->model[5] = func_8000B108_main(6, 0x88D);
    obj->model[7] = func_8000B108_main(8, 0x88D);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, 7), 1, 0x27);
    func_800E5A00_minigame(obj, 0x11, func_80017BB8_main(chr, 0xE), 1, 0xF);
    func_800E5A00_minigame(obj, 0xA, func_80017BB8_main(chr, 0x11), 1, 0x27);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 0x1E, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(obj, 0x1F, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5A00_minigame(obj, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, 0x1A), 1, 0);
    func_800E5978_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5978_minigame(obj, 0xE, func_80017BB8_main(chr, 0x36), 1, 0x78);
    w->unkEC = func_80106A60_ice_rink_risk;
    func_800E149C_minigame(obj, 0, 2);
    func_800E3568_minigame(w, 0, func_80106FC0_ice_rink_risk);
    func_800E3568_minigame(w, 1, func_80106E20_ice_rink_risk);
}

/* A puck (other) hits a player: knock the player off the rink. */
s32 func_80106A60_ice_rink_risk(omObjData* obj, omObjData* other) {
    MgWork* w = obj->data;
    f32 x;
    f32 y;
    f32 z;
    Vec d;
    f32 len;

    if (func_800E6E8C_minigame() == 2) {
        x = obj->trans.x;
        y = obj->trans.y;
        z = obj->trans.z;
        d.x = x - other->trans.x;
        d.y = obj->trans.y - other->trans.y;
        d.z = obj->trans.z - other->trans.z;
        len = HuSqrtf(d.x * d.x + d.y * d.y + d.z * d.z) * 0.5f;
        func_800202FC_main(&d);
        x += len * d.x;
        y += len * d.y;
        z += len * d.z;
        func_8004AC98_main(0x3D4, w->unk59);
        func_8004ACE0_main(0x286, w->unk59);
        func_800E5798_minigame(obj, 0x26);
        w->unk38 = -D_800EB744_minigame;
        w->unk3C = atan2df(obj->trans.x, obj->trans.z);
        w->unk40 = D_800EB760_minigame * 0.8f;
        func_8001C258_main(obj->model[1], 4, 4);
        func_800E4C88_minigame(obj, 7, x, y, z, 0.0f, 0.0f);
        D_801085FC_ice_rink_risk[w->unk59] = 0;
        obj->func = func_80106C54_ice_rink_risk;
        w->unk50 |= 0x400;
        D_8010864C_ice_rink_risk[w->unk59] = 1;
        omVibrate(w->unk59, 2, 2, 20);
    }
    return 1;
}

/* A knocked-out player flies off. */
void func_80106C54_ice_rink_risk(omObjData* obj) {
    MgWork* w = obj->data;
    f32 x = obj->trans.x;
    f32 y = obj->trans.y;
    f32 z = obj->trans.z;
    f32 vy;

    if (D_8010863C_ice_rink_risk[w->unk59] == 0) {
        if (w->unk38 != -D_800EB744_minigame) {
            w->unk38 = -D_800EB744_minigame;
        }
    }
    vy = w->unk38;
    if (D_800EB774_minigame < vy) {
        vy = D_800EB774_minigame;
    }
    y += vy * vy * ((w->unk38 >= 0.0f) ? -35.0f : 35.0f);
    w->unk38 = D_800EB748_minigame * 0.5f + w->unk38;
    x += sindf(w->unk3C) * w->unk40;
    z += cosdf(w->unk3C) * w->unk40;
    if (HuSqrtf(x * x + y * y + z * z) > 2000.0f) {
        obj->func = NULL;
        func_8001C258_main(obj->model[0], 4, 4);
    }
    func_8001C258_main(obj->model[1], 4, 4);
    D_8010863C_ice_rink_risk[w->unk59]++;
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

/* Player hook 1: restore a CPU player's saved pad; fall off below the rink. */
s32 func_80106E20_ice_rink_risk(omObjData* obj) {
    MgWork* w = obj->data;

    if (GwPlayer[w->unk59].stat & 1) {
        D_800D5558_main[w->unk57] = D_801086EC_ice_rink_risk;
        D_800CDA7C_main[w->unk57] = D_801086E8_ice_rink_risk;
        D_800CBB6E_main[w->unk57] = D_801086F0_ice_rink_risk;
        D_800D20A1_main[w->unk57] = D_801086F4_ice_rink_risk;
    }
    if (obj->trans.y < -2000.0f) {
        obj->func = NULL;
        func_8001C258_main(obj->model[0], 4, 4);
    }
    if (D_8010864C_ice_rink_risk[w->unk59] == 1) {
        func_800E5798_minigame(obj, 0x26);
        w->unk38 = -D_800EB744_minigame;
        w->unk3C = atan2df(obj->trans.x, obj->trans.z);
        w->unk40 = D_800EB760_minigame * 0.8f;
        func_8001C258_main(obj->model[1], 4, 4);
        D_801085FC_ice_rink_risk[w->unk59] = 0;
        obj->func = func_80106C54_ice_rink_risk;
        w->unk50 |= 0x400;
    }
    return 1;
}

/* Player hook 0: save the pad, then steer a CPU player away from the nearest puck and the edge. */
s32 func_80106FC0_ice_rink_risk(omObjData* obj) {
    MgWork* w = obj->data;
    s32 player = w->unk59;
    s32 port = w->unk57;
    u8 diff;
    f32 best;
    s32 bi;
    s32 i;
    omObjData* puck;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 dist;
    f32 ang;
    f32 a1;
    Vec v;

    if (func_800E6E8C_minigame() != 2 || (GwPlayer[player].stat & 1)) {
        D_801086EC_ice_rink_risk = D_800D5558_main[port];
        D_801086E8_ice_rink_risk = (u16)D_800CDA7C_main[port];
        D_801086F0_ice_rink_risk = D_800CBB6E_main[port];
        D_801086F4_ice_rink_risk = D_800D20A1_main[port];
        D_800D20A1_main[port] = 0;
        D_800CBB6E_main[port] = 0;
        D_800D5558_main[port] = 0;
        D_800CDA7C_main[port] = 0;
        diff = GwPlayer[w->unk59].cpu_difficulty;
        if (w->unk38 != 1000.0f) {
            D_800CBB6E_main[port] = D_8010865C_ice_rink_risk[player][0];
            D_800D20A1_main[port] = D_8010865C_ice_rink_risk[player][1];
            D_800CDA7C_main[port] |= 0x8000;
        } else {
            best = 20000.0f;
            bi = -1;
            for (i = 0; i < D_801085F8_ice_rink_risk; i++) {
                puck = D_800EBE70_minigame[i];
                dx = obj->trans.x - puck->trans.x;
                dy = obj->trans.y - puck->trans.y;
                dz = obj->trans.z - puck->trans.z;
                dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
                if (dist < best) {
                    best = dist;
                    bi = i;
                }
            }
            if (best < D_80108674_ice_rink_risk[diff] + 150.0f) {
                puck = D_800EBE70_minigame[bi];
                v.x = obj->trans.x - puck->trans.x;
                v.y = 0.0f;
                v.z = obj->trans.z - puck->trans.z;
                func_800202FC_main(&v);
                D_800CBB6E_main[port] = v.x * 60.0f * D_80108664_ice_rink_risk[diff];
                D_800D20A1_main[port] = v.z * -60.0f * D_80108664_ice_rink_risk[diff];
                D_800D5558_main[port] |= 0x8000;
            } else if (best < 400.0f) {
                puck = D_800EBE70_minigame[bi];
                dx = obj->trans.x;
                dz = obj->trans.z;
                dist = HuSqrtf(dx * dx + dz * dz);
                ang = atan2df(dx, dz);
                a1 = ang + 10.0f;
                dx = sindf(a1) * dist - puck->trans.x;
                dz = cosdf(a1) * dist - puck->trans.z;
                d = HuSqrtf(dx * dx + dz * dz);
                dx = sindf(ang - 10.0f) * dist - puck->trans.x;
                dz = cosdf(ang - 10.0f) * dist - puck->trans.z;
                if (HuSqrtf(dx * dx + dz * dz) < d) {
                    dx = sindf(a1) * dist;
                    dz = cosdf(a1) * dist;
                } else {
                    dx = sindf(ang - 10.0f) * dist;
                    dz = cosdf(ang - 10.0f) * dist;
                }
                v.x = dx - obj->trans.x;
                v.y = 0.0f;
                v.z = dz - obj->trans.z;
                func_800202FC_main(&v);
                D_800CBB6E_main[port] = v.x * 60.0f * D_80108664_ice_rink_risk[diff];
                D_800D20A1_main[port] = v.z * -60.0f * D_80108664_ice_rink_risk[diff];
            } else {
                dx = obj->trans.x;
                dz = obj->trans.z;
                if (HuSqrtf(dx * dx + dz * dz) > 350.0f) {
                    v.x = -obj->trans.x;
                    v.y = 0.0f;
                    v.z = -obj->trans.z;
                    func_800202FC_main(&v);
                    D_800CBB6E_main[port] = v.x * 60.0f * D_80108664_ice_rink_risk[diff];
                    D_800D20A1_main[port] = v.z * -60.0f * D_80108664_ice_rink_risk[diff];
                }
            }
        }
        D_8010865C_ice_rink_risk[player][0] = D_800CBB6E_main[port];
        D_8010865C_ice_rink_risk[player][1] = D_800D20A1_main[port];
    }
    return 1;
}

void func_80107590_ice_rink_risk(omObjData* obj) {
    func_80106710_ice_rink_risk(obj, D_800A178C_main[GwPlayer[0].chr][0], D_800A178C_main[GwPlayer[0].chr][2], 0);
    obj->trans.x = D_80108550_ice_rink_risk[0].x;
    obj->trans.y = D_80108550_ice_rink_risk[0].y;
    obj->trans.z = D_80108550_ice_rink_risk[0].z;
}

void func_80107604_ice_rink_risk(omObjData* obj) {
    func_80106710_ice_rink_risk(obj, D_800A178C_main[GwPlayer[1].chr][0], D_800A178C_main[GwPlayer[1].chr][2], 1);
    obj->trans.x = D_80108550_ice_rink_risk[1].x;
    obj->trans.y = D_80108550_ice_rink_risk[1].y;
    obj->trans.z = D_80108550_ice_rink_risk[1].z;
}

void func_80107678_ice_rink_risk(omObjData* obj) {
    func_80106710_ice_rink_risk(obj, D_800A178C_main[GwPlayer[2].chr][0], D_800A178C_main[GwPlayer[2].chr][2], 2);
    obj->trans.x = D_80108550_ice_rink_risk[2].x;
    obj->trans.y = D_80108550_ice_rink_risk[2].y;
    obj->trans.z = D_80108550_ice_rink_risk[2].z;
}

void func_801076EC_ice_rink_risk(omObjData* obj) {
    func_80106710_ice_rink_risk(obj, D_800A178C_main[GwPlayer[3].chr][0], D_800A178C_main[GwPlayer[3].chr][2], 3);
    obj->trans.x = D_80108550_ice_rink_risk[3].x;
    obj->trans.y = D_80108550_ice_rink_risk[3].y;
    obj->trans.z = D_80108550_ice_rink_risk[3].z;
}

/* A puck: models and physics constants; drops in from y 900. */
void func_80107760_ice_rink_risk(omObjData* obj) {
    IrPuck* w;
    s32 i;

    obj->data = HuMemAllocTag(sizeof(IrPuck), 31000);
    memset(obj->data, 0, sizeof(IrPuck));
    w = obj->data;
    obj->model[0] = func_8000B0A0_main(0x3A0000, 0x899);
    obj->model[1] = func_8000B0D4_main(9, 0xADD);
    obj->model[2] = func_8000B108_main(0x3A0002, 0xADD);
    func_800E3584_minigame(obj->model[1]);
    obj->func = func_8010796C_ice_rink_risk;
    w->unk44 = 0.3f;
    w->unk48 = 60.0f;
    w->unk34 = 50.0f;
    w->unk3C = rand8() * 1.4117647f;
    w->unk78 = 0;
    w->unk52 = 7;
    w->unk7C = 0;
    w->unk50 = 0;
    w->unk40 = 11.0f;
    w->unk74 = 0.5f;
    w->unk56 = D_80108684_ice_rink_risk;
    w->unk54 = 1;
    for (i = 0; i < 9; i++) {
        w->unk84[i] = NULL;
    }
    func_800E149C_minigame(obj, 0, 2);
    obj->trans.x = rand8() >> 2;
    obj->trans.y = D_80108580_ice_rink_risk[D_80108684_ice_rink_risk].y;
    obj->trans.z = rand8() >> 2;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.2f;
    D_80108684_ice_rink_risk++;
}

/* A puck's step (minigame func_800D6B70_minigame without its hooks). */
void func_8010796C_ice_rink_risk(omObjData* obj) {
    IrPuck* w = obj->data;
    s32 ret = 0;
    f32 x;
    f32 y;
    f32 z;
    f32 rot;
    f32 vy;
    f32 h;
    s32 i;
    s8 p;

    if (D_801085EC_ice_rink_risk[w->unk56] != 0) {
        D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
        x = obj->trans.x;
        y = obj->trans.y;
        z = obj->trans.z;
        rot = w->unk3C;
        if (w->unk40 > 25.0f) {
            w->unk40 = 25.0f;
        }
        x += sindf(rot) * w->unk40;
        z += cosdf(rot) * w->unk40;
        vy = w->unk38;
        if (vy != 1000.0f) {
            y += vy * vy * ((vy >= 0.0f) ? -35.0f : 35.0f);
            w->unk38 += D_800EB72C_minigame;
            if (D_800EB720_minigame < w->unk38) {
                w->unk38 = D_800EB720_minigame;
            }
            h = func_80107CB4_ice_rink_risk(obj, x, y, z);
            if (y < h) {
                y = h;
                if (ret != 1) {
                    w->unk38 = -w->unk38 * 0.7f;
                    if (w->unk38 >= -0.4f) {
                        w->unk38 = 1000.0f;
                    }
                    for (i = 0; i < 4; i++) {
                        p = (s8)(D_800EC598_minigame[i]->work[3] >> 16);
                        if (D_801085FC_ice_rink_risk[p] == 1) {
                            omVibrate(p, 2, 3, 10);
                        }
                    }
                }
            }
        } else {
            y = func_80107CB4_ice_rink_risk(obj, x, y, z);
        }
        func_800E17D4_minigame(obj, x + D_800EBE2C_minigame, y, z + D_800EC5D8_minigame);
        D_80108688_ice_rink_risk[w->unk56] += w->unk40 / 5.0f;
        D_80108688_ice_rink_risk[w->unk56] = func_800202A8_main(D_80108688_ice_rink_risk[w->unk56]);
        func_80088910_main((f32 (*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, D_80108688_ice_rink_risk[w->unk56], 0.0f);
    }
}

f32 func_80107CB4_ice_rink_risk(omObjData* obj, f32 x, f32 y, f32 z) {
    IrPuck* w = obj->data;
    Vec4f p;

    p.x = x;
    p.y = y;
    p.z = z;
    p.w = w->unk48;
    func_80107F58_ice_rink_risk(obj, x, y, z);
    func_80108134_ice_rink_risk(obj, &p);
    return func_80107D14_ice_rink_risk(obj, &p);
}

f32 func_80107D14_ice_rink_risk(omObjData* obj, Vec4f* p) {
    IrPuck* w = obj->data;
    Vec n;
    f32 y = p->y;
    f32 h = func_80107F24_ice_rink_risk(obj, p, &n);
    f32 g = h;

    if (h < y - w->unk34 || y + w->unk34 <= h) {
        if (w->unk38 == 1000.0f) {
            w->unk38 = 0.0f;
        }
        h = y;
    }
    func_80107DEC_ice_rink_risk(obj, p->x, h, p->z, g, &n);
    return h;
}

/* The shadow (model[1]) follows the rink under the puck, shrinking with the height. */
void func_80107DEC_ice_rink_risk(omObjData* obj, f32 x, f32 y, f32 z, f32 g, Vec* n) {
    IrPuck* w = obj->data;
    f32 s = 1.0f;
    f32 d;

    if (obj->model[1] != 0) {
        d = y - g;
        if (d != 0.0f) {
            if (d > 900.0f) {
                s = 0.1f;
            } else {
                s = 1.0f - fabsf(d) / 1000.0f;
            }
            w->unk53 = -1;
        }
        Hu3DModelPosSet(obj->model[1], x, g + 5.0f, z);
        Hu3DModelScaleSet(obj->model[1], s, 1.0f, s);
        func_800E3628_minigame(obj->model[1], n);
        func_8001C258_main(obj->model[1], 4, 0);
    }
}

/* The rink is flat: its top height, normal up. */
f32 func_80107F24_ice_rink_risk(omObjData* obj, Vec4f* p, Vec* n) {
    f32 h;

    ((IrPuck*)obj->data)->unk53 = 0;
    h = ((IrGround*)D_800EC1C0_minigame[0]->data)->unk14;
    n->x = 0.0f;
    n->y = 1.0f;
    n->z = 0.0f;
    return h;
}

/* Pucks hitting each other bounce off. */
// register allocation (masked 20): retail hoists 0.0f into f24 and keeps 1000.0f in a GPR (one more saved
// register), as in minigame func_800D7AA8_minigame; logic checked against the asm
#ifdef NON_MATCHING
void func_80107F58_ice_rink_risk(omObjData* obj, f32 x, f32 y, f32 z) {
    IrPuck* w = obj->data;
    omObjData* o;
    IrPuck* ow;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    s32 i;

    for (i = 0; i < D_801085F8_ice_rink_risk; i++) {
        if (i != w->unk56) {
            o = D_800EBE70_minigame[i];
            ow = o->data;
            dx = o->trans.x - (x + D_800EBE2C_minigame);
            dy = o->trans.y - y;
            dz = o->trans.z - (z + D_800EC5D8_minigame);
            d = HuSqrtf(dx * dx + dy * dy + dz * dz) - 2.0f * w->unk48;
            if (d < 0) {
                if (w->unk38 == 1000.0f) {
                    func_800DFCDC_minigame(dx, dz, d);
                }
                func_80108384_ice_rink_risk(obj, dx, dz);
                if (D_801085B0_ice_rink_risk[w->unk56].timer >= 16) {
                    D_801085B0_ice_rink_risk[w->unk56].owner = ow->unk56;
                    D_801085B0_ice_rink_risk[w->unk56].timer = 0;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107F58_ice_rink_risk);
#endif

/* The rink's wall (a cylinder) pushes the puck back (minigame func_800D7C14_minigame for one
   ground object). Retail adds the z push to the probe's y, as the framework does. */
void func_80108134_ice_rink_risk(omObjData* obj, Vec4f* p) {
    IrPuck* w = obj->data;
    Vec4f base;
    Vec4f probe;
    Vec save;
    omObjData* g;

    base.x = p->x;
    base.y = w->unk34 / 2.0f + p->y;
    base.z = p->z;
    base.w = p->w;
    D_800EB736_minigame = 0;
    g = D_800EC1C0_minigame[0];
    probe.x = save.x = p->x;
    probe.y = save.y = w->unk34 / 2.0f + p->y;
    probe.z = save.z = p->z;
    probe.w = base.w = p->w;
    func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, (Vec*)&probe, g);
    probe.x += D_800EBE2C_minigame;
    probe.y += D_800EC5D8_minigame;
    func_800DC7D8_minigame(g, &probe);
    if (D_800EB736_minigame != 0) {
        func_800E2B58_minigame(D_800EC240_minigame, D_800EC298_minigame);
    }
    func_8010826C_ice_rink_risk(obj);
}

/* After a wall contact, reflect the heading off the contact normal and speed up. */
void func_8010826C_ice_rink_risk(omObjData* obj) {
    IrPuck* w;
    Vec a;
    Vec b;
    Vec c;
    f32 d;

    if (D_800EB736_minigame != 0) {
        w = obj->data;
        HuAudFXPlay(0x3D2);
        a.x = D_800EC298_minigame[0].x;
        a.y = b.y = 0.0f;
        a.z = D_800EC298_minigame[0].z;
        b.x = sindf(w->unk3C + 180.0f);
        b.z = cosdf(w->unk3C + 180.0f);
        d = HuVecDot3F(&a, &b);
        a.x *= d;
        a.z *= d;
        HuVecSubtract(&c, &a, &b);
        HuVecAdd(&c, &a, &c);
        w->unk3C = atan2df(c.x, c.z);
        w->unk40 += 1.0f;
    }
}

/* After a puck contact, reflect the heading (with a random spread), speed up and record the hit. */
void func_80108384_ice_rink_risk(omObjData* obj, f32 dx, f32 dz) {
    IrPuck* w = obj->data;
    Vec a;
    Vec b;
    Vec c;
    f32 d;

    HuAudFXPlay(0x3D2);
    a.x = dx;
    a.y = b.y = 0.0f;
    a.z = dz;
    func_800202FC_main(&a);
    b.x = sindf(w->unk3C + 180.0f);
    b.z = cosdf(w->unk3C + 180.0f);
    d = HuVecDot3F(&a, &b);
    a.x *= d;
    a.z *= d;
    HuVecSubtract(&c, &a, &b);
    HuVecAdd(&c, &a, &c);
    w->unk3C = atan2df(c.x, c.z) + (rand8() - 128.0f) / 64.0f;
    w->unk40 += 1.0f;
    D_801085B0_ice_rink_risk[w->unk56].pos.x = dx + obj->trans.x;
    D_801085B0_ice_rink_risk[w->unk56].pos.y = obj->trans.y;
    D_801085B0_ice_rink_risk[w->unk56].pos.z = dz + obj->trans.z;
}

/* .data (0x80108550-0x801086B0) */
Vec D_80108550_ice_rink_risk[4] = { /* player start positions */
    { -150.0f, 100.0f, -150.0f },
    { -150.0f, 100.0f, 150.0f },
    { 150.0f, 100.0f, -150.0f },
    { 150.0f, 100.0f, 150.0f },
};
Vec D_80108580_ice_rink_risk[4] = { /* puck drop positions (only y is read) */
    { 40.0f, 900.0f, 10.0f },
    { 30.0f, 900.0f, 20.0f },
    { 20.0f, 900.0f, 30.0f },
    { 10.0f, 900.0f, 40.0f },
};
IrHit D_801085B0_ice_rink_risk[3] = {
    { -1, 20, { 0.0f, 0.0f, 0.0f } },
    { -1, 20, { 0.0f, 0.0f, 0.0f } },
    { -1, 20, { 0.0f, 0.0f, 0.0f } },
};
s32 D_801085EC_ice_rink_risk[3] = { 0, 0, 0 }; /* puck released */
s32 D_801085F8_ice_rink_risk = 0;              /* pucks released */
s32 D_801085FC_ice_rink_risk[4] = { 1, 1, 1, 1 }; /* player still on the rink */
IrCtrl D_8010860C_ice_rink_risk = {
    0, 0, 1, 2, 0, 0, 0, 0, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0, 0, 0, 0 }, 60, 900, -1, 75, 135,
};
s32 D_80108634_ice_rink_risk = 1; /* the finish still has to stop the pucks */
s32 D_80108638_ice_rink_risk = 0; /* frames played */
s32 D_8010863C_ice_rink_risk[4] = { 0, 0, 0, 0 }; /* frames knocked out */
s32 D_8010864C_ice_rink_risk[4] = { 0, 0, 0, 0 }; /* knocked out */
s8 D_8010865C_ice_rink_risk[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } }; /* CPU stick */
f32 D_80108664_ice_rink_risk[4] = { 0.75f, 0.8f, 0.9f, 1.0f }; /* CPU stick scale per difficulty */
f32 D_80108674_ice_rink_risk[4] = { 30.0f, 20.0f, 10.0f, 0.0f }; /* CPU dodge range - 150 per difficulty */
s32 D_80108684_ice_rink_risk = 0; /* pucks created */
f32 D_80108688_ice_rink_risk[10] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; /* puck spin */
