#include "common.h"
#include "game/hmfman.h"
#include "mallocblock.h"

/* other mgmode units (still asm) */
extern void func_801168E0_mgmode(s32);
extern void func_80116968_mgmode(s32, s16, s16, s16);
extern void func_801169A0_mgmode(s32, s16);
extern void func_801169C8_mgmode(s32, s16);
extern void func_80116D4C_mgmode(void);
extern void func_80116E24_mgmode(s16);
extern void func_80116ED4_mgmode(s16, s16, s16, void (*)(s16*));
extern void func_801181F4_mgmode(s32);
extern void func_8011822C_mgmode(void*);
extern void func_8011829C_mgmode(s32);
extern void func_801182A8_mgmode(s16);
extern void func_801182B4_mgmode(s32);
extern s16 func_801182DC_mgmode(s16, s8);
extern void func_80118D0C_mgmode(void);
extern void func_80118CD8_mgmode(void);

typedef f32 Matrix4f[4][4];

/* model part looked up by name; only its matrix at 0x58 is used here */
typedef struct MgModelPart {
    /* 0x00 */ char unk_00[0x58];
    /* 0x58 */ Matrix4f mtx;
} MgModelPart;

void* func_8001D33C_main(s16, const char*);
void func_8002367C_main(Matrix4f, Matrix4f);
void func_80017D24_main(Matrix4f, f32, f32, f32);

/* views of HmfData parts (unk60, 0x68 each) and faces (unkB0, 0x18 each) */
typedef struct MgHmfPart {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ s16 face;
    /* 0x2E */ s16 faceCount;
    /* 0x30 */ char unk30[0x20];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ void* unk54;
    /* 0x58 */ char unk58[0x10];
} MgHmfPart;

typedef struct MgHmfFace {
    /* 0x00 */ u8 count;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ s16 vtx[10];
} MgHmfFace;

s16 func_8002C834_main(HmfData*, char*);

/* sprite file list entry for func_80116794_mgmode */
typedef struct MgSprFile {
    /* 0x00 */ s32 file;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s32 unk8;
} MgSprFile;

extern s32 func_80116794_mgmode(MgSprFile*, MgSprFile*, s32);
extern u8 D_800CB8B1_main[];

/* minigame table seen from the word before D_800A6D44_main (0x14 per minigame) */
typedef struct MgTable {
    /* 0x00 */ s32 ovl;
    /* 0x04 */ u8 type;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 flags;
    /* 0x08 */ char unk8[0xC];
} MgTable;
extern MgTable D_800A6D40_main[];

/* main-segment data (undefined_syms.txt aliases: the parts this unit reads) */
extern u16 D_800CE2A0_main[10];
extern s16 D_800D1FE0_main;
extern s16 D_800CB894_main;
extern u8 D_800CE20A_main;
extern s16 D_800D0468_main;
extern u16 D_800CC698_main;
extern s8 D_800D2124_main[];
void func_8000BC48_main(u16, u16);
extern s16 func_80116B20_mgmode(void);
extern void func_80116C18_mgmode(s16);
extern void func_801182C0_mgmode(s16);
void func_80109C10_mgmode(s16, s16);
void func_80109DBC_mgmode(s16, s16);
s16 func_8010A148_mgmode(s16);
void func_8010A5F0_mgmode(void);

typedef struct MgScreenPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} MgScreenPos;
extern MgScreenPos D_8011AA18_mgmode[];
extern u16 D_80119200_mgmode[];
extern void HmfLightStatSet(s16, s16, s16);

void func_8010606C_mgmode(void);
void func_8010A8E4_mgmode(s32);
void func_8010AF78_mgmode(Gfx**, s32, s32);
void func_8010A62C_mgmode(s32, s16);
void func_8010A824_mgmode(s32, s16);
void func_8010AFEC_mgmode(void);
void func_8010BD28_mgmode(omObjData*);
extern void func_8010BEC0_mgmode(void);
extern s32 func_80111B08_mgmode(void);
extern void func_80112200_mgmode(void);
extern void func_80117DD0_mgmode(void);

/* overlay .data (shared by every mgmode unit, still asm) */
extern u8 D_80118EB0_mgmode;
extern u8 D_80118EB1_mgmode;
extern u8 D_80118EB2_mgmode;
extern s16 D_80118EB4_mgmode;
extern u8 D_80119158_mgmode[];
extern u8 D_80119170_mgmode[];
extern s32 D_80119190_mgmode[];
extern s32 D_801191E4_mgmode[];
extern Gfx D_80119290_mgmode[];
extern char* D_801192D8_mgmode[];
extern u8 D_801192F4_mgmode[];
extern s8 D_801192FC_mgmode[];
extern s8 D_80119310_mgmode[];
extern u16 D_80119320_mgmode[];
extern u16 D_8011932C_mgmode[];
extern MgSprFile D_8011988C_mgmode[];
extern MgSprFile D_801198BC_mgmode[];
extern MgSprFile D_801198C8_mgmode[]; /* D_801198BC_mgmode[1] */

/* overlay .bss */
extern char D_8011A708_mgmode[];
extern u8 D_8011A8C8_mgmode[8][20];
extern u8 D_8011A968_mgmode[8];
extern u8 D_8011A970_mgmode[8][20];
extern u8 D_8011AA10_mgmode[8];
extern Vec D_8011AA80_mgmode[][25];
extern char D_8011A400_mgmode[]; /* "00" */
extern char D_8011A404_mgmode[]; /* "door_b" */
extern char D_8011A40C_mgmode[]; /* "door_g" */
extern char D_8011A430_mgmode[]; /* "%d" */
extern char D_8011A46C_mgmode[]; /* "moniter_R" */
extern Matrix4f D_8011A808_mgmode;
extern Matrix4f D_8011A848_mgmode;
extern Matrix4f D_8011A888_mgmode;
extern u16* D_8011B3E0_mgmode;
extern s16 D_8011B3E4_mgmode;
extern s8 D_8011B3E6_mgmode[];
extern s32 D_8011B3EC_mgmode;
extern s16 D_8011B6A0_mgmode;
extern f32 D_8011B6A4_mgmode;
extern u8 D_8011B6B0_mgmode[][25];
extern s8 D_8011B778_mgmode;
extern s16 D_8011B77A_mgmode;
extern s16 D_8011B6A8_mgmode;
extern f32 D_8011B804_mgmode;
extern s16 D_8011B800_mgmode;
extern s16 D_8011B808_mgmode;
extern s16 D_8011B80A_mgmode;
extern s16 D_8011B884_mgmode;
extern Vec D_8011B88C_mgmode;
extern f32 D_8011B888_mgmode;
extern Vec D_8011B898_mgmode;
extern s8 D_8011B8A4_mgmode;
extern s16 D_8011B8A8_mgmode[];
extern s16 D_8011B8B2_mgmode;
extern s16 D_8011B8B4_mgmode;
extern s16 D_8011B8B6_mgmode[];
extern s16 D_8011B8C4_mgmode;
extern s16 D_8011B8C6_mgmode;
extern s16 D_8011B928_mgmode[];
extern f32 D_8011B938_mgmode;
extern s16 D_8011B940_mgmode[];
extern s16 D_8011B950_mgmode;
extern u8 D_8011B958_mgmode;
extern s16 D_8011B95A_mgmode;

void func_80108DDC_mgmode(s16);
void func_80108CF4_mgmode(s16);
void func_801090C4_mgmode(s16);
void func_80107D0C_mgmode(s32, s16, s16);
void func_8000BE5C_main(u16, f32, f32);
u16 GWMgRecordGet(s16);
void func_8010BD98_mgmode(omObjData*);

void func_801059A0_mgmode(void) {
    s16 i;
    HmfModel* model;

    omInitObjMan(20, 10);
    Hu3DCamInit(2);
    func_8005A6B0_main();
    func_800142A0_main(20);
    func_8001F38C_main(0, 0, 0);
    D_800CD280_main = 1;
    D_800D6A58_main = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    ScissorSet(1, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    D_8011B898_mgmode.z = 90.0f;
    CZoom = 660.0f;
    Center.x = 0.0f;
    Center.y = 181.0f;
    Center.z = -395.0f;
    D_8011B6A4_mgmode = 40.0f;
    D_8011B898_mgmode = CRot;
    D_8011B938_mgmode = CZoom;
    D_8011B88C_mgmode = Center;
    D_8011B804_mgmode = 80.0f;
    D_8011B888_mgmode = 1800.0f;
    Hu3DCamSetPerspective(0, D_8011B6A4_mgmode, 80.0f, 1800.0f);
    Hu3DCamSetPerspective(1, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
    HmfLightMaxSet(4);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 119.0f, 0.0f);
    HmfLightStatSet(0, 1, 1);
    HmfLightColorSet(2, 0x96, 0x96, 0x6E);
    HmfLightDirSet(2, 40.0f, 42.0f, 104.0f);
    HmfLightColorSet(3, 0, 0, 0);
    omAddObj(10000, 0, 0, -1, func_8010BD28_mgmode);
    omPrcSetStatBit(omAddPrcObj(func_8010AFEC_mgmode, 0x1100, 0x1000, 0), 0xA0);
    omAddPrcObj(func_80117DD0_mgmode, 0x3F00, 0x800, 0);
    func_8010A8E4_mgmode(0);
    if (omovlevtno == 0 || omovlevtno == 1 || omovlevtno == 6 || omovlevtno == 7) {
        omAddPrcObj(func_8010606C_mgmode, 0x3FF6, 0x2000, 0);
        HuAudSeqPlay(8);
    } else if (omovlevtno == 2 || omovlevtno == 4) {
        func_8010A8E4_mgmode(1);
        HmfLightColorSet(3, 0x82, 0x82, 0x32);
        HmfLightDirSet(3, -17.0f, -101.0f, -61.0f);
        omAddPrcObj(func_8010BEC0_mgmode, 0x3FF6, 0x2000, 0);
        if (omovlevtno == 4) {
            if (func_80111B08_mgmode() == 0) {
                HuAudSeqPlay(0x4C);
            } else {
                HuAudSeqPlay(0x16);
            }
        } else {
            HuAudSeqPlay(0x4C);
        }
    } else if (omovlevtno == 3 || omovlevtno == 5) {
        omAddPrcObj(func_80112200_mgmode, 0x3FF6, 0x2000, 0);
        if (omovlevtno == 5 && D_800D1FE0_main + D_800CB894_main * GwPlayer[0].bonusCoin >= 1000) {
            HuAudSeqPlay(0x46);
        } else {
            HuAudSeqPlay(0x4D);
        }
    }
    if (omovlevtno != 0) {
        for (i = 0; i < 10; i++) {
            if (D_800CE2A0_main[i] != GwCommon.mgRecord[i]) {
                break;
            }
        }
        if (i != 10) {
            func_80118CD8_mgmode();
        }
    }
    for (i = 0; i < 10; i++) {
        D_800CE2A0_main[i] = GwCommon.mgRecord[i];
    }
    D_8011B808_mgmode = 0;
    D_8011B800_mgmode = 0;
    _ClearFlag(0xD);
    _SetFlag(0x1C);
    D_800CE20A_main = 0;
    model = &HmfModelData[D_800D0468_main];
    model->unk00 = (model->unk00 & 0xF9) | 3;
    func_8001C8A8_main(D_800D0468_main, 1);
    D_8011B8A4_mgmode = 0;
    D_8011B778_mgmode = 0;
    for (i = 0; i < 6; i++) {
        if (D_8011B928_mgmode[i] >= 3) {
            D_8011B778_mgmode = 1;
            break;
        }
    }
    if (_CheckFlag(0x1D)) {
        D_8011B8A4_mgmode = 1;
    }
    D_8011B884_mgmode = 0;
    func_8001C8A8_main(func_8001AC8C_main(0, func_8010AF78_mgmode, 0), 2);
    for (i = 0; i < 4; i++) {
        D_800CB8B1_main[i] = 0;
    }
    D_800CC698_main = 0;
    for (i = 0; i < 4; i++) {
        GwPlayer[i].star = 0;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A400_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A404_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A40C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010606C_mgmode);

s16 func_80107298_mgmode(void) {
    s16 size[2];
    s16 win;
    s16 count;
    s16 total;
    s16 left;

    count = 0;
    if (_CheckFlag(0x1E) && !_CheckFlag(0x2A)) {
        count = 1;
        _SetFlag(0x2A);
    }
    if (D_8011B928_mgmode[0] >= 20 && D_8011B928_mgmode[1] >= 10 && D_8011B928_mgmode[2] >= 10 &&
        D_8011B928_mgmode[3] >= 8 && D_8011B928_mgmode[4] >= 10 && D_8011B928_mgmode[5] >= 6 && !_CheckFlag(0x2B)) {
        count++;
        _SetFlag(0x2B);
    }
    if (_CheckFlag(0x1F) && !_CheckFlag(0x2C)) {
        count++;
        _SetFlag(0x2C);
    }
    if (count == 0) {
        return 0;
    }
    func_8006022C_main((u32)D_8011A400_mgmode, 0);
    func_8006022C_main((u32)D_8011A400_mgmode, 1);
    func_800604A8_main(size, 0x570D, 0x5710);
    win = func_80061188_main(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    func_8005FE54_main(win, 1 << D_8011B808_mgmode);
    func_8005B43C_main(win, 0x570D, -1, -1);
    func_80061388_main(win);
    while (func_8005E0C0_main(win)) {
        HuPrcVSleep();
    }
    if (count == 3) {
        func_8005B43C_main(win, 0x570F, -1, -1);
    } else {
        sprintf(D_8011A708_mgmode, D_8011A430_mgmode, count);
        func_8005B6BC_main(win, (u32)D_8011A708_mgmode, 0);
        func_8005B43C_main(win, 0x570E, -1, -1);
    }
    while (func_8005E0C0_main(win)) {
        HuPrcVSleep();
    }
    total = D_8011B928_mgmode[0] + D_8011B928_mgmode[1] + D_8011B928_mgmode[2] + D_8011B928_mgmode[3] +
            D_8011B928_mgmode[4] + D_8011B928_mgmode[5] + D_8011B928_mgmode[7];
    left = 67 - total;
    if (left == 0) {
        func_8005B43C_main(win, 0x5711, -1, -1);
    } else {
        sprintf(D_8011A708_mgmode, D_8011A430_mgmode, total);
        func_8005B6BC_main(win, (u32)D_8011A708_mgmode, 0);
        func_8005B43C_main(win, 0x5710, -1, -1);
    }
    while (func_8005E0C0_main(win)) {
        HuPrcVSleep();
    }
    func_80061A5C_main(win, 0);
    func_8005F364_main(win);
    func_80118CD8_mgmode();
    return count;
}

void func_80107610_mgmode(void) {
    s32 angle = 0;

    Hu3DModelScaleSet(D_8011B8B2_mgmode, 0.5f, 0.5f, 0.5f);
    while (TRUE) {
        HuPrcVSleep();
        HmfModelData[D_8011B8B2_mgmode].pos.y = sindf(angle) * 20.0f;
        angle += 2;
        if (angle > 360) {
            angle -= 360;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A430_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A434_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A43C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A444_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A44C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A454_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A45C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A464_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A46C_mgmode);

#ifdef NON_MATCHING
/* register allocation in the face centroid loop (i/j/vtx/count swap registers); otherwise identical */
void func_801076B0_mgmode(void) {
    s16 order[20];
    Vec tmp;
    HmfData* hmf;
    MgHmfFace* face;
    s16 j;
    s16 i;
    Vtx* vtx;
    Vtx* buf;
    s16 book;
    s16 part;
    s16 count;
    s16 k;
    s16 t;
    s16 model;
    f32 x;
    f32 y;
    f32 z;
    void* anim;

    func_8002367C_main(D_8011A808_mgmode, ((MgModelPart*)func_8001D33C_main(D_8011B8A8_mgmode[6], D_8011A46C_mgmode))->mtx);
    func_8002367C_main(D_8011A848_mgmode, ((MgModelPart*)func_8001D33C_main(D_8011B8A8_mgmode[3], D_8011A404_mgmode))->mtx);
    func_8002367C_main(D_8011A888_mgmode, ((MgModelPart*)func_8001D33C_main(D_8011B8A8_mgmode[3], D_8011A40C_mgmode))->mtx);
    model = D_8011B8A8_mgmode[2];
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    hmf = HmfModelData[model].hmf;
    for (book = 0; book < 7; book++) {
        part = func_8002C834_main(hmf, D_801192D8_mgmode[book]);
        face = &(*(MgHmfFace**)hmf->unkB0)[((MgHmfPart*)hmf->unk60)[part].face];
        vtx = hmf->unk40;
        i = 0;
        count = ((MgHmfPart*)hmf->unk60)[part].faceCount;
        for (; i < count; i++, face++) {
            x = y = z = 0.0f;
            for (j = 0; j < face->count; j++) {
                x += vtx[face->vtx[j]].v.ob[0];
                y += vtx[face->vtx[j]].v.ob[1];
                z += vtx[face->vtx[j]].v.ob[2];
            }
            D_8011AA80_mgmode[book][i].x = x / face->count;
            D_8011AA80_mgmode[book][i].y = y / face->count;
            D_8011AA80_mgmode[book][i].z = z / face->count;
            order[i] = i;
        }
        for (j = count - 1; j >= 0; j--) {
            for (k = 0; k < j; k++) {
                if (D_8011AA80_mgmode[book][k + 1].x < D_8011AA80_mgmode[book][k].x) {
                    tmp = D_8011AA80_mgmode[book][k];
                    D_8011AA80_mgmode[book][k] = D_8011AA80_mgmode[book][k + 1];
                    D_8011AA80_mgmode[book][k + 1] = tmp;
                    t = order[k];
                    order[k] = order[k + 1];
                    order[k + 1] = t;
                }
            }
        }
        for (i = 0; i < count; i++) {
            face = &(*(MgHmfFace**)hmf->unkB0)[((MgHmfPart*)hmf->unk60)[part].face + order[i]];
            for (j = 0; j < D_800D1FF0_main; j++) {
                buf = hmf->unk44[j];
                for (k = 0; k < face->count; k++) {
                    if (D_8011B6B0_mgmode[D_801191E4_mgmode[book]][i] != 0xFF) {
                        if (book == 6 && i == 0) {
                            buf[face->vtx[k]].v.tc[0] += 0x1000;
                        } else {
                            buf[face->vtx[k]].v.tc[0] += D_801192F4_mgmode[book] << 9;
                        }
                    } else {
                        buf[face->vtx[k]].v.tc[0] += 0xE00;
                    }
                }
            }
        }
    }
    model = D_8011B8C6_mgmode;
    anim = DataRead(0xA002A);
    HmfAnimCreate(HmfModelData[model].hmf, anim, 0, "c160n_0_DEF");
    DataClose(anim);
    func_8001C448_main(model);
    func_8001C514_main(model);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801076B0_mgmode);
#endif

#ifdef NON_MATCHING
/* GCC hoists y - 0x47 out of the window loop where retail adds it per pass, and s0/s1/s2 swap in the unlock check; otherwise identical */
void func_80107D0C_mgmode(s32 file, s16 x, s16 y) {
    s16 win[10];
    u8 buf0[32];
    u8 buf1[32];
    u8 buf2[32];
    u8 ids[10] = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8 };
    s8 mgs[10] = { 0x0D, 0x10, 0x23, 0x34, 0x2C, 0x47, 0x47, 0x47, 0x00, -1 };
    s32 mes[10] = { 0x4501, 0x4502, 0x4503, 0x4504, 0x4505, 0x4506, 0x4507, 0x4508, 0x4509, 0x450A };
    s16 sprGrp;
    s16 spr;
    s16 cursor;
    s16 i;
    s16 j;
    s16 rec;
    s16 mg;
    f32 scale;

    HuPrcSleep(3);
    sprGrp = func_8000B838_main(file);
    spr = InitEspriteSlot(sprGrp, 0, 1);
    func_8000BBD4_main(spr, x, y);
    func_8000BCC8_main(spr, 0x8000);
    func_8000BE5C_main(spr, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        win[i] = func_80061188_main(-1, x - 0x68, y + (i * 14 - 0x47), 0xD5, 0x14, 0);
        func_8005BEE0_main(win[i], 0);
    }
    cursor = func_80061188_main(-1, 0, 0, 0xD2, 0xE, 1);
    func_8005FBF8_main(cursor, 0xFF, 0xFF, 0xFF);
    HuAudFXPlay(0x2E7);
    for (i = 1; i < 11; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        func_8000BE5C_main(spr, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        rec = GWMgRecordGet(ids[i]);
        if (rec < 0) {
            rec = 0;
        }
        switch (ids[i]) {
        case 0:
            sprintf((char*)buf0, "%3d", rec);
            func_8005B6BC_main(win[i], (u32)buf0, 0);
            break;
        case 1:
        case 2:
        case 5:
        case 6:
        case 7:
            sprintf((char*)buf0, D_8011A430_mgmode, (s16)(rec / 3600));
            func_8005B6BC_main(win[i], (u32)buf0, 0);
            rec %= 3600;
            sprintf((char*)buf1, "%2d", (s16)(rec / 60));
            if (buf1[0] == ' ') {
                buf1[0] = '0';
            }
            func_8005B6BC_main(win[i], (u32)buf1, 1);
            sprintf((char*)buf2, "%2d", (s16)((s16)(rec % 60) / 60.0f * 100.0f));
            if (buf2[0] == ' ') {
                buf2[0] = '0';
            }
            func_8005B6BC_main(win[i], (u32)buf2, 2);
            break;
        case 4:
            sprintf((char*)buf0, "%3d", (s16)(rec / 100));
            rec %= 100;
            func_8005B6BC_main(win[i], (u32)buf0, 0);
            sprintf((char*)buf1, "%2d", rec);
            if (buf1[0] == ' ') {
                buf1[0] = '0';
            }
            func_8005B6BC_main(win[i], (u32)buf1, 1);
            break;
        case 3:
        case 9:
            sprintf((char*)buf0, D_8011A430_mgmode, (s16)(rec / 1800));
            func_8005B6BC_main(win[i], (u32)buf0, 0);
            rec %= 1800;
            sprintf((char*)buf1, "%2d", (s16)(rec / 30));
            if (buf1[0] == ' ') {
                buf1[0] = '0';
            }
            func_8005B6BC_main(win[i], (u32)buf1, 1);
            sprintf((char*)buf2, "%2d", (s16)((s16)(rec % 30) * (1.0f / 30.0f) * 99.0f));
            if (buf2[0] == ' ') {
                buf2[0] = '0';
            }
            func_8005B6BC_main(win[i], (u32)buf2, 2);
            break;
        case 8:
            sprintf((char*)buf0, "%4d", rec);
            func_8005B6BC_main(win[i], (u32)buf0, 0);
            break;
        }
        func_8005FFA8_main(win[i]);
        mg = mgs[i] - 1;
        if (mg == 0x46 && _CheckFlag(0x2B)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else if (mg >= 0 && GWMgUnlockCheck(mg)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else if (mg == -1 && _CheckFlag(0x1E)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else if (mg == -2 && _CheckFlag(0x1F)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else {
            func_8005B43C_main(win[i], 0x4500, -1, -1);
        }
        func_8005BA90_main(cursor, x, y + i * 14 - 0x3E);
        func_8005FFA8_main(cursor);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            func_8005BEE0_main(cursor, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
    }
    func_8005F364_main(cursor);
    do {
        HuPrcVSleep();
    } while (!(D_800D5558_main[0] & 0xC000));
    for (i = 0; i < 10; i++) {
        func_8005FE90_main(win[i]);
    }
    HuAudFXPlay(0x2E9);
    for (i = 1; i < 11; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        func_8000BE5C_main(spr, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        func_8005F364_main(win[i]);
    }
    func_8000C184_main(spr);
    HuSprKill(sprGrp);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A484_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A490_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A49C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107D0C_mgmode);
#endif

void func_80108824_mgmode(s32 arg0) {
    s16 total;
    s16 choice;
    s16 i;
    MgModelPart* part;

    total = D_8011B928_mgmode[0] + D_8011B928_mgmode[1] + D_8011B928_mgmode[2] + D_8011B928_mgmode[3] +
            D_8011B928_mgmode[4] + D_8011B928_mgmode[5] + D_8011B928_mgmode[7];
    if (total < 0) {
        total = 0;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, total);
    func_8005B6BC_main(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    if (arg0 == 0) {
        func_8005B43C_main(D_8011B6A0_mgmode, 0x570B, -1, -1);
        func_80061388_main(D_8011B6A0_mgmode);
        while (func_8005E0C0_main(D_8011B6A0_mgmode)) {
            HuPrcVSleep();
        }
        func_8005B43C_main(D_8011B6A0_mgmode, 0x5712, -1, -1);
        while (func_8005E0C0_main(D_8011B6A0_mgmode)) {
            HuPrcVSleep();
        }
    } else {
        func_8005B43C_main(D_8011B6A0_mgmode, 0x5712, -1, -1);
        func_80061388_main(D_8011B6A0_mgmode);
        while (func_8005E0C0_main(D_8011B6A0_mgmode)) {
            HuPrcVSleep();
        }
    }
    choice = func_8005E1D8_main(D_8011B6A0_mgmode, 0, 0);
    func_80061A5C_main(D_8011B6A0_mgmode, 0);
    if (choice == -1) {
        func_8005B43C_main(D_8011B6A8_mgmode, 0x5702, -1, -1);
        func_80061388_main(D_8011B6A8_mgmode);
        func_801182B4_mgmode(1);
        return;
    }
    if (choice == 0) {
        func_801182B4_mgmode(0);
        func_80116ED4_mgmode(2, 10, 1, (void*)-1);
        func_8005B43C_main(D_8011B6A0_mgmode, 0x5713, -1, -1);
        func_80061388_main(D_8011B6A0_mgmode);
        while (func_8005E0C0_main(D_8011B6A0_mgmode)) {
            HuPrcVSleep();
        }
        func_80108DDC_mgmode(0);
    } else if (choice == 1) {
        func_801182B4_mgmode(0);
        part = func_8001D33C_main(D_8011B8B4_mgmode, D_8011A46C_mgmode);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            func_8002367C_main(part->mtx, D_8011A808_mgmode);
            func_80017D24_main(part->mtx, 0.0f, sindf(i * 9) * 117.0f, 0.0f);
        }
        func_80116ED4_mgmode(6, 10, 1, (void*)-1);
        func_80107D0C_mgmode(0x12000F, 160, 120);
        func_80116ED4_mgmode(1, 10, 1, (void*)-1);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            func_8002367C_main(part->mtx, D_8011A808_mgmode);
            func_80017D24_main(part->mtx, 0.0f, (1.0f - sindf(i * 9)) * 117.0f, 0.0f);
        }
    }
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5702, -1, -1);
    func_80061388_main(D_8011B6A8_mgmode);
}

void func_80108C88_mgmode(void) {
    func_8005FFA8_main(D_8011B6A0_mgmode);
    func_80108DDC_mgmode(((u8*)&D_800D20AC_main)[4]);
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5702, -1, -1);
    func_80061388_main(D_8011B6A8_mgmode);
}

void func_80108CF4_mgmode(s16 arg0) {
    s32 color;

    color = (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] != 0) ? 7 : 0;
    if (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] == D_8011B940_mgmode[D_801191E4_mgmode[arg0]]) {
        color = 14;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, D_8011B928_mgmode[D_801191E4_mgmode[arg0]]);
    func_8005B6BC_main(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    func_8005B43C_main(D_8011B6A0_mgmode, D_80119190_mgmode[color + arg0], -1, -1);
}

void func_80108DDC_mgmode(s16 arg0) {
    s16 cur;
    s16 sel;

    cur = arg0;
    func_80108CF4_mgmode(arg0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8011822C_mgmode(D_80119170_mgmode);
    func_801181F4_mgmode(cur);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    HuPrcSleep(5);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if ((D_800CBB6E_main[D_8011B808_mgmode] < 0 ? -D_800CBB6E_main[D_8011B808_mgmode] : D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || (D_800D20A1_main[D_8011B808_mgmode] < 0 ? -D_800D20A1_main[D_8011B808_mgmode] : D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            sel = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (sel != -1) {
                HuAudFXPlay(1);
                func_801182A8_mgmode(sel);
                HuPrcSleep(5);
                func_80108CF4_mgmode(sel);
                cur = sel;
            }
        } else if ((D_800D5558_main[D_8011B808_mgmode] & 0x8000) && D_8011B928_mgmode[D_801191E4_mgmode[cur]] != 0) {
            HuAudFXPlay(2);
            func_801182B4_mgmode(0);
            func_80061A5C_main(D_8011B6A0_mgmode, 0);
            func_80116ED4_mgmode(cur + 7, 15, 1, (void*)-1);
            func_801090C4_mgmode(cur);
            func_80116ED4_mgmode(2, 15, 1, (void*)-1);
            func_8011822C_mgmode(D_80119170_mgmode);
            func_801181F4_mgmode(cur);
            func_8011829C_mgmode(5);
            func_801182B4_mgmode(1);
            func_80108CF4_mgmode(cur);
            func_80061388_main(D_8011B6A0_mgmode);
        } else if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            break;
        }
    }
    HuAudFXPlay(4);
    func_801182B4_mgmode(0);
    func_80061A5C_main(D_8011B6A0_mgmode, 0);
    func_80116ED4_mgmode(1, 10, 1, (void*)-1);
}

#ifdef NON_MATCHING
/* register allocation only (s3/s4 and s6/s7 swap; retail spills the window id to the stack) */
void func_801090C4_mgmode(s16 arg0) {
    Vec pos;
    Vec2f scr;
    s16 type;
    s16 count;
    s16 i;
    s16 sel;
    s16 win;
    s16 sprGrp;
    s16 ok;
    s16 choice;
    s16 cur;
    u16 bgSpr;
    u16 iconSpr;

    type = D_801191E4_mgmode[arg0];
    count = D_8011B940_mgmode[type];
    for (i = 0; i < count; i++) {
        pos = D_8011AA80_mgmode[arg0][i];
        Hu3DCam3DToScreen(0, &pos, &scr);
        D_8011AA18_mgmode[i].x = scr.x;
        D_8011AA18_mgmode[i].y = scr.y;
    }
    D_8011AA18_mgmode[i].x = -1;
    D_8011AA18_mgmode[i].y = -1;
    win = func_80061188_main(-1, 24, 16, 272, 80, 0);
    func_8005FE54_main(win, 1 << D_8011B808_mgmode);
    bgSpr = func_80116B20_mgmode();
    func_8000BC48_main(bgSpr, 8);
    func_8000BBD4_main(bgSpr, 76, 56);
    func_8000BE5C_main(bgSpr, 0.75f, 0.75f);
    sprGrp = func_8000B838_main(0x120013);
    iconSpr = InitEspriteSlot(sprGrp, 0, 1);
    func_8000BCC8_main(iconSpr, 1);
    func_8000BB94_main(iconSpr);
    func_8000BBD4_main(iconSpr, 76, 84);
    func_8011822C_mgmode(D_8011AA18_mgmode);
    cur = D_800D2124_main[arg0];
    for (i = 0; i < count; i++) {
        if (D_8011B6B0_mgmode[type][i] == 0xFF || D_8011B6B0_mgmode[type][i] >= 72) {
            func_801182C0_mgmode(i);
        } else if (cur == -1) {
            cur = D_800D2124_main[arg0] = i;
        }
    }
    func_801181F4_mgmode(cur);
    func_801182B4_mgmode(1);
    func_8011829C_mgmode(3);
    if (D_8011B6B0_mgmode[type][cur] != 0xFF && D_8011B6B0_mgmode[type][cur] < 72) {
        func_80109C10_mgmode(arg0, cur);
    }
    func_8005B6BC_main(win, D_8011B6B0_mgmode[type][cur] + 0x4700, 0);
    func_8005B43C_main(win, D_80119200_mgmode[D_8011B6B0_mgmode[type][cur]], -1, -1);
    func_80061388_main(win);
    if (D_8011B6B0_mgmode[type][cur] != 0xFF && D_8011B6B0_mgmode[type][cur] < 72) {
        func_8000BB54_main(bgSpr);
        if (D_800A6D40_main[D_8011B6B0_mgmode[type][cur]].flags >> 15) {
            func_8000BB54_main(iconSpr);
        } else {
            func_8000BB94_main(iconSpr);
        }
        func_80116C18_mgmode(D_800A6D40_main[D_8011B6B0_mgmode[type][cur]].flags & 0x7FF);
    } else {
        func_8000BB94_main(bgSpr);
    }
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if ((D_800CBB6E_main[D_8011B808_mgmode] < 0 ? -D_800CBB6E_main[D_8011B808_mgmode] : D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || (D_800D20A1_main[D_8011B808_mgmode] < 0 ? -D_800D20A1_main[D_8011B808_mgmode] : D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            sel = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (sel != -1) {
                HuAudFXPlay(1);
                func_801182A8_mgmode(sel);
                cur = sel;
                D_800D2124_main[arg0] = cur;
                for (i = 0; i < 8; i++) {
                    func_8001C258_main(D_8011B8B6_mgmode[i], 4, 4);
                }
                if (D_8011B6B0_mgmode[type][cur] != 0xFF && D_8011B6B0_mgmode[type][cur] < 72) {
                    func_80109C10_mgmode(arg0, cur);
                    func_8000BB54_main(bgSpr);
                    if (D_800A6D40_main[D_8011B6B0_mgmode[type][cur]].flags >> 15) {
                        func_8000BB54_main(iconSpr);
                    } else {
                        func_8000BB94_main(iconSpr);
                    }
                    func_80116C18_mgmode(D_800A6D40_main[D_8011B6B0_mgmode[type][cur]].flags & 0x7FF);
                    func_8005B6BC_main(win, D_8011B6B0_mgmode[type][cur] + 0x4700, 0);
                    func_8005B43C_main(win, D_80119200_mgmode[D_8011B6B0_mgmode[type][cur]], -1, -1);
                } else {
                    func_8000BB94_main(bgSpr);
                    func_8005B43C_main(win, 0x4401, -1, -1);
                }
                HuPrcSleep(3);
            }
        } else if ((D_800D5558_main[D_8011B808_mgmode] & 0x8000) && D_8011B6B0_mgmode[type][cur] != 0xFF) {
            HuAudFXPlay(2);
            for (i = 0; i < 4; i++) {
                GwPlayer[i].group = i;
            }
            ok = 1;
            if (type == 1 || type == 2) {
                func_801182B4_mgmode(0);
                ok = func_8010A148_mgmode(type);
                if (!ok) {
                    func_8010A5F0_mgmode();
                    func_801182B4_mgmode(1);
                    HuPrcSleep(5);
                }
            }
            if (ok) {
                func_8005B43C_main(win, 0x4400, -1, -1);
                while (func_8005E0C0_main(win)) {
                    HuPrcVSleep();
                }
                choice = func_8005E1D8_main(win, 0, 0);
                if (type == 1 || type == 2) {
                    func_8010A5F0_mgmode();
                }
                if (choice == -1) {
                    func_801182B4_mgmode(1);
                    HuPrcSleep(2);
                    func_8005B43C_main(win, D_80119200_mgmode[D_8011B6B0_mgmode[type][cur]], -1, -1);
                } else {
                    func_801182B4_mgmode(0);
                    _SetFlag(0xD);
                    func_80109DBC_mgmode(arg0, cur);
                    if (choice == 1) {
                        GwSystem.show_minigame_explanations = 1;
                    } else {
                        GwSystem.show_minigame_explanations = 0;
                    }
                    GwSystem.minigame_index = D_8011B6B0_mgmode[type][cur] + 1;
                    ((u8*)&D_800D20AC_main)[4] = arg0;
                    omOvlHisChg(0, 0x69, 1, 0x84);
                    D_80118EB1_mgmode = 1;
                    D_8011B95A_mgmode = 0x68;
                    if (GwSystem.minigame_index == 0x47 || GwSystem.minigame_index == 0x1F) {
                        D_8011B950_mgmode = 0;
                    } else {
                        HuAudSeqFadeOut(0x3C);
                        D_8011B950_mgmode = 1;
                    }
                    D_80118EB4_mgmode = 0x82;
                    D_800D1FE0_main = 0;
                    while (TRUE) {
                        HuPrcVSleep();
                    }
                }
            }
        } else if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            HuAudFXPlay(4);
            func_801182B4_mgmode(0);
            func_80116D4C_mgmode();
            func_8000C184_main(iconSpr);
            HuSprKill(sprGrp);
            func_80061A5C_main(win, 0);
            for (i = 0; i < 8; i++) {
                func_8001C258_main(D_8011B8B6_mgmode[i], 4, 4);
            }
            func_8005F364_main(win);
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801090C4_mgmode);
#endif

void func_80109C10_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    f32 x;
    f32 z;
    f32 len;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    func_8001C258_main(model, 4, 0);
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    len = HuSqrtf(x * x + z * z);
    x = x / len * 20.0f;
    z = z / len * 20.0f;
    Hu3DModelPosSet(model, x + D_8011AA80_mgmode[arg0][arg1].x, D_8011AA80_mgmode[arg0][arg1].y - 3.0f,
                    z + D_8011AA80_mgmode[arg0][arg1].z);
}

#ifdef NON_MATCHING
/* float register allocation: retail keeps the end point in f22/s4/s3 and the start point in f30/f28/f26 */
void func_80109DBC_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    s16 i;
    f32 x;
    f32 z;
    f32 len;
    f32 rotX;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 t;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    len = HuSqrtf(x * x + z * z);
    x = x / len * 20.0f;
    z = z / len * 20.0f;
    rotX = 15.0f;
    startX = x + D_8011AA80_mgmode[arg0][arg1].x;
    startY = D_8011AA80_mgmode[arg0][arg1].y - 3.0f;
    startZ = z + D_8011AA80_mgmode[arg0][arg1].z;
    endX = sindf(CRot.y) * cosdf(CRot.x) * CZoom + Center.x - 50.0f;
    endY = -sindf(CRot.x) * CZoom + Center.y;
    endZ = cosdf(CRot.y) * cosdf(CRot.x) * CZoom + Center.z;
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        if (i == 20) {
            WipeCreateOut(0xB, 10);
        }
        t = i / 30.0f * 0.5f;
        Hu3DModelPosSet(model, startX + (endX - startX) * t, startY + (endY - startY) * t, startZ + (endZ - startZ) * t);
        Hu3DModelRotSet(model, rotX, CRot.y - i * 3, 0.0f);
        rotX -= 3.0f;
        if (rotX < 0.0f) {
            rotX = 0.0f;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80109DBC_mgmode);
#endif

s16 func_8010A148_mgmode(s16 arg0) {
    s8* table;
    s16 i;
    s16 sel;
    s16 delay;
    s16 ret;
    MgSprFile* spr;
    s32 base;

    ret = 1;
    if (arg0 == 2) {
        D_8011B3E0_mgmode = D_80119320_mgmode;
    } else {
        D_8011B3E0_mgmode = D_8011932C_mgmode;
    }
    if (arg0 == 2) {
        table = D_801192FC_mgmode;
    } else {
        table = D_80119310_mgmode;
    }
    for (i = 0; i < 4; i++) {
        D_8011B3E6_mgmode[i] = i;
    }
    D_8011B3E4_mgmode = func_80061188_main(-1, 50, 100, 220, 80, 0);
    func_8005FE54_main(D_8011B3E4_mgmode, 1 << D_8011B808_mgmode);
    func_8005B43C_main(D_8011B3E4_mgmode, 0x5729, -2, -1);
    func_80061388_main(D_8011B3E4_mgmode);
    for (i = 0, base = 0x130000; i < 4; i++) {
        D_8011988C_mgmode[i].file = (GwPlayer[i].chr + 0x36) | base;
    }
    spr = D_801198BC_mgmode;
    spr->file = 0x120012;
    if (arg0 == 1) {
        D_801198BC_mgmode[1].file = 0x120012;
    } else {
        D_801198C8_mgmode[0].file = 0x120011;
    }
    sel = 0;
    D_8011B3EC_mgmode = func_80116794_mgmode(D_8011988C_mgmode, spr, base);
    func_8010A62C_mgmode(160, 134);
    func_8010A824_mgmode(160, 134);
    delay = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (delay != 0) {
            delay--;
        }
        func_80118D0C_mgmode();
        if ((D_800CBB6E_main[D_8011B808_mgmode] < 0 ? -D_800CBB6E_main[D_8011B808_mgmode] : D_800CBB6E_main[D_8011B808_mgmode]) >= 31 && delay == 0) {
            HuAudFXPlay(1);
            if (D_800CBB6E_main[D_8011B808_mgmode] >= 31) {
                sel++;
                if (table[sel * 4] == -1) {
                    sel = 0;
                }
            } else {
                sel--;
                if (sel < 0) {
                    for (i = 0; table[i * 4] != -1; i++) {
                    }
                    sel = i - 1;
                }
            }
            for (i = 0; i < 4; i++) {
                D_8011B3E6_mgmode[i] = table[sel * 4 + i];
            }
            func_8010A62C_mgmode(160, 134);
            delay = 10;
            continue;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
            HuAudFXPlay(2);
            if (arg0 == 2) {
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8011B3E6_mgmode[i]].group = D_800CB8B1_main[D_8011B3E6_mgmode[i]] = (i != 0);
                }
            } else {
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8011B3E6_mgmode[i]].group = D_800CB8B1_main[D_8011B3E6_mgmode[i]] = (i >= 2);
                }
            }
            break;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            HuAudFXPlay(4);
            ret = 0;
            break;
        }
    }
    return ret;
}

void func_8010A5F0_mgmode(void) {
    func_801168E0_mgmode(D_8011B3EC_mgmode);
    func_80061A5C_main(D_8011B3E4_mgmode, 0);
    func_8005F364_main(D_8011B3E4_mgmode);
}

void func_8010A62C_mgmode(s32 arg0, s16 arg1) {
    s16 i;
    s16 icon;

    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i], arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i] + 10, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1 + 30);
        func_80116968_mgmode(D_8011B3EC_mgmode, i + 4, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        if (GwPlayer[D_8011B3E6_mgmode[i]].stat & 1) {
            icon = i + 14;
            func_801169A0_mgmode(D_8011B3EC_mgmode, icon);
            func_80116968_mgmode(D_8011B3EC_mgmode, icon, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1 + 14);
        } else {
            func_801169C8_mgmode(D_8011B3EC_mgmode, i + 14);
        }
    }
}

#ifdef NON_MATCHING
/* scheduling: retail computes arg0 - 0x54 after loading D_8011B3E0_mgmode */
void func_8010A824_mgmode(s32 arg0, s16 arg1) {
    func_80116968_mgmode(D_8011B3EC_mgmode, 0x12, D_8011B3E0_mgmode[4] + (arg0 - 0x54), arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 8, D_8011B3E0_mgmode[0] + arg0 - 0x70, arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 9, D_8011B3E0_mgmode[3] + arg0 - 0x38, arg1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A824_mgmode);
#endif

#ifdef NON_MATCHING
/* retail re-sign-extends the minigame type at every use and orders the counter loops differently; logic checked against the asm */
void func_8010A8E4_mgmode(s32 arg0) {
    s16 i;
    s16 j;
    s16 k;
    s16 type;

    D_8011B77A_mgmode = 0;
    D_8011B80A_mgmode = 0;
    for (i = 0; i < 8; i++) {
        D_8011AA10_mgmode[i] = 0;
        D_8011A968_mgmode[i] = 0;
        D_8011B928_mgmode[i] = 0;
        D_8011B940_mgmode[i] = 0;
    }
    for (i = 0; i < 71; i++) {
        type = D_800A6D40_main[i].type;
        if (D_800A6D40_main[i].ovl == 0x70 || D_800A6D40_main[i].ovl == -1) {
            continue;
        }
        if (arg0 != 0 && (i == 0x1B || i == 8 || i == 0x10)) {
            continue;
        }
        if (GWMgUnlockCheck(i)) {
            D_8011B928_mgmode[type]++;
            D_8011B80A_mgmode++;
            if (D_800A6D40_main[i].flags >> 15) {
                D_8011A8C8_mgmode[type][D_8011A968_mgmode[type]] = i;
                D_8011A968_mgmode[type]++;
            } else {
                D_8011A970_mgmode[type][D_8011AA10_mgmode[type]] = i;
                D_8011AA10_mgmode[type]++;
            }
            D_8011B6B0_mgmode[type][D_8011B940_mgmode[type]] = i;
        } else {
            if (D_800A6D40_main[i].flags >> 15) {
                D_8011A8C8_mgmode[type][D_8011A968_mgmode[type]] = 0xFF;
                D_8011A968_mgmode[type]++;
            } else {
                D_8011A970_mgmode[type][D_8011AA10_mgmode[type]] = 0xFF;
                D_8011AA10_mgmode[type]++;
            }
            D_8011B6B0_mgmode[type][D_8011B940_mgmode[type]] = 0xFF;
        }
        D_8011B940_mgmode[type]++;
        D_8011B77A_mgmode++;
    }
    for (j = 0, k = 0; j < 7; j++) {
        for (i = 0; i < D_8011A968_mgmode[j]; i++) {
            D_8011B6B0_mgmode[j][k++] = D_8011A8C8_mgmode[j][i];
        }
        for (i = 0; i < D_8011AA10_mgmode[j]; i++) {
            D_8011B6B0_mgmode[j][k++] = D_8011A970_mgmode[j][i];
        }
        k = 0;
    }
    D_8011B940_mgmode[7] = 3;
    D_8011B928_mgmode[7] = 0;
    if (_CheckFlag(0x1E)) {
        D_8011B6B0_mgmode[7][0] = 0x41;
        D_8011B928_mgmode[7]++;
        D_8011B80A_mgmode++;
    } else {
        D_8011B6B0_mgmode[7][0] = 0xFF;
    }
    if (D_8011B928_mgmode[0] >= 20 && D_8011B928_mgmode[1] >= 10 && D_8011B928_mgmode[2] >= 10 &&
        D_8011B928_mgmode[3] >= 8 && D_8011B928_mgmode[4] >= 10 && D_8011B928_mgmode[5] >= 6) {
        D_8011B6B0_mgmode[7][1] = 0x46;
        D_8011B928_mgmode[7]++;
        D_8011B80A_mgmode++;
    } else {
        D_8011B6B0_mgmode[7][1] = 0xFF;
    }
    if (_CheckFlag(0x1F)) {
        D_8011B6B0_mgmode[7][2] = 0x47;
        D_8011B928_mgmode[7]++;
        D_8011B80A_mgmode++;
    } else {
        D_8011B6B0_mgmode[7][2] = 0xFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A8E4_mgmode);
#endif

void func_8010AF78_mgmode(Gfx** gfx, s32 arg1, s32 arg2) {
    if (D_8011B884_mgmode != 0) {
        gDPSetDepthImage((*gfx)++, 0x3D0800);
        gDPSetColorImage((*gfx)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x3D0800);
        gSPDisplayList((*gfx)++, D_80119290_mgmode);
    }
}

void func_8010AFEC_mgmode(void) {
    Vec eye;
    Vec at;
    Vec up;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    while (TRUE) {
        rx = CRot.x;
        ry = CRot.y;
        rz = CRot.z;
        eye.x = sindf(ry) * cosdf(rx) * CZoom + Center.x;
        eye.y = -sindf(rx) * CZoom + Center.y;
        eye.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        ux = sindf(ry) * sindf(rx);
        uy = cosdf(rx);
        uz = cosdf(ry) * sindf(rx);
        dx = at.x - eye.x;
        dy = at.y - eye.y;
        dz = at.z - eye.z;
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        dx /= len;
        dy /= len;
        dz /= len;
        up.x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
             + uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz))
             + uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
        up.y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz))
             + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
             + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
        up.z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz))
             + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
             + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
        Hu3DCamSetPerspective(0, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
        Hu3DCamSetPositionOrientation(0, &eye, &at, &up);
        Hu3DCamUpdateMtx(0);
        Hu3DCamSetPerspective(1, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
        Hu3DCamSetPositionOrientation(1, &eye, &at, &up);
        Hu3DCamUpdateMtx(1);
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
/* float regalloc (rx and speed swap f22/f24); retail also keeps &Center in s0 in the 0x800/0x400 branches */
void func_8010B574_mgmode(void) {
    char buf[256];
    HmfModel* model;
    f32 speed;
    f32 rx;
    f32 ry;
    f32 dx;
    f32 dz;
    f32 inv;

    model = &HmfModelData[D_8011B8C6_mgmode];
    if (D_800D5558_main[1] & 0x10) {
        D_80118EB0_mgmode ^= 1;
        if (D_80118EB0_mgmode != 0) {
            osSyncPrintf("\t{\n\t{%4.1f,%4.1f,%4.1f},\n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf("\t{%4.1f,%4.1f,%4.1f},\n", Center.x, Center.y, Center.z);
            osSyncPrintf("\t%4.1f,%4.1f\n\t},\n", CZoom, D_8011B6A4_mgmode);
            osSyncPrintf("HMF>%4.1f,%4.1f,%4.1f\n", model->rot.x, model->rot.y, model->rot.z);
        }
    }
    if (D_800CDA7C_main[1] & 0x1000) {
        func_80116E24_mgmode(D_8011B958_mgmode);
    }
    if (D_800CDA7C_main[1] & 8) {
        CZoom = (D_800CDA7C_main[1] & 0x2000) ? CZoom + 30.0f : CZoom + 10.0f;
    }
    if ((D_800CDA7C_main[1] & 4) && CZoom - 10.0f != 0.0f) {
        CZoom = (D_800CDA7C_main[1] & 0x2000) ? CZoom - 30.0f : CZoom - 10.0f;
    }
    if (D_800CDA7C_main[1] & 2) {
        D_8011B6A4_mgmode += 1.0f;
    }
    if (D_800CDA7C_main[1] & 1) {
        D_8011B6A4_mgmode -= 1.0f;
    }
    Hu3DCamSetPerspective(0, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
    rx = D_8011B898_mgmode.x;
    ry = D_8011B898_mgmode.y;
    if (D_800CDA7C_main[1] & 0x2000) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    ry += (-D_800CBB6E_main[1] / 30) * speed;
    if (ry >= 360.0f) {
        ry -= 360.0f;
    } else if (ry < 0.0f) {
        ry += 360.0f;
    }
    D_8011B898_mgmode.y = ry;
    rx += (s8)(D_800D20A1_main[1] / 30) * speed;
    if (rx >= 360.0f) {
        rx -= 360.0f;
    } else if (rx < 0.0f) {
        rx += 360.0f;
    }
    D_8011B898_mgmode.x = rx;
    CRot.x = (s16)D_8011B898_mgmode.x;
    CRot.y = (s16)D_8011B898_mgmode.y;
    if (D_800CDA7C_main[1] & 0x2000) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (D_800CDA7C_main[1] & 0x800) {
        dx = sindf(ry) * sindf(rx);
        speed = -speed;
        Center.x += dx * speed;
        Center.y += cosdf(rx) * speed;
        Center.z += cosdf(ry) * sindf(rx) * speed;
    } else if (D_800CDA7C_main[1] & 0x400) {
        dx = sindf(ry) * sindf(rx);
        Center.x += dx * speed;
        Center.y += cosdf(rx) * speed;
        Center.z += cosdf(ry) * sindf(rx) * speed;
    } else if (D_800CDA7C_main[1] & 0x200) {
        dx = gCameraList->pos.z - Center.z;
        dz = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(dx * dx + dz * dz);
        Center.x += dx * inv * speed;
        Center.y += 0.0f;
        Center.z += dz * inv * speed;
    } else if (D_800CDA7C_main[1] & 0x100) {
        dx = -(gCameraList->pos.z - Center.z);
        dz = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(dx * dx + dz * dz);
        Center.x += dx * inv * speed;
        Center.y += 0.0f;
        Center.z += dz * inv * speed;
    }
    if (D_80118EB0_mgmode != 0) {
        sprintf(buf, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, buf);
        sprintf(buf, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, buf);
        sprintf(buf, "CZOOM %4.1f  FOVY %4.1f", CZoom, D_8011B6A4_mgmode);
        print8(32, 200, buf);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010B574_mgmode);
#endif

void func_8010BD28_mgmode(omObjData* obj) {
    if (D_80118EB1_mgmode != 0 || D_800D530C_main != 0) {
        if (!(D_80118EB4_mgmode & 0x80)) {
            WipeCreateOut(0xB, 8);
            HuAudSeqFadeOut(0x3C);
        }
        obj->func = func_8010BD98_mgmode;
    }
}

void func_8010BD98_mgmode(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        if (D_80118EB2_mgmode != 0) {
            func_80118CD8_mgmode();
        }
        func_80116D4C_mgmode();
        D_80118EB4_mgmode &= 0xF;
        _ClearFlag(0x1C);
        if (D_80118EB4_mgmode == 0) {
            omOvlReturnEx(1);
        } else if (D_80118EB4_mgmode == 2) {
            if (D_8011B95A_mgmode == 0x68) {
                _SetFlag(0x1C);
            }
            if (D_8011B95A_mgmode == 0x70) {
                _SetFlag(0x1C);
                omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
            } else {
                omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x84);
            }
        } else {
            omOvlGotoEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
        }
    }
}
