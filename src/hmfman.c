#include "common.h"
#include "game/hmfman.h"
#include "game/camera.h"
#include "game/hmflight.h"
#include "macros.h"
#include "mallocblock.h"
#include "include_asm.h"

s32 func_80023264_main(HmfData *);
extern s32 D_800A0530_main;
extern s32 D_800C9940_main;

// graphics.c
u8 func_8000EF64_main(void *arg0, u16 arg1, s32 arg2, void *arg3, s32 arg4);

// hmfload.c
void func_8000F978_main(HmfData *);

// 20A20.c
void func_80021AF4_main(void);

// 22EB0.c
void func_800222B0_main(void *arg0, void *arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5);
void func_800224BC_main(void);
void func_80022660_main(HmfData *);
s16 func_8002C834_main(void *, char *);
void func_8002D260_main(void);
s32 func_8002D3AC_main(void *);
void func_8002D514_main(void);
void func_80030030_main(f32);

// 30C40.c
void func_80030198_main(void);
s32 func_800300A4_main(void *, void *);

// 32160.c
void func_80033450_main(void);
void func_80033510_main(void);

// 8AC70.c
void func_8008A070_main(void *);

// unknown
void func_8000D3AC_main(void);

extern Gfx *gMainGfxPos;

void Hmfload(HmfData *, void *, s32);
void *func_80010AC8_main(void *);
void func_8001EF60_main(void);
s32 func_8001FF04_main(s32);
s32 func_8002D2D8_main(void *, HmfData *);

extern u8 D_800A0540_main;
extern u8 D_800A0541_main;
extern u8 D_800A0542_main;
extern Gfx D_800A09B0_main[];
extern Gfx D_800A0A08_main[];
extern Gfx D_800A0A38_main[];
extern s16 D_800A0A78_main;
extern s16 D_800C9932_main;
extern s32 D_800C9940_main;
extern u16 D_800CBB72_main[];
extern s8 D_800CC0A8_main;
extern void* D_800CC3D8_main[];
extern u16 D_800CD2F6_main;
extern s16 D_800CDD6A_main;
extern u8 D_800CE19A_main;
extern s8 D_800CE1C6_main;
extern u8 D_800CD280_main;
extern s32 D_800D0444_main;
extern u16 D_800D05A0_main[][128];
extern s32 D_800D10F4_main;
extern s32 D_800D1F70_main;
extern s32 D_800D1FE8_main;
extern s8 D_800D2008_main; /* current frame buffer (read as u8 too) */
extern u8 D_800D1FF0_main; /* frame buffer count */
extern s8 HmfPauseF;
extern s16 D_800D20EE_main;
extern u16 D_800D5204_main;

/* ---- wave 2a: MP3 layouts of the model structures, for the functions brought from MP2
   src/274D0.c and MP1 src/24740.c. MP2 include/game/hmfman.h names the fields; MP3's HmfData
   keeps three vertex buffers (MP2 four), so MP2's fields 0x54-0xC0 sit 4 bytes earlier here,
   and MP3 has one more word at 0xC0 (src/hmfload.c's HmfLoadData has the same layout). ---- */

typedef struct HmfVtxM {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8 unk0C[3];
    /* 0x0F */ u8 unk0F;
} HmfVtxM; /* size 0x10 */

typedef struct HmfMotionObjM {
    /* 0x00 */ s16 unk00; /* child count */
    /* 0x02 */ char unk02[0x4E];
    /* 0x50 */ s16* unk50; /* children: part index, or 0x8000 | motion object index */
    /* 0x54 */ char unk54[0x44];
} HmfMotionObjM; /* size 0x98 */

typedef struct HitXformM {
    /* 0x00 */ s16 unk00; /* part index, < 0 for none */
    /* 0x02 */ char unk02[0x8A];
} HitXformM; /* size 0x8C */

typedef struct HmfFaceM {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ s16 unk04[4]; /* vertices (MP2 0x02) */
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} HmfFaceM; /* size 0x18 */

typedef struct HmfTexM {
    /* 0x00 */ char unk00[0x22]; /* name */
    /* 0x22 */ u16 unk22;        /* name hash (MP2 0x24) */
    /* 0x24 */ char unk24[0x10];
} HmfTexM; /* size 0x34 */

typedef struct HmfTexRefM {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ HmfTexM* unk0C;
} HmfTexRefM; /* size 0x10 */

/* A part's face (HmfPartM.unk54) */
typedef struct HmfFaceRecM {
    /* 0x00 */ u8 unk00; /* vertex count | 0x80 unlit */
    /* 0x01 */ s8 unk01[3]; /* normal */
    /* 0x04 */ s16 unk04[4]; /* vertices */
    /* 0x0C */ f32 unk0C[4]; /* s */
    /* 0x1C */ f32 unk1C[4]; /* t */
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
} HmfFaceRecM; /* size 0x34 */

typedef struct HmfMatM {
    /* 0x00 */ u8 unk00[9];
    /* 0x09 */ u8 unk09; /* flags (MP2 0x0C) */
    /* 0x0A */ u8 unk0A; /* MP2 0x0D */
} HmfMatM; /* size 0xB (MP2 0xE) */

typedef struct HmfDataM {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B; /* link count */
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ char unk0D;
    /* 0x0E */ s16 unk0E; /* heap tag */
    /* 0x10 */ s16 unk10; /* part count */
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18; /* vertex count */
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ char unk20[2];
    /* 0x22 */ s16 unk22;
    /* 0x24 */ char unk24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A; /* texture animation count (unkC8) */
    /* 0x2C */ u8* unk2C;
    /* 0x30 */ u8* unk30;
    /* 0x34 */ u8* unk34;
    /* 0x38 */ void* unk38;
    /* 0x3C */ HmfModelData_Unk64_Unk3C_Struct* unk3C;
    /* 0x40 */ HmfVtxM* unk40;
    /* 0x44 */ HmfVtxM* unk44[3]; /* per frame buffer */
    /* 0x50 */ void* unk50;  /* MP2 0x54 */
    /* 0x54 */ u8* unk54;    /* MP2 0x58 */
    /* 0x58 */ void* unk58;  /* MP2 0x5C */
    /* 0x5C */ s16* unk5C;   /* MP2 0x60 */
    /* 0x60 */ struct HmfPartM* unk60; /* MP2 0x64 */
    /* 0x64 */ s16 unk64;    /* MP2 0x68 */
    /* 0x66 */ char unk66[2];
    /* 0x68 */ HitXformM* unk68; /* MP2 0x6C */
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ HmfMotionObjM* unk80; /* MP2 0x84: motion objects, -1 for none */
    /* 0x84 */ HmfTexRefM* unk84; /* MP2 0x88: texture refs */
    /* 0x88 */ struct HmfMatM* unk88; /* MP2 0x8C: materials */
    /* 0x8C */ void* unk8C;  /* MP2 0x90 */
    /* 0x90 */ void* unk90;  /* MP2 0x94 */
    /* 0x94 */ void* unk94;  /* MP2 0x98 */
    /* 0x98 */ void* unk98;  /* MP2 0x9C: HmfAnim */
    /* 0x9C */ void* unk9C;  /* MP2 0xA0 */
    /* 0xA0 */ f32 unkA0;    /* MP2 0xA4 */
    /* 0xA4 */ f32 unkA4;    /* MP2 0xA8 */
    /* 0xA8 */ f32 unkA8;    /* MP2 0xAC */
    /* 0xAC */ f32 unkAC;    /* MP2 0xB0 */
    /* 0xB0 */ HmfFaceM* unkB0; /* MP2 0xB4 */
    /* 0xB4 */ void* unkB4;  /* MP2 0xB8 */
    /* 0xB8 */ void* unkB8;  /* MP2 0xBC */
    /* 0xBC */ void* unkBC;  /* MP2 0xC0 */
    /* 0xC0 */ void* unkC0;
    /* 0xC4 */ void* unkC4;
    /* 0xC8 */ u8* unkC8;
    /* 0xCC */ void* unkCC;
    /* 0xD0 */ HmfData_UnkD0* unkD0;
    /* 0xD4 */ void (*unkD4)(f32 (*)[4], f32, f32, f32);
    /* 0xD8 */ void (*unkD8)(f32 (*)[4], f32, f32, f32);
} HmfDataM; /* size 0xDC */

typedef struct HmfPartM {
    /* 0x00 */ char unk00[0x1C]; /* name (MP2 0x12) */
    /* 0x1C */ u8 unk1C;           /* reflection texture (MP2 0x2E) */
    /* 0x1D */ char unk1D[3];
    /* 0x20 */ s16 unk20;          /* alpha (MP2 0x02) */
    /* 0x22 */ s16 unk22;          /* face count (MP2 0x04) */
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;          /* first vertex (MP2 0x0A) */
    /* 0x2A */ s16 unk2A;          /* vertex count (MP2 0x0C) */
    /* 0x2C */ u16 unk2C;          /* first face (MP2 0x0E) */
    /* 0x2E */ u16 unk2E;          /* face count (MP2 0x10) */
    /* 0x30 */ char unk30[0x12];
    /* 0x42 */ s16 unk42;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[2];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ HmfFaceRecM* unk54;
    /* 0x58 */ HmfDataM* unk58;
    /* 0x5C */ void* unk5C;
    /* 0x60 */ void* unk60;
    /* 0x64 */ Gfx* unk64;
} HmfPartM; /* size 0x68 */

typedef struct HmfModelM {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ s8 unk07;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ char unk12[2];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ Vec pos;
    /* 0x28 */ Vec rot;
    /* 0x34 */ Vec scale;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ HmfDataM* hmf;
    /* 0x68 */ HmfDataM* unk68;
    /* 0x6C */ HmfDataM* unk6C;
    /* 0x70 */ void (*unk70)(Gfx**, s32, s32);
    /* 0x74 */ f32 mtx[4][4];
    /* 0xB4 */ HmfData_UnkD0* unkB4;
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ void* unkBC;
} HmfModelM; /* size 0xC0: MP3's HmfModel */

void func_8001CF1C_main(HmfDataM* arg0, HmfDataM* arg1, f32 arg2, s16 arg3, s16 arg4, s32 arg5);

void func_8001D874_main(HmfDataM* arg0, f32 arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8001DACC_main(HmfDataM* arg0, f32 arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8001DDB8_main(HmfDataM* arg0, f32 arg1, f32 arg2, u16 arg3, u16 arg4);

s16 func_80011460_main(u8 *);
int strcmp(const char *, const char *);
extern HmfTexM* D_800D1FCC_main; /* loaded textures (128) */

extern s16 D_800D6B64_main;
extern s16 D_800CC0B6_main;
extern u8 D_800D0599_main;
extern u8 D_800D41C4_main;
extern u8 D_800CDA84_main;
extern HmfDataM D_800CB8C0_main; /* the scratch model for motion-only files */
#define CAM (*(HuCamera**)&D_800D10F4_main)

f32 func_8002FC7C_main(D_800CCF58_main_Struct*, s16, f32, f32, f32);
void func_80032FC0_main(s16, u8, u8);
void func_80034048_main(s16, s16);
/* retail calls it with the model only (as MP1/MP2 do), though its definition takes a name too:
   a host build must pass NULL for it */
void* func_80031A44_main();
void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);

void func_80017D24_main(f32 (*)[4], f32, f32, f32);
void func_80088910_main(f32 (*)[4], f32, f32, f32);

/* HmfModelData seen through the full layout */
#define MDL ((HmfModelM*)HmfModelData)

const char D_800A6BB8_main[] = "%x\n";
const char D_800A6BBC_main[] = "Model Entry Over!\n";

void func_8001A070_main(void *arg0, void *arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5) {
    s16 modelId;

    func_800222B0_main(arg0, arg1, arg2, arg3, arg4, arg5);
    func_8002D260_main();
    HmfModelData = HuMemAlloc(HU3D_MODEL_MAX * sizeof(HmfModel));
    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        HmfModelData[modelId].hmf = NULL;
    }
    func_800224BC_main();
    D_800D20AC_main = 0;
    D_800D1F70_main = 0;
    D_800D20EE_main = 1;
    HmfPauseF = 0;
    D_800CD280_main = 1;
    D_800CC3D8_main[0] = D_800CC3D8_main[1] = 0;
    func_8000D3AC_main();
    D_800D1FE8_main = 0;
}

s16 Hu3DModelCreate(u8 *data, u32 arg1) {
    HmfModel *modelP;
    HmfData *hmf;
    void *var_a1;
    s16 modelId;
    s16 var_a0;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (HmfModelData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(D_800A6BBC_main);
        return -1;
    }
    D_800D5204_main = 10000 + modelId * 2;
    D_800CDD6A_main = 10001 + modelId * 2;
    modelP = &HmfModelData[modelId];
    modelP->unk08 = 0xFF;
    hmf = modelP->hmf = HuMemAlloc(sizeof(HmfData));
    hmf->unk0E = D_800D5204_main;
    if (data[0] == 'M' && data[1] == 'T') {
        hmf->unk14 = 0;
        hmf->unk84 = 0;
        hmf->unk38 = 0;
        hmf->unkC8 = 0;
        hmf->unk98 = NULL;
        if (data[2] == 'N' && data[3] == 'X') {
            modelP->unk02 = func_8002D3AC_main(data);
            arg1 &= ~(0x10 | 0x1);
        } else {
            var_a1 = data + 8;
            if (data[8] == 'M') {
                if (data[9] == 'T' && data[10] == 'N' && data[11] == 'X') {
                    modelP->unk02 = func_8002D3AC_main(var_a1);
                    arg1 &= ~0x11;
                    var_a1 = func_80010AC8_main(data + 12);
                } else {
                    modelP->unk02 = 0xFF;
                }
            } else {
                modelP->unk02 = 0xFF;
            }
            modelP->unk08 = func_800300A4_main(data, var_a1);
        }
    } else {
        Hmfload(hmf, data, arg1);
        if (hmf->unk38 != 0) {
            HuMemSetTag(hmf->unk50, D_800CDD6A_main);
            modelP->unk10 = func_8001FF04_main(modelId);
        } else {
            modelP->unk10 = -1;
        }
        hmf->unk00 = (arg1 >> 10) & 7;
        modelP->unk18 = arg1;
        modelP->unk02 = func_8002D2D8_main(data, hmf);
        if (modelP->unk02 != 0xFF) {
            if (hmf->unk14 == 0) {
                func_8000F978_main(hmf);
            } else {
                goto skip;
            }
        }
    }
    if (hmf->unk14 == 0) {
        arg1 |= 4;
    }
skip:
    modelP->unk18 = arg1;
    if (arg1 & 8) {
        gFreeFunc(data);
    }
    if (arg1 & 1) {
        D_800C9940_main = modelP->unk18;
        func_80022660_main(hmf);
    }
    hmf->unk0B = 1;
    if (arg1 & 0x10) {
        for (var_a0 = 0; var_a0 < hmf->unk10; var_a0++) {
            if (hmf->unk60[var_a0].unk50 & 0x06000000) {
                break;
            }
        }
        if (var_a0 == hmf->unk10) {
            HuMemFreeAllWithTag(D_800D5204_main);
        }
    }
    modelP->unk40 =
        modelP->unk03 =
            modelP->unk48 =
                modelP->unk4C =
                    modelP->unk05 =
                        modelP->unk54 =
                            modelP->unk58 =
                                modelP->unk07 =
                                    modelP->unk60 = 0;
    modelP->unk5C = 1.0f;
    modelP->unk50 = 1.0f;
    modelP->unk44 = 1.0f;
    modelP->unk06 = -1;
    modelP->unk04 = -1;
    modelP->unk09 = -1;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    modelP->unk01 = -1;
    modelP->unk00 = 0;
    modelP->unkB4 = 0;
    func_8008A070_main(modelP->mtx);
    D_800D1FE8_main++;
    return modelId;
}

s32 Hu3DModelLink(s16 linkMdlId) {
    HmfModel *modelP;
    s16 modelId;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (HmfModelData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(D_800A6BBC_main);
        return -1;
    }
    modelP = &HmfModelData[modelId];
    modelP->hmf = HmfModelData[linkMdlId].hmf;
    modelP->unk18 = HmfModelData[linkMdlId].unk18;
    modelP->unk00 = HmfModelData[linkMdlId].unk00;
    modelP->unk10 = HmfModelData[linkMdlId].unk10;
    modelP->unk02 = HmfModelData[linkMdlId].unk02;
    modelP->hmf->unk0B++;
    modelP->unk40 =
        modelP->unk03 =
            modelP->unk48 =
                modelP->unk4C =
                    modelP->unk05 =
                        modelP->unk54 =
                            modelP->unk58 =
                                modelP->unk07 =
                                    modelP->unk60 = 0;
    modelP->unk5C = 1.0f;
    modelP->unk50 = 1.0f;
    modelP->unk44 = 1.0f;
    modelP->unk06 = -1;
    modelP->unk04 = -1;
    modelP->unk09 = -1;
    modelP->unk08 = -1;
    modelP->unkB4 = 0;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    modelP->unk01 = -1;
    func_8008A070_main(modelP->mtx);
    D_800D1FE8_main++;
    return modelId;
}

/* MP2 func_80027FA4_28BA4: a model drawn from a display list (arg1) or a callback */
s32 func_8001A894_main(s32 arg0, void* arg1, s32 arg2) {
    HmfDataM* hmf;
    HmfModelM* modelP;
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (MDL[i].hmf == NULL) {
            break;
        }
    }
    if (i == HU3D_MODEL_MAX) {
        osSyncPrintf(D_800A6BBC_main);
        return -1;
    }
    D_800D5204_main = i * 2 + 10000;
    D_800CDD6A_main = i * 2 + 10001;
    modelP = &MDL[i];
    hmf = modelP->hmf = HuMemAllocTag(sizeof(HmfDataM), D_800CDD6A_main);
    hmf->unk0E = D_800D5204_main;
    hmf->unk3C = arg1;
    hmf->unk0B = 1;
    hmf->unk00 = ((u32)arg0 >> 10) & 7;
    modelP->unk70 = NULL;
    modelP->hmf->unk98 = NULL;
    modelP->unk08 = 0xFF;
    modelP->unk18 = arg0 | 1;
    modelP->unk40 =
        modelP->unk03 =
            modelP->unk48 =
                modelP->unk4C =
                    modelP->unk05 =
                        modelP->unk54 = 0;
    modelP->unk44 = modelP->unk50 = 1.0f;
    modelP->unk04 = 0xFF;
    modelP->unk02 = 0xFF;
    modelP->unk09 = 0xFF;
    modelP->unkB4 = NULL;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;

    switch (arg2 & 6) {
        case 4:
            func_8008A070_main(modelP->mtx);
            hmf->unk3C = HuMemAllocTag(sizeof(void*), D_800CDD6A_main);
            hmf->unk3C->unk00[0] = arg1;
            hmf->unk60 = HuMemAllocTag(sizeof(HmfPartM), D_800CDD6A_main);
            hmf->unk10 = 1;
            hmf->unk14 = 1;
            hmf->unk38 = NULL;
            hmf->unkC8 = NULL;
            hmf->unk60->unk50 = 0;
            hmf->unk60->unk20 = -1;
            hmf->unk60->unk5C = (void*)-1;
            hmf->unk60->unk60 = NULL;
            hmf->unkB4 = NULL;
            hmf->unk0A = 0;
            hmf->unkD4 = func_80017D24_main;
            hmf->unkD8 = func_80088910_main;
            hmf->unk60->unk42 = hmf->unk60->unk44 = hmf->unk60->unk46 = -0x8000;
            hmf->unk60->unk48 = hmf->unk60->unk4A = hmf->unk60->unk4C = -0x8000;
        case 0:
        case 2:
            modelP->unk01 = 0xFF;
            break;
        case 6:
            modelP->unk01 = 0;
            break;
    }
    modelP->unk00 = arg2 | 1;
    D_800D1FE8_main++;
    return i;
}

s16 func_8001ABD4_main(s16 arg0, s8 arg1) {
    s16 idx = Hu3DModelLink(arg0);

    if (idx < 0) {
        return -1;
    }
    HmfModelData[idx].unk00 = arg1;
    return idx;
}

void func_8001AC34_main(s16 arg0, s32 arg1) {
    HmfModelM* modelP = &MDL[arg0];

    modelP->unk00 &= ~6;
    modelP->unk00 |= 1;
    modelP->unk00 = arg1 | modelP->unk00;
    if ((u8)arg1 == 6) {
        modelP->unk01 = 0;
    } else {
        modelP->unk01 = 0xFF;
    }
}

s16 func_8001AC8C_main(s32 arg0, void (*arg1)(Gfx **, s32, s32), u8 arg2) {
    s16 idx = func_8001A894_main(arg0, NULL, arg2);
    HmfModel *var_v1 = &HmfModelData[idx];

    var_v1->unk70 = arg1;
    return idx;
}

INCLUDE_ASM("asm/nonmatchings/hmfman", func_8001ACDC_main);

void func_8001AFE4_main(void) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (HmfModelData[i].hmf != NULL) {
            func_8001ACDC_main(i);
        }
    }
    func_80033510_main();
    func_80033450_main();
    func_80030198_main();
    func_80021AF4_main();
    func_8002D514_main();
    func_8001EF60_main();
    D_800CC3D8_main[0] = D_800CC3D8_main[1] = 0;
    func_80030030_main(1.0f);
    func_80019968_main(1);
    func_8000D3AC_main();
}

INCLUDE_ASM("asm/nonmatchings/hmfman", func_8001B0B4_main);

Gfx *func_8001BD24_main(Gfx *arg0, s16 arg1, u16 arg2) {
    s16 i;

    for (i = 0; i < D_800CBB72_main[arg1]; i++) {
        HmfModel *temp_s0 = &HmfModelData[D_800D05A0_main[arg1][i]];

        if (!(temp_s0->unk01 & arg2) && arg2 != 0) {
            continue;
        }
        D_800CD2F6_main = D_800D05A0_main[arg1][i];
        if (temp_s0->hmf->unk00 != D_800CE19A_main) {
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            func_8000EF64_main(arg0, D_800CE19A_main, 0, NULL, 0);
            D_800CE19A_main = temp_s0->hmf->unk00;
            arg0 = gMainGfxPos;
        }
        if (temp_s0->unk70 != NULL) {
            temp_s0->unk70(&gMainGfxPos, D_800D0444_main, D_800D10F4_main);
        } else if (temp_s0->hmf->unk3C != NULL) {
            gSPDisplayList(gMainGfxPos++, temp_s0->hmf->unk3C);
        }
    }
    return arg0;
}

void func_8001BF14_main(void) {
    s16 i;

    HuMemSetDirty();
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        HmfModelData[i].hmf = NULL;
    }
    gCameraList = NULL;
    D_800C9932_main = 0;
    D_800D2008_main = 0;
    D_800D20EE_main = 0;
}

void func_8001BF90_main(u32 arg0, u32 arg1) {
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);
    gSPDisplayList(gMainGfxPos++, D_800A09B0_main);
    gDPSetDepthImage(gMainGfxPos++, arg1);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, arg1);
    gSPDisplayList(gMainGfxPos++, D_800A0A08_main);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, arg0);
    if (D_800CD280_main != 0) {
        gDPSetFillColor(gMainGfxPos++, PACK_FILL_COLOR(D_800A0540_main, D_800A0541_main, D_800A0542_main, 1));
        gSPDisplayList(gMainGfxPos++, D_800A0A38_main);
    }
}

void Hu3DModelPosSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].pos.x = x;
        HmfModelData[idx].pos.y = y;
        HmfModelData[idx].pos.z = z;
    }
}

void Hu3DModelPosGet(s16 idx, Vec *arg1) {
    arg1->x = HmfModelData[idx].pos.x;
    arg1->y = HmfModelData[idx].pos.y;
    arg1->z = HmfModelData[idx].pos.z;
}

void Hu3DModelRotSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].rot.x = x;
        HmfModelData[idx].rot.y = y;
        HmfModelData[idx].rot.z = z;
    }
}

void Hu3DModelScaleSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].scale.x = x;
        HmfModelData[idx].scale.y = y;
        HmfModelData[idx].scale.z = z;
    }
}

void func_8001C1F0_main(s16 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        func_8001C258_main(i, arg0, arg1);
    }
}

void func_8001C258_main(s16 idx, s32 arg1, s32 arg2) {
    HmfModel *model = &HmfModelData[idx];

    if (model->hmf != NULL) {
        if (arg1 & 0xB3F82) {
            arg2 |= 0x800000;
        }
        if (arg1 & 0x1C00) {
            func_8001C8E4_main(idx, arg2 & 0x1C00);
        }
        model->unk18 &= ~arg1;
        model->unk18 |= arg2;
    }
}

void func_8001C2FC_main(s16 idx, s32 arg1, s32 arg2) {
    HmfData *temp_a3 = HmfModelData[idx].hmf;
    s16 var_t0;

    for (var_t0 = 0; var_t0 < temp_a3->unk10; var_t0++) {
        temp_a3->unk60[var_t0].unk50 &= ~arg1;
        temp_a3->unk60[var_t0].unk50 |= arg2;
    }
}

void func_8001C39C_main(s16 idx, s32 arg1, s32 arg2, s32 arg3) {
    HmfData *temp_s0 = HmfModelData[idx].hmf;
    s16 temp_v0 = func_8002C834_main(temp_s0, (char *)arg1);

    if (temp_v0 >= 0) {
        temp_s0->unk60[temp_v0].unk50 &= ~arg2;
        temp_s0->unk60[temp_v0].unk50 |= arg3;
    }
}

void func_8001C448_main(s16 arg0) {
    func_8001C258_main(arg0, 0x00800001, 1);
    D_800C9940_main = HmfModelData[arg0].unk18;

    if (D_800C9940_main & 0x10) {
        osSyncPrintf("RemakeStatic Error! Executed DynamicFree already!\n");
        D_800A0530_main = 0x10002;
        return;
    }

    if (func_80023264_main(HmfModelData[arg0].hmf) != NULL) {
        func_8001C954_main(arg0);
    }
}

/* hmfman.h declares an s32 result; retail returns nothing */
s32 func_8001C514_main(s16 arg0) {
    HmfDataM* model = MDL[arg0].hmf;

    if (model->unk0A != 0) {
        func_80019C68_main(model->unk0E);
    } else {
        HuMemFreeAllWithTag(MDL[arg0].hmf->unk0E);
    }
    func_8001C258_main(arg0, 0x10, 0x10);
}

void func_8001C5B4_main(s16 arg0, s16 arg1) {
    HmfModelM* modelP = &MDL[arg0];

    modelP->unk02 = MDL[arg1].unk02;
    modelP->unk48 = modelP->unk40 = modelP->unk03 = 0;
    modelP->unk44 = 1.0f;
    modelP->unk04 = 0xFF;
}

void func_8001C624_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HmfModel *temp_a0;

    temp_a0 = &HmfModelData[arg0];
    if (temp_a0->unk04 != 0xFF) {
        temp_a0->unk02 = temp_a0->unk04;
        temp_a0->unk40 = temp_a0->unk4C;
        temp_a0->unk03 = temp_a0->unk05;
        temp_a0->unk48 = temp_a0->unk54;
    }
    temp_a0->unk04 = (u8)arg1;
    temp_a0->unk4C = arg2;
    temp_a0->unk0E = (u16)0;
    temp_a0->unk0C = arg3;
    temp_a0->unk05 = (u8)arg4;
    temp_a0->unk54 = 0.0f;
}

/* MP1 func_80025CA8 (src/24740.c) */
void func_8001C6A8_main(s32 arg0, f32 arg1) {
    HmfModelM* modelP = &MDL[(s16)arg0];
    f32 len = D_800CCF58_main[modelP->unk02].unk02;

    if (len < arg1) {
        modelP->unk40 = len;
    } else {
        modelP->unk40 = arg1;
    }
}

/* MP1 func_80025D90 (src/24740.c; its decomp-permuter shape) */
f32 func_8001C718_main(s16 arg0) {
    f32 new_var;
    f32 x = MDL[arg0].unk58;
    f32 r;

    if (!(x < 0.0f)) {
        new_var = x;
        r = new_var;
    } else {
        r = 0.0f;
    }
    return r;
}

/* MP1 func_80025DD8 (src/24740.c) */
f32 func_8001C760_main(s16 arg0) {
    if (MDL[arg0].unk58 < 0.0f) {
        return 0.0f;
    }
    return D_800CCF58_main[MDL[arg0].unk06].unk02;
}

f32 func_8001C7D0_main(s16 idx) {
    if (HmfModelData[idx].unk04 == 0xFF) {
        return -1.0f;
    }
    return HmfModelData[idx].unk4C;
}

void func_8001C814_main(s16 idx, s16 arg1, s16 arg2) {
    HmfModel *temp_a3 = &HmfModelData[idx];

    temp_a3->unk03 &= ~arg1;
    temp_a3->unk03 |= arg2;
    if (temp_a3->hmf->unk98 != NULL) {
        temp_a3->hmf->unk98->unk02 &= ~arg1;
        temp_a3->hmf->unk98->unk02 |= arg2;
    }
    if (temp_a3->unk04 != 0xFF) {
        temp_a3->unk05 &= ~arg1;
        temp_a3->unk05 |= arg2;
    }
}

void func_8001C8A8_main(s16 idx, s16 arg1) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].unk01 = arg1;
    }
}

void func_8001C8E4_main(s16 idx, u32 arg1) {
    HmfModelData[idx].unk18 &= ~0x1C00;
    HmfModelData[idx].unk18 |= arg1;
    HmfModelData[idx].hmf->unk00 = (arg1 >> 10) & 7;
}

void func_8001C92C_main(s16 arg0, f32 arg1) {
    HmfModelM* modelP = &MDL[arg0];

    modelP->unk44 = arg1;
}

// officially named "DynamicFree"
/* MP1 func_80026040 (src/24740.c); copies only frame buffers still shared with unk40 */
s32 func_8001C954_main(s16 arg0) {
    HmfDataM* hmf = MDL[arg0].hmf;
    HmfVtxM* dst;
    HmfVtxM* src;
    s16 n;
    s16 j;
    s16 i;

    for (i = 0; i < D_800D1FF0_main; i++) {
        src = hmf->unk40;
        if (hmf->unk44[i] == src) {
            n = hmf->unk18;
            dst = hmf->unk44[i] = HuMemAllocTag(n * sizeof(HmfVtxM), hmf->unk0E + 1);
            for (j = 0; j < n; j++) {
                *dst++ = *src++;
            }
        }
    }
}

/* MP1 func_80026174 (src/24740.c): blend two models' vertices */
void func_8001CAA4_main(s16 arg0, s16 arg1, f32 arg2) {
    HmfDataM* model = MDL[arg0].hmf;
    HmfVtxM* var_a3 = model->unk40;
    HmfVtxM* var_a2 = MDL[arg1].hmf->unk40;
    HmfVtxM* var_t0 = model->unk44[(u8)D_800D2008_main];
    s16 n = model->unk18;
    s16 i;

    for (i = 0; i < n; i++) {
        *var_t0 = *var_a3;
        if (var_a3->unk00 != var_a2->unk00 || var_a3->unk02 != var_a2->unk02 || var_a3->unk04 != var_a2->unk04) {
            var_t0->unk00 = var_a3->unk00 * arg2 + var_a2->unk00 * (1.0f - arg2);
            var_t0->unk02 = var_a3->unk02 * arg2 + var_a2->unk02 * (1.0f - arg2);
            var_t0->unk04 = var_a3->unk04 * arg2 + var_a2->unk04 * (1.0f - arg2);
            var_t0->unk0C[0] = (s32) ((s8) var_a3->unk0C[0] * arg2 + (s8) var_a2->unk0C[0] * (1.0f - arg2));
            var_t0->unk0C[1] = (s32) ((s8) var_a3->unk0C[1] * arg2 + (s8) var_a2->unk0C[1] * (1.0f - arg2));
            var_t0->unk0C[2] = (s32) ((s8) var_a3->unk0C[2] * arg2 + (s8) var_a2->unk0C[2] * (1.0f - arg2));
        }
        var_a3++;
        var_a2++;
        var_t0++;
    }
}

/* MP1 func_80026404 (src/24740.c) */
void func_8001CD34_main(s16 arg0, s16 arg1, f32 arg2, char* arg3, s32 arg4) {
    s16 temp_s0;
    s16 temp_v0;
    HmfDataM* temp_s2;
    HmfDataM* temp_s3;

    temp_s3 = MDL[arg0].hmf;
    temp_s2 = MDL[arg1].hmf;
    temp_s0 = func_8002C834_main(temp_s3, arg3);
    temp_v0 = func_8002C834_main(temp_s2, arg3);

    if (temp_s0 == -1 || temp_v0 == -1) {
        return;
    }

    func_8001CF1C_main(temp_s3, temp_s2, arg2, temp_s0, temp_v0, arg4);
}

/* MP1 func_800264F8 (src/24740.c) */
void func_8001CE28_main(s16 arg0, s16 arg1, f32 arg2, char* arg3, char* arg4, s32 arg5) {
    s16 temp_s0;
    s16 temp_v0;
    HmfDataM* temp_s2;
    HmfDataM* temp_s3;

    temp_s3 = MDL[arg0].hmf;
    temp_s2 = MDL[arg1].hmf;
    temp_s0 = func_8002C834_main(temp_s3, arg3);
    temp_v0 = func_8002C834_main(temp_s2, arg4);

    if (temp_s0 == -1 || temp_v0 == -1) {
        return;
    }

    func_8001CF1C_main(temp_s3, temp_s2, arg2, temp_s0, temp_v0, arg5);
}

/* MP1 func_800265EC (src/24740.c): blend one part's vertices */
void func_8001CF1C_main(HmfDataM* arg0, HmfDataM* arg1, f32 arg2, s16 arg3, s16 arg4, s32 arg5) {
    HmfVtxM* var_a2;
    HmfVtxM* var_a3;
    HmfVtxM* var_t0;
    s16 temp_v1;
    s16 temp_t3;
    s16 var_t4;
    s16 i;

    var_t4 = 0;

    if (arg5 != 0) {
        var_t0 = arg0->unk40;
        var_a2 = arg0->unk44[(u8)D_800D2008_main];
        var_t4 = arg0->unk60[arg3].unk28;

        for (i = 0; i < var_t4; i++) {
            *var_a2 = *var_t0;
            var_t0++;
            var_a2++;
        }
    }

    var_t0 = &arg0->unk40[arg0->unk60[arg3].unk28];
    var_a3 = &arg1->unk40[arg1->unk60[arg4].unk28];
    var_a2 = &arg0->unk44[(u8)D_800D2008_main][arg0->unk60[arg3].unk28];

    temp_t3 = arg0->unk60[arg3].unk2A;
    for (i = 0; i < temp_t3; i++) {
        *var_a2 = *var_t0;
        if (var_t0->unk00 != var_a3->unk00 || var_t0->unk02 != var_a3->unk02 || var_t0->unk04 != var_a3->unk04) {
            var_a2->unk00 = var_t0->unk00 * arg2 + var_a3->unk00 * (1.0f - arg2);
            var_a2->unk02 = var_t0->unk02 * arg2 + var_a3->unk02 * (1.0f - arg2);
            var_a2->unk04 = var_t0->unk04 * arg2 + var_a3->unk04 * (1.0f - arg2);
            var_a2->unk0C[0] = (s32) ((s8) var_t0->unk0C[0] * arg2 + (s8) var_a3->unk0C[0] * (1.0f - arg2));
            var_a2->unk0C[1] = (s32) ((s8) var_t0->unk0C[1] * arg2 + (s8) var_a3->unk0C[1] * (1.0f - arg2));
            var_a2->unk0C[2] = (s32) ((s8) var_t0->unk0C[2] * arg2 + (s8) var_a3->unk0C[2] * (1.0f - arg2));
        }
        var_t0++;
        var_a3++;
        var_a2++;
    }

    if (arg5 != 0) {
        temp_v1 = var_t4 + temp_t3;
        temp_t3 = arg0->unk18;
        for (i = temp_v1; i < temp_t3; i++) {
            *var_a2 = *var_t0;
            var_t0++;
            var_a2++;
        }
    }
}

void func_8001D330_main(s16 arg0) {
    D_800A0A78_main = arg0;
}

/* MP1 func_80026A0C (src/24740.c; its decomp-permuter shape): the motion group holding a part;
   falls back to the hit transforms (unk68) when the model has no groups */
void* func_8001D33C_main(s16 arg0, char* arg1) {
    HmfDataM* model = MDL[arg0].hmf;
    s16 new_var;
    s16 idx = func_8002C834_main(model, arg1);
    s16 n;
    s16 j;
    s16 i;

    if (model->unk80 != (void*)-1) {
        for (i = 0; i < model->unk16; i++) {
            n = model->unk80[i].unk00;
            for (j = 0; j < n; j++) {
                if (model->unk80[i].unk50[j] == idx) {
                    break;
                }
            }
            new_var = j;
            if (new_var != n) {
                break;
            }
        }
        if (i == model->unk16) {
            return (void*)-1;
        }
        return &model->unk80[i];
    }
    for (i = 0; i < model->unk64; i++) {
        if (model->unk68[i].unk00 == idx) {
            break;
        }
    }
    if (i == model->unk64) {
        return (void*)-1;
    }
    return &model->unk68[i];
}

/* MP1 func_80026B8C (src/24740.c) */
void func_8001D558_main(s16 arg0, f32 arg1, f32 arg2, s32 arg3) {
    HmfDataM* model = MDL[arg0].hmf;

    if (model != NULL) {
        switch (arg3 & 0xF) {
            case 0:
                func_8001D874_main(model, arg1, arg2, 0, model->unk1A);
                break;
            case 1:
                func_8001DACC_main(model, arg1, arg2, 0, model->unk1A);
                break;
            case 2:
                func_8001DDB8_main(model, arg1, arg2, 0, model->unk1A);
                break;
        }
    }
}

/* MP1 func_80026C6C (src/24740.c): retail keeps a second copy of arg4 (s2) for the switch, as
   MP1 and MP2 do (register allocation); NON_MATCHING in both */
#ifdef NON_MATCHING
void func_8001D638_main(s16 arg0, f32 arg1, f32 arg2, char* arg3, s32 arg4) {
    HmfDataM* model = MDL[arg0].hmf;
    HmfVtxM* src;
    HmfVtxM* dst;
    s16 idx;
    s16 n;
    s16 i;

    if (model == NULL) {
        return;
    }
    idx = func_8002C834_main(model, arg3);
    if (idx == -1) {
        return;
    }
    if (arg4 & 0x80) {
        src = model->unk40;
        dst = model->unk44[(u8)D_800D2008_main];
        n = model->unk18;
        for (i = 0; i < n; i++) {
            *dst++ = *src++;
        }
    }
    switch (arg4 & 0xF) {
        case 0:
            func_8001D874_main(model, arg1, arg2, model->unk60[idx].unk2C, model->unk60[idx].unk2E);
            break;
        case 1:
            func_8001DACC_main(model, arg1, arg2, model->unk60[idx].unk2C, model->unk60[idx].unk2E);
            break;
        case 2:
            func_8001DDB8_main(model, arg1, arg2, model->unk60[idx].unk2C, model->unk60[idx].unk2E);
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/hmfman", func_8001D638_main);
#endif

/* MP1 func_80026EA8 (src/24740.c) */
void func_8001D874_main(HmfDataM* arg0, f32 arg1, f32 arg2, u16 arg3, u16 arg4) {
    HmfFaceM* b = &arg0->unkB0[arg3];
    f32 inv = 1.0f - arg1;
    HmfVtxM* src;
    HmfVtxM* dst;
    s16* idx;
    s16 cx, cy, cz;
    s16 sx, sy, sz;
    s16 n;
    s16 j;
    s16 i;

    for (i = 0; i < arg4; i++) {
        cx = b->unk0C;
        cy = b->unk10;
        cz = b->unk14;
        sx = cx * arg2;
        sy = cy * arg2;
        sz = cz * arg2;
        n = (u8)(b->unk00 & 0x7F);
        idx = b->unk04;
        for (j = 0; j < n; j++) {
            src = &arg0->unk40[*idx];
            dst = &arg0->unk44[(u8)D_800D2008_main][*idx];
            dst->unk00 = (src->unk00 - cx) * inv + sx;
            dst->unk02 = (src->unk02 - cy) * inv + sy;
            dst->unk04 = (src->unk04 - cz) * inv + sz;
            idx++;
        }
        b++;
    }
}

INCLUDE_ASM("asm/nonmatchings/hmfman", func_8001DACC_main);

INCLUDE_ASM("asm/nonmatchings/hmfman", func_8001DDB8_main);

/* MP1 func_80027AC8 (src/24740.c): point a model's texture arg1 at the loaded texture arg2 */
void func_8001E500_main(s16 arg0, char* arg1, char* arg2) {
    HmfTexM* found = NULL;
    HmfDataM* model = MDL[arg0].hmf;
    u16 hash = func_80011460_main((u8*)arg2);
    s16 i;

    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].unk22 != 0 && D_800D1FCC_main[i].unk22 == hash
            && strcmp((char*)&D_800D1FCC_main[i], arg2) == 0) {
            found = &D_800D1FCC_main[i];
            break;
        }
    }
    hash = func_80011460_main((u8*)arg1);
    for (i = 0; i < model->unk12; i++) {
        if (model->unk84[i].unk0C->unk22 == hash) {
            model->unk84[i].unk0C = found;
        }
    }
}

/* MP1 func_80027C1C (src/24740.c): scroll the texture coordinates */
void func_8001E65C_main(s16 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
    u16 w;
    u16 h;
    s16 i;
    u16 var_a0;
    u16 var_a0_2;
    s16 temp_t2;
    HmfDataM* temp_s0;
    HmfVtxM* var_t0;
    HmfVtxM* var_t1;

    temp_s0 = MDL[arg0].hmf;
    if (temp_s0 != NULL) {
        var_t0 = temp_s0->unk40;
        var_t1 = temp_s0->unk44[(u8)D_800D2008_main];
        temp_t2 = temp_s0->unk18;
        w = arg3 << 5;
        h = arg4 << 5;
        var_a0 = arg1 * 32.0f;
        var_a0_2 = arg2 * 32.0f;

        if (arg1 < 0.0f) {
            arg1 = -arg1;
        }
        if (arg2 < 0.0f) {
            arg2 = -arg2;
        }

        if ((arg1 * 32.0f) > w) {
            var_a0 = var_a0 % w;
        }

        if ((arg2 * 32.0f) > h) {
            var_a0_2 = var_a0_2 % h;
        }

        for (i = 0; i < temp_t2; i++) {
            var_t1->unk08 = var_a0 + var_t0->unk08;
            var_t1->unk0A = var_a0_2 + var_t0->unk0A;
            var_t0++;
            var_t1++;
        }
    }
}

/* MP1 func_80027E48 (src/24740.c): scroll one part's texture coordinates */
void func_8001E888_main(s16 arg0, f32 arg1, f32 arg2, u16 arg3, u16 arg4, char* arg5, u8 arg6) {
    s16 i;
    u16 var_a0;
    u16 var_a0_2;
    s16 temp_t2;
    HmfDataM* temp_s0;
    HmfVtxM* var_t0;
    HmfVtxM* var_t1;
    s32 temp2;

    temp_s0 = MDL[arg0].hmf;
    if (temp_s0 != NULL) {
        if (arg6 != 0) {
            var_t0 = temp_s0->unk40;
            var_t1 = temp_s0->unk44[(u8)D_800D2008_main];
            temp_t2 = temp_s0->unk18;
            for (i = 0; i < temp_t2; i++) {
                *var_t1++ = *var_t0++;
            }
        }
        temp2 = func_8002C834_main(temp_s0, arg5);
        temp_t2 = temp_s0->unk60[temp2].unk2A;
        var_t0 = &temp_s0->unk40[temp_s0->unk60[temp2].unk28];
        var_t1 = &temp_s0->unk44[(u8)D_800D2008_main][temp_s0->unk60[temp2].unk28];
        arg3 = (arg3 << 5);
        arg4 = (arg4 << 5);
        var_a0 = arg1 * 32.0f;
        var_a0_2 = arg2 * 32.0f;

        if (arg1 < 0.0f) {
            arg1 = -arg1;
        }
        if (arg2 < 0.0f) {
            arg2 = -arg2;
        }

        if ((arg1 * 32.0f) > arg3) {
            var_a0 = var_a0 % arg3;
        }

        if ((arg2 * 32.0f) > arg4) {
            var_a0_2 = var_a0_2 % arg4;
        }

        for (i = 0; i < temp_t2; i++) {
            var_t1->unk08 = var_a0 + var_t0->unk08;
            var_t1->unk0A = var_a0_2 + var_t0->unk0A;
            var_t0++;
            var_t1++;
        }
    }
}

/* MP1 func_80028180 (src/24740.c): set one part's vertex colours */
void func_8001EBC0_main(s16 arg0, char* arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    HmfDataM* model = MDL[arg0].hmf;
    HmfVtxM* src;
    HmfVtxM* dst;
    s16 idx;
    s16 n;
    s16 i;

    if (model != NULL) {
        if (arg5 != 0) {
            src = model->unk40;
            dst = model->unk44[(u8)D_800D2008_main];
            n = model->unk18;
            for (i = 0; i < n; i++) {
                *dst++ = *src++;
            }
        }
        idx = func_8002C834_main(model, arg1);
        n = model->unk60[idx].unk2A;
        src = &model->unk44[(u8)D_800D2008_main][model->unk60[idx].unk28];
        for (i = 0; i < n; i++) {
            src->unk0C[0] = arg2;
            src->unk0C[1] = arg3;
            src->unk0C[2] = arg4;
            src++;
        }
    }
}

/* MP1 func_80028314 (src/24740.c): reverse every face's winding */
void func_8001ED54_main(s16 arg0) {
    HmfDataM* model = MDL[arg0].hmf;
    HmfPartM* obj;
    HmfFaceRecM* key;
    s16 tmp;
    f32 ftmp;
    s16 n;
    s16 k;
    s16 j;
    s16 i;

    for (i = 0; i < model->unk10; i++) {
        obj = &model->unk60[i];
        for (j = 0; j < obj->unk22; j++) {
            key = &obj->unk54[j];
            n = (u8)(key->unk00 & 0x7F);
            for (k = 0; k < n / 2; k++) {
                tmp = key->unk04[k];
                key->unk04[k] = key->unk04[n - k - 1];
                key->unk04[n - k - 1] = tmp;
                ftmp = key->unk0C[k];
                key->unk0C[k] = key->unk0C[n - k - 1];
                key->unk0C[n - k - 1] = ftmp;
                ftmp = key->unk1C[k];
                key->unk1C[k] = key->unk1C[n - k - 1];
                key->unk1C[n - k - 1] = ftmp;
            }
        }
    }
}

void func_8001EED8_main(s16 arg0, u8 arg1, s8 arg2) {
    HmfModelM* modelP = &MDL[arg0];

    modelP->unk06 = arg1;
    modelP->unk60 = modelP->unk58 = 0.0f;
    modelP->unk07 = arg2;
    modelP->unk5C = 1.0f;
}

/* MP1 func_80028510 (src/24740.c). Retail reads arg4 as a byte (lbu 0x13(sp)) */
void func_8001EF24_main(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4) {
    D_800CE1C6_main = 1;
    D_800D6B64_main = arg0;
    D_800CC0B6_main = arg1;
    D_800D0599_main = arg2;
    D_800D41C4_main = arg3;
    D_800CDA84_main = arg4;
}

void func_8001EF60_main(void) {
    D_800CE1C6_main = 0;
}

/* MP1 func_8002859C (src/24740.c): make model arg0 follow part arg2 of model arg1 */
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2) {
    HmfDataM* model = MDL[arg1].hmf;
    s16 idx = func_8002C834_main(model, arg2);

    MDL[arg0].unk68 = model;
    MDL[arg0].unk0A = idx;
}

/* MP1 func_8002861C (src/24740.c) */
void func_8001EFEC_main(s16 arg0) {
    HmfDataM* model = MDL[arg0].hmf;

    model->unk9C = func_80031A44_main(model);
}

/* MP1 func_80028668 (src/24740.c): advance a model's three motions */
void func_8001F038_main(HmfModelM* arg0, u16 arg1) {
    arg0->unk40 = func_8002FC7C_main(&D_800CCF58_main[arg0->unk02], arg0->unk03, arg0->unk40, arg0->unk48, (f32)arg1 * arg0->unk44);
    if (arg0->unk04 != 0xFF) {
        arg0->unk4C = func_8002FC7C_main(&D_800CCF58_main[arg0->unk04], arg0->unk05, arg0->unk4C, arg0->unk54, (f32)arg1 * arg0->unk50);
    }
    if (arg0->unk06 != 0xFF) {
        arg0->unk58 = func_8002FC7C_main(&D_800CCF58_main[arg0->unk06], (u8)arg0->unk07, arg0->unk58, arg0->unk60, (f32)arg1 * arg0->unk5C);
    }
}

void func_8001F154_main(HmfModelM* arg0) {
    HmfDataM* hmf = arg0->hmf;
    s16 frame = arg0->unk40;
    s16 i;

    for (i = 0; i < hmf->unk2A; i++) {
        func_80032FC0_main(hmf->unkC8[i], 1, 1);
        func_80034048_main(hmf->unkC8[i], frame);
    }
}

/* MP1 func_80028784 (src/24740.c): load a motion file */
s32 func_8001F1FC_main(void* arg0, s32 arg1) {
    u8* data = arg0;
    s16 ret;

    if (data[0] != 'M' || data[1] != 'T' || data[2] != 'N' || data[3] != 'X') {
        D_800D5204_main = 10256;
        D_800CDD6A_main = 10257;
        D_800CB8C0_main.unk0E = D_800D5204_main;
        Hmfload((HmfData*)&D_800CB8C0_main, data, (s16)arg1);
        ret = func_8002D2D8_main(data, (HmfData*)&D_800CB8C0_main);
        HuMemFreeAllWithTag(D_800D5204_main);
        HuMemFreeAllWithTag(D_800CDD6A_main);
    } else {
        ret = func_8002D3AC_main(data);
    }
    if (arg1 & 8) {
        gFreeFunc(data);
    }
    return ret;
}

void func_8001F304_main(s16 arg0, s16 arg1) {
    HmfModel *temp_v0;

    temp_v0 = &HmfModelData[arg0];
    temp_v0->unk02 = arg1;
    temp_v0->unk03 = 0;
    temp_v0->unk48 =
        temp_v0->unk40 = 0.0f;
    temp_v0->unk44 = 1.0f;
    temp_v0->unk04 = 0xFF;
}

f32 func_8001F358_main(s16 arg0) {
    return D_800CCF58_main[arg0].unk02;
}

/* MP1 func_80072724 (src/72D90.c) */
void func_8001F38C_main(s32 arg0, s32 arg1, s32 arg2) {
    D_800A0540_main = arg0;
    D_800A0541_main = arg1;
    D_800A0542_main = arg2;
}

/* MP1 func_80028928 (src/24740.c) */
void func_8001F3A8_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    HmfModelM* p = &MDL[arg0];

    if ((arg1 & 1) && p->unk02 != 0xFF) {
        p->unk03 = (p->unk03 & ~arg2) | arg3;
        if ((arg1 & 2) && p->unk04 != 0xFF) {
            p->unk05 = (p->unk05 & ~arg2) | arg3;
        }
        if ((arg1 & 4) && p->unk06 != 0xFF) {
            p->unk07 = arg3 | (p->unk07 & ~arg2);
        }
    }
}

/* MP1 func_800289D0 (src/24740.c): level of detail, model arg1 replaces arg0 beyond distance arg2 */
void func_8001F450_main(s16 arg0, s16 arg1, f32 arg2) {
    HmfModelM* p = &MDL[arg0];

    p->unk09 = arg1;
    p->unk6C = p->hmf;
    p->unk14 = arg2;
    p = &MDL[arg1];
    p->unk09 = arg0;
    p->unk6C = NULL;
    p->unk14 = 0.0f;
    p->unk18 |= 4;
}

/* MP1 func_80028A34 (src/24740.c): pick the level-of-detail model by camera distance */
void func_8001F4BC_main(s16 arg0) {
    HmfModelM* p = &MDL[arg0];
    f32 dx = CAM->pos.x - p->pos.x;
    f32 dy = CAM->pos.y - p->pos.y;
    f32 dz = CAM->pos.z - p->pos.z;
    HmfDataM* model;
    HmfModelM* q;
    s32 flags;
    s16 i;

    if (p->unk14 < HuSqrtf(dx * dx + dy * dy + dz * dz)) {
        model = p->unk6C;
    } else {
        model = MDL[p->unk09].hmf;
    }
    if (model != p->hmf) {
        p->hmf = model;
        for (i = 0; i < HU3D_MODEL_MAX; i++) {
            q = &MDL[i];
            if (q->hmf != NULL) {
                continue;
            }
            flags = q->unk18;
            if (flags & 4) {
                continue;
            }
            if (!(flags & 0x4000)) {
                continue;
            }
            if (p->hmf == q->unk68 || MDL[p->unk09].hmf == q->unk68) {
                MDL[i].unk68 = model;
            }
        }
    }
    MDL[p->unk09].unk18 |= 4;
}

s32 func_8001F668_main(s16 arg0) {
    HmfModelM* p = &MDL[arg0];

    return p->hmf == MDL[p->unk09].hmf;
}

void func_8001F6B0_main(s8 arg0) {
    D_800CC0A8_main = arg0;
}

/* MP1 func_80028BEC (src/24740.c) */
void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    HmfDataM* model = MDL[arg0].hmf;

    model->unk02 = arg1;
    model->unk03 = arg2;
    model->unk04 = arg3;
    model->unk05 = arg4;
}

/* MP1 func_80028C28 (src/24740.c) */
void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    HmfDataM* model = MDL[arg0].hmf;

    model->unk06 = arg1;
    model->unk07 = arg2;
    model->unk08 = arg3;
    model->unk09 = arg4;
}

/* MP1 func_80028C64 (src/24740.c) */
void func_8001F734_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    func_8001F6BC_main(arg0, arg1, arg2, arg3, arg4);
    func_8001F6F8_main(arg0, arg1 * 0.5f, arg2 * 0.5f, arg3 * 0.5f, arg4 * 0.5f);
}

/* MP1 func_80028E8C (src/24740.c) */
void func_8001F95C_main(s32 arg0, void* func) {
    D_800CC3D8_main[(s16)arg0] = func;
}

void func_8001F974_main(s16 arg0, s16 arg1) {
    func_8001C5B4_main(arg0, arg1);
    MDL[arg0].unk08 = MDL[arg1].unk08;
}

void func_8001F9E4_main(s16 arg0, u8 arg1) {
    HmfDataM* model = MDL[arg0].hmf;
    s16 i;

    for (i = 0; i < model->unk10; i++) {
        model->unk60[i].unk20 = arg1;
    }
}

/* MP1 func_80021240 (src/1EA70.c) */
void func_8001FA68_main(s16 index) {
    s16 i;
    HmfMatM* temp_v1;
    HmfDataM* temp_s0;

    temp_s0 = MDL[index].hmf;
    func_8001C2FC_main(index, 0x110000, 0x110000);
    for (i = 0; i < temp_s0->unk1E; i++) {
        temp_s0->unk88[i].unk0A = 0xFF;
        temp_v1 = &temp_s0->unk88[i];
        temp_v1->unk09 = temp_v1->unk09 | 5;
    }
    func_8001C448_main(index);
}

void func_8001FB34_main(s16 arg0, u8 arg1) {
    HmfModelM* p = &MDL[arg0];
    HmfData_UnkD0* l;

    if (p->unkB4 == NULL) {
        l = p->unkB4 = HuMemAllocTag(0x38, D_800CDD6A_main);
        l->unk03 = arg1;
        l->unk00 = l->unk01 = l->unk02 = 0x40;
        l->unk04 = l->unk05 = l->unk06 = 0x64;
    }
}

void func_8001FBBC_main(s16 arg0, s8 arg1, s8 arg2, s8 arg3) {
    HmfModel *other;

    other = HmfModelData[arg0].unkB4;
    if (other != NULL) {
        other->unk00 = arg1;
        other->unk01 = arg2;
        other->unk02 = arg3;
    }
}

/* the lights' direction: (x, y, z) normalised, scaled to 120. Register allocation, as in MP2:
   retail loads unkB4 into v0 and copies it to s0 after the NULL test (masked 1) */
#ifdef NON_MATCHING
void func_8001FBFC_main(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    HmfData_UnkD0* l = MDL[arg0].unkB4;
    f32 len;

    if (l != NULL) {
        len = HuSqrtf(arg1 * arg1 + arg2 * arg2 + arg3 * arg3);
        if (len != 0.0f) {
            l->unk04 = (arg1 / len) * 120.0f;
            l->unk05 = (arg2 / len) * 120.0f;
            l->unk06 = (arg3 / len) * 120.0f;
        } else {
            l->unk04 = 0;
            l->unk05 = 120;
            l->unk06 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/hmfman", func_8001FBFC_main);
#endif

/* mark every face unlit */
void func_8001FD08_main(s16 arg0) {
    HmfDataM* model = MDL[arg0].hmf;
    HmfPartM* obj;
    s16 j;
    s16 i;

    for (i = 0; i < model->unk10; i++) {
        obj = &model->unk60[i];
        for (j = 0; j < obj->unk22; j++) {
            obj->unk54[j].unk00 |= 0x80;
        }
    }
}

void func_8001FDE8_main(s16 arg0) {
    HmfModelData[arg0].unk02 = 0xFF;
}

INCLUDE_RODATA("asm/nonmatchings/hmfman", D_800A6C04_main);
