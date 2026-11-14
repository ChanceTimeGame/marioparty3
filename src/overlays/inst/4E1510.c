#include "common.h"
#include "inst.h"
#include "malloc.h"
#include "mallocblock.h"
#include "game/hvq.h"

extern s32 D_8010D520_inst;
extern s32 D_8010D524_inst;
void func_80108808_inst(omObjData *);
void func_80108870_inst(omObjData *);
void func_80108954_inst(omObjData *);
void func_8010C848_inst(void);
extern InstBoard D_8010DDE8_inst; /* the second host */
extern s32 D_8010D530_inst;
extern s32 D_8010D534_inst;
void func_8010986C_inst(omObjData *);
void func_801098D8_inst(omObjData *);
void func_801099C0_inst(omObjData *);
void func_80109A84_inst(omObjData *);
void func_801097DC_inst(omObjData *);
extern s32 D_8010DC30_inst; /* the second host's texture animation */
extern s16 D_8010DC32_inst; /* low half of D_8010DC30_inst */
extern void (*D_8010DDEC_inst)(omObjData *); /* D_8010DDE8_inst.func */
void func_8010C8D0_inst(void);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_8002C834_main(HmfData *, char *);

/* Process: the host character (model 0xA0075 with its motions and texture animation) beside
   the board; runs its handler (D_8010DDE0_inst.func) every frame. */
void func_80108350_inst(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x19, 5, 5, -1, NULL);
    D_8010DDE0_inst.obj = obj;
    obj->model[0] = func_8000B108_main(0xA0075, 0x16A9);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0xA0077);
    func_8000B460_main(obj, 2, 0xA0078);
    func_8000B460_main(obj, 3, 0xA0079);
    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    data = DataRead(0xA007E);
    D_8010DC20_inst.anim = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80032FC0_main(D_8010DC22_inst, 1, 0);
    func_80032FF8_main(D_8010DC22_inst, 0);
    D_8010DC28_inst = func_80032694_main(HmfModelData[obj->model[0]].hmf, D_8010DC22_inst, 0, "c204n_0_DEF");
    D_8010DC20_inst.anim = D_800D1714_main[D_8010DC20_inst.anim].unk_00;
    data = DataRead(0xA007F);
    D_8010DC20_inst.unk4 = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80108A18_inst(obj->model[0], D_8010DC28_inst, D_8010DC22_inst);
    obj->trans.x = -86.0f;
    obj->trans.y = -148.0f;
    obj->trans.z = 253.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 0.4f;
    Hu3DModelScaleSet(obj->model[0], 0.4f, 0.4f, 0.4f);
    func_8001C258_main(obj->model[0], 4, 4);
    if (D_8010D408_inst == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[3]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C258_main(obj->model[0], 4, 0);
        obj->trans.x = -86.0f;
        obj->trans.y = 52.0f;
        obj->trans.z = 253.0f;
        obj->rot.x = -20.0f;
        obj->rot.y = 15.0f;
        D_8010DDE0_inst.func = func_80108A10_inst;
    } else {
        D_8010DDE0_inst.func = func_8010872C_inst;
    }
    while (TRUE) {
        D_8010DDE0_inst.func(obj);
        HuPrcVSleep();
    }
}

/* Host handlers: below the screen, waits, jumps up (sound 0x2A7), lands and idles. */
void func_8010872C_inst(omObjData *obj) {
    obj->trans.x = -86.0f;
    obj->trans.y = -148.0f;
    obj->trans.z = 253.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    func_80108A18_inst(obj->model[0], D_8010DC28_inst, D_8010DC22_inst);
    D_8010DDE0_inst.func = func_80108808_inst;
}

void func_80108808_inst(omObjData *obj) {
    if (++D_8010D520_inst >= 100) {
        func_8001C258_main(obj->model[0], 4, 0);
        HuAudFXPlay(0x135);
        D_8010DDE0_inst.func = func_80108870_inst;
        D_8010D520_inst = 0;
        func_8010C8D0_inst();
    }
}

void func_80108870_inst(omObjData *obj) {
    D_8010D524_inst++;
    obj->trans.y = sindf(D_8010D524_inst * 5) * 200.0f + -148.0f;
    if (D_8010D524_inst >= 17) {
        obj->trans.y = 52.0f;
        D_8010D524_inst = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[2]);
        func_8001C814_main(obj->model[0], 2, 0);
        HuPrcSleep(10);
        HuAudFXPlay(0x2A7);
        D_8010DDE0_inst.func = func_80108954_inst;
    }
}

void func_80108954_inst(omObjData *obj) {
    s16 m = obj->model[0];
    f32 frame = HmfModelData[m].unk40;

    if (D_800CCF58_main[HmfModelData[m].unk02].unk02 <= frame) {
        func_8001C5B4_main(m, obj->motion[3]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8010C848_inst();
        D_8010DDE0_inst.func = func_80108A10_inst;
    }
}

void func_80108A10_inst(omObjData *obj) {
}

/* Starts texture animation anim of model at frame (frame -1: plays it as it is). */
#ifdef NON_MATCHING
/* Instruction-identical, but retail has a nop after it (func_80108AF0_inst is 16-byte
   aligned in retail; no file split explains it, see the report). */
void func_80108A18_inst(s16 model, s16 anim, s16 frame) {
    TexAnimSlot *slot;

    if (anim >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            slot = &D_800D1714_main[anim];
            slot->unk_00 = frame;
            slot->unk_04 = 0;
            slot->unk_0A = 0;
            slot->unk_06 = 0;
            slot->unk_02 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108A18_inst);
#endif

/* A face of a model part (HmfModelData_Unk64_Unk60_Unk54_Struct): count vertex indices. */
typedef struct InstFace {
    /* 0x00 */ u8 count;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ s16 vtx[4];
    /* 0x0C */ char unk0C[0x28];
} InstFace; /* size 0x34 */
#define INST_POS(hmf) ((s16(*)[3])(hmf)->unk50)
#define INST_FACES(obj) ((InstFace *)(obj)->unk54)
#define INST_GFX(pkt, a, b) \
    { \
        Gfx *_g = (Gfx *)(pkt); \
        _g->words.w0 = (a); \
        _g->words.w1 = (b); \
    }

/* Decodes the HVQ image (data, an RGBA5551 128x96 picture) and its 8-bit alpha (alpha, at
   the offset its header's bytes 0x0A/0x0B give) into an RGBA32 texture, then builds the
   display list of model's "gamen" (screen) part: each face gets its own texture tile, the
   bounding box of the face within the whole part mapped onto the picture. */
#ifdef NON_MATCHING
/* Masked 5: retail loads the first pass's vertex index twice (lhu into the kept index, lh
   for the first compare); the rest is register allocation (data/alpha argument registers,
   the pixel loop's float registers). */
void func_80108AF0_inst(s16 model, void *start, void *data, void *alpha) {
    HmfData *hmf;
    u16 *pixels;
    u8 *work;
    u8 *tex;
    u8 *mask;
    s16 w;
    s16 h;
    f32 x;
    f32 y;
    s16 i;
    s16 j;
    s16 part;
    HmfModelData_Unk64_Unk60_Struct *obj;
    Vtx *vtx;
    Vtx *vtxStart;
    Gfx *gfx;
    Gfx *dl;
    s16 n;
    f32 s, tt;
    s32 tuls, tlrs, tult, tlrt;
    f32 minX, maxX, minY, maxY;
    f32 baseX, baseY;
    f32 rangeX, rangeY;
    f32 vx, vy;
    u16 c;
    u16 k;

    w = 0x80;
    h = 0x60;
    hmf = HmfModelData[model].hmf;
    pixels = HuMemMemoryAllocPerm(0x6000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(start);
    work = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(data, pixels, 0x80, work);
    HuMemMemoryFreePerm(work);
    tex = HuMemAllocTag(0xC000, hmf->unk0E);
    mask = (u8 *)alpha + ((((u8 *)alpha)[10] << 16) + ((u8 *)alpha)[11]);
    i = 0;
    for (y = 0.0f; y < h; y += 1.0f) {
        for (x = 0.0f; x < w; x += 1.0f) {
            c = pixels[i];
            tex[i * 4 + 0] = (c >> 8) & 0xF8;
            tex[i * 4 + 1] = (c >> 3) & 0xF8;
            tex[i * 4 + 2] = (c << 2) & ~7;
            tex[i * 4 + 3] = mask[i];
            i++;
        }
    }
    HuMemMemoryFreePerm(pixels);
    part = func_8002C834_main(hmf, "gamen");
    obj = &hmf->unk60[part];
    vtx = HuMemAllocTag(0x640, hmf->unk0E);
    dl = HuMemAllocTag(0x2000, hmf->unk0E);
    hmf->unk3C->unk00[part] = gfx = dl;
    obj->unk50 |= 0x10000;
    INST_GFX(gfx++, 0xFCFFFFFF, 0xFFFCF279); /* combine: texture colour, texture x shade alpha */
    INST_GFX(gfx++, 0xE200001C, 0x005049D8); /* render mode */
    gSPClearGeometryMode(gfx++, G_LIGHTING);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    maxX = -100000.0f;
    maxY = -100000.0f;
    minX = 100000.0f;
    minY = 100000.0f;
    for (i = 0; i < obj->unk22; i++) {
        for (j = 0; j < INST_FACES(obj)[i].count; j++) {
            k = INST_FACES(obj)[i].vtx[j];
            if (INST_POS(hmf)[INST_FACES(obj)[i].vtx[j]][0] < minX) {
                minX = INST_POS(hmf)[(s16)k][0];
            }
            if (maxX < INST_POS(hmf)[(s16)k][0]) {
                maxX = INST_POS(hmf)[(s16)k][0];
            }
            if (INST_POS(hmf)[(s16)k][1] < minY) {
                minY = INST_POS(hmf)[(s16)k][1];
            }
            if (maxY < INST_POS(hmf)[(s16)k][1]) {
                maxY = INST_POS(hmf)[(s16)k][1];
            }
        }
    }
    rangeX = maxX - minX;
    rangeY = maxY - minY;
    baseX = minX;
    baseY = minY;
    for (i = 0; i < obj->unk22; i++) {
        vtxStart = vtx;
        maxX = -100000.0f;
        maxY = -100000.0f;
        minX = 100000.0f;
        minY = 100000.0f;
        for (j = 0; j < INST_FACES(obj)[i].count; j++) {
            n = INST_FACES(obj)[i].vtx[j];
            vx = vtx->v.ob[0] = INST_POS(hmf)[n][0];
            vy = vtx->v.ob[1] = INST_POS(hmf)[n][1];
            vtx->v.ob[2] = INST_POS(hmf)[n][2];
            if (vx < minX) {
                minX = vx;
            }
            if (maxX < vx) {
                maxX = vx;
            }
            if (vy < minY) {
                minY = vy;
            }
            if (maxY < vy) {
                maxY = vy;
            }
            vtx->n.n[0] = vtx->n.n[1] = vtx->n.n[2] = -1; /* white */
            s = w - w * ((-vx - baseX) / rangeX);
            tt = h * ((-vy - baseY) / rangeY);
            vtx->v.tc[0] = s * 32.0f;
            vtx->v.tc[1] = tt * 32.0f;
            vtx->v.cn[3] = 0xFF;
            vtx++;
        }
        minX = ((minX - baseX) / rangeX) * w;
        maxX = ((maxX - baseX) / rangeX) * w;
        minY = h - ((minY - baseY) / rangeY) * h;
        if (minY == h) {
            minY = h - 0.1f;
        }
        maxY = h - ((maxY - baseY) / rangeY) * h;
        tult = maxY;
        tlrt = minY;
        tlrs = maxX;
        tuls = minX;
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPLoadTextureTile(gfx++, tex, G_IM_FMT_RGBA, G_IM_SIZ_32b, w, h, (s16)tuls, (u16)tult,
                           (s16)tlrs, (u16)tlrt, 0, 0, 0, 0, 0, 0, 0);
        gSPVertex(gfx++, vtxStart, INST_FACES(obj)[i].count, 0);
        if (INST_FACES(obj)[i].count == 3) {
            gSP1Triangle(gfx++, 0, 1, 2, 0);
        } else {
            gSP1Quadrangle(gfx++, 0, 1, 2, 3, 0);
        }
    }
    gSPEndDisplayList(gfx++);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108AF0_inst);
#endif

/* Process: the second host character (model 0xA0000, the 2-player screen) beside the board;
   runs its handler (D_8010DDE8_inst.func) every frame. */
void func_801094B0_inst(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x19, 5, 8, -1, NULL);
    D_8010DDE8_inst.obj = obj;
    obj->model[0] = func_8000B108_main(0xA0000, 0x16A9);
    func_8000B460_main(obj, 0, 0xA0001);
    func_8000B460_main(obj, 1, 0xA0002);
    func_8000B460_main(obj, 2, 0xA0006);
    func_8000B460_main(obj, 3, 0xA0023);
    func_8000B460_main(obj, 4, 0xA0018);
    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    data = DataRead(0xA002A);
    D_8010DC30_inst = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c160n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80032FC0_main(D_8010DC32_inst, 1, 0);
    func_80032FF8_main(D_8010DC32_inst, 0);
    obj->trans.x = -91.0f;
    obj->trans.y = -171.0f;
    obj->trans.z = 210.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 0.4f;
    Hu3DModelScaleSet(obj->model[0], 0.4f, 0.4f, 0.4f);
    func_8001C258_main(obj->model[0], 4, 4);
    if (D_8010D408_inst == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[3]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C258_main(obj->model[0], 4, 0);
        obj->trans.x = -91.0f;
        obj->trans.y = 29.0f;
        obj->trans.z = 210.0f;
        obj->rot.x = -20.0f;
        obj->rot.y = 15.0f;
        D_8010DDE8_inst.func = func_80109A84_inst;
    } else {
        D_8010DDEC_inst = func_801097DC_inst;
    }
    while (TRUE) {
        D_8010DDEC_inst(obj);
        HuPrcVSleep();
    }
}

/* Second host's handlers (the 2-player screen): waits, jumps up (sound 0x298), lands. */
void func_801097DC_inst(omObjData *obj) {
    obj->trans.x = -91.0f;
    obj->trans.y = -171.0f;
    obj->trans.z = 210.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010DDE8_inst.func = func_8010986C_inst;
}

void func_8010986C_inst(omObjData *obj) {
    if (++D_8010D530_inst >= 100) {
        D_8010DDE8_inst.func = func_801098D8_inst;
        D_8010D530_inst = 0;
        func_8001C258_main(obj->model[0], 4, 0);
        HuAudFXPlay(0x298);
        func_8010C8D0_inst();
    }
}

void func_801098D8_inst(omObjData *obj) {
    D_8010D534_inst++;
    obj->trans.y = sindf(D_8010D534_inst * 5) * 200.0f + -171.0f;
    if (D_8010D534_inst == 13) {
        func_8001C5B4_main(obj->model[0], obj->motion[4]);
        func_8001C814_main(obj->model[0], 2, 0);
    }
    if (D_8010D534_inst >= 17) {
        obj->trans.y = 29.0f;
        D_8010D534_inst = 0;
        D_8010DDE8_inst.func = func_801099C0_inst;
    }
}

/* Retail indexes HmfModelData with the motion id (obj->motion[3]) for the blend length. */
#ifdef NON_MATCHING
/* Masked 2: the HmfModelData load is scheduled before the model index. */
void func_801099C0_inst(omObjData *obj) {
    HmfModel *models;
    HmfModel *model;
    s16 m;

    m = obj->model[0];
    models = HmfModelData;
    model = &models[m];

    if (D_800CCF58_main[model->unk02].unk02 <= model->unk40) {
        func_8001C624_main(m, models[obj->motion[3]].unk02, 0, 30, 2);
        func_8010C848_inst();
        D_8010DDE8_inst.func = func_80109A84_inst;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801099C0_inst);
#endif

void func_80109A84_inst(omObjData *obj) {
}

/* .data (8010D520). Retail has 8 zero bytes after each host's pair of counters (the text
   also pads to 16 bytes after func_80108A18_inst and func_80108AF0_inst), but the unit's
   rodata strings run on without a file boundary, so the unit stays one file here. */
s32 D_8010D520_inst = 0; /* the host's wait timer */
s32 D_8010D524_inst = 0; /* the host's jump frame */
s32 D_8010D528_inst[2] = { 0, 0 }; /* unreferenced */
s32 D_8010D530_inst = 0; /* the second host's wait timer */
s32 D_8010D534_inst = 0; /* the second host's jump frame */
