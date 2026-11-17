#include "common.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkStaff {
    char unk_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkStaff;

typedef struct UnkStaff_1 {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[8];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
} UnkStaff_1;

typedef struct UnkStaff_2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} UnkStaff_2;

void func_80105E6C_staff(void *, s16 *, s32);
void func_8010C680_staff(s16 *, s32 *, f32 *, void *);
void func_8010C8F4_staff(UnkStaff_1 *);
void func_8010CD74_staff(UnkStaff_1 *);
void func_8010CFD4_staff(UnkStaff *);
extern f32 D_80110534_staff;
extern s8 D_80110538_staff;
extern char D_80110FF4_staff[]; // unk type
extern Vec D_80111534_staff;
extern Vec D_80111540_staff;
extern f32 D_80111560_staff;
extern f32 D_80111564_staff;

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801059A0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105BD4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105CB4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105DB8_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105E6C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105F48_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010601C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106044_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010609C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010615C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106720_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010674C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106C50_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106E20_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801073EC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107508_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107740_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107A9C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107B1C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107BA0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107DBC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107EB8_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801085F0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801088F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010919C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801091CC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109264_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801095E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010992C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010998C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D08_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D74_staff);

// story j2
#include "mallocblock.h"

typedef struct StaffTextGrp {
    /* 0x00 */ s16 grp;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 count;
} StaffTextGrp; // size 0x8: one line of sprite-letter text

extern s32 D_80110AA0_staff[]; // set 0 letter sprite files
extern s32 D_80110B0C_staff[]; // set 1 letter sprite files
extern s16 D_80111490_staff[27];
extern StaffTextGrp *D_801114C8_staff;
extern s16 D_801114D0_staff[28];
extern StaffTextGrp *D_80111508_staff;
extern u16 D_8011150C_staff;
extern u16 D_8011150E_staff;
void func_8005BF70_main(s16 winId, s32 alpha);
typedef struct StaffS16Vec {
    s16 x;
    s16 y;
    s16 z;
} StaffS16Vec;

typedef struct StaffScript {
    /* 0x00 */ f32 scale; // 0 ends the script
    /* 0x04 */ s32 file;
    /* 0x08 */ s32 file2; // optional attached model
    /* 0x0C */ StaffS16Vec unkC;
    /* 0x12 */ s16 type;
    /* 0x14 */ s16 param;
    /* 0x16 */ s16 anim; // 1-based index into D_80110674_staff
} StaffScript; // size 0x18

typedef struct StaffActor {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 model;
    /* 0x1E */ s16 model2;
    /* 0x20 */ s16 anim;
    /* 0x22 */ StaffS16Vec unk22;
    /* 0x28 */ s16 models[4];
    /* 0x30 */ s16 anim2;
    /* 0x32 */ s16 anim3;
    /* 0x34 */ s16 type;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 flags;
} StaffActor; // size 0x3C

typedef struct StaffAnimDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ char *name;
} StaffAnimDef;

extern StaffAnimDef D_80110674_staff[];
void func_80034048_main(s16, s16);
typedef struct StaffWork {
    /* 0x00 */ StaffActor *actors;
    /* 0x04 */ s16 state; // 1 ends the credits actors
    /* 0x06 */ char unk06[6];
} StaffWork; // size 0xC

extern StaffScript D_80110704_staff[];
StaffScript *func_80109D74_staff(StaffActor *actors, StaffScript *script);
void func_8010A848_staff(void);
typedef struct StaffMdl {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ s16 model;
    /* 0x1A */ s16 model2;
    /* 0x1C */ s16 anim;
    /* 0x1E */ s16 model4; // < 0 when absent
} StaffMdl; // size 0x20: the file head's UnkStaff

typedef struct StaffFlyer {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 unk18; // angle
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 model;
    /* 0x2A */ s16 unk2A;
} StaffFlyer; // size 0x2C: the file head's UnkStaff_1 (its 0x18/0x1C are f32)

extern Vec D_80110FA0_staff[3];
u32 func_8010601C_staff(void);
typedef struct StaffLine {
    /* 0x00 */ Vec pos; // portrait model position
    /* 0x0C */ s16 x;
    /* 0x0E */ s16 y; // scrolls up one per frame
    /* 0x10 */ s16 line0; // set-0 text line (name)
    /* 0x12 */ s16 line1; // set-1 text line (title)
    /* 0x14 */ s16 esprite;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 model;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 type; // 0 free, 1 title, 2 sprite, 3 name, 4 name with portrait
} StaffLine; // size 0x20

typedef struct StaffCredit {
    /* 0x00 */ s8 type; // -1 ends this list
    /* 0x01 */ s8 delay;
    /* 0x02 */ u16 mes;
} StaffCredit;

extern s32 D_80110B80_staff[];
extern StaffCredit *D_80110F04_staff[]; // NULL-terminated
void func_8010992C_staff(Process *proc, s16 arg1);
void func_8010998C_staff(Process *proc, s16 *arg1, s16 *arg2, void *line);
void func_80109D08_staff(Process *proc, s16 arg1, void *line);
StaffScript *func_80109F34_staff(StaffActor *e, StaffScript *script);
void func_8010BA30_staff(s16 set, s16 idx, u32 mes, s16 x, s16 y);
// end story j2

#ifdef NON_MATCHING
// Register allocation: retail keeps attach in fp and spills sub; logic checked block by block.
StaffScript *func_80109F34_staff(StaffActor *e, StaffScript *script) {
    s32 attach;
    void *data;
    s32 i;
    s16 mdl;
    s16 m;
    s16 sub;

    e->flags = 0;
    switch (e->type) {
    case 7:
        for (i = 0; i < 4; i++) {
            func_8001ACDC_main(e->models[i]);
        }
        func_80033354_main(e->anim);
        func_80033354_main(e->anim2);
        break;
    case 4:
    case 8:
    case 10:
        func_8001ACDC_main(e->models[0]);
        break;
    case 12:
        func_80046558_main(e->model);
        break;
    }
    if (e->anim3 >= 0) {
        func_80033354_main(e->anim3);
    }
    if (e->model >= 0) {
        func_8001ACDC_main(e->model);
    }
    if (e->model2 >= 0) {
        func_8001ACDC_main(e->model2);
    }
    e->model2 = e->model = -1;
    HuPrcVSleep();
    if (script->scale == 0.0f) {
        return script;
    }
    e->type = script->type;
    attach = 0;
    data = DataRead(script->file);
    HuPrcVSleep();
    HuPrcVSleep();
    e->model = mdl = Hu3DModelCreate(data, 0x2AD);
    func_8001C814_main(mdl, -1, 2);
    Hu3DModelScaleSet(mdl, script->scale, script->scale, script->scale);
    e->unk22 = script->unkC;
    HuPrcVSleep();
    HuPrcVSleep();
    e->anim3 = -1;
    if (script->anim != 0) {
        i = script->anim - 1;
        attach = 1;
        data = DataRead(D_80110674_staff[i].file);
        HuPrcVSleep();
        HuPrcVSleep();
        e->anim3 = HmfAnimCreate(HmfModelData[mdl].hmf, data, 0, D_80110674_staff[i].name);
        HuMemMemoryFreePerm(data);
        HuPrcVSleep();
    }
    if (script->file2 != 0) {
        data = DataRead(script->file2);
        HuPrcVSleep();
        HuPrcVSleep();
        sub = Hu3DModelCreate(data, 0x1D);
        HuPrcVSleep();
        func_8001C5B4_main(mdl, sub);
        func_8001C814_main(mdl, -1, 2);
        e->model2 = sub;
    }
    switch (e->type) {
    case 1:
        e->unk36 = 0;
        e->rot.x = e->rot.y = e->rot.z = 0.0f;
        e->unk18 = 90.0f;
        Hu3DModelRotSet(mdl, 0.0f, 90.0f, 0.0f);
        break;
    case 2:
        e->unk36 = 0;
        e->unk38 = script->param;
        e->unk18 = 0.0f;
        e->rot.x = e->rot.y = e->rot.z = e->unk18;
        break;
    case 3:
        e->unk18 = 0.0f;
        e->unk36 = 30;
        e->rot.x = 0.0f;
        func_8001FA68_main(mdl);
        func_8001F9E4_main(mdl, 0xFF);
        break;
    case 4:
        e->unk36 = script->param;
        data = DataRead(0xA00C3);
        HuPrcVSleep();
        HuPrcVSleep();
        e->models[0] = m = Hu3DModelCreate(data, 0x2AD);
        Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
        func_8001C5B4_main(m, sub);
        func_8001C814_main(m, -1, 2);
        HuPrcVSleep();
        func_8001C514_main(m);
        HuPrcVSleep();
        break;
    case 5:
    case 11:
        e->unk18 = 0.0f;
        break;
    case 6:
        e->unk18 = e->rot.x = e->rot.y = e->rot.z = 0.0f;
        e->unk36 = e->unk38 = 0;
        break;
    case 7:
        data = DataRead(0xA008C);
        HuPrcVSleep();
        attach = 1;
        HuPrcVSleep();
        e->anim = HmfAnimCreate(HmfModelData[mdl].hmf, data, 0, "c201n_00_DEF");
        func_80034048_main(e->anim, 5);
        HuMemMemoryFreePerm(data);
        HuPrcVSleep();
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                data = DataRead(script->file);
                HuPrcVSleep();
                HuPrcVSleep();
                m = Hu3DModelCreate(data, 0x2AD);
                HuPrcVSleep();
                data = DataRead(0xA008D);
                HuPrcVSleep();
                HuPrcVSleep();
                e->anim2 = HmfAnimCreate(HmfModelData[m].hmf, data, 0, "c201n_00_DEF");
                HuMemMemoryFreePerm(data);
                HuPrcVSleep();
                func_80034048_main(e->anim2, 8);
                func_8001C448_main(m);
                func_8001C514_main(m);
                break;
            case 1:
                data = DataRead(script->file);
                HuPrcVSleep();
                HuPrcVSleep();
                m = Hu3DModelCreate(data, 0x2AD);
                HuPrcVSleep();
                data = DataRead(0xA008D);
                HuPrcVSleep();
                HuPrcVSleep();
                e->anim3 = HmfAnimCreate(HmfModelData[m].hmf, data, 0, "c201n_00_DEF");
                HuMemMemoryFreePerm(data);
                HuPrcVSleep();
                func_8001C448_main(m);
                func_8001C514_main(m);
                break;
            case 2:
                m = Hu3DModelLink(e->models[1]);
                break;
            case 3:
                m = Hu3DModelLink(e->models[0]);
                break;
            }
            e->models[i] = m;
            func_8001C814_main(m, -1, 2);
            Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
            HuPrcVSleep();
        }
        HuPrcVSleep();
        HuPrcVSleep();
        break;
    case 8:
        e->models[0] = m = Hu3DModelLink(mdl);
        e->unk36 = script->param;
        func_8001C814_main(m, -1, 2);
        func_8001C6A8_main(m, D_800CCF58_main[HmfModelData[m].unk02].unk02 * 0.5f);
        Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
        Hu3DModelRotSet(mdl, -15.0f, 80.0f, 0.0f);
        Hu3DModelRotSet(m, -15.0f, -80.0f, 0.0f);
        break;
    case 10:
        e->models[0] = m = Hu3DModelLink(mdl);
        e->unk36 = script->param;
        func_8001C814_main(m, -1, 2);
        func_8001C6A8_main(m, D_800CCF58_main[HmfModelData[m].unk02].unk02 * 0.5f);
        Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
        Hu3DModelRotSet(mdl, 0.0f, -30.0f, 0.0f);
        Hu3DModelRotSet(m, 0.0f, 30.0f, 0.0f);
        break;
    case 12:
        func_800461B4_main(mdl);
        break;
    case 9:
        Hu3DModelRotSet(mdl, -30.0f, script->param, 0.0f);
        break;
    case 0:
    default:
        if (script->param != 0) {
            Hu3DModelRotSet(mdl, 0.0f, script->param, 0.0f);
        }
        break;
    }
    if (attach) {
        func_8001C448_main(mdl);
    }
    func_8001C514_main(mdl);
    e->flags = 1;
    HuPrcVSleep();
    return script + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109F34_staff);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010A848_staff);

void func_8010B1E0_staff(void) {
    StaffActor actors[3];
    StaffWork *w;
    Process *proc;
    StaffScript *script;
    StaffActor *a;
    s32 i;
    s16 cur;

    w = HuMemAllocTag(sizeof(StaffWork), 0x7918);
    memset(w, 0, sizeof(StaffWork));
    cur = 0;
    HuPrcCurrentGet()->user_data = w;
    proc = omAddPrcObj(func_8010A848_staff, 0x4000, 0x800, 0);
    proc->user_data = actors;
    w->actors = actors;
    script = func_80109D74_staff(actors, D_80110704_staff);
    while (cur >= 0) {
        if (cur != w->state) {
            switch (w->state) {
            default:
            case 0:
                cur = w->state;
                break;
            case 1:
                cur = -1;
                continue;
            }
        }
        for (a = actors, i = 0; i < 3; i++, a++) {
            if (a->flags != 0 && (a->flags & 4)) {
                script = func_80109F34_staff(a, script);
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(proc);
    for (a = actors, i = 0; i < 3; i++, a++) {
        if (a->flags != 0) {
            a->flags = 0;
            switch (a->type) {
            case 7:
                for (i = 0; i < 4; i++) {
                    func_8001ACDC_main(a->models[i]);
                }
                func_80033354_main(a->anim);
                func_80033354_main(a->anim2);
                break;
            case 4:
            case 8:
            case 10:
                func_8001ACDC_main(a->models[0]);
                break;
            case 12:
                func_80046558_main(a->model);
                break;
            }
            if (a->anim3 >= 0) {
                func_80033354_main(a->anim3);
            }
            if (a->model >= 0) {
                func_8001ACDC_main(a->model);
            }
            if (a->model2 >= 0) {
                func_8001ACDC_main(a->model2);
            }
            a->model2 = a->model = -1;
        }
    }
    HuMemFree(w);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010B430_staff(s16 group, s16 member, s16 dx, s16 dy) {
    HuSprGrp *grp = HuSprGrpData[group];
    HuSprite *spr = grp->members[member];

    if ((dx != 0) | (dy != 0)) {
        grp->unk_0C = 1;
        spr->unk_48 = dx + spr->unk_48;
        spr->unk_4C = dy + spr->unk_4C;
    }
}

void func_8010B4B4_staff(s16 group, s16 member, s16 y) {
    f32 fy = y;
    HuSprGrp *grp = HuSprGrpData[group];
    HuSprite *spr = grp->members[member];

    if (spr->unk_4C != fy) {
        grp->unk_0C = 1;
        spr->unk_4C = fy;
    }
}

void func_8010B514_staff(s16 set, s16 count) {
    s16 *sprIds;
    s16 *id;
    s32 *files;
    s16 numSpr;
    s16 numMembers;
    s32 i;
    s32 j;
    StaffTextGrp *grps;
    StaffTextGrp *g;
    s16 grp;

    switch (set) {
    default:
    case 0:
        sprIds = D_80111490_staff;
        numMembers = 24;
        files = D_80110AA0_staff;
        numSpr = 27;
        break;
    case 1:
        numMembers = 28;
        sprIds = D_801114D0_staff;
        files = D_80110B0C_staff;
        numSpr = 28;
        break;
    }
    id = sprIds;
    for (i = 0; i < numSpr; i++) {
        *id++ = func_8000B838_main(*files++);
    }
    grps = HuMemAllocTag(count * sizeof(StaffTextGrp), 0x7918);
    g = grps;
    for (i = 0; i < count; i++, g++) {
        g->x = 160;
        g->y = 120;
        g->count = 0;
        g->grp = grp = HuSprGrpCreate(numMembers, 2);
        for (j = 0; j < numMembers; j++) {
            func_80055458_main(grp, j, 0x100);
            HuSprAttrReset(grp, j, 0xFFFF);
            HuSprAttrSet(grp, j, 0x9000);
            HuSprScaleSet(grp, j, 1.0f, 1.0f);
            func_800550F4_main(grp, j, 0);
            HuSprPriSet(grp, j, 400);
            func_80055420_main(grp, j, 0xFF, 0xFF, 0xFF);
            if (j != 0) {
                func_800554C4_main(grp, j, 0);
            } else {
                func_800554C4_main(grp, 0, -1);
            }
        }
    }
    switch (set) {
    default:
    case 0:
        D_801114C8_staff = grps;
        D_8011150C_staff = count;
        break;
    case 1:
        D_80111508_staff = grps;
        D_8011150E_staff = count;
        break;
    }
}

void func_8010B794_staff(s16 set) {
    StaffTextGrp *grps;
    s16 *sprIds;
    s16 count;
    s16 numSpr;
    StaffTextGrp *g;
    s32 i;

    switch (set) {
    default:
    case 0:
        grps = D_801114C8_staff;
        sprIds = D_80111490_staff;
        count = D_8011150C_staff;
        numSpr = 27;
        break;
    case 1:
        numSpr = 28;
        grps = D_80111508_staff;
        sprIds = D_801114D0_staff;
        count = D_8011150E_staff;
        break;
    }
    g = grps;
    if (grps != NULL) {
        for (i = 0; i < count; i++, g++) {
            HuSprGrpKill(g->grp);
        }
        HuMemFree(grps);
        for (i = 0; i < numSpr; i++, sprIds++) {
            HuSprKill(*sprIds);
        }
        switch (set) {
        default:
        case 0:
            D_801114C8_staff = NULL;
            break;
        case 1:
            D_80111508_staff = NULL;
            break;
        }
    }
}

void func_8010B8C0_staff(s16 set, s16 idx, s16 show) {
    StaffTextGrp *g;
    s16 n;
    s16 grp;
    s32 i;

    switch (set) {
    default:
    case 0:
        g = &D_801114C8_staff[idx];
        break;
    case 1:
        g = &D_80111508_staff[idx];
        break;
    }
    n = g->count;
    if (n != 0) {
        grp = g->grp;
        if (show != 0) {
            for (i = 0; i < n; i++) {
                HuSprAttrReset(grp, i, 0x8000);
            }
        } else {
            for (i = 0; i < n; i++) {
                HuSprAttrSet(grp, i, 0x8000);
            }
        }
    }
}

void func_8010B9BC_staff(s16 set, s16 idx, s16 x, s16 y) {
    StaffTextGrp *g;

    switch (set) {
    default:
    case 0:
        g = &D_801114C8_staff[idx];
        break;
    case 1:
        g = &D_80111508_staff[idx];
        break;
    }
    if (g->count != 0) {
        func_80054904_main(g->grp, 0, x, y);
    }
}

#ifdef NON_MATCHING
// Register allocation: retail keeps g in s8 and spills x, y and str; logic checked block by block.
void func_8010BA30_staff(s16 set, s16 idx, u32 mes, s16 x, s16 y) {
    s16 pos[24];
    StaffTextGrp *g;
    s16 *sprIds;
    s16 numMembers;
    s16 step;
    s16 width;
    s16 n;
    u8 c;
    s32 i;
    s16 ofs;
    u8 *str;
    u8 *buf;
    s16 grp;
    s16 extraI;

    switch (set) {
    default:
    case 0:
        g = &D_801114C8_staff[idx];
        sprIds = D_80111490_staff;
        numMembers = 24;
        extraI = -2;
        step = 10;
        break;
    case 1:
        g = &D_80111508_staff[idx];
        sprIds = D_801114D0_staff;
        numMembers = 28;
        extraI = 0;
        step = 10;
        break;
    }
    grp = g->grp;
    n = g->count;
    if (n != 0) {
        for (i = 0; i < n; i++) {
            HuSprAttrSet(grp, i, 0x8000);
        }
    }
    g->x = x;
    g->y = y;
    buf = NULL;
    if (mes > 0x80000000U) {
        str = (u8 *)mes;
    } else {
        str = buf = func_800364DC_main((void *)mes);
    }
    width = 0;
    for (n = 1; n < numMembers; str++) {
        c = *str;
        if (c == 0) {
            break;
        }
        if ((u32)(c - 'a') < 26) {
            c -= 0x20;
        }
        if ((c == 0x10) | (c == ' ')) {
            width += step;
        } else if (c == 0x1A) {
            width += step;
        } else if ((u8)(c - 'A') < 26) {
            c -= 'A';
            func_80055024_main(grp, n, sprIds[c], 0);
            if (n != 0) {
                func_800554C4_main(grp, n, 0);
            }
            pos[n] = width;
            width += step;
            if (c == 'I' - 'A') {
                width += extraI;
            }
            n++;
        } else if (c == '3') {
            func_80055024_main(grp, n, sprIds[26], 0);
            if (n != 0) {
                func_800554C4_main(grp, n, 0);
            }
            pos[n] = width;
            width += step;
            n++;
        } else if ((u8)(c - '[') < 2) {
            c -= 'A';
            func_80055024_main(grp, n, sprIds[c], 0);
            if (n != 0) {
                func_800554C4_main(grp, n, 0);
            }
            pos[n] = width;
            width += step;
            n++;
        }
    }
    if (width > step) {
        width -= step;
    }
    ofs = -(width >> 1);
    func_80054904_main(grp, 0, g->x, g->y);
    for (i = 1; i < n; i++) {
        func_80054904_main(grp, i, ofs + pos[i], 0);
        HuSprAttrReset(grp, i, 0x8000);
    }
    g->count = n;
    if (buf != NULL) {
        func_800365E8_main(buf);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BA30_staff);
#endif

void func_8010BE20_staff(s16 *wins, s16 count) {
    s32 i;
    s16 win;

    for (i = 0; i < count; i++) {
        *wins = win = func_8005A968_main(-120, -50, 240, 20, 0, 12);
        func_8005BCA4_main(win, 120, 10);
        func_8005BDFC_main(win, 0);
        func_8005BEE0_main(win, 0);
        func_8005C060_main(win, 2, 0xFF, 0, 0);
        func_8005C060_main(win, 4, 0, 0x90, 0);
        func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
        func_8005C060_main(win, 6, 0xFF, 0xAD, 0);
        func_8005C154_main(win, 0x40, 0x40, 0x40);
        func_8005FBF8_main(win, 0, 0, 0);
        func_8005C02C_main(win, 7);
        func_8005BF70_main(win, 0x100);
        func_8005FE90_main(win);
        wins++;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011133C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111348_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111354_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111360_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011136C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111378_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111384_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111390_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011139C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113A8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113B4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113C0_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113CC_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113D8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113E4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113F0_staff);

#ifdef NON_MATCHING
// Branch layout of the scroll switch and register choice differ; logic checked block by block.
void func_8010BF84_staff(void) {
    StaffLine lines[12];
    s16 models[16]; // only 3 used
    s16 spr[1];
    s16 slot[1];
    Process *proc;
    StaffWork *work;
    s16 *state;
    s16 mdlIdx;
    s16 nameIdx;
    StaffLine *l;
    s32 i;
    s16 base;
    s16 m;
    s16 cur;
    s16 titleIdx;
    s16 wait;
    StaffCredit *cred;
    s16 credIdx;
    s16 active;
    s16 done;
    s16 n;

    state = HuPrcCurrentGet()->user_data;
    proc = omAddPrcObj(func_8010B1E0_staff, 0x4000, 0x1000, 0);
    HuPrcVSleep();
    work = proc->user_data;
    for (l = lines, i = 0; i < 12; i++, l++) {
        l->type = 0;
        l->unk1C = l->model = l->esprite = l->line1 = l->line0 = l->unk18 = l->unk16 = -1;
    }
    base = -1;
    for (i = 0; i < 3; i++) {
        if (base < 0) {
            base = m = func_8000B108_main(0x160025, 0x2B9);
        } else {
            m = Hu3DModelLink(base);
        }
        models[i] = m;
        func_8001C258_main(m, 4, 4);
    }
    for (i = 0; i <= 0; i++) {
        spr[i] = func_8000B838_main(D_80110B80_staff[i]);
        slot[i] = InitEspriteSlot(spr[i], 0, 0);
        func_8000BB94_main(slot[i]);
    }
    mdlIdx = 0;
    nameIdx = 0;
    titleIdx = 0;
    cur = 0;
    do {
        if (cur != *state) {
            switch (*state) {
            case 0:
                break;
            case 1:
                wait = 1;
                cred = D_80110F04_staff[0];
                credIdx = 1;
                break;
            }
            cur = *state;
        }
        if (cur == 1) {
            if (credIdx >= 0 && --wait == 0) {
                if (cred->type == -1) {
                    cred = D_80110F04_staff[credIdx];
                    credIdx++;
                    if (cred == NULL) {
                        credIdx = -1;
                    }
                    wait += 127;
                } else {
                    for (l = lines, i = 0; i < 12; i++, l++) {
                        if (l->type == 0) {
                            break;
                        }
                    }
                    if (i < 12) {
                        l->x = 160;
                        l->y = 320;
                        l->pos.x = 0.0f;
                        l->pos.y = -480.0f;
                        l->pos.z = 380.0f;
                        l->type = cred->type;
                        switch (l->type) {
                        case 1:
                            func_8010BA30_staff(1, titleIdx, cred->mes, l->x, l->y);
                            l->line1 = titleIdx;
                            n = titleIdx + 1;
                            titleIdx = (n < 12) ? n : 0;
                            break;
                        case 4:
                            l->model = models[mdlIdx];
                            func_8001C258_main(l->model, 4, 0);
                            Hu3DModelPosSet(l->model, l->pos.x, l->pos.y, l->pos.z);
                            func_8010998C_staff(proc, &l->unk16, &l->unk18, l);
                            n = mdlIdx + 1;
                            mdlIdx = (n < 3) ? n : 0;
                            /* fallthrough */
                        case 3:
                            func_8010BA30_staff(0, nameIdx, cred->mes, l->x, l->y);
                            l->line0 = nameIdx;
                            n = nameIdx + 1;
                            nameIdx = (n < 6) ? n : 0;
                            wait += 22;
                            break;
                        case 2:
                            l->esprite = slot[cred->mes];
                            func_8000BB54_main(l->esprite);
                            break;
                        }
                        wait += cred->delay;
                        cred++;
                        if (l->type == 1 && cred->type >= 3) {
                            wait += 22;
                        }
                        wait += 30;
                    } else {
                        wait = 1;
                    }
                }
            }
            for (active = 0, l = lines, i = 0; i < 12; i++, l++) {
                if (l->type == 0) {
                    continue;
                }
                active++;
                l->y--;
                done = 0;
                if (l->type == 4) {
                    done = l->y < -63;
                } else if (l->y < -15) {
                    done++;
                }
                if (done) {
                    l->type = 0;
                    if (l->unk16 >= 0) {
                        func_8001C258_main(l->unk16, 4, 4);
                        func_8010992C_staff(proc, l->unk16);
                    }
                    l->unk18 = l->unk16 = -1;
                    if (l->line1 >= 0) {
                        func_8010B8C0_staff(1, l->line1, 0);
                        l->line1 = -1;
                    }
                    if (l->esprite >= 0) {
                        func_8000BB94_main(l->esprite);
                        l->esprite = -1;
                    }
                    if (l->line0 >= 0) {
                        func_8010B8C0_staff(0, l->line0, 0);
                        l->line0 = -1;
                    }
                    if (l->model >= 0) {
                        func_8001C258_main(l->model, 4, 4);
                        l->model = -1;
                    }
                    continue;
                }
                switch (l->type) {
                case 2:
                    func_8000BBD4_main(l->esprite, l->x, l->y);
                    break;
                case 1:
                    if (l->line1 >= 0) {
                        func_8010B9BC_staff(1, l->line1, l->x, l->y);
                    }
                    break;
                case 4:
                    l->pos.y = 288.0 - l->y * 2.4;
                    Hu3DModelPosSet(l->model, l->pos.x, l->pos.y, l->pos.z);
                    if (l->unk16 >= 0) {
                        func_80109D08_staff(proc, l->unk16, l);
                    }
                    /* fallthrough */
                case 3:
                    func_8010B9BC_staff(0, l->line0, l->x, l->y);
                    break;
                }
            }
            if ((active == 0) & (credIdx < 0)) {
                *state = -1;
            }
        }
        HuPrcVSleep();
    } while (cur >= 0);
    work->state = 1;
    for (i = 0; i < 3; i++) {
        func_8001ACDC_main(models[i]);
    }
    for (i = 0; i <= 0; i++) {
        func_8000C184_main(slot[i]);
        HuSprKill(spr[i]);
    }
    HuPrcVSleep();
    *state = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BF84_staff);
#endif

#ifdef NON_MATCHING
// masked 0; raw 2: retail copies the second parameter before the third.
void func_8010C680_staff(s16 *state, s32 *arg1, f32 *arg2, void *arg3) {
    StaffMdl *mdl = arg3;
    f32 *t = (f32 *)arg1;
    f32 *rotY = arg2;
    Vec pos;
    Vec *p;
    f32 d;

    pos = mdl->pos;
    p = &pos;
    switch (*state) {
    case 0:
        p->x += 6.266667f;
        if (p->x >= 260.0f) {
            (*state)++;
            *t = 0.0f;
        }
        break;
    case 1:
        *t += 12.0f;
        if (*t >= 180.0f) {
            *t = 180.0f;
            (*state)++;
        }
        d = cosdf(*t) * 6.266667f;
        p->x = d + p->x;
        d = 90.0f - *t;
        *rotY = d;
        break;
    case 2:
        p->x -= 6.266667f;
        if (p->x <= -680.0f) {
            (*state)++;
            *t = 0.0f;
        }
        break;
    case 3:
        *t += 12.0f;
        if (*t >= 180.0f) {
            *t = 180.0f;
            *state = 0;
        }
        d = cosdf(*t) * -6.266667f;
        p->x = d + p->x;
        d = *t + -90.0f;
        *rotY = d;
        break;
    }
    mdl->pos.x = p->x;
    Hu3DModelPosSet(mdl->model, p->x, p->y, p->z);
    Hu3DModelPosSet(mdl->model4, p->x, 0.0f, p->z);
    Hu3DModelRotSet(mdl->model, mdl->rot.x, *rotY - 8.0f, mdl->rot.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C680_staff);
#endif

void func_8010C8F4_staff(UnkStaff_1 *arg0) {
    Vec pos[3];
    StaffFlyer *flyers;
    StaffFlyer *f;
    Vec *p;
    s32 i;
    f32 a;
    f32 rot;
    f32 s;
    f32 c;

    f = (StaffFlyer *)arg0;
    flyers = f;
    for (p = pos, i = 0; i < 3; i++, f++, p++) {
        *p = f->pos;
        f->unk20 += 25.714285f;
        if (f->unk20 >= 180.0f) {
            f->unk20 -= 180.0f;
            a = (f32)(func_8010601C_staff() & 0x1F) - 15.0f;
            a += 20.0f;
            f->unk24 = a;
        }
        a = sindf(f->unk20) * f->unk24;
        p->y = a + p->y;
    }
    f = flyers;
    p = pos;
    switch (f->unk2A) {
    case 0:
        p->x += 6.266667f;
        if (p->x >= 260.0f) {
            f->unk2A++;
            f->unk18 = 0.0f;
        }
        break;
    case 1:
        f->unk18 += 12.0f;
        if (f->unk18 >= 180.0f) {
            f->unk18 = 180.0f;
            f->unk2A++;
        }
        s = cosdf(f->unk18) * 6.266667f;
        p->x = s + p->x;
        rot = f->unk18 + -90.0f;
        f->rot.y = rot;
        break;
    case 2:
        p->x -= 6.266667f;
        if (p->x <= -680.0f) {
            f->unk2A++;
            f->unk18 = 0.0f;
        }
        break;
    case 3:
        f->unk18 += 12.0f;
        if (f->unk18 >= 180.0f) {
            f->unk18 = 180.0f;
            f->unk2A = 0;
        }
        s = cosdf(f->unk18) * -6.266667f;
        p->x = s + p->x;
        rot = 90.0f - f->unk18;
        f->rot.y = rot;
        break;
    }
    f->pos.x = p->x;
    for (f = &flyers[1], p = &pos[1], i = 1; i < 3; i++, f++, p++) {
        a = f->unk18;
        switch (i) {
        case 1:
            a += 6.0f;
            rot = -90.0f;
            break;
        case 2:
            a -= 5.0f;
            rot = 90.0f;
            break;
        }
        if (a < 0.0f) {
            a += 360.0f;
        } else if (a >= 360.0f) {
            a -= 360.0f;
        }
        f->unk18 = a;
        s = sindf(a) * f->unk1C;
        c = cosdf(a) * f->unk1C;
        p->x = s + p->x;
        p->z = c + p->z;
        rot += a;
        if (rot < 0.0f) {
            rot += 360.0f;
        } else if (rot >= 360.0f) {
            rot -= 360.0f;
        }
        f->rot.y = rot;
    }
    for (f = flyers, p = pos, i = 0; i < 3; i++, f++, p++) {
        Hu3DModelPosSet(f->model, p->x, p->y, p->z);
        Hu3DModelRotSet(f->model, f->rot.x, f->rot.y, f->rot.z);
    }
}

void func_8010CD74_staff(UnkStaff_1 *arg0) {
    StaffFlyer *f;
    s16 base;
    s16 m;
    s32 i;

    base = -1;
    f = (StaffFlyer *)arg0;
    for (i = 0; i < 3; i++, f++) {
        if (base < 0) {
            base = m = Hu3DModelCreate(DataReadTemp(0xA015E), 0x2B9);
        } else {
            m = Hu3DModelLink(base);
        }
        f->model = m;
        func_8001C814_main(m, -1, 2);
        f->pos = D_80110FA0_staff[i];
        Hu3DModelPosSet(m, f->pos.x, f->pos.y, f->pos.z);
        f->rot.x = f->rot.y = f->rot.z = 0.0f;
        f->unk24 = 30.0f;
        switch (i) {
        case 0:
            Hu3DModelScaleSet(m, 0.8f, 0.8f, 0.8f);
            f->rot.y = -90.0f;
            Hu3DModelRotSet(m, 0.0f, -90.0f, 0.0f);
            f->unk1C = f->unk18 = f->unk20 = 0.0f;
            break;
        case 1:
            Hu3DModelScaleSet(m, 0.4f, 0.4f, 0.4f);
            f->unk20 = 60.0f;
            f->unk18 = 0.0f;
            f->unk1C = 50.0f;
            break;
        case 2:
            Hu3DModelScaleSet(m, 0.4f, 0.4f, 0.4f);
            f->unk20 = 120.0f;
            f->unk18 = 180.0f;
            f->unk1C = 80.0f;
            break;
        }
        f->unk2A = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CFD4_staff);

void func_8010D1E8_staff(void) {
    s16 sp10[3][2];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    s32 sp1AC;
    f32 sp1B0;
    s16 var_v0;
    s16 *temp_s2;
    s16 var_s0;
    s32 i;
    UnkStaff_1 *temp;
    UnkStaff *temp2;
    s16 *temp3;

    temp_s2 = HuPrcCurrentGet()->user_data;
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    func_800E8110_name_81();
    D_80110538_staff = 1;
    D_80111540_staff.x = 350.0f;
    D_80111540_staff.y = 190.0f;
    D_80111540_staff.z = 3770.0f;
    D_80111534_staff.x = -1000.0f;
    D_80111534_staff.y = 130.0f;
    D_80111534_staff.z = 450.0f;
    D_80110534_staff = 40.0f;
    Hu3DCamSetPerspective(0, 40.0f, D_80111564_staff, D_80111560_staff);
    func_80105E6C_staff(D_80110FF4_staff, &sp10[0][0], 3);
    func_8010CFD4_staff(sp20);
    func_8010CD74_staff(sp120);
    *temp_s2 = 0;
    sp1A8 = 0;
    sp1B0 = 90.0f;
    sp1AC = 0;
    for (var_s0 = 0; var_s0 >= 0;) {
        if (var_s0 != *temp_s2) {
            if (*temp_s2 == -1) {
                var_s0 = -1;
            } else {
                var_s0 = *temp_s2;
                func_8010C8F4_staff(sp120);
                func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
                HuPrcVSleep();
            }
        } else {
            func_8010C8F4_staff(sp120);
            func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
            HuPrcVSleep();
        }
    }

    // TODO: fix typing of temp3 or sp10
    for (temp3 = sp10[0], i = 0; i < 3; i++, temp3 += 2) {
        func_8001ACDC_main(*temp3); //?
    }
    for (temp2 = sp20, i = 0; i < 8; i++, temp2++) {
        func_8001ACDC_main(temp2->unk_18);
        func_8001ACDC_main(temp2->unk_1A);
        func_80033354_main(temp2->unk_1C);
        if (temp2->unk_1E >= 0) {
            func_8001ACDC_main(temp2->unk_1E);
        }
    }

    for (temp = sp120, i = 0; i < 3; i++, temp++) {
        func_8001ACDC_main(temp->unk_28);
    }

    MBDBackKill();
    MBDBackClose();
    *temp_s2 = 0;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D450_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D580_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D998_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DE50_staff);

void func_8010DEDC_staff(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEE4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEF4_staff);

void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF0C_staff);

s16 func_8010DF24_staff(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F04C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F3E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F4C4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F9D4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB28_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB88_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111484_staff);
