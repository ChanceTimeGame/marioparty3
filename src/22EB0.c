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
    /* 0x1C */ u8 unk1C; /* format */
    /* 0x1D */ u8 unk1D; /* size */
    /* 0x1E */ u8 unk1E_;
    /* 0x1F */ u8 unk1F_; /* flags (MP2 0x1F is the height) */
    /* 0x20 */ char unk20[4];
    /* 0x24 */ u16 unk1E; /* MP2 0x1E (u8): width */
    /* 0x26 */ u16 unk1F; /* MP2 0x1F (u8): height */
    /* 0x28 */ u8* unk28; /* image */
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
    /* 0x09 */ u8 unk0C; /* MP2 0x0C: flags */
    /* 0x0A */ u8 unk0D; /* MP2 0x0D */
} HmfMat; /* size = 0xB (MP2 0xE: MP3 has no unk09[3]) */

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
    /* 0x00 */ char unk12[0x1C]; /* MP2 0x12: name */
    /* 0x1C */ u8 unk2E; /* MP2 0x2E */
    /* 0x1D */ u8 unk2F; /* MP2 0x2F */
    /* 0x1E */ s16 unk00; /* MP2 0x00: material */
    /* 0x20 */ s16 unk02; /* MP2 0x02: alpha */
    /* 0x22 */ s16 unk04; /* MP2 0x04: face count */
    /* 0x24 */ s16 unk24; /* MP3 only (padding in MP2) */
    /* 0x26 */ s16 unk08; /* MP2 0x08 */
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
} HmfPart; /* size = 0x68; MP3 HmfModelData_Unk64_Unk60_Struct. Fields keep MP2 names; MP3 puts the name first */

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
} HmfMotionSlot; /* size 0x18 (MP2 0x1C: MP3 has no unk18) */

/* A motion file loaded whole */
typedef struct HmfMotionFile {
    /* 0x00 */ char unk00[9];
    /* 0x09 */ u8 unk09; /* track count */
    /* 0x0A */ s16 unk0A; /* length */
    /* 0x0C */ s32 unk0C; /* offsets from the file start: track kinds, */
    /* 0x10 */ s32 unk10; /* key frames, */
    /* 0x14 */ s32 unk14; /* key values, */
    /* 0x18 */ s32 unk18[1]; /* and each track (unk09 of them) */
} HmfMotionFile;

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
    /* 0x54 */ HmfData_UnkD0* unk54;
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

void func_800222B0_main(HuAllocFunc arg0, HuFreeFunc arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5) {
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
        if (arg0->unk88[i].unk0C->unk1F_ & 1) {
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

extern s16 D_800C9932_main;
void func_80088700_main(Matrix4f, f32, f32, f32);
void func_80088800_main(Matrix4f, f32, f32, f32);

#ifdef NON_MATCHING
/* Register allocation only: list and the matrix index swap s3/s4 */
void func_80023AF8_main(HmfObj* arg0, s16 arg1) {
    HmfMotionObj* temp_s1;
    s16* list;
    HmfPart* part;
    s32 count;
    s32 temp_v1;
    s32 var_s4;
    s32 var_s7;
    s32 var_s3;
    Matrix4f sp10;
    Matrix4f sp50;
    s32 i;

    temp_s1 = &arg0->unk84[arg1 & 0x7FFF];
    var_s7 = 0;
    var_s4 = 0;

    if (arg0->unk90 == NULL) {
        func_80018044_main(temp_s1->unk58, D_800D5A00_main[0], sp10);
        if (temp_s1->unk1C.x != 1.0f || temp_s1->unk1C.y != 1.0f || temp_s1->unk1C.z != 1.0f) {
            func_80088700_main(sp50, temp_s1->unk1C.x, temp_s1->unk1C.y, temp_s1->unk1C.z);
            D_800D5214_main++;
            func_80018044_main(sp50, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            var_s7 = 1;
        }
    } else {
        if (temp_s1->unk28.x != 0.0f || temp_s1->unk28.y != 0.0f || temp_s1->unk28.z != 0.0f) {
            func_80088800_main(sp10, temp_s1->unk28.x, temp_s1->unk28.y, temp_s1->unk28.z);
            var_s4 = 1;
        }
        if (temp_s1->unk34.x != 0.0f || temp_s1->unk34.y != 0.0f || temp_s1->unk34.z != 0.0f) {
            if (var_s4 == 0) {
                arg0->unkD8(sp10, temp_s1->unk34.x, temp_s1->unk34.y, temp_s1->unk34.z);
            } else {
                arg0->unkD4(sp10, temp_s1->unk34.x, temp_s1->unk34.y, temp_s1->unk34.z);
            }
            var_s4 = 1;
        }
        if (temp_s1->unk40.x != 1.0f || temp_s1->unk40.y != 1.0f || temp_s1->unk40.z != 1.0f) {
            if (var_s4 != 0) {
                func_80017CD0_main(sp10, temp_s1->unk40.x, temp_s1->unk40.y, temp_s1->unk40.z);
            } else {
                func_80088700_main(sp10, temp_s1->unk40.x, temp_s1->unk40.y, temp_s1->unk40.z);
            }
            func_80088700_main(sp50, temp_s1->unk40.x, temp_s1->unk40.y, temp_s1->unk40.z);
            D_800D5214_main++;
            func_80018044_main(sp50, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            var_s7 = 1;
            var_s4 = 1;
        }
        if (var_s4 != 0) {
            D_800D138A_main++;
            func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
        }
        if (D_800C9932_main != 1 && arg0->unk0B == 1) {
            func_8002367C_main(temp_s1->unk58, D_800D5A00_main[D_800D138A_main]);
        }
        func_80018044_main(D_800D5A00_main[D_800D138A_main], D_800D5A00_main[0], sp10);
    }

    func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
    var_s3 = MTXBufNum++;

    count = temp_s1->unk00;
    list = temp_s1->unk50;
    for (i = 0; i < count; i++) {
        temp_v1 = *list++;
        if (temp_v1 & 0x8000) {
            if (temp_v1 != -1) {
                func_80023AF8_main(arg0, temp_v1 & 0x7FFF);
            }
        } else {
            part = &temp_s1->unk54->unk64[temp_v1];
            if (part->unk24 == 1) {
                break;
            }
            if (part->unk50 & 0x70000000) {
                func_8002C4C0_main((HmfData*) temp_s1->unk54, temp_v1, sp10, sp50);
                func_80018044_main(D_800D41B0_main[D_800D5214_main + 1], sp50, sp10);
                func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
                var_s3 = MTXBufNum++;
            }
            func_80024DF0_main(temp_s1->unk54, temp_v1, &MTXBuf[var_s3], sp10);
            if (arg0->unk64[temp_v1].unk58 != NULL) {
                if (arg0 == temp_s1->unk54) {
                    func_80023AF8_main(arg0->unk64[temp_v1].unk58, 0);
                }
            }
        }
    }

    if (var_s4 != 0) {
        D_800D138A_main--;
    }

    if (var_s7 != 0) {
        D_800D5214_main--;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/22EB0", func_80023AF8_main);
#endif

void func_8002404C_main(HmfObj* arg0, s16 arg1) {
    HmfMotionObj* temp_s1;
    s16* list;
    HmfPart* part;
    s16 count;
    s16 temp_v1;
    s16 var_s7;
    s16 var_s3;
    Matrix4f sp10;
    Matrix4f sp50;
    s16 i;

    temp_s1 = &arg0->unk84[arg1 & 0x7FFF];
    var_s7 = 0;

    func_80018044_main(temp_s1->unk58, D_800D5A00_main[0], sp10);
    if (temp_s1->unk1C.x != 1.0f || temp_s1->unk1C.y != 1.0f || temp_s1->unk1C.z != 1.0f) {
        func_80088700_main(sp50, temp_s1->unk1C.x, temp_s1->unk1C.y, temp_s1->unk1C.z);
        D_800D5214_main++;
        func_80018044_main(sp50, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
        var_s7 = 1;
    }

    func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
    var_s3 = MTXBufNum++;

    list = temp_s1->unk50;
    count = temp_s1->unk00;
    for (i = 0; i < count; i++) {
        temp_v1 = *list++;
        if (temp_v1 & 0x8000) {
            if (temp_v1 != -1) {
                func_8002404C_main(arg0, temp_v1 & 0x7FFF);
            }
        } else {
            part = &temp_s1->unk54->unk64[temp_v1];
            if (part->unk24 == 1) {
                break;
            }
            if (part->unk50 & 0x70000000) {
                func_8002C4C0_main((HmfData*) temp_s1->unk54, temp_v1, sp10, sp50);
                func_80018044_main(D_800D41B0_main[D_800D5214_main + 1], sp50, sp10);
                func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
                var_s3 = MTXBufNum++;
            }
            func_80024DF0_main(temp_s1->unk54, temp_v1, &MTXBuf[var_s3], sp10);
            if (arg0->unk64[temp_v1].unk58 != NULL) {
                if (arg0 == temp_s1->unk54) {
                    func_8002404C_main(arg0->unk64[temp_v1].unk58, 0);
                }
            }
        }
    }

    if (var_s7 != 0) {
        D_800D5214_main--;
    }
}

/* wave 2c D */
void HmfLightExec(s16);
void func_800127C4_main(s16 camIndex, Gfx** dispList);
u8 func_8000EF64_main(void* arg0, u16 arg1, s32 arg2, void* arg3, s32 arg4);
void func_8002AF40_main(void);
void func_8002AC5C_main(u16 arg0);
void func_80024814_main(HmfObj* arg0, s16 arg1, HmfDrawRec* arg2);
extern s32 D_800D1F74_main;
extern u8 D_800CD2A0_main;
extern u8 D_800D211C_main;
extern u8 D_800D1F2A_main;

/* A batch of faces drawn with one material and texture (MP2 HmfDrawFace) */
typedef struct HmfDrawFace {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[4];
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ char unk0B;
    /* 0x0C */ HmfMat* unk0C;
    /* 0x10 */ HmfTexRef* unk10;
} HmfDrawFace; /* size 0x14 */

extern HmfPart* D_800B19F0_main;
extern s32 D_800B19F4_main;
extern s16 D_800D0A44_main;
extern s16 D_800CDD66_main;
extern s16 D_800CE1CE_main;
extern s16 D_800D5562_main;
extern u8 D_800A0AD8_main[];
extern HmfDrawFace D_800CD6B0_main[];
void func_800260F0_main(HmfObj*, s32*);
void func_80029FB4_main(HmfObj* arg0, s16 arg1);

/* MP3 only: HmfObj 0xC4 ("unkC8") points to 0x2C-byte records with a position at 0x20; 0xBC
   ("unkC0") names three of them and keeps a copy of their positions that motion tracks can drive */
typedef struct HmfObjC4 {
    /* 0x00 */ char unk00[0x20];
    /* 0x20 */ Vec unk20;
} HmfObjC4; /* size 0x2C */

typedef struct HmfObjBC {
    /* 0x00 */ s16 unk00[3];
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec unk08[3];
} HmfObjBC; /* size 0x2C */

f32 func_8002E78C_main(HmfMotionSlot*, HmfMotionTrack*, f32);
f32 func_8002E8E8_main(HmfMotionSlot*, HmfMotionTrack*, f32);

/* A Hermite key value: the value and its two tangents (MP2 HmfBezierKey) */
typedef struct HmfHermiteKey {
    /* 0x00 */ f32 v;
    /* 0x04 */ f32 in;
    /* 0x08 */ f32 out;
} HmfHermiteKey; /* size = 0xC */

extern s16 D_800A0A78_main;
extern f32 D_800D2120_main;

void func_80024354_main(HmfObj* arg0, s16 arg1) {
    HmfMotionObj* temp_s1;
    HmfPart* temp_s4;
    s32 temp_s2;
    s32 temp_s0;
    s32 var_v1;
    s32 var_a0_2;
    Matrix4f sp10;
    Matrix4f sp50;

    temp_s1 = &arg0->unk84[arg1 & 0x7FFF];
    temp_s2 = *temp_s1->unk50;
    temp_s4 = &temp_s1->unk54->unk64[temp_s2];
    if (temp_s4->unk24 == 1) {
        return;
    }
    temp_s0 = temp_s4->unk50 & 0x70000000;
    var_v1 = 0;
    if (arg0->unk90 == NULL) {
        func_80018044_main(temp_s1->unk58, D_800D5A00_main[0], sp10);
        if (temp_s0 != 0 && (temp_s1->unk1C.x != 1.0f || temp_s1->unk1C.y != 1.0f || temp_s1->unk1C.z != 1.0f)) {
            func_80088700_main(sp50, temp_s1->unk1C.x, temp_s1->unk1C.y, temp_s1->unk1C.z);
            D_800D5214_main++;
            func_80018044_main(sp50, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
        }
    } else {
        if (temp_s1->unk28.x != 0.0f || temp_s1->unk28.y != 0.0f || temp_s1->unk28.z != 0.0f) {
            func_80088800_main(sp10, temp_s1->unk28.x, temp_s1->unk28.y, temp_s1->unk28.z);
            var_v1 = 1;
        }
        if (temp_s1->unk34.x != 0.0f || temp_s1->unk34.y != 0.0f || temp_s1->unk34.z != 0.0f) {
            if (var_v1 == 0) {
                arg0->unkD8(sp10, temp_s1->unk34.x, temp_s1->unk34.y, temp_s1->unk34.z);
            } else {
                arg0->unkD4(sp10, temp_s1->unk34.x, temp_s1->unk34.y, temp_s1->unk34.z);
            }
            var_v1 = 1;
        }
        if (temp_s1->unk40.x != 1.0f || temp_s1->unk40.y != 1.0f || temp_s1->unk40.z != 1.0f) {
            if (var_v1 != 0) {
                func_80017CD0_main(sp10, temp_s1->unk40.x, temp_s1->unk40.y, temp_s1->unk40.z);
            } else {
                func_80088700_main(sp10, temp_s1->unk40.x, temp_s1->unk40.y, temp_s1->unk40.z);
            }
            if (temp_s0 != 0) {
                func_80088700_main(sp50, temp_s1->unk40.x, temp_s1->unk40.y, temp_s1->unk40.z);
                D_800D5214_main++;
                func_80018044_main(sp50, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            }
            var_v1 = 1;
        }
        if (var_v1 != 0) {
            D_800D138A_main++;
            func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
        }
        if (D_800C9932_main != 1 && arg0->unk0B == 1) {
            func_8002367C_main(temp_s1->unk58, D_800D5A00_main[D_800D138A_main]);
        }
        func_80018044_main(D_800D5A00_main[D_800D138A_main], D_800D5A00_main[0], sp10);
    }

    func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
    var_a0_2 = MTXBufNum++;
    if (temp_s4->unk50 & 0x70000000) {
        func_8002C4C0_main((HmfData*) temp_s1->unk54, temp_s2, sp10, sp50);
        func_80018044_main(D_800D41B0_main[D_800D5214_main + 1], sp50, sp10);
        func_800898F0_main((Mtx*) sp10, &MTXBuf[MTXBufNum]);
        var_a0_2 = MTXBufNum++;
    }
    func_80024DF0_main(temp_s1->unk54, temp_s2, &MTXBuf[var_a0_2], sp10);
    if (arg0->unk64[temp_s2].unk58 != NULL && arg0 == temp_s1->unk54) {
        func_80023AF8_main(arg0->unk64[temp_s2].unk58, 0);
    }
}

void func_8002AFEC_main(HmfObj*, s32, s16);
void func_80033694_main(HmfObj*);

void func_80024814_main(HmfObj* arg0, s16 arg1, HmfDrawRec* arg2) {
    HmfPart* temp_s4;
    s32 temp_v1;

    temp_v1 = arg0->unk64[arg1].unk50;
    if (temp_v1 & 0x06000000) {
        if (D_800C9940_main == 0) {
            arg0->unk64[arg1].unk50 = temp_v1 & ~0x06000000;

            gSPSegment(gMainGfxPos++, 0x01, osVirtualToPhysical(D_800D5308_main));

            func_80024814_main(arg0, arg1, arg2);

            arg0->unk64[arg1].unk50 = temp_v1;
        } else {
            temp_s4 = &arg0->unk64[arg1];
            func_8002AFEC_main(arg0, temp_s4->unk50 & ~0x06000000, arg1);

            gSPSegment(gMainGfxPos++, 0x01, osVirtualToPhysical(arg0->unk44[D_800D2008_main]));
            if (temp_s4->unk5C != NULL) {
                if ((D_800D0440_main != temp_s4->unk5C && temp_s4->unk5C != (HmfTexRef*) -1)) {
                    gSPDisplayList(gMainGfxPos++, temp_s4->unk64);
                }
                D_800D0440_main = temp_s4->unk60;
            } else {
                D_800D0440_main = NULL;
            }
            gSPDisplayList(gMainGfxPos++, HMF_DL(arg0)[arg1]);

            func_8002AFEC_main(arg0, temp_s4->unk50, arg1);

            gSPMatrix(gMainGfxPos++, osVirtualToPhysical(arg2->unk44), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gMainGfxPos++, (*arg0->unkCC)[arg1]);
            return;
        }
    }

    temp_s4 = &arg0->unk64[arg1];

    func_8002AFEC_main(arg0, temp_s4->unk50, arg1);

    if (temp_s4->unk50 & 0x40000) {
        func_80033694_main(arg0);
    }

    if (temp_s4->unk02 != -1 || (arg0->unk9C != NULL && arg0->unk8C[temp_s4->unk00].unk0C & 4)) {
        HmfMat* temp_a0 = &arg0->unk8C[temp_s4->unk00];
        gDPSetPrimColor(gMainGfxPos++, 0, 0, temp_a0->unk05[0], temp_a0->unk05[1], temp_a0->unk05[2], temp_s4->unk02);
    }

    if (D_800C9940_main & 0x10000) {
        gDPSetEnvColor(gMainGfxPos++, arg0->unk06, arg0->unk07, arg0->unk08, arg0->unk09);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, arg0->unk02, arg0->unk03, arg0->unk04, arg0->unk05);
    }

    if (D_800C9940_main & 1) {
        if (HMF_DL(arg0)[arg1] == NULL) {
            return;
        }
        if (temp_s4->unk5C != NULL) {
            if ((D_800D0440_main != temp_s4->unk5C && temp_s4->unk5C != (HmfTexRef*) -1)) {
                gSPDisplayList(gMainGfxPos++, temp_s4->unk64);
            }
            D_800D0440_main = temp_s4->unk60;
        } else {
            D_800D0440_main = NULL;
        }
        gSPSegment(gMainGfxPos++, 0x01, osVirtualToPhysical(arg0->unk44[D_800D2008_main]));
        gSPDisplayList(gMainGfxPos++, HMF_DL(arg0)[arg1]);
    } else {
        gSPSegment(gMainGfxPos++, 0x01, osVirtualToPhysical(D_800D5308_main));
        func_800257BC_main(arg0, arg1);
    }

    if (gMainGfxPos >= &D_800D1FF8_main[D_800D5306_main * 8]) {
        osSyncPrintf("GfxMax Over\n");
    }
}

void func_80089980_main(Matrix4f, void*);

void func_80024D94_main(HmfObj* arg0, s16 arg1, void* arg2) {
    Matrix4f sp10;

    func_80089980_main(sp10, arg2);
    func_80024DF0_main(arg0, arg1, arg2, sp10);
}

#define SQ(x) ((x) * (x))

void func_80024DF0_main(HmfObj* arg0, s16 arg1, void* arg2, Matrix4f arg3) {
    f32 temp_f4;
    f32 temp_f0;
    f32 temp_f2;
    f32 var_f12;
    u32 temp_v1;
    s16 temp_v0;
    s16 var_a1;
    s16 temp_s4;
    HmfLayerEnt* temp_a0;
    HmfLayerEnt* temp_s0;
    HmfDrawRec* rec;

    temp_s4 = arg0->unk00;
    temp_v0 = D_800D6AC8_main[temp_s4];

    if (temp_v0 >= D_800A0AD0_main[temp_s4]) {
        osSyncPrintf("Model Object Entry Over!! UCODE%d\n", temp_s4);
        return;
    }

    temp_s0 = D_800D2070_main[temp_s4];

    if (arg0->unk64[arg1].unk50 & 0x81210000) {
        temp_f4 = arg3[3][0];
        temp_f0 = arg3[3][1];
        temp_f2 = arg3[3][2];

        var_f12 = SQ(temp_f4) + SQ(temp_f0) + SQ(temp_f2);
        if (var_f12 != 0.0f) {
            var_f12 = HuSqrtf(var_f12);
        } else {
            var_f12 = 0.0f;
        }

        temp_v1 = arg0->unk64[arg1].unk50;
        if (temp_v1 & 0x80210000) {
            var_f12 = 100000.0f - var_f12;
        } else if (temp_v1 & 0x01000000) {
            var_f12 = -var_f12;
        }

        for (var_a1 = temp_s0->unk00; temp_s0[var_a1].unk00 != 0; var_a1 = temp_s0[var_a1].unk00) {
            if (var_f12 < temp_s0[var_a1].unk04) {
                break;
            }
        }
    } else {
        var_a1 = temp_s0->unk00;
        var_f12 = 0.0f;
    }

    arg0->unk64[arg1].unk2F = temp_v0;
    var_a1 = temp_s0[var_a1].unk01;

    temp_a0 = &temp_s0[temp_v0];
    temp_a0->unk01 = var_a1;
    temp_a0->unk00 = temp_s0[var_a1].unk00;

    temp_s0[var_a1].unk00 = temp_v0;
    temp_s0[temp_a0->unk00].unk01 = temp_v0;

    D_800D6AC8_main[temp_s4]++;

    temp_a0->unk04 = var_f12;
    rec = &D_800CC0BC_main[D_800D5564_main];
    temp_a0->unk02 = D_800D5564_main++;
    rec->unk44 = arg2;
    rec->unk48 = arg0;
    rec->unk00 = arg1;
    rec->unk50 = D_800C9940_main;
    rec->unk4C = arg0->unk64[arg1].unk50;
    rec->unk54 = arg0->unkD0;
}

Gfx* func_800250D4_main(u16 arg0, Gfx* arg1, Gfx* arg2) {
    s16 sp2E;
    s16 sp36;
    u8 sp3F;
    u8 sp47;
    u8 sp4F;
    Gfx* var_s7;
    s32 var_fp;
    HmfDrawRec* temp_s1;
    HmfObj* temp_s2;
    HmfLayerEnt* var_s3;
    s16 var_s4;
    s16 i;
    s16 j;
    s16 k;
    s16 n;

    var_s7 = gMainGfxPos;

    if (arg2 != NULL) {
        gSPDisplayList(gMainGfxPos++, arg2);
    }

    var_fp = (D_800CE19A_main != 0);

    HmfLightExec(arg0);

    sp3F = D_800CB8A8_main->l.col[0];
    sp47 = D_800CB8A8_main->l.col[1];
    sp4F = D_800CB8A8_main->l.col[2];
    sp2E = D_800CE1D4_main->unk00 + 1;

    for (i = 0, sp36 = 0; i < 8; i++) {
        if (D_800D6AC8_main[i] == 2) {
            continue;
        }

        if (var_fp != 0) {
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            func_8000EF64_main(var_s7, D_800CE19A_main, 0, NULL, 0);
            var_s7 = gMainGfxPos;
        }

        func_800127C4_main(arg0, &gMainGfxPos);

        sp36++;
        var_fp = 1;
        D_800CE19A_main = i;

        gSPDisplayList(gMainGfxPos++, arg1);

        D_800CE2F0_main = 0xFFFFFFFF;
        D_800D1FD0_main = 0xFFFFFFFF;
        D_800D1F74_main = 0xFFFFFFFF;
        D_800D0440_main = NULL;

        gSPNumLights(gMainGfxPos++, sp2E - 1);

        for (j = 1; j < sp2E; j++) {
            gSPLight(gMainGfxPos++, D_800CB8A8_main + j, j);
        }

        gSPLight(gMainGfxPos++, D_800CB8A8_main, sp2E);

        D_800CD2A0_main = 255;
        D_800D211C_main = 255;
        D_800D1F2A_main = 255;
        var_s4 = -1;

        func_8002AF40_main();

        var_s3 = &D_800D2070_main[i][D_800D2070_main[i]->unk00];
        n = D_800D6AC8_main[i];
        for (k = 2; k < n; k++) {
            temp_s1 = &D_800CC0BC_main[var_s3->unk02];
            temp_s2 = temp_s1->unk48;

            D_800D1F78_main = sp3F;
            D_800D1FE2_main = sp47;
            D_800CDA76_main = sp4F;
            D_800CDA86_main = 0;
            D_800CE170_main = 0;
            D_800CDD5A_main = 0;

            func_8002D094_main(&gMainGfxPos, sp2E,
                (D_800D1F78_main << 0x18) + (D_800D1FE2_main << 0x10) + (D_800CDA76_main << 8));
            func_8002D094_main(&gMainGfxPos, 1, 0);

            if (temp_s1->unk54 != NULL) {
                gSPLight(gMainGfxPos++, &temp_s2->unkD0->unk08[D_800D2008_main], 2);
            }

            if (var_s4 != temp_s1->unk4C) {
                var_s4 = temp_s1->unk4C;
                func_8002AC5C_main(var_s4);
            }

            gSPMatrix(gMainGfxPos++, osVirtualToPhysical(temp_s1->unk44), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            D_800C9940_main = temp_s1->unk50;
            func_80024814_main(temp_s2, temp_s1->unk00, temp_s1);

            if (temp_s1->unk54 != NULL) {
                gSPLight(gMainGfxPos++, &D_800CB8A8_main[2], 2);
            }

            var_s3 = &D_800D2070_main[i][var_s3->unk00];
            if (var_s3->unk00 == 0) {
                break;
            }
        }
    }

    if (sp36 == 0) {
        gSPDisplayList(gMainGfxPos++, arg1);
        gSPNumLights(gMainGfxPos++, sp2E - 1);

        for (j = 1; j < sp2E; j++) {
            gSPLight(gMainGfxPos++, D_800CB8A8_main + j, j);
        }

        gSPLight(gMainGfxPos++, D_800CB8A8_main, sp2E);
    }

    return var_s7;
}

/* MP2 func_800329E8_335E8 (NON_MATCHING the same way): batch a part's faces and their vertices. MP3 adds
   a flush after a texture with flag bit 0 and records the face's unk01 bytes.
   Register allocation (masked 100, 712 vs 713): retail spills the batch limit as a halfword and the
   extended arg1 to the stack; here loop motion hoists the limit's zero-extension (word spill) and
   keeps arg1 in s8, so every callee-saved register shifts */
#ifdef NON_MATCHING
void func_800257BC_main(HmfObj* arg0, s16 arg1) {
    s16 i;
    s16 count;
    u16 limit;
    HmfMat* curMat;
    HmfTexRef* curTex;
    s16 n;
    s16 var_s4;
    s16 var_s6;
    s16 var_t1;
    s16 temp_f2;
    s16 temp_f2_2;
    s16 var_a1;
    s16 var_a2;
    s16 var_a1_2;
    s32 temp_v0;
    s32 record;
    s32 texFlush;
    u8* var_a3;
    HmfFaceRec* temp_s1;
    HmfTexRef* var_s0;
    HmfMat* temp_s2;
    HmfTex* tex;
    HmfDrawFace* temp_t2;
    HmfVtx* var_a0;
    ColVtx* temp_t0;

    D_800B19F0_main = &arg0->unk64[arg1];
    count = D_800B19F0_main->unk04;
    D_800D0A44_main = 0;
    D_800B19F4_main = -1;
    D_800CDD66_main = D_800CE1CE_main;
    temp_s1 = D_800B19F0_main->unk54;
    curMat = &arg0->unk8C[temp_s1->unk30];
    temp_v0 = D_800B19F0_main->unk50 &= ~0x00040000;
    record = (temp_v0 & 0x06020000) == 0x20000;

    if ((D_800C9940_main & 0x2001) == 0x2001) {
        func_80029FB4_main(arg0, arg1);
    }

    var_s6 = var_s4 = temp_s1->unk00 & 0x80;
    if (var_s4 != 0) {
        gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
    } else {
        gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
    }

    if (temp_s1->unk32 >= 0) {
        curTex = &arg0->unk88[temp_s1->unk32];
    } else {
        curTex = (HmfTexRef*) -1;
    }
    limit = D_800A0AD8_main[(D_800C9940_main & 0x1C00) >> 10];
    texFlush = 0;

    for (i = 0; i < count; i++) {
        temp_s1 = &arg0->unk64[arg1].unk54[i];
        if (temp_s1->unk00 >= 3) {
            temp_s2 = &arg0->unk8C[temp_s1->unk30];

            if (temp_s1->unk32 >= 0) {
                var_s0 = &arg0->unk88[temp_s1->unk32];
            } else {
                var_s0 = (HmfTexRef*) -1;
            }

            var_s4 = temp_s1->unk00 & 0x80;

            if (((limit < D_800CE1CE_main - D_800CDD66_main) | (curMat != temp_s2)) || curTex != var_s0
                || ((D_800D0A44_main >= 48) | (var_s4 != var_s6)) || texFlush != 0) {
                curMat = temp_s2;
                curTex = var_s0;
                func_800260F0_main(arg0, &D_800B19F0_main->unk50);
                if (var_s4 != var_s6) {
                    if (var_s4 != 0) {
                        gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
                    } else {
                        gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
                    }
                    var_s6 = var_s4;
                }
                D_800D0A44_main = 0;
                texFlush = 0;
            }

            temp_t2 = &D_800CD6B0_main[D_800D0A44_main];
            n = temp_t2->unk00 = temp_s1->unk00 & 0x7F;

            if (n == 2) {
                continue;
            }

            temp_t2->unk0C = temp_s2;
            temp_t2->unk10 = var_s0;

            if (var_s0 != (HmfTexRef*) -1) {
                tex = var_s0->unk0C;
                var_a1 = tex->unk1E << 5;
                var_a2 = tex->unk1F << 5;
                if (tex->unk1F_ & 1) {
                    texFlush = 1;
                }
            } else {
                var_a1 = var_a2 = 0;
            }

            if (record) {
                arg0->unkB4[D_800D5562_main].unk00 = n;
                arg0->unkB4[D_800D5562_main].unk01[0] = temp_s1->unk01[0];
                arg0->unkB4[D_800D5562_main].unk01[1] = temp_s1->unk01[1];
                arg0->unkB4[D_800D5562_main].unk01[2] = temp_s1->unk01[2];
            }

            for (var_t1 = 0; var_t1 < n; var_t1++) {
                temp_t0 = &arg0->unk54[temp_s1->unk04[var_t1]];

                if (var_s4 != 0) {
                    var_a3 = arg0->unk8C[temp_s1->unk2C[var_t1]].unk05;
                } else {
                    var_a3 = &arg0->unk58[temp_s1->unk04[var_t1] * 3];
                }

                temp_f2 = var_a1 * temp_s1->unk0C[var_t1];
                temp_f2_2 = var_a2 * temp_s1->unk1C[var_t1];

                var_a0 = &D_800D5308_main[D_800CE1CE_main - 1];
                if (temp_v0 & 0x20000) {
                    if (record) {
                        arg0->unkB4[D_800D5562_main].unk02[var_t1] = D_800CE1CE_main;
                    }
                    var_a1_2 = D_800CDD66_main;
                } else {
                    for (var_a1_2 = D_800CE1CE_main - 1; var_a1_2 >= D_800CDD66_main; var_a1_2--, var_a0--) {
                        if (var_a0->unk00 == temp_t0->x && var_a0->unk02 == temp_t0->y && var_a0->unk04 == temp_t0->z
                            && (s8) var_a0->unk0C[0] == (s8) var_a3[0] && (s8) var_a0->unk0C[1] == (s8) var_a3[1] && (s8) var_a0->unk0C[2] == (s8) var_a3[2]
                            && var_a0->unk08 == temp_f2 && var_a0->unk0A == temp_f2_2) {
                            break;
                        }
                    }
                }

                if (var_a1_2 <= D_800CDD66_main) {
                    var_a0 = &D_800D5308_main[D_800CE1CE_main];
                    var_a0->unk00 = temp_t0->x;
                    var_a0->unk02 = temp_t0->y;
                    var_a0->unk04 = temp_t0->z;
                    var_a0->unk0C[0] = var_a3[0];
                    var_a0->unk0C[1] = var_a3[1];
                    var_a0->unk0C[2] = var_a3[2];
                    var_a0->unk08 = temp_f2;
                    var_a0->unk0A = temp_f2_2;
                    var_a0->unk0F = 255;
                    temp_t2->unk02[var_t1] = D_800CE1CE_main - D_800CDD66_main;
                    temp_t2->unk0A = var_s4;
                    if (arg0->unk60 != NULL) {
                        arg0->unk60[temp_s1->unk04[var_t1]] = D_800CE1CE_main;
                    }
                    D_800CE1CE_main++;
                } else {
                    temp_t2->unk02[var_t1] = var_a1_2 - D_800CDD66_main;
                    if (arg0->unk60 != NULL) {
                        arg0->unk60[temp_s1->unk04[var_t1]] = var_a1_2;
                    }
                }
            }

            if (record) {
                D_800D5562_main++;
            }

            D_800D0A44_main++;
        }
    }

    if (D_800CE1CE_main != D_800CDD66_main) {
        if (var_s4 != var_s6) {
            if (var_s4 != 0) {
                gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
            } else {
                gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
            }
        }

        func_800260F0_main(arg0, &D_800B19F0_main->unk50);
        if (var_s4 != 0) {
            gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/22EB0", func_800257BC_main);
#endif

/* wave 2c C */
/* A batch of faces drawn with one material and texture (MP2 HmfDrawFace) */
typedef struct HmfDrawFace {
    /* 0x00 */ s16 unk00; /* 3: triangle, else quadrangle */
    /* 0x02 */ s16 unk02[4];
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ HmfMat* unk0C;
    /* 0x10 */ HmfTexRef* unk10;
} HmfDrawFace; /* size 0x14 */

extern HmfDrawFace D_800CD6B0_main[];
extern s16 D_800D0A44_main;
extern s32 D_800B19F4_main;
extern s16 D_800CDD66_main;
extern u32 D_800C952C_main;
extern u32 D_800CCF88_main;
extern u32 D_800CD2FC_main;
extern u32 D_800D1FFC_main;
extern u32 D_800D6A20_main;
void func_8002A358_main(HmfMat*, HmfTexRef*, s32);

#define INTEGER_LOG2(x) ((x) <= 2 ? 1 : (x) <= 4 ? 2 : (x) <= 8 ? 3 : (x) <= 16 ? 4 : (x) <= 32 ? 5 : (x) <= 64 ? 6 : (x) <= 128 ? 7 : (x) <= 256 ? 8 : 9)

/* MP2 func_80033288_33E88: flush the batched faces (D_800CD6B0_main) of one material: material
   colours, texture and palette loads (a texture with flag 1 loads only the tile its vertices'
   texture coordinates cover), then the vertices and triangles */
void func_800260F0_main(HmfObj* arg0, s32* arg1) {
    HmfDrawFace* face;
    HmfTex* tex;
    HmfMat* mat;
    HmfTexRef* ref;
    Gfx** dlp;
    HmfVtx* vtx;
    u8* img;
    u16* pal;
    u16 r;
    u16 g;
    u16 b;
    s16 sMin;
    s16 sMax;
    s16 tMin;
    s16 tMax;
    s16 s;
    s16 t;
    s16 sub; /* untextured: a light colour changed; textured: load a sub-tile */
    s16 i;

    if (D_800D0A44_main == 0) {
        return;
    }

    /* retail's D_800CD6BC_main is D_800CD6B0_main[0].unk0C under a second name */
    mat = D_800CD6B0_main[0].unk0C;
    ref = D_800CD6B0_main[0].unk10;

    if (!(*arg1 & 0x06000000)) {
        func_8002A358_main(mat, ref, *arg1);
        b = 0;
        g = 0;
        r = 0;

        if (ref == (HmfTexRef*) -1) {
            sub = 0;
            if (D_800C9940_main & 0x200) {
                r = mat->unk01[0] * D_800D5410_main;
                if (r > 255) {
                    r = 255;
                }
                g = mat->unk01[1] * D_800D5410_main;
                if (g > 255) {
                    g = 255;
                }
                b = mat->unk01[2] * D_800D5410_main;
                if (b > 255) {
                    b = 255;
                }

                if (D_800D1F78_main != r || D_800D1FE2_main != g || D_800CDA76_main != b) {
                    D_800D1F78_main = r;
                    D_800D1FE2_main = g;
                    D_800CDA76_main = b;
                    func_8002D094_main(&gMainGfxPos, D_800CE1D4_main->unk00 + 1,
                        (D_800D1F78_main << 24) + (D_800D1FE2_main << 16) + (D_800CDA76_main << 8));
                    sub = 1;
                }
            }

            r = mat->unk05[0] * D_800D51FC_main;
            if (r > 255) {
                r = 255;
            }
            g = mat->unk05[1] * D_800D51FC_main;
            if (g > 255) {
                g = 255;
            }
            b = mat->unk05[2] * D_800D51FC_main;
            if (b > 255) {
                b = 255;
            }

            if (D_800CDD5A_main != r || D_800CE170_main != g || D_800CDA86_main != b) {
                D_800CDD5A_main = r;
                D_800CE170_main = g;
                D_800CDA86_main = b;
                func_8002D094_main(&gMainGfxPos, 1, (D_800CDD5A_main << 24) + (D_800CE170_main << 16) + (D_800CDA86_main << 8));
                sub = 1;
            }

            if (sub) {
                gDPPipeSync(gMainGfxPos++);
            }
        } else {
            tex = ref->unk0C;
            if (tex->unk1F_ & 1) {
                tMin = 32000;
                sMin = 32000;
                tMax = -32000;
                sMax = -32000;
                vtx = &D_800D5308_main[D_800CDD66_main];
                for (i = 0; i < D_800CE1CE_main - D_800CDD66_main; i++, vtx++) {
                    t = vtx->unk0A;
                    s = vtx->unk08;
                    if (sMin > s) {
                        sMin = s;
                    }
                    if (sMax < s) {
                        sMax = s;
                    }
                    if (tMin > t) {
                        tMin = t;
                    }
                    if (tMax < t) {
                        tMax = t;
                    }
                }
                sMin >>= 5;
                tMin >>= 5;
                sMax >>= 5;
                tMax >>= 5;
                sub = 1;
            } else {
                tMin = 0;
                tMax = 0;
                sMin = 0;
                sMax = 0;
                sub = 0;
            }

            switch (ref->unk00) {
                case 42:
                case 43:
                    r = mat->unk01[0] * D_800D5410_main;
                    if (r > 255) {
                        r = 255;
                    }
                    g = mat->unk01[1] * D_800D5410_main;
                    if (g > 255) {
                        g = 255;
                    }
                    b = mat->unk01[2] * D_800D5410_main;
                    if (b > 255) {
                        b = 255;
                    }
                    break;
                case 41:
                    r = D_800D5410_main * 255.0f;
                    if (r > 255) {
                        r = 255;
                    }
                    g = b = r;
                    break;
            }

            if ((D_800C9940_main & 0x200) && (D_800D1F78_main != r || D_800D1FE2_main != g || D_800CDA76_main != b)) {
                D_800D1F78_main = r;
                D_800D1FE2_main = g;
                D_800CDA76_main = b;
                func_8002D094_main(&gMainGfxPos, D_800CE1D4_main->unk00 + 1,
                    (D_800D1F78_main << 24) + (D_800D1FE2_main << 16) + (D_800CDA76_main << 8));
            }

            switch (ref->unk00) {
                case 43:
                    r = ref->unk05 * D_800D51FC_main;
                    if (r > 255) {
                        r = 255;
                    }
                    g = ref->unk06 * D_800D51FC_main;
                    if (g > 255) {
                        g = 255;
                    }
                    b = ref->unk07 * D_800D51FC_main;
                    if (b > 255) {
                        b = 255;
                    }
                    break;
                case 41:
                    r = D_800D51FC_main * 255.0f;
                    if (r > 255) {
                        r = 255;
                    }
                    b = r;
                    g = b;
                    break;
                default:
                    r = mat->unk05[0] * D_800D51FC_main;
                    if (r > 255) {
                        r = 255;
                    }
                    g = mat->unk05[1] * D_800D51FC_main;
                    if (g > 255) {
                        g = 255;
                    }
                    b = mat->unk05[2] * D_800D51FC_main;
                    if (b > 255) {
                        b = 255;
                    }
                    break;
            }

            if (D_800CDD5A_main != r || D_800CE170_main != g || D_800CDA86_main != b) {
                D_800CDD5A_main = r;
                D_800CE170_main = g;
                D_800CDA86_main = b;
                func_8002D094_main(&gMainGfxPos, 1, (D_800CDD5A_main << 24) + (D_800CE170_main << 16) + (D_800CDA86_main << 8));
            }

            if (sub || (ref != D_800D0440_main && !(*arg1 & 0x08000000))) {
                D_800D0440_main = ref;

                if (ref->unk03 != -1) {
                    img = (u8*) (ref->unk03 << 24); /* a segmented address */
                    *arg1 |= 0x40000;
                    dlp = &gMainGfxPos;
                    D_800D5544_main = 1;
                } else {
                    img = tex->unk28;
                    if (D_800D5544_main == 0 && !(D_800C9940_main & 0x2000) && !sub) {
                        dlp = &D_800D6A88_main;
                        D_800CC0AC_main = D_800D0440_main;
                    } else {
                        dlp = &gMainGfxPos;
                    }
                }

                if (tex->unk1C != G_IM_FMT_CI) {
                    if (D_800B19F4_main != G_TT_NONE) {
                        D_800B19F4_main = G_TT_NONE;
                        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
                    }

                    if (tex->unk1D != G_IM_SIZ_4b) {
                        if (tex->unk1F_ & 1) {
                            gDPSetTextureImage((*dlp)++, tex->unk1C, tex->unk1D, tex->unk1E, img);
                            switch (tex->unk1D) {
                                case G_IM_SIZ_16b:
                                    D_800CD2FC_main = G_IM_SIZ_16b_TILE_BYTES;
                                    D_800D6A20_main = G_IM_SIZ_16b_LINE_BYTES;
                                    break;
                                case G_IM_SIZ_8b:
                                    D_800CD2FC_main = G_IM_SIZ_8b_TILE_BYTES;
                                    D_800D6A20_main = G_IM_SIZ_8b_LINE_BYTES;
                                    break;
                                case G_IM_SIZ_4b:
                                    D_800CD2FC_main = G_IM_SIZ_4b_TILE_BYTES;
                                    D_800D6A20_main = G_IM_SIZ_4b_LINE_BYTES;
                                    break;
                                default:
                                    D_800CD2FC_main = G_IM_SIZ_32b_TILE_BYTES;
                                    D_800D6A20_main = G_IM_SIZ_32b_LINE_BYTES;
                                    break;
                            }
                            gDPSetTile((*dlp)++, tex->unk1C, tex->unk1D, (((sMax - sMin) + 1) * D_800CD2FC_main + 7) >> 3, 0x0000,
                                G_TX_LOADTILE, 0, ref->unk02, INTEGER_LOG2(tex->unk1F), G_TX_NOLOD,
                                ref->unk01, INTEGER_LOG2(tex->unk1E), G_TX_NOLOD);
                            gDPLoadSync((*dlp)++);
                            gDPLoadTile((*dlp)++, G_TX_LOADTILE, sMin << 2, tMin << 2, sMax << 2, tMax << 2);
                            gDPPipeSync((*dlp)++);
                            gDPSetTile((*dlp)++, tex->unk1C, tex->unk1D, (((sMax - sMin) + 1) * D_800D6A20_main + 7) >> 3, 0x0000,
                                G_TX_RENDERTILE, 0, ref->unk02, INTEGER_LOG2(tex->unk1F), G_TX_NOLOD,
                                ref->unk01, INTEGER_LOG2(tex->unk1E), G_TX_NOLOD);
                            gDPSetTileSize((*dlp)++, G_TX_RENDERTILE, sMin << 2, tMin << 2, sMax << 2, tMax << 2);
                        } else {
                            switch (tex->unk1D) {
                                case G_IM_SIZ_16b:
                                    D_800CCF88_main = G_IM_SIZ_16b_LOAD_BLOCK;
                                    D_800CD2FC_main = G_IM_SIZ_16b_INCR;
                                    D_800D6A20_main = G_IM_SIZ_16b_BYTES;
                                    D_800C952C_main = G_IM_SIZ_16b_LINE_BYTES;
                                    D_800D1FFC_main = G_IM_SIZ_16b_SHIFT;
                                    break;
                                case G_IM_SIZ_8b:
                                    D_800CCF88_main = G_IM_SIZ_8b_LOAD_BLOCK;
                                    D_800CD2FC_main = G_IM_SIZ_8b_INCR;
                                    D_800D6A20_main = G_IM_SIZ_8b_BYTES;
                                    D_800C952C_main = G_IM_SIZ_8b_LINE_BYTES;
                                    D_800D1FFC_main = G_IM_SIZ_8b_SHIFT;
                                    break;
                                case G_IM_SIZ_4b:
                                    D_800CCF88_main = G_IM_SIZ_4b_LOAD_BLOCK;
                                    D_800CD2FC_main = G_IM_SIZ_4b_INCR;
                                    D_800D6A20_main = G_IM_SIZ_4b_BYTES;
                                    D_800C952C_main = G_IM_SIZ_4b_LINE_BYTES;
                                    D_800D1FFC_main = G_IM_SIZ_4b_SHIFT;
                                    break;
                                default:
                                    D_800CCF88_main = G_IM_SIZ_32b_LOAD_BLOCK;
                                    D_800CD2FC_main = G_IM_SIZ_32b_INCR;
                                    D_800D6A20_main = G_IM_SIZ_32b_BYTES;
                                    D_800C952C_main = G_IM_SIZ_32b_LINE_BYTES;
                                    D_800D1FFC_main = G_IM_SIZ_32b_SHIFT;
                                    break;
                            }

                            gDPSetTextureImage((*dlp)++, tex->unk1C, D_800CCF88_main, 1, img);
                            gDPSetTile((*dlp)++, tex->unk1C, D_800CCF88_main, 0, 0x0000, G_TX_LOADTILE, 0,
                                ref->unk02, INTEGER_LOG2(tex->unk1F), G_TX_NOLOD,
                                ref->unk01, INTEGER_LOG2(tex->unk1E), G_TX_NOLOD);
                            gDPLoadSync((*dlp)++);
                            gDPLoadBlock((*dlp)++, G_TX_LOADTILE, 0, 0,
                                ((tex->unk1E * tex->unk1F + D_800CD2FC_main) >> D_800D1FFC_main) - 1,
                                CALC_DXT(tex->unk1E, D_800D6A20_main));
                            gDPPipeSync((*dlp)++);
                            gDPSetTile((*dlp)++, tex->unk1C, tex->unk1D, (tex->unk1E * D_800C952C_main + 7) >> 3, 0x0000,
                                G_TX_RENDERTILE, 0, ref->unk02, INTEGER_LOG2(tex->unk1F), G_TX_NOLOD,
                                ref->unk01, INTEGER_LOG2(tex->unk1E), G_TX_NOLOD);
                            gDPSetTileSize((*dlp)++, G_TX_RENDERTILE, 0, 0, (tex->unk1E - 1) * 4, (tex->unk1F - 1) * 4);
                        }
                    } else if (tex->unk1E < 16) {
                        gDPLoadTextureTile_4b((*dlp)++, img, tex->unk1C, tex->unk1E, tex->unk1F,
                            0, 0, tex->unk1E, tex->unk1F, 0, ref->unk01, ref->unk02,
                            INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F), G_TX_NOLOD, G_TX_NOLOD);
                    } else if (tex->unk1F_ & 1) {
                        gDPLoadTextureTile_4b((*dlp)++, img, tex->unk1C, tex->unk1E, tex->unk1F,
                            sMin, tMin, sMax + 1, tMax + 1, 0, ref->unk01, ref->unk02,
                            INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F), G_TX_NOLOD, G_TX_NOLOD);
                    } else {
                        gDPLoadTextureBlock_4b((*dlp)++, img, tex->unk1C, tex->unk1E, tex->unk1F, 0,
                            ref->unk01, ref->unk02, INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F),
                            G_TX_NOLOD, G_TX_NOLOD);
                    }
                } else {
                    if (ref->unk04 != -1) {
                        pal = (u16*) (ref->unk04 << 24); /* a segmented address */
                        *arg1 |= 0x40000;
                        dlp = &gMainGfxPos;
                        D_800D5544_main = 1;
                    } else {
                        pal = tex->unk30->unk28;
                        if (D_800D5544_main == 0 && !(D_800C9940_main & 0x2000) && !sub) {
                            dlp = &D_800D6A88_main;
                            D_800CC0AC_main = D_800D0440_main;
                        } else {
                            dlp = &gMainGfxPos;
                        }
                    }

                    if (D_800B19F4_main != G_TT_RGBA16) {
                        D_800B19F4_main = G_TT_RGBA16;
                        gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
                    }

                    if (tex->unk30->unk1E < 17) {
                        gDPLoadTLUT_pal16((*dlp)++, 0, pal);

                        if (tex->unk1E < 16) {
                            gDPLoadTextureTile_4b((*dlp)++, img, tex->unk1C, tex->unk1E, tex->unk1F,
                                0, 0, tex->unk1E, tex->unk1F, 0, ref->unk01, ref->unk02,
                                INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F), G_TX_NOLOD, G_TX_NOLOD);
                        } else if (tex->unk1F_ & 1) {
                            gDPLoadTextureTile_4b((*dlp)++, img, tex->unk1C, tex->unk1E, tex->unk1F,
                                sMin, tMin, sMax + 1, tMax + 1, 0, ref->unk01, ref->unk02,
                                INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F), G_TX_NOLOD, G_TX_NOLOD);
                        } else {
                            gDPLoadTextureBlock_4b((*dlp)++, img, tex->unk1C, tex->unk1E, tex->unk1F, 0,
                                ref->unk01, ref->unk02, INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F),
                                G_TX_NOLOD, G_TX_NOLOD);
                        }
                    } else {
                        gDPLoadTLUT_pal256((*dlp)++, pal);

                        if (tex->unk1E < 8) {
                            /* retail sends this one to the main list even when dlp is the second one */
                            dlp = &gMainGfxPos;
                            gDPLoadTextureTile((*dlp)++, img, tex->unk1C, G_IM_SIZ_8b, tex->unk1E, tex->unk1F,
                                0, 0, tex->unk1E, tex->unk1F, 0, ref->unk01, ref->unk02,
                                INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F), G_TX_NOLOD, G_TX_NOLOD);
                        } else if (tex->unk1F_ & 1) {
                            gDPLoadTextureTile((*dlp)++, img, tex->unk1C, G_IM_SIZ_8b, tex->unk1E, tex->unk1F,
                                sMin, tMin, sMax, tMax, 0, ref->unk01, ref->unk02,
                                INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F), G_TX_NOLOD, G_TX_NOLOD);
                        } else {
                            gDPLoadTextureBlockYuv((*dlp)++, img, tex->unk1C, G_IM_SIZ_8b, tex->unk1E, tex->unk1F, 0,
                                ref->unk01, ref->unk02, INTEGER_LOG2(tex->unk1E), INTEGER_LOG2(tex->unk1F),
                                G_TX_NOLOD, G_TX_NOLOD);
                        }
                    }
                }
                D_800D5544_main = 1;
            }
        }
    }

    if (D_800CE1CE_main - D_800CDD66_main > 32) {
        gSPVertex(gMainGfxPos++, D_800CDD66_main * 16 + 0x01000000, 32, 0);
        gSPVertex(gMainGfxPos++, (D_800CDD66_main + 32) * 16 + 0x01000000, D_800CE1CE_main - D_800CDD66_main - 32, 32);
    } else {
        gSPVertex(gMainGfxPos++, D_800CDD66_main * 16 + 0x01000000, D_800CE1CE_main - D_800CDD66_main, 0);
    }

    face = D_800CD6B0_main;
    for (i = 0; i < D_800D0A44_main; i++) {
        if (face->unk00 == 3) {
            if (i + 1 < D_800D0A44_main && face[1].unk00 == 3) {
                gSP2Triangles(gMainGfxPos++, face[0].unk02[0], face[0].unk02[1], face[0].unk02[2], 0,
                    face[1].unk02[0], face[1].unk02[1], face[1].unk02[2], 0);
                i++;
                face += 2;
            } else {
                gSP1Triangle(gMainGfxPos++, face->unk02[0], face->unk02[1], face->unk02[2], 0);
                face++;
            }
        } else {
            gSP1Quadrangle(gMainGfxPos++, face->unk02[0], face->unk02[1], face->unk02[2], face->unk02[3], 0);
            face++;
        }
    }

    D_800CDD66_main = D_800CE1CE_main;
}

extern s16 D_800CDD66_main;

void func_80029FB4_main(HmfObj* arg0, s16 arg1) {
    s16* p;

    gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk42;
    *p++ = arg0->unk64[arg1].unk44;
    *p = arg0->unk64[arg1].unk46;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk42;
    *p++ = arg0->unk64[arg1].unk4A;
    *p = arg0->unk64[arg1].unk46;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk48;
    *p++ = arg0->unk64[arg1].unk4A;
    *p = arg0->unk64[arg1].unk46;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk48;
    *p++ = arg0->unk64[arg1].unk44;
    *p = arg0->unk64[arg1].unk46;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk42;
    *p++ = arg0->unk64[arg1].unk44;
    *p = arg0->unk64[arg1].unk4C;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk42;
    *p++ = arg0->unk64[arg1].unk4A;
    *p = arg0->unk64[arg1].unk4C;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk48;
    *p++ = arg0->unk64[arg1].unk4A;
    *p = arg0->unk64[arg1].unk4C;

    p = &D_800D5308_main[D_800CE1CE_main++].unk00;
    *p++ = arg0->unk64[arg1].unk48;
    *p++ = arg0->unk64[arg1].unk44;
    *p = arg0->unk64[arg1].unk4C;

    gSPVertex(gMainGfxPos++, D_800CDD66_main * 16 + 0x01000000, D_800CE1CE_main - D_800CDD66_main, 0);

    D_800CDD66_main = D_800CE1CE_main;

    gSPCullDisplayList(gMainGfxPos++, 0, 7);
}

extern HmfPart* D_800B19F0_main;

#ifdef NON_MATCHING
/* MP2 func_80035FBC_36BBC is NON_MATCHING the same way: GCC turns the 64-bit combine if/else pairs into default-then-override and shares render-mode tails that retail keeps per arm (block layout). MP3 adds the arg2 >> 24 z-buffer case */
void func_8002A358_main(HmfMat* arg0, HmfTexRef* arg1, s32 arg2) {
    u64 cc;
    s64 rm;
    s32 flags;
    s32 zbuf;
    s16 zmode;
    s32 t;

    flags = arg0->unk0C;
    if ((D_800C9940_main & 0x180) == 0x100) {
        zbuf = (((u32) arg2 >> 24) ^ 1) & 1;
    } else {
        zbuf = D_800C9940_main & 0x180;
    }
    if (arg2 & 0x80000) {
        return;
    }
    if (D_800C9940_main & 0x80000) {
        cc = 0xFCFFFFFFFFFFFFFFLL;
    } else if (D_800C9940_main & 0x10000) {
        cc = 0xFC127E2455FDF2F9LL;
    } else if (arg2 & 0x200000) {
        cc = 0xFCFFFFFFFFFE793CLL;
    } else if (arg1 == (HmfTexRef*) -1) {
        if (arg0->unk0C & 1) {
            cc = 0xFC327E64FFFFF7FBLL;
        } else {
            if (!(flags & 4)) {
                gDPSetPrimColor(gMainGfxPos++, 0, 0, arg0->unk05[0], arg0->unk05[1], arg0->unk05[2], 1);
            }
            if (D_800CE1C6_main == 0) {
                cc = 0xFC327E64FFFFFDFELL;
            } else {
                cc = 0xFC327FFFFFFFFC38LL;
            }
        }
    } else if (arg1->unk0C->unk1C == 3) {
        if (D_800CE1C6_main == 0) {
            cc = 0xFC119623FF2FFFFFLL;
            flags |= 1;
        } else {
            cc = 0xFC1197FFFFFFFE38LL;
            flags |= 1;
        }
    } else if (arg1->unk0C->unk1C == 4) {
        if (D_800CE1C6_main == 0) {
            cc = 0xFCFF97FFFF2DFEFFLL;
            flags |= 1;
        } else {
            cc = 0xFCFF97FFFFFDFE38LL;
            flags |= 1;
        }
    } else if (arg1->unk0C->unk1D == 3) {
        if (D_800CE1C6_main == 0) {
            cc = 0xFC121624FF2FFFFFLL;
            flags |= 1;
        } else {
            cc = 0xFC1217FFFFFFFE38LL;
            flags |= 1;
        }
    } else if (flags & 1) {
        if (D_800CE1C6_main == 0) {
            cc = 0xFC121624FF2FFFFFLL;
        } else {
            cc = 0xFC1217FFFFFFFE38LL;
        }
    } else if (D_800CE1C6_main == 0) {
        cc = 0xFC127E24FFFFF3F9LL;
    } else {
        cc = 0xFC127FFFFFFFF238LL;
    }

    t = D_800C9940_main & 0x60;
    if (t == 0x20) {
        zmode = 0x48;
    } else {
        zmode = (t == 0x40) ? 8 : 0;
    }
    if (D_800C9940_main & 0x80000) {
        rm = 0x5553F0;
    } else if (arg2 & 0x8000) {
        gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 1);
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
        if (!(flags & 4)) {
            gDPSetPrimColor(gMainGfxPos++, 0, 0, arg0->unk05[0], arg0->unk05[1], arg0->unk05[2], arg0->unk0D);
        }
        rm = (arg1 == (HmfTexRef*) -1) ? 0x50007B : 0x50307B;
        D_800CE2F0_main = 0;
    } else if (arg2 & 0x200000) {
        rm = 0x507858;
    } else if (arg2 < 0) {
        if (flags & 1) {
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 1);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            if (!(flags & 4)) {
                gDPSetPrimColor(gMainGfxPos++, 0, 0, arg0->unk05[0], arg0->unk05[1], arg0->unk05[2], arg0->unk0D);
            }
            if (D_800CE1C6_main == 0) {
                rm = 0x504DD8;
            } else {
                rm = (s32) 0xC8104DD8;
            }
        } else {
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            if (D_800CE1C6_main == 0) {
                rm = zmode | 0x553D10;
            } else {
                rm = (s32) 0xC8113D10 | zmode;
            }
        }
        D_800B19F0_main->unk00 = arg0->unk00;
    } else if (flags & 1) {
        gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 1);
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
        if (!(flags & 4)) {
            gDPSetPrimColor(gMainGfxPos++, 0, 0, arg0->unk05[0], arg0->unk05[1], arg0->unk05[2], arg0->unk0D);
        }
        if (zmode != 0) {
            zmode |= 0x180;
        } else {
            zmode |= 0x200;
        }
        if (zbuf != 0) {
            if (D_800CE1C6_main == 0) {
                rm = zmode | 0x504850;
            } else {
                rm = (s32) 0xC8104850 | zmode;
            }
        } else if (D_800CE1C6_main == 0) {
            rm = zmode | 0x504040;
        } else {
            rm = (s32) 0xC8104040 | zmode;
        }
        D_800B19F0_main->unk00 = arg0->unk00;
    } else {
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
        if (arg1 == (HmfTexRef*) -1) {
            if (zmode == 0) {
                zmode |= 0x200;
            }
            if (zbuf != 0) {
                if (D_800CE1C6_main == 0) {
                    rm = zmode | 0x552030;
                } else {
                    rm = (s32) 0xC8112030 | zmode;
                }
            } else if (D_800CE1C6_main == 0) {
                rm = zmode | 0x552000;
            } else {
                rm = (s32) 0xC8112000 | zmode;
            }
        } else if (D_800C9940_main & 0x20000) {
            if (zmode == 0) {
                zmode |= 0x200;
            }
            if (zbuf != 0) {
                if (D_800CE1C6_main == 0) {
                    rm = zmode | 0x552030;
                } else {
                    rm = (s32) 0xC8112030 | zmode;
                }
            } else if (D_800CE1C6_main == 0) {
                rm = zmode | 0x552000;
            } else {
                rm = (s32) 0xC8112000 | zmode;
            }
        } else if (zbuf != 0) {
            if (D_800CE1C6_main == 0) {
                rm = zmode | 0x553038;
            } else {
                rm = (s32) 0xC8113038 | zmode;
            }
        } else if (D_800CE1C6_main == 0) {
            rm = zmode | 0x0F0A7008;
        } else {
            rm = (s32) 0xCB027008 | zmode;
        }
    }

    if (D_800D1FD0_main != cc || D_800CE2F0_main != (u64) rm) {
        gDPPipeSync(gMainGfxPos++);
        if (D_800D1FD0_main != cc) {
            D_800D1FD0_main = cc;
            {
                Gfx* g = gMainGfxPos++;

                g->words.w0 = cc >> 32;
                g->words.w1 = cc;
            }
        }
        if (D_800CE2F0_main != (u64) rm) {
            {
                Gfx* g = gMainGfxPos++;

                g->words.w0 = 0xE200001C;
                g->words.w1 = rm;
            }
            D_800CE2F0_main = rm;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002A358_main);
#endif

extern s16 D_800A0AE0_main[];
extern s32 D_800A0AE8_main[];
extern u8 D_800CD2A0_main;
extern u8 D_800D1F2A_main;
extern s32 D_800D1F74_main;
extern u8 D_800D20A0_main;
extern u8 D_800D211C_main;
extern Gfx D_800A0A80_main[];

void func_8002AC5C_main(u16 arg0) {
    u8 temp_v1;

    temp_v1 = (arg0 >> 7) & 3;
    if (temp_v1 != D_800D1F2A_main) {
        D_800D1F2A_main = temp_v1;
        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT | D_800A0AE0_main[temp_v1]);
    }

    if (D_800D20A0_main != D_800D211C_main) {
        D_800D211C_main = D_800D20A0_main;
        if (D_800D20A0_main == 0) {
            gSPSetGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        } else {
            gSPClearGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        }
    }

    temp_v1 = (arg0 >> 9) & 3;
    if (temp_v1 != D_800CD2A0_main) {
        D_800CD2A0_main = temp_v1;
        switch (temp_v1) {
            case 0:
                gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
                break;
            case 1:
                gDPSetColorDither(gMainGfxPos++, G_CD_NOISE);
                break;
            case 2:
                gDPSetColorDither(gMainGfxPos++, G_CD_BAYER);
                break;
            case 3:
                gDPSetColorDither(gMainGfxPos++, G_CD_MAGICSQ);
                break;
            }
    }

    if (D_800CE1C6_main != 0) {
        gSPFogFactor(gMainGfxPos++, 500 * 256 / (D_800CC0B6_main - D_800D6B64_main), (500 - D_800D6B64_main) * 256 / (D_800CC0B6_main - D_800D6B64_main));
        gDPSetFogColor(gMainGfxPos++, D_800D0599_main, D_800D41C4_main, D_800CDA84_main, 255);
    }
}

void func_8002AF40_main(void) {
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RNX, *(D_800CC0A8_main * 2 + &D_800A0AE8_main[0]));
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RNY, *(D_800CC0A8_main * 2 + &D_800A0AE8_main[0]));
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RPX, *(D_800CC0A8_main * 2 + &D_800A0AE8_main[1]));
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RPY, *(D_800CC0A8_main * 2 + &D_800A0AE8_main[1]));
}

void func_8002B104_main(HmfObj*, s16);
void func_8002C0EC_main(HmfObj*, s16);

void func_8002AFEC_main(HmfObj* arg0, s32 arg1, s16 arg2) {
    if (D_800D1F74_main != arg1 || arg1 & 0x0E000000) {
        D_800D1F74_main = arg1;

        gSPDisplayList(gMainGfxPos++, D_800A0A80_main);

        if (arg1 & 0x2000) {
            gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK);
        }

        if (D_800CE1C6_main != 0) {
            gDPSetCycleType(gMainGfxPos++, G_CYC_2CYCLE);
            gSPSetGeometryMode(gMainGfxPos++, G_FOG);
        }

        if (arg1 & 0x06000000) {
            func_8002C0EC_main(arg0, arg2);
        } else if (arg1 & 0x08000000) {
            func_8002B104_main(arg0, arg2);
        }
    }
}

extern HuCamera* D_800D10F4_main;
void func_8002B2AC_main(HmfTex*, s32, s32);

void func_8002B104_main(HmfObj* arg0, s16 arg1) {
    Mtx sp30;
    HmfTex* var_a0;

    if (arg0->unk64[arg1].unk2E != 255) {
        gDPPipeSync(gMainGfxPos++);

        guLookAtReflect(&sp30, &D_800CE20C_main->unk_40, D_800D10F4_main->pos.x, D_800D10F4_main->pos.y, D_800D10F4_main->pos.z,
            D_800D10F4_main->at.x, D_800D10F4_main->at.y, D_800D10F4_main->at.z, D_800D10F4_main->up.x,
            D_800D10F4_main->up.y, D_800D10F4_main->up.z);

        gSPLookAt(gMainGfxPos++, &D_800CE20C_main->unk_40);
        gSPTexture(gMainGfxPos++, 1984, 1984, 0, G_TX_RENDERTILE, G_ON);

        if (arg0->unkA0 == 0) {
            var_a0 = arg0->unk88[arg0->unk64[arg1].unk2E].unk0C;
        } else {
            var_a0 = arg0->unkA0;
        }

        func_8002B2AC_main(var_a0, 0, 0);

        gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING | G_TEXTURE_GEN);
    }
}

extern u32 D_800C952C_main;
extern u32 D_800CCF88_main;
extern u32 D_800CD2FC_main;
extern u32 D_800D1FFC_main;
extern u32 D_800D6A20_main;

/* MP2 stops at 8: MP3 textures go up to 512 texels */
#define INTEGER_LOG2(x) ((x) <= 2 ? 1 : (x) <= 4 ? 2 : (x) <= 8 ? 3 : (x) <= 16 ? 4 : (x) <= 32 ? 5 : (x) <= 64 ? 6 : (x) <= 128 ? 7 : (x) <= 256 ? 8 : 9)

#ifdef NON_MATCHING
/* Register allocation only: the cms argument and the display-list pointer swap t1/t2 */
void func_8002B2AC_main(HmfTex* arg0, s32 arg1, s32 arg2) {
    if (arg0->unk1C != 2) {
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);

        switch (arg0->unk1D) {
            case G_IM_SIZ_16b:
                D_800CCF88_main = G_IM_SIZ_16b_LOAD_BLOCK;
                D_800CD2FC_main = G_IM_SIZ_16b_INCR;
                D_800D6A20_main = G_IM_SIZ_16b_BYTES;
                D_800C952C_main = G_IM_SIZ_16b_LINE_BYTES;
                D_800D1FFC_main = G_IM_SIZ_16b_SHIFT;
                break;
            case G_IM_SIZ_8b:
                D_800CCF88_main = G_IM_SIZ_8b_LOAD_BLOCK;
                D_800CD2FC_main = G_IM_SIZ_8b_INCR;
                D_800D6A20_main = G_IM_SIZ_8b_BYTES;
                D_800C952C_main = G_IM_SIZ_8b_LINE_BYTES;
                D_800D1FFC_main = G_IM_SIZ_8b_SHIFT;
                break;
            case G_IM_SIZ_4b:
                D_800CCF88_main = G_IM_SIZ_4b_LOAD_BLOCK;
                D_800CD2FC_main = G_IM_SIZ_4b_INCR;
                D_800D6A20_main = G_IM_SIZ_4b_BYTES;
                D_800C952C_main = G_IM_SIZ_4b_LINE_BYTES;
                D_800D1FFC_main = G_IM_SIZ_4b_SHIFT;
                break;
            default:
                D_800CCF88_main = G_IM_SIZ_32b_LOAD_BLOCK;
                D_800CD2FC_main = G_IM_SIZ_32b_INCR;
                D_800D6A20_main = G_IM_SIZ_32b_BYTES;
                D_800C952C_main = G_IM_SIZ_32b_LINE_BYTES;
                D_800D1FFC_main = G_IM_SIZ_32b_SHIFT;
                break;
        }

        gDPSetTextureImage(gMainGfxPos++, arg0->unk1C, D_800CCF88_main, 1, arg0->unk28);
        gDPSetTile(gMainGfxPos++, arg0->unk1C, D_800CCF88_main, 0, 0x0000, G_TX_LOADTILE, 0,
            arg2, INTEGER_LOG2(arg0->unk1F), G_TX_NOLOD, arg1, INTEGER_LOG2(arg0->unk1E), G_TX_NOLOD);
        gDPLoadSync(gMainGfxPos++);
        gDPLoadBlock(gMainGfxPos++, G_TX_LOADTILE, 0, 0,
            ((arg0->unk1E * arg0->unk1F + D_800CD2FC_main) >> D_800D1FFC_main) - 1,
            CALC_DXT(arg0->unk1E, D_800D6A20_main));
        gDPPipeSync(gMainGfxPos++);
        gDPSetTile(gMainGfxPos++, arg0->unk1C, arg0->unk1D, (arg0->unk1E * D_800C952C_main + 7) >> 3, 0x0000, G_TX_RENDERTILE, 0,
            arg2, INTEGER_LOG2(arg0->unk1F), G_TX_NOLOD, arg1, INTEGER_LOG2(arg0->unk1E), G_TX_NOLOD);
        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, 0, 0, (arg0->unk1E - 1) * 4, (arg0->unk1F - 1) * 4);
    } else {
        gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);

        if (arg0->unk30->unk1E < 17) {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, arg0->unk30->unk28);
            gDPLoadTextureBlock_4b(gMainGfxPos++, arg0->unk28, arg0->unk1C, arg0->unk1E, arg0->unk1F, 0,
                arg1, arg2, INTEGER_LOG2(arg0->unk1E), INTEGER_LOG2(arg0->unk1F), 0, 0);
        } else {
            gDPLoadTLUT_pal256(gMainGfxPos++, arg0->unk30->unk28);
            gDPLoadTextureBlockYuv(gMainGfxPos++, arg0->unk28, arg0->unk1C, G_IM_SIZ_8b, arg0->unk1E, arg0->unk1F, 0,
                arg1, arg2, INTEGER_LOG2(arg0->unk1E), INTEGER_LOG2(arg0->unk1F), 0, 0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002B2AC_main);
#endif

extern Gfx D_800A1118_main[];
extern s16 D_800CC0B4_main;
extern void* D_800A114C_main[4];

void func_8002C0EC_main(HmfObj* arg0, s16 arg1) {
    Light* temp_s0;
    HmfPart* temp_a0;
    void* timg;
    Mtx sp50;

    gSPDisplayList(gMainGfxPos++, D_800A1118_main);
    temp_s0 = &D_800CB8A8_main[D_800CC0B4_main];
    guLookAtHilite(&sp50, &D_800CE20C_main->unk_40, &D_800CE20C_main->unk_00,
        D_800D10F4_main->pos.x, D_800D10F4_main->pos.y, D_800D10F4_main->pos.z,
        D_800D10F4_main->at.x, D_800D10F4_main->at.y, D_800D10F4_main->at.z,
        D_800D10F4_main->up.x, D_800D10F4_main->up.y, D_800D10F4_main->up.z,
        temp_s0->l.dir[0], temp_s0->l.dir[1], temp_s0->l.dir[2], 0, 0, 115.0f, 32, 32);
    gSPLookAt(gMainGfxPos++, &D_800CE20C_main->unk_40);

    temp_a0 = &arg0->unk64[arg1];
    gDPSetPrimColor(gMainGfxPos++, 0, 0, temp_s0->l.col[0], temp_s0->l.col[1], temp_s0->l.col[2], 255);
    gDPSetEnvColor(gMainGfxPos++, 64, 64, 64, 128);

    timg = D_800A114C_main[((u32) arg0->unk64[arg1].unk50 >> 25) % 4];
    gDPLoadTextureBlock_4b(gMainGfxPos++, timg, G_IM_FMT_I, 32, 32, 0,
        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, D_800CE20C_main->unk_00.h.x1, D_800CE20C_main->unk_00.h.y1,
        D_800CE20C_main->unk_00.h.x1 + 124, D_800CE20C_main->unk_00.h.y1 + 124);

    if (arg0->unk64[arg1].unk50 & 0x10000) {
        gDPSetRenderMode(gMainGfxPos++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
    } else {
        gDPSetRenderMode(gMainGfxPos++, G_RM_ZB_OVL_SURF, G_RM_ZB_OVL_SURF2);
    }

    D_800D0440_main = NULL;
    D_800CE2F0_main = 0xFFFFFFFF;
    D_800D1FD0_main = 0xFFFFFFFF;
}

s32 func_8002C4C0_main(HmfData *arg0, s16 arg1, Matrix4f arg2, Matrix4f arg3) {
    if (!(arg0->unk60[arg1].unk50 & 0x70000000)) {
        return 0;
    }
    func_80018544_main(arg2, arg3);
    return 1;
}

s32 func_8002C5B8_main(HmfObj*, s16, s16);

void func_8002C520_main(HmfObj* arg0, s16 arg1, Matrix4f arg2) {
    D_800D138A_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    if (arg0->unk84 == (HmfMotionObj*) -1 && arg0->unk68 != 0) {
        func_8002C5B8_main(arg0, 0, arg1);
        func_8002367C_main(arg2, D_800D5A00_main[D_800D138A_main]);
    }
}

s32 func_8002C5B8_main(HmfObj* arg0, s16 arg1, s16 arg2) {
    Matrix4f sp10;
    HitXform* node;
    s16 pushed;

    node = &arg0->unk6C[arg1];
    pushed = 0;
    guMtxIdentF(sp10);
    if (node->unk08.x != 0.0f || node->unk08.y != 0.0f || node->unk08.z != 0.0f) {
        func_80017C10_main((Mtx*) sp10, node->unk08.x, node->unk08.y, node->unk08.z);
        pushed = 1;
    }
    if (node->unk14.x != 0.0f || node->unk14.y != 0.0f || node->unk14.z != 0.0f) {
        arg0->unkD4(sp10, node->unk14.x, node->unk14.y, node->unk14.z);
        pushed = 1;
    }
    if (node->unk20.x != 1.0f || node->unk20.y != 1.0f || node->unk20.z != 1.0f) {
        func_80017CD0_main(sp10, node->unk20.x, node->unk20.y, node->unk20.z);
        pushed = 1;
    }
    if (pushed != 0) {
        D_800D138A_main++;
        func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
    }
    if (arg2 == arg1) {
        return 0;
    }
    if (node->unk04 != 0 && func_8002C5B8_main(arg0, arg1 + node->unk04, arg2) == 0) {
        return 0;
    }
    if (pushed != 0) {
        D_800D138A_main--;
    }
    if (node->unk02 != 0 && func_8002C5B8_main(arg0, arg1 + node->unk02, arg2) == 0) {
        return 0;
    }
    return 1;
}

s16 func_80011460_main(char*);
int strcmp(const char*, const char*);

s16 func_8002C834_main(HmfObj* arg0, char* arg1) {
    s16 temp_a1;
    s16 i;

    temp_a1 = func_80011460_main(arg1);
    for (i = 0; i < arg0->unk10; i++) {
        if (arg0->unk64[i].unk08 == temp_a1 && strcmp(arg0->unk64[i].unk12, arg1) == 0) {
            break;
        }
    }

    if (i == arg0->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", arg1);
        return -1;
    }

    return i;
}

void func_8002C960_main(HmfObj*, s16, HmfObj*);

void func_8002C914_main(HmfObj* arg0, char* arg1, HmfObj* arg2) {
    s16 idx;

    idx = func_8002C834_main(arg0, arg1);
    if (idx != -1) {
        func_8002C960_main(arg0, idx, arg2);
    }
}

void func_8002C960_main(HmfObj* arg0, s16 arg1, HmfObj* arg2) {
    s16 i;
    s16 j;
    s16 name;
    HitXform* node;

    name = arg0->unk64[arg1].unk08;
    for (i = 0; i < arg2->unk10; i++) {
        if (arg2->unk64[i].unk08 == name && strcmp(arg2->unk64[i].unk12, arg0->unk64[arg1].unk12) == 0) {
            break;
        }
    }
    if (i != arg2->unk10) {
        for (j = 0; j < arg0->unk68; j++) {
            node = &arg0->unk6C[j];
            if (node->unk00 == arg1) {
                node->unk48 = arg2;
                node->unk00 = i;
            }
        }
    }
}

void func_8002CB6C_main(HmfObj*, s16);
void func_8002CDF4_main(HmfObj*, s16);

void func_8002CAE4_main(HmfObj* arg0) {
    if (arg0->unk14 != 0) {
        D_800D5214_main = 0;
        D_800D138A_main = 0;

        func_8008A070_main(D_800D5A00_main[0]);

        if (arg0->unk84 == (void*) -1) {
            if (arg0->unk68 != 0) {
                func_8002CB6C_main(arg0, 0);
            }
        } else if (arg0->unk16 != 0) {
            func_8002CDF4_main(arg0, 0);
        }
    }
}

void func_8002CB6C_main(HmfObj* arg0, s16 arg1) {
    HitXform* temp_s1 = &arg0->unk6C[arg1];
    s16 var_s3 = 0;
    s16 var_s0 = 0;
    Matrix4f sp10;

    func_8008A070_main(sp10);

    if (arg0->unk90 == 0) {
        if (temp_s1->unk08.x != 0.0f || temp_s1->unk08.y != 0.0f || temp_s1->unk08.z != 0.0f) {
            func_80017C10_main((Mtx*) sp10, temp_s1->unk08.x, temp_s1->unk08.y, temp_s1->unk08.z);
            var_s0 = 1;
        }

        if (temp_s1->unk14.x != 0.0f || temp_s1->unk14.y != 0.0f || temp_s1->unk14.z != 0.0f) {
            arg0->unkD4(sp10, temp_s1->unk14.x, temp_s1->unk14.y, temp_s1->unk14.z);
            var_s0 = 1;
        }
    }

    if (temp_s1->unk20.x != 1.0f || temp_s1->unk20.y != 1.0f || temp_s1->unk20.z != 1.0f) {
        func_80017CD0_main(sp10, temp_s1->unk20.x, temp_s1->unk20.y, temp_s1->unk20.z);
        var_s3 = 1;
        var_s0 = 1;
    }

    if (var_s0 != 0) {
        D_800D138A_main++;
        func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
    }

    func_8002367C_main(temp_s1->unk4C, D_800D5A00_main[D_800D138A_main]);

    if (temp_s1->unk04 != 0) {
        func_8002CB6C_main(arg0, arg1 + temp_s1->unk04);
    }

    if (var_s0) {
        D_800D138A_main--;
    }

    if (var_s3) {
        D_800D5214_main--;
    }

    if (temp_s1->unk02 != 0) {
        func_8002CB6C_main(arg0, arg1 + temp_s1->unk02);
    }
}

void func_8002CDF4_main(HmfObj* arg0, s16 arg1) {
    HmfMotionObj* temp_s1 = &arg0->unk84[arg1];
    s16 var_s5 = 0;
    s16 var_s2 = 0;
    s16 i;
    Matrix4f sp10;

    func_8008A070_main(sp10);

    if (temp_s1->unk04.x != 0.0f || temp_s1->unk04.y != 0.0f || temp_s1->unk04.z != 0.0f) {
        func_80017C10_main((Mtx*) sp10, temp_s1->unk04.x, temp_s1->unk04.y, temp_s1->unk04.z);
        var_s2 = 1;
    }

    if (temp_s1->unk10.x != 0.0f || temp_s1->unk10.y != 0.0f || temp_s1->unk10.z != 0.0f) {
        arg0->unkD4(sp10, temp_s1->unk10.x, temp_s1->unk10.y, temp_s1->unk10.z);
        var_s2 = 1;
    }

    if (temp_s1->unk1C.x != 1.0f || temp_s1->unk1C.y != 1.0f || temp_s1->unk1C.z != 1.0f) {
        func_80017CD0_main(sp10, temp_s1->unk1C.x, temp_s1->unk1C.y, temp_s1->unk1C.z);
        var_s5 = 1;
        var_s2 = 1;
    }

    if (var_s2) {
        D_800D138A_main++;
        func_80018044_main(sp10, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
    }

    func_8002367C_main(temp_s1->unk58, D_800D5A00_main[D_800D138A_main]);

    for (i = 0; i < temp_s1->unk00; i++) {
        if ((temp_s1->unk50[i] & 0x8000) && (temp_s1->unk50[i] != -1)) {
            func_8002CDF4_main(arg0, temp_s1->unk50[i] & ~0x8000);
        }
    }

    if (var_s2) {
        D_800D138A_main--;
    }

    if (var_s5) {
        D_800D5214_main--;
    }
}

void func_8002D094_main(Gfx** arg0, s16 arg1, s32 arg2) {
    switch (arg1) {
        case 0:
        case 1:
            gSPLightColor((*arg0)++, LIGHT_1, arg2);
            break;
        case 2:
            gSPLightColor((*arg0)++, LIGHT_2, arg2);
            break;
        case 3:
            gSPLightColor((*arg0)++, LIGHT_3, arg2);
            break;
        case 4:
            gSPLightColor((*arg0)++, LIGHT_4, arg2);
            break;
        case 5:
            gSPLightColor((*arg0)++, LIGHT_5, arg2);
            break;
        case 6:
            gSPLightColor((*arg0)++, LIGHT_6, arg2);
            break;
        case 7:
            gSPLightColor((*arg0)++, LIGHT_7, arg2);
            break;
        default:
            gSPLightColor((*arg0)++, LIGHT_8, arg2);
            break;
    }
}

/* Unreferenced: the rodata word after func_8002D094_main's jump table */
const s32 D_800A6CC8_main = 0;

/* D_800CCF58_main (variables.h): the 128 motion slots */
#define MOTION_SLOTS ((HmfMotionSlot*) D_800CCF58_main)
extern s16 D_800CE2B4_main;
void func_80030030_main(f32);
s16 func_8002D3D0_main(HmfObj*, u8*, s16);
s32 func_8002D5B0_main(HmfMotionSlot*, HmfObj*);
s32 func_8002DF2C_main(HmfMotionSlot*, struct HmfMotionFile*);

void func_8002D260_main(void) {
    s16 i;

    func_80030030_main(1.0f);
    D_800CCF58_main = HuMemAlloc(128 * sizeof(HmfMotionSlot));

    for (i = 0; i < 128; i++) {
        MOTION_SLOTS[i].unk02 = -1;
    }
}


s16 func_8002D2D8_main(u8* arg0, HmfObj* arg1) {
    s16 i;

    for (i = 0; i < 128; i++) {
        if (MOTION_SLOTS[i].unk02 == -1) {
            break;
        }
    }

    if (i == 128) {
        return -1;
    }

    if (func_8002D3D0_main(arg1, arg0, i) != 0) {
        if (arg1 == NULL) {
            return i;
        }
        arg1->unkA4 = 0;
        return i;
    }

    return -1;
}


s16 func_8002D3AC_main(u8* arg0) {
    return func_8002D2D8_main(arg0, NULL);
}


s16 func_8002D3D0_main(HmfObj* arg0, u8* arg1, s16 arg2) {
    void* temp_v0;
    s32 temp_s0;
    s32* var_a1;

    var_a1 = (s32*) arg1;

    D_800CE2B4_main = arg2 + 10356;
    MOTION_SLOTS[arg2].unk00 = 0;

    if (arg0 != NULL) {
        return func_8002D5B0_main(&MOTION_SLOTS[arg2], arg0) != 0;
    }

    temp_s0 = var_a1[1] + 8;
    temp_v0 = HuMemAllocTag(temp_s0, D_800CE2B4_main);

    bcopy(arg1, temp_v0, temp_s0);
    func_8002DF2C_main(&MOTION_SLOTS[arg2], temp_v0);

    return 1;
}


void func_8002D4B8_main(s16 arg0) {
    if (arg0 != 0xFF) {
        HuMemFreeAllWithTag(arg0 + 10356);
        MOTION_SLOTS[arg0].unk02 = -1;
    }
}


void func_8002D514_main(void) {
    s16 i;

    for (i = 0; i < 128; i++) {
        if (MOTION_SLOTS[i].unk02 != -1) {
            HuMemFreeAllWithTag(i + 10356);
            MOTION_SLOTS[i].unk02 = -1;
        }
    }
}

extern u16 D_800B1A00_main;
extern u16 D_800B1A02_main;
s16 func_8000FDAC_main(void*, s16);
u8* func_80010A38_main(s32, void*, void*);
void* func_80010AC8_main(void*);
s32 func_8002DA98_main(HmfMotionSlot*, s16, u8*);
s32 func_8002DD4C_main(HmfObj*, s16, u8*);

s32 func_8002D5B0_main(HmfMotionSlot* arg0, HmfObj* arg1) {
    HmfAnimTrack* temp_v0;
    HmfMotionTrack* sp14;
    s16 sp1E;
    s16 sp26;
    s16 sp2E;
    s16 sp36;
    s16 var_s0;
    s16 var_s5;
    s16 var_s6;
    s16 temp_a0;
    s16 temp_s3;
    f32* sp3C;
    s16* sp44;
    u8* var_s1;
    u8* var_s2;
    s16 i;

    var_s1 = arg1->unk34;
    var_s0 = 0;
    sp2E = 0;

    while (TRUE) {
        var_s1 = func_80010A38_main(0x4D544E31, var_s1, arg1->unk30);
        if (var_s1 == NULL) {
            break;
        }

        temp_a0 = var_s1[2];
        if (temp_a0 == 78 || temp_a0 == 13 || temp_a0 == 8) {
            var_s0 += var_s1[10];
        }
        sp2E++;

        var_s1 = func_80010AC8_main(var_s1 + 4);
    }

    if (var_s0 == 0) {
        return 0;
    }

    arg0->unk08 = HuMemAllocTag(var_s0 * sizeof(HmfMotionTrack*), D_800CE2B4_main);
    arg0->unk0C = HuMemAllocTag(var_s0 * sizeof(u8), D_800CE2B4_main);
    sp44 = arg0->unk10 = HuMemAllocTag(4096 * sizeof(s16), D_800CE2B4_main);
    sp3C = arg0->unk14 = HuMemAllocTag(4096 * sizeof(f32), D_800CE2B4_main);

    D_800B1A02_main = 0;
    D_800B1A00_main = 0;
    sp36 = 0;

    var_s1 = arg1->unk34;
    for (var_s6 = var_s5 = sp1E = 0; sp1E < sp2E; sp1E++) {
        var_s2 = var_s1 = func_80010A38_main(0x4D544E31, var_s1, arg1->unk30);
        sp26 = func_8000FDAC_main(arg1, (var_s2[8] << 8) + var_s2[9]);

        temp_s3 = var_s2[10];
        if (temp_s3 != 0) {
            if ((var_s2[11] << 8) + var_s2[12] > sp36) {
                sp36 = (var_s2[11] << 8) + var_s2[12];
            }

            var_s2 += 13;
            sp14 = HuMemAllocTag(temp_s3 * sizeof(HmfMotionTrack), D_800CE2B4_main);

            for (i = 0; i < temp_s3; i++) {
                temp_a0 = var_s2[2];

                arg0->unk0C[var_s5] = temp_a0;
                arg0->unk08[var_s5] = &sp14[i];

                switch (temp_a0) {
                    case 78:
                        if (func_8002DA98_main(arg0, var_s5, var_s2 + 2) != 0) {
                            var_s5++;
                        }
                        break;
                    case 13:
                        if (func_8002DA98_main(arg0, var_s5, var_s2 + 2) != 0) {
                            arg0->unk08[var_s5]->unk_08 = sp26;
                            if (sp26 == -1) {
                                arg0->unk0C[var_s5] = 78;
                            }
                            var_s5++;
                        }
                        break;
                    case 8:
                        if (var_s6 == 0) {
                            arg1->unk9C = HuMemAllocTag(sizeof(HmfAnim), arg1->unk0E + 1);
                        }
                        if (func_8002DD4C_main(arg1, var_s6, var_s2 + 4) != 0) {
                            var_s6++;
                        }
                        break;
                }

                var_s2 += (var_s2[0] << 8) + var_s2[1] + 2;
            }

            var_s1 = func_80010AC8_main(var_s1 + 4);
        }
    }

    if (var_s6 != 0) {
        arg1->unk9C->unk00 = var_s6;
        arg1->unk9C->unk08 = 0;

        for (sp1E = i = 0; i < var_s6; i++) {
            temp_v0 = &arg1->unk9C->unk0C[i];
            if (temp_v0->unk06 > sp1E) {
                sp1E = temp_v0->unk06;
            }
        }

        arg1->unk9C->unk04 = sp1E;
        arg1->unk9C->unk02 = 0;
    }

    arg0->unk10 = HuMemAllocTag(D_800B1A00_main * sizeof(s16), D_800CE2B4_main);
    bcopy(sp44, arg0->unk10, D_800B1A00_main * sizeof(s16));
    HuMemFree(sp44);

    arg0->unk14 = HuMemAllocTag(D_800B1A02_main * sizeof(f32), D_800CE2B4_main);
    bcopy(sp3C, arg0->unk14, D_800B1A02_main * sizeof(f32));
    HuMemFree(sp3C);

    arg0->unk02 = sp36;
    arg0->unk00 = var_s5;

    return 1;
}

s32 func_8002DA98_main(HmfMotionSlot *arg0, s16 arg1, u8 *arg2)
{
  HmfMotionTrack *p;
  f32 scale;
  s16 i;
  f32 *var_a3;
  union 
  {
    s32 i;
    f32 f;
  } u;
  p = arg0->unk08[arg1];
  arg1 = *(arg2++);
  p->unk_00 = arg2[0];
  scale = 1.0f;
  p->unk_04 = (arg2[1] << 8) + arg2[2];
  p->unk_06 = (arg2[3] << 8) + arg2[4];
  p->unk_01 = arg2[5];
  if (arg1 == 78)
  {
    p->unk_08 = arg2[6];
    arg2++;
  }
  p->unk_02 = arg2[6];
  arg2 += 7;
  if ((*p).unk_02 == 73)
  {
    p->unk_03 = arg2[0];
    p->unk_0E = arg2[1];
    arg2 += 2;
    p->unk_0A = D_800B1A00_main;
    p->unk_0C = D_800B1A02_main;
    for (i = 0; i < p->unk_0E; i++)
    {
      arg0->unk10[D_800B1A00_main++] = (arg2[0] << 8) + arg2[1];
      if (1)
      {
        u.i = (((arg2[2] << 24) + (arg2[3] << 16)) + (arg2[4] << 8)) + arg2[5];
        arg0->unk14[D_800B1A02_main++] = scale * u.f;
      }
      arg2 += 6;
    }

  }
  else
    if (p->unk_02 == 35)
  {
    if (arg1)
    {
      arg2++;
      p->unk_0E = *(arg2++);
      p->unk_0A = D_800B1A00_main;
      p->unk_0C = D_800B1A02_main;
      var_a3 = &arg0->unk14[D_800B1A02_main];
    }
    else
    {
      arg2++;
      p->unk_0E = *(arg2++);
      p->unk_0A = D_800B1A00_main;
      p->unk_0C = D_800B1A02_main;
      var_a3 = &arg0->unk14[D_800B1A02_main];
    }
    for (i = 0; i < p->unk_0E; i++)
    {
      arg0->unk10[D_800B1A00_main++] = (arg2[0] << 8) + arg2[1];
      ((u8 *) var_a3)[0] = arg2[2];
      ((u8 *) var_a3)[1] = arg2[3];
      ((u8 *) var_a3)[2] = arg2[4];
      ((u8 *) var_a3)[3] = arg2[5];
      ((u8 *) var_a3)[4] = arg2[6];
      ((u8 *) var_a3)[5] = arg2[7];
      ((u8 *) var_a3)[6] = arg2[8];
      ((u8 *) var_a3)[7] = arg2[9];
      ((u8 *) var_a3)[8] = arg2[10];
      ((u8 *) var_a3)[9] = arg2[11];
      ((u8 *) var_a3)[10] = arg2[12];
      ((u8 *) var_a3)[11] = arg2[13];
      var_a3[0] = scale * var_a3[0];
      var_a3 += 3;
      D_800B1A02_main += 3;
      arg2 += 14;
    }

  }
  return 1;
}

s32 func_8002DD4C_main(HmfObj* arg0, s16 arg1, u8* arg2) {
    HmfAnimTrack* temp_s3;
    s16 temp_s0;
    s16 var_a3;
    s16 i;

    temp_s3 = &arg0->unk9C->unk0C[arg1];

    temp_s3->unk04 = (arg2[0] << 8) + arg2[1];
    temp_s3->unk00 = (arg2[2] << 8) + arg2[3];

    arg0->unk8C[temp_s3->unk00].unk0C |= 5;

    temp_s0 = temp_s3->unk02 = (arg2[6] << 8) + arg2[7];
    temp_s3->unk08 = HuMemAllocTag(temp_s0 * sizeof(u16), arg0->unk0E + 1);
    temp_s3->unk0C = HuMemAllocTag(temp_s0 * sizeof(s32), arg0->unk0E + 1);

    arg2 += 8;

    for (var_a3 = i = 0; i < temp_s0; i++) {
        ((u8*) &temp_s3->unk0C[i])[0] = arg2[0];
        ((u8*) &temp_s3->unk0C[i])[1] = arg2[1];
        ((u8*) &temp_s3->unk0C[i])[2] = arg2[2];
        ((u8*) &temp_s3->unk0C[i])[3] = arg2[3];

        temp_s3->unk08[i] = (arg2[4] << 8) + arg2[5];
        var_a3 += temp_s3->unk08[i];

        arg2 += 6;
    }

    temp_s3->unk08[i - 1]++;
    temp_s3->unk06 = var_a3 + 1;

    return 1;
}


s32 func_8002DF2C_main(HmfMotionSlot* arg0, HmfMotionFile* arg1) {
    HmfMotionTrack** tracks;
    HmfMotionTrack** var_v1;
    s32* var_a0;
    s16 temp_s3;
    s16 i;

    temp_s3 = arg0->unk00 = arg1->unk09;
    arg0->unk02 = arg1->unk0A;
    arg0->unk0C = (u8*) arg1 + arg1->unk0C;
    arg0->unk10 = (s16*) ((u8*) arg1 + arg1->unk10);
    arg0->unk14 = (f32*) ((u8*) arg1 + arg1->unk14);
    tracks = HuMemAllocTag(temp_s3 * sizeof(HmfMotionTrack*), D_800CE2B4_main);
    arg0->unk08 = tracks;

    var_a0 = arg1->unk18;
    var_v1 = tracks;
    for (i = 0; i < temp_s3; i++) {
        *var_v1 = (HmfMotionTrack*) ((u8*) arg1 + *var_a0);
        var_v1++;
        var_a0++;
    }

    return 1;
}

void func_8002DFF8_main(HmfObj* arg0, f32 arg1, void* arg2v, s32 arg3) {
    HmfMotionSlot* arg2 = arg2v;
    HitXform* p40;
    HitXform* q;
    HmfMotionObj* p50;
    HmfMotionTrack* e;
    HmfObjBC* bc;
    f32* dst;
    s32 i;
    u32 idx;
    s32 n;
    s32 t;

    bc = NULL;
    if (arg3 != 0) {
        if (arg0->unk84 == (void*) -1) {
            idx = arg0->unk68;
            p40 = arg0->unk6C;
            for (i = 0; i < (s32) idx; i++) {
                if (p40->unk44 != 0) {
                    p40->unk2C = p40->unk08;
                }
                if (p40->unk45 != 0) {
                    p40->unk38 = p40->unk14;
                }
                p40->unk44 = 0;
                p40->unk45 = 0;
                p40++;
            }
        } else {
            p50 = arg0->unk84;
            n = arg0->unk16;
            for (i = 0; i < n; i++) {
                if (p50->unk4C != 0) {
                    p50->unk28 = p50->unk04;
                }
                if (p50->unk4D != 0) {
                    p50->unk34 = p50->unk10;
                }
                if (p50->unk4E != 0) {
                    p50->unk40 = p50->unk1C;
                }
                p50->unk4E = 0;
                p50->unk4D = 0;
                p50->unk4C = 0;
                p50++;
            }
        }
        if (arg0->unkC8 != NULL) {
            bc = arg0->unkC0;
            bc->unk08[0].x = ((HmfObjC4*) arg0->unkC8)[bc->unk00[0]].unk20.x;
            bc->unk08[0].y = ((HmfObjC4*) arg0->unkC8)[bc->unk00[0]].unk20.y;
            bc->unk08[0].z = ((HmfObjC4*) arg0->unkC8)[bc->unk00[0]].unk20.z;
            bc->unk08[1].x = ((HmfObjC4*) arg0->unkC8)[bc->unk00[1]].unk20.x;
            bc->unk08[1].y = ((HmfObjC4*) arg0->unkC8)[bc->unk00[1]].unk20.y;
            bc->unk08[1].z = ((HmfObjC4*) arg0->unkC8)[bc->unk00[1]].unk20.z;
            bc->unk08[2].x = ((HmfObjC4*) arg0->unkC8)[bc->unk00[2]].unk20.x;
            bc->unk08[2].y = ((HmfObjC4*) arg0->unkC8)[bc->unk00[2]].unk20.y;
            bc->unk08[2].z = ((HmfObjC4*) arg0->unkC8)[bc->unk00[2]].unk20.z;
        }
    }

    if (arg2 != (HmfMotionSlot*) -1) {
        n = arg2->unk00;
        for (i = 0; i < n; i++) {
            e = arg2->unk08[i];
            if (e->unk_04 & 0x8000) {
                continue;
            }
            idx = e->unk_08 & 0x7FFF;
            if (idx == 0x7FFF) {
                idx = 0;
            }
            if ((idx >> 14) & (t = (bc != NULL))) {
                idx &= 0x3FFF;
                if (bc->unk00[0] == idx) {
                    dst = &bc->unk08[0].x;
                } else if (bc->unk00[1] == idx) {
                    dst = &bc->unk08[1].x;
                } else {
                    dst = &bc->unk08[2].x;
                }
                if (e->unk_01 != 'E') {
                    if (e->unk_01 == 'F') {
                        dst += 1;
                    } else {
                        dst += 2;
                    }
                }
                if (e->unk_02 == 'I') {
                    *dst = func_8002E78C_main(arg2, e, arg1);
                } else {
                    *dst = func_8002E8E8_main(arg2, e, arg1);
                }
                continue;
            }
            if (arg1 < arg2->unk10[e->unk_0A]) {
                continue;
            }
            switch (arg2->unk0C[i]) {
                case 78:
                    switch (e->unk_00) {
                        case 76:
                            q = &arg0->unk6C[idx];
                            dst = &q->unk38.x;
                            if (e->unk_01 != 'E') {
                                if (e->unk_01 == 'F') {
                                    dst = &q->unk38.y;
                                } else {
                                    dst += 2;
                                }
                            }
                            if (e->unk_02 == 'I') {
                                *dst = func_8002E78C_main(arg2, e, arg1);
                            } else {
                                *dst = func_8002E8E8_main(arg2, e, arg1);
                            }
                            arg0->unk6C[idx].unk45 = 0x80;
                            break;
                        case 79:
                            dst = &arg0->unk6C[idx].unk2C.x;
                            if (e->unk_01 != 'E') {
                                if (e->unk_01 == 'F') {
                                    dst += 1;
                                } else {
                                    dst += 2;
                                }
                            }
                            if (e->unk_02 == 'I') {
                                *dst = func_8002E78C_main(arg2, e, arg1);
                            } else {
                                *dst = func_8002E8E8_main(arg2, e, arg1);
                            }
                            arg0->unk6C[idx].unk44 = 0x80;
                            break;
                        case 23:
                            dst = &arg0->unk6C[idx].unk2C.x;
                            if (e->unk_01 != 'E') {
                                if (e->unk_01 == 'F') {
                                    dst += 1;
                                } else {
                                    dst += 2;
                                }
                            }
                            if (e->unk_02 == 'I') {
                                *dst = func_8002E78C_main(arg2, e, arg1);
                            } else {
                                *dst = func_8002E8E8_main(arg2, e, arg1);
                            }
                            arg0->unk6C[idx].unk44 = 0x80;
                            break;
                    }
                    break;
                case 13:
                    p50 = &arg0->unk84[idx];
                    switch (e->unk_00) {
                        case 23:
                            dst = &p50->unk28.x;
                            if (e->unk_01 == 'F') {
                                dst = &p50->unk28.y;
                            } else if (e->unk_01 == 'G') {
                                dst += 2;
                            }
                            if (e->unk_02 == 'I') {
                                *dst = func_8002E78C_main(arg2, e, arg1);
                            } else {
                                *dst = func_8002E8E8_main(arg2, e, arg1);
                            }
                            p50->unk4C = 0x80;
                            break;
                        case 76:
                            dst = &p50->unk34.x;
                            if (e->unk_01 == 'F') {
                                dst = &p50->unk34.y;
                            } else if (e->unk_01 == 'G') {
                                dst += 2;
                            }
                            if (e->unk_02 == 'I') {
                                *dst = func_8002E78C_main(arg2, e, arg1);
                            } else {
                                *dst = func_8002E8E8_main(arg2, e, arg1);
                            }
                            p50->unk4D = 0x80;
                            break;
                        case 27:
                            dst = &p50->unk40.x;
                            if (e->unk_01 == 'F') {
                                dst = &p50->unk40.y;
                            } else if (e->unk_01 == 'G') {
                                dst += 2;
                            }
                            if (e->unk_02 == 'I') {
                                *dst = func_8002E78C_main(arg2, e, arg1);
                            } else {
                                *dst = func_8002E8E8_main(arg2, e, arg1);
                            }
                            p50->unk4E = 0x80;
                            break;
                    }
                    break;
            }
        }
    }
}

f32 func_8002E78C_main(HmfMotionSlot* arg0, HmfMotionTrack* arg1, f32 arg2) {
    f32* vals;
    s16* keys;
    s16 i;
    s16 j;
    s16 d;

    vals = &arg0->unk14[arg1->unk_0C];
    if (arg2 == 0.0f || arg1->unk_0E == 1) {
        return vals[0];
    }
    keys = &arg0->unk10[arg1->unk_0A];
    for (i = 0; i < arg1->unk_0E; i++) {
        if (arg2 < keys[i]) {
            break;
        }
    }
    if (i == arg1->unk_0E) {
        return vals[arg1->unk_0E - 1];
    }
    j = i - 1;
    d = keys[i] - keys[j];
    return (vals[i] - vals[j]) / d * (arg2 - keys[j]) + vals[j];
}

/* func_8002E8E8_main's constants: as literals the assembler pools them and pads the unit's .rodata */
const f64 D_800A6CD0_main = 1.0;
const f64 D_800A6CD8_main = 3.0;

f32 func_8002E8E8_main(HmfMotionSlot* arg0, HmfMotionTrack* arg1, f32 arg2) {
    HmfHermiteKey* vals;
    HmfHermiteKey* cur;
    HmfHermiteKey* prev;
    s16* keys;
    s16* kp;
    s32 n;
    s32 i;
    s16 k0;
    s32 k1;
    f32 t;
    f32 r;
    f32 r2;
    f32 t2;
    f32 a;
    f32 b;
    f32 h1;
    f32 h2;

    vals = (HmfHermiteKey*) &arg0->unk14[arg1->unk_0C];
    if (arg2 == 0.0f || arg1->unk_0E == 1) {
        return vals[0].v;
    }
    keys = &arg0->unk10[arg1->unk_0A];
    n = arg1->unk_0E;
    for (kp = keys, i = 0; i < n; i++) {
        if (arg2 < *kp++) {
            break;
        }
    }
    if (i == n) {
        return vals[arg1->unk_0E - 1].v;
    }
    cur = &vals[i];
    k1 = keys[i];
    i--;
    prev = &vals[i];
    k0 = keys[i];
    t = arg2 - k0;
    r = D_800A6CD0_main / (k1 - k0);
    r2 = r * r;
    t2 = t * t;
    a = t2 * r;
    b = t2 * t * r2;
    h1 = 2.0 * b * r;
    h2 = t2 * D_800A6CD8_main * r2;
    return (h1 - h2 + 1.0f) * prev->v + (-h1 + h2) * cur->v + (b - a - a + t) * prev->in + (b - a) * prev->out;
}

f32 func_8002E78C_main(HmfMotionSlot*, HmfMotionTrack*, f32);
f32 func_8002E8E8_main(HmfMotionSlot*, HmfMotionTrack*, f32);

#ifdef NON_MATCHING
/* MP2 func_8003A4B8_3B0B8 is NON_MATCHING the same way: retail loads -180.0f before *dst in the second wrap test, GCC the reverse (plus a nop); the rest follows MP3's asm */
void func_8002EAC0_main(HmfObj* arg0, f32 arg1, f32 arg2) {
    HmfMotionSlot* anim;
    HmfMotionTrack* e;
    HitXform* p40;
    HmfMotionObj* p50;
    f32* dst;
    f32 time;
    f32 w;
    f32 inv;
    f32 val;
    s32 axis;
    u8 f;
    s16 idx;
    s16 i;

    time = arg1;
    w = arg2;
    anim = arg0->unk94;
    inv = 1.0f - w;
    for (i = 0; i < anim->unk00; i++) {
        e = anim->unk08[i];
        if (e->unk_04 & 0x8000) {
            continue;
        }
        idx = e->unk_08 & 0x7FFF;
        if (idx == 0x7FFF) {
            idx = 0;
        }
        if (idx & 0x4000) {
            continue;
        }
        if (time < anim->unk10[e->unk_0A]) {
            continue;
        }
        if (e->unk_01 != 'E') {
            axis = 2;
            if (e->unk_01 == 'F') {
                axis = 1;
            }
        } else {
            axis = 0;
        }
        switch (anim->unk0C[i]) {
            case 78:
                switch (e->unk_00) {
                    case 76:
                    dst = &(&arg0->unk6C[idx].unk38.x)[axis];
                    if (e->unk_02 == 'I') {
                        val = func_8002E78C_main(anim, e, time);
                    } else {
                        val = func_8002E8E8_main(anim, e, time);
                    }
                    if (val < -180.0f) {
                        val += 360.0f;
                    }
                    if (*dst < -180.0f) {
                        *dst += 360.0f;
                    }
                    if (val > 180.0f) {
                        val -= 360.0f;
                    }
                    if (*dst > 180.0f) {
                        *dst -= 360.0f;
                    }
                    *dst = inv * *dst + val * w;
                    arg0->unk6C[idx].unk45 |= (1 << axis) | 0x40;
                    break;
                    case 79:
                    dst = &(&arg0->unk6C[idx].unk2C.x)[axis];
                    if (e->unk_02 == 'I') {
                        val = func_8002E78C_main(anim, e, time);
                    } else {
                        val = func_8002E8E8_main(anim, e, time);
                    }
                    *dst = inv * *dst + val * w;
                    arg0->unk6C[idx].unk44 |= (1 << axis) | 0x40;
                    break;
                }
                break;
            case 13:
                switch (e->unk_00) {
                    case 23:
                    dst = &(&arg0->unk84[idx].unk28.x)[axis];
                    if (e->unk_02 == 'I') {
                        val = func_8002E78C_main(anim, e, time);
                    } else {
                        val = func_8002E8E8_main(anim, e, time);
                    }
                    *dst = inv * *dst + val * w;
                    arg0->unk84[idx].unk4C |= (1 << axis) | 0x40;
                    break;
                    case 76:
                    dst = &(&arg0->unk84[idx].unk34.x)[axis];
                    if (e->unk_02 == 'I') {
                        val = func_8002E78C_main(anim, e, time);
                    } else {
                        val = func_8002E8E8_main(anim, e, time);
                    }
                    if (val < 0.0f) {
                        val += 360.0f;
                    }
                    if (*dst < 0.0f) {
                        *dst += 360.0f;
                    }
                    if (val < 180.0f) {
                        if (val + 180.0f < *dst) {
                            *dst -= 360.0f;
                        }
                    } else if (*dst < val - 180.0f) {
                        val -= 360.0f;
                    }
                    *dst = inv * *dst + val * w;
                    arg0->unk84[idx].unk4D |= (1 << axis) | 0x40;
                    break;
                    case 27:
                    dst = &(&arg0->unk84[idx].unk40.x)[axis];
                    if (e->unk_02 == 'I') {
                        val = func_8002E78C_main(anim, e, time);
                    } else {
                        val = func_8002E8E8_main(anim, e, time);
                    }
                    *dst = inv * *dst + val * w;
                    arg0->unk84[idx].unk4E |= (1 << axis) | 0x40;
                    break;
                }
                break;
        }
    }

    if (arg0->unk84 == (void*) -1) {
        p40 = arg0->unk6C;
        idx = arg0->unk68;
        for (i = 0; i < idx; i++) {
            if (p40->unk44 != 0) {
            f = p40->unk44;
            dst = &p40->unk2C.x;
            if (!(f & 0x40)) {
                dst[0] = inv * dst[0] + w * p40->unk08.x;
                dst[1] = inv * dst[1] + w * p40->unk08.y;
                dst[2] = inv * dst[2] + w * p40->unk08.z;
            } else {
                if (!(f & 1)) {
                    dst[0] = inv * dst[0] + w * p40->unk08.x;
                }
                if (!(f & 2)) {
                    dst[1] = inv * dst[1] + w * p40->unk08.y;
                }
                if (!(f & 4)) {
                    dst[2] = inv * dst[2] + w * p40->unk08.z;
                }
            }
        }
            if (p40->unk45 != 0) {
            f = p40->unk45;
            dst = &p40->unk38.x;
            if (!(f & 0x40)) {
                dst[0] = inv * dst[0] + w * p40->unk14.x;
                dst[1] = inv * dst[1] + w * p40->unk14.y;
                dst[2] = inv * dst[2] + w * p40->unk14.z;
            } else {
                if (!(f & 1)) {
                    dst[0] = inv * dst[0] + w * p40->unk14.x;
                }
                if (!(f & 2)) {
                    dst[1] = inv * dst[1] + w * p40->unk14.y;
                }
                if (!(f & 4)) {
                    dst[2] = inv * dst[2] + w * p40->unk14.z;
                }
            }
        }
            p40++;
        }
    } else {
        for (i = 0; i < arg0->unk16; i++) {
            p50 = &arg0->unk84[i];
            if (p50->unk4C != 0) {
            f = p50->unk4C;
            dst = &p50->unk28.x;
            if (!(f & 0x40)) {
                dst[0] = inv * dst[0] + w * p50->unk04.x;
                dst[1] = inv * dst[1] + w * p50->unk04.y;
                dst[2] = inv * dst[2] + w * p50->unk04.z;
            } else {
                if (!(f & 1)) {
                    dst[0] = inv * dst[0] + w * p50->unk04.x;
                }
                if (!(f & 2)) {
                    dst[1] = inv * dst[1] + w * p50->unk04.y;
                }
                if (!(f & 4)) {
                    dst[2] = inv * dst[2] + w * p50->unk04.z;
                }
            }
        }
            if (p50->unk4D != 0) {
            f = p50->unk4D;
            dst = &p50->unk34.x;
            if (!(f & 0x40)) {
                dst[0] = inv * dst[0] + w * p50->unk10.x;
                dst[1] = inv * dst[1] + w * p50->unk10.y;
                dst[2] = inv * dst[2] + w * p50->unk10.z;
            } else {
                if (!(f & 1)) {
                    dst[0] = inv * dst[0] + w * p50->unk10.x;
                }
                if (!(f & 2)) {
                    dst[1] = inv * dst[1] + w * p50->unk10.y;
                }
                if (!(f & 4)) {
                    dst[2] = inv * dst[2] + w * p50->unk10.z;
                }
            }
        }
            if (p50->unk4E != 0) {
            f = p50->unk4E;
            dst = &p50->unk40.x;
            if (!(f & 0x40)) {
                dst[0] = inv * dst[0] + w * p50->unk1C.x;
                dst[1] = inv * dst[1] + w * p50->unk1C.y;
                dst[2] = inv * dst[2] + w * p50->unk1C.z;
            } else {
                if (!(f & 1)) {
                    dst[0] = inv * dst[0] + w * p50->unk1C.x;
                }
                if (!(f & 2)) {
                    dst[1] = inv * dst[1] + w * p50->unk1C.y;
                }
                if (!(f & 4)) {
                    dst[2] = inv * dst[2] + w * p50->unk1C.z;
                }
            }
        }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002EAC0_main);
#endif

#define B4_DUR(p, k) (((s16*) (p)->unk08)[k])
#define B4_COL(p, k) ((u8*) (p)->unk0C + (k) * 4)

s32 func_8002F60C_main(HmfObj* arg0) {
    HmfAnimTrack* p;
    s16 frame;
    s16 sum;
    s16 rem;
    s16 i;
    s16 j;
    s16 k;
    f32 d;

    for (i = 0; i < arg0->unk9C->unk00; i++) {
        p = &arg0->unk9C->unk0C[i];
        frame = arg0->unk9C->unk08;
        sum = 0;
        for (k = 0; k < p->unk02; k++) {
            sum += B4_DUR(p, k);
            if (sum >= frame) {
                break;
            }
        }
        if (k < p->unk02 - 1) {
            rem = frame - (sum - B4_DUR(p, k));
            d = B4_COL(p, k)[4] - B4_COL(p, k)[0];
            arg0->unk8C[p->unk00].unk05[0] = B4_COL(p, k)[0] + d / B4_DUR(p, k) * rem;
            d = B4_COL(p, k)[5] - B4_COL(p, k)[1];
            arg0->unk8C[p->unk00].unk05[1] = B4_COL(p, k)[1] + d / B4_DUR(p, k) * rem;
            d = B4_COL(p, k)[6] - B4_COL(p, k)[2];
            arg0->unk8C[p->unk00].unk05[2] = B4_COL(p, k)[2] + d / B4_DUR(p, k) * rem;
            d = B4_COL(p, k)[7] - B4_COL(p, k)[3];
            d = B4_COL(p, k)[3] + d / B4_DUR(p, k) * rem;
        } else {
            arg0->unk8C[p->unk00].unk05[0] = B4_COL(p, k)[0];
            arg0->unk8C[p->unk00].unk05[1] = B4_COL(p, k)[1];
            arg0->unk8C[p->unk00].unk05[2] = B4_COL(p, k)[2];
            d = B4_COL(p, k)[3];
        }
        for (j = 0; j < arg0->unk10; j++) {
            if (arg0->unk64[j].unk00 == p->unk00) {
                arg0->unk64[j].unk02 = d;
            }
        }
    }
    return 1;
}

extern f32 D_800D2120_main;
extern s16 D_800A1160_main;

void func_8002FB08_main(HmfObj* arg0, f32 arg1) {
    if (!(arg0->unk9C->unk02 & 1)) {
        arg0->unk9C->unk08 += arg1 * D_800D2120_main;
        if (arg0->unk9C->unk04 <= arg0->unk9C->unk08) {
            if (arg0->unk9C->unk02 & 2) {
                arg0->unk9C->unk08 = 0.0f;
            } else {
                arg0->unk9C->unk08 = arg0->unk9C->unk04;
            }
        }
    }
}


void func_8002FB98_main(HmfObj* arg0, f32 arg1) {
    arg0->unkA4 += arg1 * D_800D2120_main;
    if (((HmfMotionSlot*) arg0->unk90)->unk02 <= arg0->unkA4) {
        if (D_800A1160_main != 0) {
            arg0->unkA4 = 0.0f;
        } else {
            arg0->unkA4 = ((HmfMotionSlot*) arg0->unk90)->unk02;
        }
    }
}


void func_8002FC14_main(HmfObj* arg0, f32 arg1) {
    arg0->unkA4 -= arg1 * D_800D2120_main;
    if (arg0->unkA4 < 0.0f) {
        if (D_800A1160_main != 0) {
            arg0->unkA4 = ((HmfMotionSlot*) arg0->unk90)->unk02;
        } else {
            arg0->unkA4 = 0.0f;
        }
    }
}

f32 func_8002FC7C_main(HmfMotionSlot* arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4) {
    arg4 *= D_800A0A78_main * D_800D2120_main;
    if (!(arg1 & 9)) {
        if (!(arg1 & 4)) {
            arg2 += arg4;
            if (arg0->unk02 <= arg2) {
                if (arg1 & 2) {
                    return arg3;
                }
                return arg0->unk02;
            }
        } else {
            arg2 -= arg4;
            if (arg2 < arg3) {
                if (arg1 & 2) {
                    return arg0->unk02 - arg4;
                }
                return arg3;
            }
        }
    }
    return arg2;
}

void func_8002FD48_main(HmfData *arg0) {
    arg0->unkA0 = 0;
}


void func_8002FD50_main(HmfObj* arg0) {
    arg0->unkA4 = ((HmfMotionSlot*) arg0->unk90)->unk02 - 1;
}


s16 func_8002FD70_main(HmfObj* arg0) {
    return arg0->unkA4;
}

void func_8002FE08_main(s16, s16, char*, s16, u16, u16);

void func_8002FD8C_main(s16 arg0, s16 arg1, char* arg2, s16 arg3, s16 arg4) {
    ((void (*)()) func_8002FE08_main)(arg0, arg1, arg2, arg3, arg4, -0x8000);
}


void func_8002FDCC_main(s16 arg0, s16 arg1, char* arg2, s16 arg3, s16 arg4) {
    ((void (*)()) func_8002FE08_main)(arg0, arg1, arg2, arg3, arg4, 0);
}

void func_8002FE08_main(s16 arg0, s16 arg1, char* arg2, s16 arg3, u16 arg4, u16 arg5) {
    HmfMotionSlot* slot;
    HmfObj* hmf;
    HmfMotionTrack* e;
    s16 part;
    s16 i;
    s16 j;

    slot = &MOTION_SLOTS[arg1];
    hmf = (HmfObj*) HmfModelData[arg0].hmf;
    part = func_8002C834_main(hmf, arg2);

    for (i = 0; i < hmf->unk16; i++) {
        for (j = 0; j < hmf->unk84[i].unk00; j++) {
            if (hmf->unk84[i].unk50[j] == part) {
                break;
            }
        }
        if (j != hmf->unk84[i].unk00) {
            break;
        }
    }

    for (j = 0; j < slot->unk00; j++) {
        e = slot->unk08[j];
        if ((e->unk_08 & 0x7FFF) == i && e->unk_00 == arg3 && e->unk_01 == (s16) arg4) {
            e->unk_04 = arg5 | (e->unk_04 & 0x7FFF);
            return;
        }
    }
}

void func_80030030_main(f32 arg0) {
    D_800D2120_main = arg0;
}
