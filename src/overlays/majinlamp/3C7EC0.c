#include "common.h"
#include "game/board.h"
#include "game/hmfman.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/1006F0.h"

// event e5: the Genie lamp (the genie carries the player to the star)
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_8008A120_main(f32 (*m)[4], f32 angle);
void func_80007DD8_main(s16);
void func_80105B14_majinlamp(omObjData *obj);
void func_80105E2C_majinlamp(omObjData *obj);
void func_801067EC_majinlamp(omObjData *obj);
void func_80106BB0_majinlamp(omObjData *obj);
void func_80106D3C_majinlamp(omObjData *obj);
void func_80106E74_majinlamp(void);
void func_8010771C_majinlamp(void);
void func_80107D98_majinlamp(void);
void func_80107DD8_majinlamp(omObjData *obj);
void func_80107E1C_majinlamp(omObjData *obj);
void func_80107E40_majinlamp(void);
void func_80107E64_majinlamp(void);
void func_80107EA0_majinlamp(void);
void func_80107F54_majinlamp(void);
void func_801080C4_majinlamp(void);

extern f32 D_801080D0_majinlamp; /* camera 0 fov, near, far */
extern f32 D_801080D4_majinlamp;
extern f32 D_801080D8_majinlamp;
extern f32 D_801080DC_majinlamp; /* camera 1 fov, near, far */
extern f32 D_801080E0_majinlamp;
extern f32 D_801080E4_majinlamp;
extern s16 D_801080E8_majinlamp; /* the player rides the genie */
extern s16 D_801080EA_majinlamp; /* the player turns with the genie */
extern s16 D_801080EC_majinlamp; /* the genie bobs */
extern f32 D_801080F0_majinlamp; /* the player's height above the genie */
extern Vec D_801080F4_majinlamp[3];
extern Vec D_80108118_majinlamp;
extern s32 D_80108124_majinlamp;

extern Process *D_801082E0_majinlamp;
extern Vec D_801082E4_majinlamp;
extern Vec D_801082F0_majinlamp;
extern Vec D_801082FC_majinlamp;
extern Vec D_80108308_majinlamp;
extern Vec D_80108314_majinlamp;
extern Vec D_80108320_majinlamp;
extern Object *D_8010832C_majinlamp; /* the genie */
extern Object *D_80108330_majinlamp; /* the sky background */
extern GW_PLAYER *D_80108334_majinlamp;
extern s16 D_80108338_majinlamp;
extern s16 D_8010833A_majinlamp;
extern s32 D_8010833C_majinlamp; /* the player */
extern s16 D_8010833E_majinlamp;
extern s16 D_80108340_majinlamp;
extern s16 D_80108342_majinlamp;
extern omObjData *D_80108350_majinlamp[32]; /* the movers */

void func_801059A0_majinlamp(void) {
    D_8010833C_majinlamp = GwSystem.current_player_index;
    omInitObjMan(80, 80);
    func_80107F54_majinlamp();
    func_80107E40_majinlamp();
    func_8005A6B0_main();
    omAddPrcObj(func_80107D98_majinlamp, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80107E1C_majinlamp);
}

void func_80105A20_majinlamp(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80108350_majinlamp[i] = NULL;
    }
}

void func_80105A50_majinlamp(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] != NULL
            && (D_80108350_majinlamp[i]->func == func_80105B14_majinlamp || D_80108350_majinlamp[i]->func == func_80105E2C_majinlamp
                || D_80108350_majinlamp[i]->func == func_801067EC_majinlamp)) {
            if (D_80108350_majinlamp[i]->stat & 4) {
                D_80108350_majinlamp[i]->data = NULL;
                omDelObj(D_80108350_majinlamp[i]);
            }
        }
    }
}

void func_80105B14_majinlamp(omObjData *obj) {
    Object *model = obj->data;

    obj->work[1]--;
    if (model == NULL) {
        if (obj->work[1] == 0) {
            GwPlayer[obj->work[0]].player_obj->coords.x = obj->trans.x;
            GwPlayer[obj->work[0]].player_obj->coords.y = obj->trans.y;
            GwPlayer[obj->work[0]].player_obj->coords.z = obj->trans.z;
            omDelObj(obj);
            return;
        }
        GwPlayer[obj->work[0]].player_obj->coords.x += obj->scale.x;
        GwPlayer[obj->work[0]].player_obj->coords.y += obj->scale.y;
        GwPlayer[obj->work[0]].player_obj->coords.z += obj->scale.z;
    } else {
        if (obj->work[1] == 0) {
            model->coords.x = obj->trans.x;
            model->coords.y = obj->trans.y;
            model->coords.z = obj->trans.z;
            obj->data = NULL;
            omDelObj(obj);
            return;
        }
        model->coords.x += obj->scale.x;
        model->coords.y += obj->scale.y;
        model->coords.z += obj->scale.z;
    }
}

omObjData *func_80105CA8_majinlamp(s32 player, Vec *pos, s32 frames, Object *model) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, func_80105B14_majinlamp);
    obj->work[0] = player;
    obj->work[1] = frames;
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    if (model == NULL) {
        obj->scale.x = (pos->x - GwPlayer[player].player_obj->coords.x) / frames;
        obj->scale.y = (pos->y - GwPlayer[player].player_obj->coords.y) / frames;
        obj->scale.z = (pos->z - GwPlayer[player].player_obj->coords.z) / frames;
    } else {
        obj->scale.x = (pos->x - model->coords.x) / frames;
        obj->scale.y = (pos->y - model->coords.y) / frames;
        obj->scale.z = (pos->z - model->coords.z) / frames;
    }
    obj->data = model;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_80105E2C_majinlamp(omObjData *obj) {
    Object *model = obj->data;

    obj->work[1]--;
    if (model == NULL) {
        if (obj->work[1] == 0) {
            GwPlayer[obj->work[0]].player_obj->coords.x = obj->trans.x;
            GwPlayer[obj->work[0]].player_obj->coords.y = obj->trans.y;
            GwPlayer[obj->work[0]].player_obj->coords.z = obj->trans.z;
            omDelObj(obj);
            return;
        }
        GwPlayer[obj->work[0]].player_obj->coords.x += obj->scale.x;
        GwPlayer[obj->work[0]].player_obj->coords.y += obj->scale.y;
        GwPlayer[obj->work[0]].player_obj->coords.z += obj->scale.z;
        GwPlayer[obj->work[0]].player_obj->coords.x += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x
                                                     - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x;
        GwPlayer[obj->work[0]].player_obj->coords.y += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y
                                                     - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y;
        GwPlayer[obj->work[0]].player_obj->coords.z += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z
                                                     - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z;
    } else {
        if (obj->work[1] == 0) {
            model->coords.x = obj->trans.x;
            model->coords.y = obj->trans.y;
            model->coords.z = obj->trans.z;
            obj->data = NULL;
            omDelObj(obj);
            return;
        }
        model->coords.x += obj->scale.x;
        model->coords.y += obj->scale.y;
        model->coords.z += obj->scale.z;
        model->coords.x += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x
                         - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.x;
        model->coords.y += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y
                         - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.y;
        model->coords.z += sinf((f32)obj->work[1] * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z
                         - sinf((f32)(obj->work[1] + 1) * 180.0f / obj->work[2] * (M_PI / 180.0)) * obj->rot.z;
    }
}

/* model is an Object, or a player index smuggled in the pointer (retail tells them apart by the sign bit: KSEG0) */
omObjData *func_80106634_majinlamp(Object *model, Vec *pos, s32 frames, Vec *arc) {
    omObjData *obj;
    s32 player = -1;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, func_80105E2C_majinlamp);
    if ((s32)model >= 0) {
        player = (s32)model;
        model = NULL;
        obj->work[0] = player;
    }
    obj->work[1] = frames;
    obj->work[2] = frames;
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    if (model == NULL) {
        obj->scale.x = (pos->x - GwPlayer[player].player_obj->coords.x) / frames;
        obj->scale.y = (pos->y - GwPlayer[player].player_obj->coords.y) / frames;
        obj->scale.z = (pos->z - GwPlayer[player].player_obj->coords.z) / frames;
    } else {
        obj->scale.x = (pos->x - model->coords.x) / frames;
        obj->scale.y = (pos->y - model->coords.y) / frames;
        obj->scale.z = (pos->z - model->coords.z) / frames;
    }
    obj->rot.x = arc->x;
    obj->rot.y = arc->y;
    obj->rot.z = arc->z;
    obj->data = model;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_801067EC_majinlamp(omObjData *obj) {
    Object *model = obj->data;

    obj->work[1]--;
    if (model == NULL) {
        if (obj->work[1] == 0) {
            GwPlayer[obj->work[0]].player_obj->rot.x = obj->rot.x;
            GwPlayer[obj->work[0]].player_obj->rot.y = obj->rot.y;
            GwPlayer[obj->work[0]].player_obj->rot.z = obj->rot.z;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
        GwPlayer[obj->work[0]].player_obj->rot.x = sinf(obj->scale.y * (M_PI / 180.0));
        GwPlayer[obj->work[0]].player_obj->rot.y = 0.0f;
        GwPlayer[obj->work[0]].player_obj->rot.z = cosf(obj->scale.y * (M_PI / 180.0));
    } else {
        if (obj->work[1] == 0) {
            model->rot.x = obj->rot.x;
            model->rot.y = obj->rot.y;
            model->rot.z = obj->rot.z;
            obj->data = NULL;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
        model->rot.x = sinf(obj->scale.y * (M_PI / 180.0));
        model->rot.y = 0.0f;
        model->rot.z = cosf(obj->scale.y * (M_PI / 180.0));
    }
}

omObjData *func_801069B8_majinlamp(s32 player, Vec *target, s32 frames, Object *model) {
    omObjData *obj;
    Vec dir;
    f32 from;
    f32 to;
    s32 i;

    if (model == NULL) {
        MBVecDirGet(&GwPlayer[player].player_obj->coords, target, &dir);
    } else {
        MBVecDirGet(&model->coords, target, &dir);
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_801067EC_majinlamp);
    obj->work[0] = player;
    obj->work[1] = frames;
    obj->rot.x = dir.x;
    obj->rot.y = dir.y;
    obj->rot.z = dir.z;
    if (model == NULL) {
        from = MBVecAngleGet(&GwPlayer[player].player_obj->rot);
        to = MBVecAngleGet(&dir);
        if (to < from) {
            if (from - to >= 180.0f) {
                to += 360.0f;
            }
        } else if (to - from >= 180.0f) {
            from += 360.0f;
        }
    } else {
        from = MBVecAngleGet(&model->rot);
        to = MBVecAngleGet(&dir);
        if (to < from) {
            if (from - to >= 180.0f) {
                to += 360.0f;
            }
        } else if (to - from >= 180.0f) {
            from += 360.0f;
        }
    }
    obj->scale.y = from;
    obj->scale.x = (to - from) / frames;
    obj->data = model;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_80106BB0_majinlamp(omObjData *obj) {
    func_8001E888_main(D_80108330_majinlamp->omObj1->model[0], 0, obj->trans.x, 0x40, 0x40, "bg_in", 0);
    obj->trans.x += 1.0f;
    if (D_80108124_majinlamp != 0) {
        func_8001E888_main(D_80108330_majinlamp->omObj1->model[0], 0, obj->trans.y, 0x40, 0x40, "bg_out", 0);
        obj->trans.y += 1.0f;
    }
    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
}

void func_80106D3C_majinlamp(omObjData *obj) {
    if (D_801080EC_majinlamp != 0) {
        D_8010832C_majinlamp->velocity.x = sindf(obj->rot.y) * 30.0f;
        obj->rot.y += 2.0f;
        if (obj->rot.y >= 360.0f) {
            obj->rot.y -= 360.0f;
        }
    }
    if (D_801080E8_majinlamp != 0) {
        D_80108334_majinlamp->player_obj->velocity.x = D_801080F0_majinlamp * D_8010832C_majinlamp->scale.x + D_8010832C_majinlamp->velocity.x;
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_8010832C_majinlamp->coords);
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->scale, &D_8010832C_majinlamp->scale);
    }
    if (D_801080EA_majinlamp != 0) {
        D_80108334_majinlamp->player_obj->rot.x = D_8010832C_majinlamp->rot.x;
        D_80108334_majinlamp->player_obj->rot.z = D_8010832C_majinlamp->rot.z;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80106E74_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_8010771C_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107D98_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107DD8_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107E1C_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107E40_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107E64_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107EA0_majinlamp);

INCLUDE_ASM("asm/nonmatchings/overlays/majinlamp/3C7EC0", func_80107F54_majinlamp);

void func_801080C4_majinlamp(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_80108270_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_80108290_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082B0_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082BC_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082C8_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082D4_majinlamp);
