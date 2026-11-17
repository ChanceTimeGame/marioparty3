#include "common.h"

/* Debug "select menu": a 10x10 page table of overlays to boot, with per-player setup. */

typedef struct SelMenuEntry {
    /* 0x00 */ u8 kind; /* 1: empty slot, skipped by the cursor */
    /* 0x01 */ u8 cfg;  /* index into the player-group presets (1-based) */
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s32 ovl;
    /* 0x08 */ s16 evt;
    /* 0x0A */ s16 stat;
    /* 0x0C */ char *name;
} SelMenuEntry; /* 0x10 on N64 */

typedef struct SelMenuCfg {
    /* 0x00 */ u8 group[4];
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ s16 unk8[4];
} SelMenuCfg;

typedef struct SelMenuSe {
    /* 0x00 */ s16 seId;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ s8 vib;
} SelMenuSe;

extern s32 fontcolor;
extern SelMenuEntry D_80108C90_selmenu[100]; /* [page * 10 + row] */
extern SelMenuCfg D_801092C0_selmenu[];
extern SelMenuSe D_80109740_selmenu[];
extern s16 D_8010A070_selmenu; /* page */
extern s16 D_8010A072_selmenu; /* row */
extern s16 D_8010A078_selmenu[10]; /* row remembered per page */
extern GW_PLAYER D_8010A098_selmenu[4];

void func_80107DFC_selmenu(omObjData *obj);
void func_80108814_selmenu(s32 dir);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_801059A0_selmenu);

void func_80105F30_selmenu(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z) {
    func_8000B5F0_main(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = x;
    Center.y = y;
    Center.z = z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80105FC8_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106770_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106A10_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106DEC_selmenu);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107924_selmenu);

void func_80107DEC_selmenu(omObjData *obj) {
    obj->func = func_80107DFC_selmenu;
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107DFC_selmenu);

void func_801087C8_selmenu(u16 no) {
    func_8004AAD0_main(HuAudFXPlay(D_80109740_selmenu[no].seId), D_80109740_selmenu[no].vib);
}

void func_80108814_selmenu(s32 dir) {
    s16 row = D_8010A072_selmenu;

    do {
        row += dir;
        if (row >= 10) {
            row = 0;
        } else if (row < 0) {
            row = 9;
        }
    } while (D_80108C90_selmenu[D_8010A070_selmenu * 10 + row].kind == 1);
    D_8010A072_selmenu = row;
}

void func_80108890_selmenu(s32 dir) {
    u16 found = FALSE;
    s16 prev;
    s16 page;
    s32 i;

    prev = page = D_8010A070_selmenu;

    do {
        page += dir;
        if (page >= 10) {
            page = 0;
        } else if (page < 0) {
            page = 9;
        }
        for (i = 0; i < 10; i++) {
            if (D_80108C90_selmenu[page * 10 + i].kind == 0) {
                found = TRUE;
                break;
            }
        }
    } while (!found);
    D_8010A070_selmenu = page;
    if (prev == -1) {
        D_8010A072_selmenu = -1;
        func_80108814_selmenu(1);
        D_8010A078_selmenu[D_8010A070_selmenu] = D_8010A072_selmenu;
    } else {
        D_8010A078_selmenu[prev] = D_8010A072_selmenu;
        D_8010A072_selmenu = D_8010A078_selmenu[D_8010A070_selmenu];
    }
}

void func_801089C0_selmenu(u16 x, u16 y, char *str, u16 color, u16 shadow) {
    fontcolor = shadow;
    print8(x + 1, y + 1, str);
    fontcolor = color;
    print8(x, y, str);
}

void func_80108A40_selmenu(void) {
    SelMenuCfg *cfg = &D_801092C0_selmenu[D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].cfg];

    GW_PLAYER *player = D_8010A098_selmenu;

    player->group = cfg->group[0];
    player++;
    player->group = cfg->group[1];
    player++;
    player->group = cfg->group[2];
    player++;
    player->group = cfg->group[3];
}

void func_80108AB4_selmenu(void) {
    s32 i;

    GW_PLAYER *src;
    GW_PLAYER *dst;

    for (i = 0; i < 4; i++) {
        src = &D_8010A098_selmenu[i];
        dst = &GwPlayer[i];
        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

void func_80108B1C_selmenu(void) {
    u8 group[4];
    u8 used[4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        group[i] = D_8010A098_selmenu[i].group;
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        do {
            j = rand8() & 3;
        } while (used[j] == 1);
        used[j] = 1;
        D_8010A098_selmenu[i].group = group[j];
    }
}

void func_80108BE8_selmenu(void) {
    u8 used[4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        do {
            j = rand8() & 3;
        } while (used[j] == 1);
        used[j] = 1;
        D_8010A098_selmenu[i].pad = j;
    }
}
