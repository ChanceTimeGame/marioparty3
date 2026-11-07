#include "common.h"
#include "mallocblock.h"

/* Model (HMF) display-list build and drawing, materials and textures, matrix walks, motion and
   morph/vertex animation (MP2 src/30560.c, MP1 src/2C0C0.c and src/34D80.c).
   Local model structs (MP2 include/game/hmfman.h). HmfObj is MP3's HmfData in full: its fields keep
   MP2's names (MP2 offsets), but MP3's HmfData has 3 vertex buffers (unk44) where MP2 has 4, so from
   unk54 on every field sits 4 bytes earlier than its name says (the comments give MP3's offset). */

typedef f32 Matrix4f[4][4];

typedef struct HmfVtx {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8 unk0C[3];
    /* 0x0F */ u8 unk0F;
} HmfVtx; /* size = 0x10 */

typedef struct HmfFace {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ s16 unk02[4]; /* MP2 0x02 */
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} HmfFace; /* size = 0x18 */

typedef struct HmfPal {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ char unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ void* unk24;
    /* 0x28 */ u16* unk28;
} HmfPal;

typedef struct HmfTex {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ char unk20[2];
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ char unk26[2];
    /* 0x28 */ u8* unk28;
    /* 0x2C */ void* unk2C;
    /* 0x30 */ HmfPal* unk30;
} HmfTex;

typedef struct HmfTexRef {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ char unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ HmfTex* unk0C;
} HmfTexRef; /* size = 0x10 */

typedef struct HmfMat {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01[3];
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05[3];
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09[3];
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
} HmfMat; /* size = 0xE */

typedef struct HmfAnimTrack {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16* unk08;
    /* 0x0C */ s32* unk0C;
} HmfAnimTrack; /* size = 0x10 */

typedef struct HmfAnim {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ HmfAnimTrack unk0C[16];
} HmfAnim;

typedef struct HmfDisp {
    /* 0x00 */ void* unk00[4];
    /* 0x10 */ void* unk10;
    /* 0x14 */ void* unk14;
} HmfDisp; /* MP3 HmfModelData_Unk64_Unk3C_Struct */

typedef struct HmfPart {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ char unk04_[4];
    /* 0x08 */ char unk08[0x14];
    /* 0x1C */ u8 unk2E; /* MP2 0x2E */
    /* 0x1D */ u8 unk2F; /* MP2 0x2F */
    /* 0x1E */ char unk1E[4];
    /* 0x22 */ s16 unk04; /* MP2 0x04: face count */
    /* 0x24 */ char unk24[4];
    /* 0x28 */ s16 unk0A; /* MP2 0x0A: first vertex */
    /* 0x2A */ s16 unk0C; /* MP2 0x0C: vertex count */
    /* 0x2C */ u16 unk0E; /* MP2 0x0E: first face */
    /* 0x2E */ u16 unk10; /* MP2 0x10: face count */
    /* 0x30 */ char unk30[0x12];
    /* 0x42 */ s16 unk42;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[2];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ struct HmfFaceRec* unk54;
    /* 0x58 */ struct HmfObj* unk58;
    /* 0x5C */ HmfTexRef* unk5C;
    /* 0x60 */ HmfTexRef* unk60;
    /* 0x64 */ Gfx* unk64;
} HmfPart; /* size = 0x68; MP3 HmfModelData_Unk64_Unk60_Struct. Fields keep MP2 names; MP3 moves 0x0A-0x2F */

typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

typedef struct HmfVtxCopy {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ ColVtx* unk04;
    /* 0x08 */ u8* unk08;
    /* 0x0C */ u8* unk0C;
} HmfVtxCopy; /* size = 0x10 */

typedef struct HitXform {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ Vec unk20;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ Vec unk38;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ char unk46[2];
    /* 0x48 */ struct HmfObj* unk48;
    /* 0x4C */ f32 unk4C[4][4];
} HitXform; /* size 0x8C */

typedef struct HmfObj {
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
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ char unk0D;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ char unk20[2];
    /* 0x22 */ s16 unk22;
    /* 0x24 */ char unk24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ u8* unk2C;
    /* 0x30 */ u8* unk30;
    /* 0x34 */ u8* unk34;
    /* 0x38 */ void* unk38;
    /* 0x3C */ HmfDisp* unk3C;
    /* 0x40 */ HmfVtx* unk40;
    /* 0x44 */ HmfVtx* unk44[3];
    /* 0x50 */ ColVtx* unk54;
    /* 0x54 */ u8* unk58;
    /* 0x58 */ HmfVtxCopy* unk5C;
    /* 0x5C */ s16* unk60;
    /* 0x60 */ HmfPart* unk64;
    /* 0x64 */ s16 unk68;
    /* 0x66 */ char unk6A[2];
    /* 0x68 */ HitXform* unk6C;
    /* 0x6C */ char unk70[0x14];
    /* 0x80 */ struct HmfMotionObj* unk84;
    /* 0x84 */ HmfTexRef* unk88;
    /* 0x88 */ HmfMat* unk8C;
    /* 0x8C */ void* unk90;
    /* 0x90 */ void* unk94;
    /* 0x94 */ void* unk98;
    /* 0x98 */ HmfAnim* unk9C;
    /* 0x9C */ void* unkA0;
    /* 0xA0 */ f32 unkA4;
    /* 0xA4 */ f32 unkA8;
    /* 0xA8 */ f32 unkAC;
    /* 0xAC */ f32 unkB0;
    /* 0xB0 */ HmfFace* unkB4;
    /* 0xB4 */ void* unkB8;
    /* 0xB8 */ void* unkBC;
    /* 0xBC */ void* unkC0;
    /* 0xC0 */ void* unkC4;
    /* 0xC4 */ u8* unkC8;
    /* 0xC8 */ void* unkC8_mp3; /* MP3 only; where between 0xB4 and 0xCC MP3 adds it is unconfirmed */
    /* 0xCC */ Gfx*** unkCC;
    /* 0xD0 */ HmfData_UnkD0* unkD0;
    /* 0xD4 */ void (*unkD4)(f32 (*)[4], f32, f32, f32);
    /* 0xD8 */ void (*unkD8)(f32 (*)[4], f32, f32, f32);
    /* 0xDC */ s32 unkDC;
} HmfObj; /* size 0xE0 */

typedef struct HmfFaceRec {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ s8 unk01[3];
    /* 0x04 */ s16 unk04[4];
    /* 0x0C */ f32 unk0C[4];
    /* 0x1C */ f32 unk1C[4];
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
} HmfFaceRec; /* size 0x34 */

typedef struct HmfMotionObj {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ Vec unk28;
    /* 0x34 */ Vec unk34;
    /* 0x40 */ Vec unk40;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ char unk4F;
    /* 0x50 */ s16* unk50;
    /* 0x54 */ struct HmfObj* unk54;
    /* 0x58 */ f32 unk58[4][4];
} HmfMotionObj; /* size = 0x98 */

typedef struct HmfMotionTrack {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} HmfMotionTrack; /* size = 0x10 */

typedef struct HmfMotionSlot {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ char unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ HmfMotionTrack** unk08;
    /* 0x0C */ u8* unk0C;
    /* 0x10 */ s16* unk10;
    /* 0x14 */ f32* unk14;
    /* 0x18 */ s32 unk18;
} HmfMotionSlot; /* size 0x1C */

typedef struct HmfLayerEnt {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
} HmfLayerEnt; /* size = 0x8 */

typedef struct HmfDrawRec {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x42];
    /* 0x44 */ void* unk44;
    /* 0x48 */ HmfObj* unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ u32 unk50;
    /* 0x54 */ struct HmfData_UnkD0* unk54;
} HmfDrawRec; /* size = 0x58 */

typedef struct HmfLight {
    /* 0x00 */ Hilite unk_00;
    /* 0x10 */ char unk_10[0x30];
    /* 0x40 */ LookAt unk_40;
} HmfLight; /* size = 0x60 */


void func_80018544_main(f32 (*)[4], f32 (*)[4]);
void func_80019C00_main(void *data);
void func_80022660_main(struct HmfObj *);
extern s16 D_800CDD6A_main;
extern u16 D_800D5204_main;

extern u8 D_800D1FF0_main;
extern u8 D_800D2008_main;
extern u16 D_800D1FEE_main;
extern u16 D_800C9528_main;
extern u16 D_800D5306_main;
extern HmfVtx* D_800D6A98_main[];
extern void* D_800CD1B8_main[];
extern Gfx* D_800D1F38_main[];
extern HmfLayerEnt* D_800D2070_main[8];
extern u8 D_800A0AD0_main[8];
extern HmfDrawRec* D_800CC0BC_main;
typedef struct HmfLightSet {
    /* 0x00 */ s16 unk00;
} HmfLightSet; /* hmflight's light data; only its light count is read here */
extern HmfLightSet* D_800CE1D4_main;
extern u8 D_800CB8B0_main;
extern u8 D_800D10F0_main;
extern f32 D_800D5410_main;
extern f32 D_800D51FC_main;
extern u8 D_800CE1C6_main;
extern u8 D_800CDA84_main;
extern u8 D_800D41C4_main;
extern u8 D_800D0599_main;
extern s16 D_800D6B64_main;
extern s16 D_800CC0B6_main;
extern u8 D_800CC0A8_main;
extern u16 D_800D20EE_main;
extern HmfVtx* D_800D5308_main;
extern Mtx* MTXBuf;
extern s16 MTXBufNum;
extern Gfx* gMainGfxPos;
extern Gfx* D_800D1FF8_main;
extern HmfLight D_800D1408_main[];
extern HmfLight* D_800CE20C_main;
extern s16 D_800CE1CE_main;
extern s16 D_800D1FD8_main;
extern s16 D_800D6A92_main;
extern u8 D_800CE19A_main;
extern s32 D_800D20AC_main;
extern s16 D_800D6AC8_main[8];
extern s16 D_800D5564_main;

void HmfLightInit(void);
void HmfLightClose(void);
void func_80031560_main(void);
void func_80030040_main(void);
void func_800123F4_main(void);

void func_800222B0_main(void* (*arg0)(s32), void (*arg1)(void*), u16 arg2, u16 arg3, u16 arg4, u8 arg5) {
    s16 i;

    D_800D1FF0_main = arg5;
    D_800D2008_main = 0;
    HuMemInit(arg0, arg1);
    D_800D1FEE_main = arg2;
    D_800C9528_main = arg4;
    D_800D5306_main = arg3;
    for (i = 0; i < arg5; i++) {
        D_800D6A98_main[i] = HuMemAlloc(arg2 * sizeof(HmfVtx));
        D_800CD1B8_main[i] = HuMemAlloc(arg4 * 64);
        D_800D1F38_main[i] = HuMemAlloc(arg3 * sizeof(Gfx));
    }
    for (i = 0; i < 8; i++) {
        D_800D2070_main[i] = HuMemAlloc(D_800A0AD0_main[i] * 8);
    }
    D_800CC0BC_main = HuMemAlloc(0x8400);
    D_800CE1D4_main = 0;
    HmfLightInit();
    func_80031560_main();
    func_80030040_main();
    D_800CB8B0_main = 1;
    D_800D10F0_main = 2;
    D_800D5410_main = 1.0f;
    D_800D51FC_main = 1.0f;
    D_800CE1C6_main = 0;
    D_800CDA84_main = 0xFF;
    D_800D41C4_main = 0xFF;
    D_800D0599_main = 0xFF;
    D_800D6B64_main = 950;
    D_800CC0B6_main = 1000;
    D_800CC0A8_main = 1;
}

void func_800224BC_main(void) {
    HuMemCleanUp();

    if (D_800D20EE_main != 0) {
        s32 temp_v0 = D_800D2008_main;

        D_800D5308_main = D_800D6A98_main[temp_v0];
        MTXBuf = D_800CD1B8_main[temp_v0];
        D_800D1FF8_main = gMainGfxPos = D_800D1F38_main[temp_v0];
        D_800CE20C_main = &D_800D1408_main[temp_v0];

        if (++D_800D2008_main >= D_800D1FF0_main) {
            D_800D2008_main = 0;
        }

        HmfLightClose();

        D_800CE1CE_main = 0;
        MTXBufNum = 0;
        D_800D1FD8_main = 0;
        D_800D6A92_main = 0;
        D_800CE19A_main = 0;

        func_800123F4_main();

        D_800D20AC_main++;
    }
}

void func_800225D4_main(void) {
    HmfLayerEnt** p;
    s16 i;

    for (i = 0; i < 8; i++) {
        D_800D6AC8_main[i] = 2;
        p = &D_800D2070_main[i];
        (*p)->unk00 = 1;
        (*p + 1)->unk01 = 0;
        (*p + 1)->unk00 = 0;
        (*p + 1)->unk04 = 200000.0f;
    }
    D_800D5564_main = 0;
}

extern u32 D_800C9940_main;
extern Light* D_800CB8A8_main;
extern HmfTexRef* D_800CC0AC_main;
extern u16 D_800CDA76_main;
extern u16 D_800CDA86_main;
extern u16 D_800CDD5A_main;
extern u16 D_800CE170_main;
extern void* D_800D0440_main;
extern u16 D_800D1F78_main;
extern u16 D_800D1FE2_main;
extern u8 D_800D5544_main;
extern s16 D_800D5562_main;
extern Gfx* D_800D6A88_main;
extern u64 D_800CE2F0_main;
extern u64 D_800D1FD0_main;
void HmfLightReset(void);
void func_80022F08_main(HmfObj*);
void func_80022FF4_main(HmfObj*);
void func_800230F8_main(HmfData*);
void func_800257BC_main(HmfObj*, s16);
void func_8002D094_main(Gfx**, s16, s32);
void func_80030208_main(HmfObj*);

#define HMF_DL(a) ((Gfx**) (a)->unk3C)

#ifdef NON_MATCHING
/* Register allocation only: the allocation size is built in v0, not a0 */
void func_80022660_main(HmfObj* arg0) {
    s16 savedCount;
    s16 found;
    s16 maxLen;
    Gfx* savedDl;
    HmfVtx* savedVtx;
    Gfx* buf2;
    Gfx* var_s4;
    HmfPart* part;
    HmfVtx* vtx;
    s16* map;
    s32 flags;
    s32 size;
    u16 vtxStart;
    s16 i;
    s16 j;

    maxLen = 0;
    if (arg0->unk10 == 0 || arg0->unk14 == 0) {
        return;
    }

    savedDl = gMainGfxPos;
    savedVtx = D_800D5308_main;
    savedCount = D_800CE1CE_main;

    arg0->unk3C = HuMemAllocTag(arg0->unk10 * sizeof(Gfx*), D_800CDD6A_main);
    buf2 = HuMemAlloc(25 * sizeof(Gfx));
    size = arg0->unk1C * 4 + arg0->unk10 * 8;
    D_800D5308_main = HuMemAlloc(size * sizeof(HmfVtx));
    if (arg0->unkB8 != NULL || (D_800C9940_main & 0x400000)) {
        if (arg0->unk60 != NULL) {
            HuMemFree(arg0->unk60);
        }
        arg0->unk60 = HuMemAlloc(arg0->unk14 * sizeof(s16));
        arg0->unk28 = 0;
    }
    if (D_800D5308_main == NULL) {
        D_800D5308_main = arg0->unk40 = (HmfVtx*) 0 + D_800CE1CE_main;
    }

    for (i = 0, found = 0; i < arg0->unk12; i++) {
        if (arg0->unk88[i].unk0C->unk1F & 1) {
            found++;
            break;
        }
    }
    var_s4 = HuMemAlloc(arg0->unk1C * (found == 0 ? 4 : 16) * sizeof(Gfx) + 500 * sizeof(Gfx));
    if (var_s4 == NULL) {
        var_s4 = gMainGfxPos;
    }

    if (arg0->unkCC != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if ((*arg0->unkCC)[i] != NULL) {
                func_80019C00_main((*arg0->unkCC)[i]);
            }
        }
        HuMemFree(*arg0->unkCC);
        HuMemFree(arg0->unkCC);
        arg0->unkCC = NULL;
    }

    func_80022F08_main(arg0);
    D_800CE1CE_main = 0;
    D_800D5562_main = 0;
    HmfLightReset();
    func_800230F8_main((HmfData*) arg0);

    part = arg0->unk64;
    for (i = 0; i < arg0->unk10; i++, part++) {
        gMainGfxPos = var_s4;
        D_800D6A88_main = buf2;
        D_800D5544_main = 0;
        vtxStart = D_800CE1CE_main;
        D_800CDA86_main = 0;
        D_800CE170_main = 0;
        D_800CDD5A_main = 0;
        D_800CE2F0_main = 0xFFFFFFFF;
        D_800D1FD0_main = 0xFFFFFFFF;
        D_800D0440_main = NULL;

        func_8002D094_main(&gMainGfxPos, 1, 0);

        if (D_800C9940_main & 0x200) {
            gSPLight(gMainGfxPos++, D_800CB8A8_main, D_800CE1D4_main->unk00 + 1);
            D_800D1F78_main = D_800CB8A8_main->l.col[0];
            D_800D1FE2_main = D_800CB8A8_main->l.col[1];
            D_800CDA76_main = D_800CB8A8_main->l.col[2];
        }

        flags = part->unk50;
        part->unk0A = D_800CE1CE_main;
        part->unk0E = D_800D5562_main;
        part->unk50 &= ~0x06000000;

        func_800257BC_main(arg0, i);

        flags &= 0x06000000;
        if (flags != 0) {
            part->unk50 |= flags;
        }

        part->unk0C = D_800CE1CE_main - part->unk0A;
        part->unk10 = D_800D5562_main - part->unk0E;

        gSPEndDisplayList(gMainGfxPos++);
        part->unk60 = D_800D0440_main;

        if (D_800D6A88_main == buf2) {
            HMF_DL(arg0)[i] = HuMemAllocTag(size = (gMainGfxPos - var_s4) * sizeof(Gfx), D_800CDD6A_main);
            bcopy(var_s4, HMF_DL(arg0)[i], size);
            part->unk5C = NULL;
            part->unk64 = NULL;
        } else {
            gSPEndDisplayList(D_800D6A88_main++);
            part->unk5C = D_800CC0AC_main;
            HMF_DL(arg0)[i] = HuMemAllocTag(
                (gMainGfxPos - var_s4 + D_800D6A88_main - buf2) * sizeof(Gfx), D_800CDD6A_main);
            bcopy(var_s4, HMF_DL(arg0)[i], (gMainGfxPos - var_s4) * sizeof(Gfx));
            part->unk64 = (gMainGfxPos - var_s4) + HMF_DL(arg0)[i];
            bcopy(buf2, part->unk64, (D_800D6A88_main - buf2) * sizeof(Gfx));
        }

        if (maxLen < gMainGfxPos - var_s4) {
            maxLen = gMainGfxPos - var_s4;
        }

        if (part->unk50 & 0x06000000) {
            if (arg0->unkCC == NULL) {
                arg0->unkCC = HuMemAllocTag(sizeof(Gfx**), D_800CDD6A_main);
                *arg0->unkCC = HuMemAllocTag(arg0->unk10 * sizeof(Gfx*), D_800CDD6A_main);
                for (j = 0; j < arg0->unk10; j++) {
                    (*arg0->unkCC)[j] = NULL;
                }
            }
            gMainGfxPos = var_s4;
            D_800CE1CE_main = vtxStart;
            D_800CDA86_main = 0;
            D_800CE170_main = 0;
            D_800CDD5A_main = 0;
            D_800CDA76_main = 0;
            D_800D1FE2_main = 0;
            D_800D1F78_main = 0;
            D_800CE2F0_main = 0xFFFFFFFF;
            D_800D1FD0_main = 0xFFFFFFFF;
            D_800D0440_main = NULL;

            func_800257BC_main(arg0, i);

            gSPEndDisplayList(gMainGfxPos++);
            (*arg0->unkCC)[i] = HuMemAllocTag((gMainGfxPos - var_s4) * sizeof(Gfx), D_800CDD6A_main);
            bcopy(var_s4, (*arg0->unkCC)[i], (gMainGfxPos - var_s4) * sizeof(Gfx));
        }
    }

    arg0->unk18 = D_800CE1CE_main;
    arg0->unk1A = D_800D5562_main;

    vtx = HuMemAllocTag(D_800CE1CE_main * sizeof(HmfVtx), D_800CDD6A_main);
    bcopy(D_800D5308_main, vtx, D_800CE1CE_main * sizeof(HmfVtx));
    arg0->unk40 = vtx;

    func_80022FF4_main(arg0);

    for (i = 0; i < 3; i++) {
        arg0->unk44[i] = vtx;
    }

    if (arg0->unk60 != NULL) {
        map = HuMemAllocTag(arg0->unk14 * sizeof(s16), D_800CDD6A_main);
        bcopy(arg0->unk60, map, arg0->unk14 * sizeof(s16));
        HuMemFree(arg0->unk60);
        arg0->unk60 = map;
    }

    if (arg0->unkB8 != NULL || (D_800C9940_main & 0x400000)) {
        func_80030208_main(arg0);
    }

    if (arg0->unk1C * 4 + arg0->unk10 * 8 < D_800CE1CE_main) {
        osSyncPrintf("Vertex Over!\n");
    }

    HuMemFree(D_800D5308_main);
    HuMemFree(var_s4);
    HuMemFree(buf2);

    D_800CE1CE_main = savedCount;
    D_800D5308_main = savedVtx;
    gMainGfxPos = savedDl;
}
#else
INCLUDE_ASM("asm/nonmatchings/22EB0", func_80022660_main);
#endif


void func_80022F08_main(HmfObj* arg0) {
    u16 var_a2;
    s16 var_a3 = 0;
    s16 i;

    for (i = 0, var_a2 = 0; i < arg0->unk10; i++) {
        if (arg0->unk64[i].unk50 & 0x20000) {
            var_a3 = 1;
        }
        var_a2 += arg0->unk64[i].unk04;
    }

    if (var_a3 && arg0->unkB4 == NULL) {
        arg0->unkB4 = HuMemAllocTag(var_a2 * sizeof(HmfFace), D_800CDD6A_main);
    }
}

void func_80022FF4_main(HmfObj* arg0) {
    HmfFace* var_a3;
    f32 var_f4;
    f32 var_f6;
    f32 var_f8;
    s16* var_a1;
    u16 temp_t2;
    s16 i;
    s16 j;

    if (arg0->unkB4 == NULL) {
        return;
    }

    var_a3 = arg0->unkB4;
    for (i = 0; i < arg0->unk1A; i++, var_a3++) {
        var_a1 = var_a3->unk02;
        temp_t2 = var_a3->unk00;

        var_f6 = var_f8 = var_f4 = 0.0f;
        for (j = 0; j < temp_t2; j++, var_a1++) {
            var_f6 += arg0->unk40[*var_a1].unk00;
            var_f8 += arg0->unk40[*var_a1].unk02;
            var_f4 += arg0->unk40[*var_a1].unk04;
        }

        var_a3->unk0C = var_f6 / temp_t2;
        var_a3->unk10 = var_f8 / temp_t2;
        var_a3->unk14 = var_f4 / temp_t2;
    }
}

void func_800230F8_main(HmfData *arg0) {
    s16 textureIndex;
    s16 i, j;

    textureIndex = 4; // TODO: why does this start at 4?

    for (i = 0; i < arg0->unk12; i++) {
        /* Skip entries marked as 0xFF */
        if (arg0->unk84[i].unk9 == 0xFF) {
            continue;
        }

        /* Find first entry with different unkC value */
        for (j = 0; j < i; j++) {
            if (arg0->unk84[i].unkC == arg0->unk84[j].unkC) {
                break;
            }
        }

        /* Copy or assign texture indices */
        if (j != i) {
            arg0->unk84[i].unk3 = arg0->unk84[j].unk3;
            arg0->unk84[i].unk4 = arg0->unk84[j].unk4;
        } else {
            arg0->unk84[i].unk3 = textureIndex++;
            if (arg0->unk84[i].unkC->unk_30 != NULL) {
                arg0->unk84[i].unk4 = textureIndex++;
            }

            if (textureIndex > 16) {
                osSyncPrintf("Texture Anime Over\n");
                return;
            }
        }
    }
}

s32 func_80023264_main(HmfData *arg0) {
    s32 var_s2;
    s16 i;

    var_s2 = 0;
    if (arg0->unk40 != NULL) {
        for (i = 0; i < ARRAY_COUNT(arg0->unk44); i++) {
            if (arg0->unk40 != arg0->unk44[i]) {
                if (arg0->unk0A != 0) {
                    func_80019C00_main(arg0->unk44[i]);
                } else {
                    HuMemFree(arg0->unk44[i]);
                }
                arg0->unk44[i] = arg0->unk40;
                var_s2 = 1;
            }
        }

        if (arg0->unk0A != 0) {
            func_80019C00_main(arg0->unk40);
        } else {
            HuMemFree(arg0->unk40);
        }
    }
    if (arg0->unk3C != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if (arg0->unk0A != 0) {
                func_80019C00_main(arg0->unk3C->unk00[i]);
            } else {
                HuMemFree(arg0->unk3C->unk00[i]);
            }
        }

        if (arg0->unk0A != 0) {
            func_80019C00_main(arg0->unk3C);
        } else {
            HuMemFree(arg0->unk3C);
        }
    }
    D_800D5204_main = arg0->unk0E;
    D_800CDD6A_main = arg0->unk0E + 1;
    func_80022660_main((HmfObj*) arg0);
    return var_s2;
}

extern u8 D_800CD6A6_main;
extern s16 D_800D138A_main;
extern s16 D_800D5214_main;
extern Matrix4f D_800D41B0_main[];
extern Matrix4f D_800D5A00_main[];
extern f32 D_800D5A40_main[4][4];
void func_8002367C_main(Matrix4f, Matrix4f);
s32 func_8002C4C0_main(HmfData*, s16, Matrix4f, Matrix4f);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void func_80023700_main(HmfObj*, s16);
void func_80023AF8_main(HmfObj*, s16);
void func_8002404C_main(HmfObj*, s16);
void func_80024354_main(HmfObj*, s16);
void func_80024DF0_main(HmfObj*, s16, void*, Matrix4f);
void func_8002DFF8_main(HmfObj*, f32, void*, s32);
void func_8002EAC0_main(HmfObj*, f32, f32);

void func_80023404_main(HmfObj* arg0, Matrix4f arg1, Matrix4f arg2) {
    Matrix4f sp10;

    if (arg0->unk14 != 0) {
        func_8002367C_main(D_800D5A00_main[0], arg1);
        D_800D138A_main = 1;
        guMtxIdentF(D_800D5A40_main);
        D_800D5214_main = 0;
        func_8002367C_main(D_800D41B0_main[1], arg2);

        if (arg0->unk01 & 4) {
            if (arg0->unk64->unk50 & 0x70000000) {
                func_8002C4C0_main((HmfData*) arg0, 0, arg1, sp10);
                func_80018044_main(arg2, sp10, arg1);
            }
            func_800898F0_main((Mtx*) arg1, &MTXBuf[MTXBufNum]);
            func_80024DF0_main(arg0, 0, &MTXBuf[MTXBufNum++], arg1);
            return;
        }

        if (arg0->unk84 == (void*) -1) {
            if (arg0->unk90 != NULL) {
                func_8002DFF8_main(arg0, arg0->unkA4, arg0->unk90, 1);
                if (arg0->unk94 != NULL) {
                    func_8002EAC0_main(arg0, arg0->unkA8, arg0->unkAC);
                }
                if (arg0->unk98 != NULL) {
                    func_8002DFF8_main(arg0, arg0->unkB0, arg0->unk98, 0);
                }
            }
            if (arg0->unk68 != 0) {
                func_80023700_main(arg0, 0);
                if (D_800C9528_main <= MTXBufNum) {
                    osSyncPrintf("Mtx Over\n");
                }
            }
        } else if (arg0->unk16 != 0) {
            if (D_800CD6A6_main != 0 && arg0->unk0B == 1 && arg0->unk0C != 0) {
                func_8002404C_main(arg0, 0);
            } else {
                if (arg0->unk90 != NULL) {
                    func_8002DFF8_main(arg0, arg0->unkA4, arg0->unk90, 1);
                    if (arg0->unk94 != NULL) {
                        func_8002EAC0_main(arg0, arg0->unkA8, arg0->unkAC);
                    }
                    if (arg0->unk98 != NULL) {
                        func_8002DFF8_main(arg0, arg0->unkB0, arg0->unk98, 0);
                    }
                }
                if (arg0->unk16 == 1) {
                    func_80024354_main(arg0, 0);
                } else {
                    func_80023AF8_main(arg0, 0);
                }
            }
            if (D_800C9528_main <= MTXBufNum) {
                osSyncPrintf("Mtx Over\n");
            }
        }
    }
}

void func_8002367C_main(Matrix4f arg0, Matrix4f arg1) {
    arg0[0][0] = arg1[0][0];
    arg0[0][1] = arg1[0][1];
    arg0[0][2] = arg1[0][2];
    arg0[0][3] = arg1[0][3];
    arg0[1][0] = arg1[1][0];
    arg0[1][1] = arg1[1][1];
    arg0[1][2] = arg1[1][2];
    arg0[1][3] = arg1[1][3];
    arg0[2][0] = arg1[2][0];
    arg0[2][1] = arg1[2][1];
    arg0[2][2] = arg1[2][2];
    arg0[2][3] = arg1[2][3];
    arg0[3][0] = arg1[3][0];
    arg0[3][1] = arg1[3][1];
    arg0[3][2] = arg1[3][2];
    arg0[3][3] = arg1[3][3];
}

void func_8008A070_main(Matrix4f);
void func_80017CD0_main(Matrix4f, f32, f32, f32);

void func_80023700_main(HmfObj* arg0, s16 arg1) {
    HitXform* temp_s1;
    s32 var_s3;
    s32 var_s5;
    s32 temp_s4;
    Matrix4f sp10;
    Matrix4f sp50;

    temp_s1 = &arg0->unk6C[arg1];
    temp_s4 = temp_s1->unk00;
    var_s5 = 0;
    var_s3 = 0;

    if (arg0->unk90 == 0) {
        func_80018044_main(temp_s1->unk4C, D_800D5A00_main[0], sp10);
    } else {
        func_8008A070_main(sp10);
        if (temp_s1->unk2C.x != 0.0f || temp_s1->unk2C.y != 0.0f || temp_s1->unk2C.z != 0.0f) {
            func_80017C10_main((Mtx*) sp10, temp_s1->unk2C.x, temp_s1->unk2C.y, temp_s1->unk2C.z);
            var_s3 = 1;
        }
        if (temp_s1->unk38.x != 0.0f || temp_s1->unk38.y != 0.0f || temp_s1->unk38.z != 0.0f) {
            arg0->unkD4(sp10, temp_s1->unk38.x, temp_s1->unk38.y, temp_s1->unk38.z);
            var_s3 = 1;
        }
        if (temp_s1->unk20.x != 1.0f || temp_s1->unk20.y != 1.0f || temp_s1->unk20.z != 1.0f) {
            func_80017CD0_main(sp10, temp_s1->unk20.x, temp_s1->unk20.y, temp_s1->unk20.z);
            func_8008A070_main(sp50);
            func_80017CD0_main(sp50, temp_s1->unk20.x, temp_s1->unk20.y, temp_s1->unk20.z);
            D_800D5214_main++;
            func_80018044_main(sp50, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            var_s5 = 1;
            var_s3 = 1;
        }
        if (var_s3 != 0) {
            D_800D138A_main++;
            func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
        }
        func_80018044_main(D_800D5A00_main[D_800D138A_main], D_800D5A00_main[0], sp10);
    }

    if (temp_s4 >= 0) {
        if (temp_s1->unk48->unk64[temp_s4].unk50 & 0x70000000) {
            func_8002C4C0_main((HmfData*) temp_s1->unk48, temp_s4, sp10, sp50);
            func_80018044_main(D_800D41B0_main[D_800D5214_main + 1], sp50, sp10);
        }

        func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
        func_80024DF0_main(temp_s1->unk48, temp_s4, &MTXBuf[MTXBufNum], sp10);
        MTXBufNum++;
    }

    if (temp_s1->unk04 != 0) {
        func_80023700_main(arg0, arg1 + temp_s1->unk04);
    }

    if (var_s3 != 0) {
        D_800D138A_main--;
    }

    if (var_s5 != 0) {
        D_800D5214_main--;
    }

    if (temp_s4 >= 0 && temp_s1->unk48 == arg0) {
        if (arg0->unk64[temp_s4].unk58 != 0) {
            func_80023700_main(arg0->unk64[temp_s4].unk58, 0);
        }
    }

    if (temp_s1->unk02 != 0) {
        func_80023700_main(arg0, arg1 + temp_s1->unk02);
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80023AF8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002404C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024354_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024814_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024D94_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024DF0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800250D4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800257BC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800260F0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80029FB4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002A358_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AC5C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AF40_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AFEC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002B104_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002B2AC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C0EC_main);

s32 func_8002C4C0_main(HmfData *arg0, s16 arg1, Matrix4f arg2, Matrix4f arg3) {
    if (!(arg0->unk60[arg1].unk50 & 0x70000000)) {
        return 0;
    }
    func_80018544_main(arg2, arg3);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C520_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C5B8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C834_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C914_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C960_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002CAE4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002CB6C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002CDF4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D094_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D260_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D2D8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D3AC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D3D0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D4B8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D514_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D5B0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DA98_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DD4C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DF2C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DFF8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002E78C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002E8E8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002EAC0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002F60C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FB08_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FB98_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FC14_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FC7C_main);

void func_8002FD48_main(HmfData *arg0) {
    arg0->unkA0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FD50_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FD70_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FD8C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FDCC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FE08_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80030030_main);
