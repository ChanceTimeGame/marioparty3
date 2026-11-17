#include "common.h"

/* Second select menu (a later revision of selmenu's: 8 pages, its own name tables). */

typedef struct SelMenuEntry {
    /* 0x00 */ u8 kind; /* 1: empty slot, skipped by the cursor */
    /* 0x01 */ u8 mgNo; /* group preset (1-based) */
    /* 0x02 */ u8 unk2; /* GwSystem.minigame_index for the pick */
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

/* m5: data and bss the C functions use */
extern s32 fontcolor;
extern GW_PLAYER D_80109B20_selmenu2[4];
extern s8 D_80109C80_selmenu2[4]; /* last stick x per pad */
extern s8 D_80109C84_selmenu2[4]; /* last stick y per pad */
extern u8 D_80109CF8_selmenu2[4]; /* menu input bits per pad */
extern u16 D_80109CFC_selmenu2[4]; /* held direction per pad */
extern u16 D_80109D04_selmenu2[4]; /* hold time */
extern u16 D_80109D0C_selmenu2[4]; /* repeat delay */
void func_80107DA4_selmenu2(omObjData *obj);

/* .data */
SelMenuEntry D_80108BE0_selmenu2[80] = {
    { 0, 1, 1, 0, 1, 100, 0, "201:PUKUPUKU FISHING" },
    { 0, 2, 2, 0, 2, 100, 0, "202:HIYA2 YASHINOMI" },
    { 0, 3, 3, 0, 3, 100, 0, "203:TERASHITE SEARCH LIGHT" },
    { 0, 4, 4, 0, 4, 100, 0, "204:GOROGORO IWAKOROGASHI" },
    { 0, 4, 5, 0, 5, 100, 0, "205:GURU2 KILLER ATTACK" },
    { 0, 4, 6, 0, 6, 100, 0, "206:DOKO?2 KAKURENBO" },
    { 0, 5, 7, 0, 7, 100, 0, "207:DOTABATA RELAY" },
    { 0, 5, 8, 0, 8, 100, 0, "208:DOSSUN DOSSUN!" },
    { 0, 5, 9, 0, 9, 100, 0, "209:SUIJYOU SKI" },
    { 0, 5, 10, 0, 10, 100, 0, "210:WAVE*WAVE" },
    { 0, 6, 11, 0, 11, 100, 0, "211:MOGO2 PIZZA HOUSE" },
    { 0, 6, 12, 0, 12, 100, 0, "212:ATECHAE! MINI KOOPA" },
    { 0, 6, 13, 0, 13, 100, 0, "213:GO!GO! ROCKET" },
    { 0, 6, 14, 0, 14, 100, 0, "214:BOBBLE HINO YOUJIN!" },
    { 0, 7, 15, 0, 15, 100, 0, "215:FRUITS BASCKET" },
    { 0, 8, 16, 0, 16, 100, 0, "216:OJAMA COSTER" },
    { 0, 8, 17, 0, 17, 100, 0, "217:COIN LAKE" },
    { 0, 8, 18, 0, 18, 100, 0, "218:KAKONDE KUREYON" },
    { 0, 9, 19, 0, 19, 100, 0, "219:NAKAYOSHI MAKIWARI" },
    { 0, 9, 20, 0, 20, 100, 0, "220:NUIGURUMI FACTORY" },
    { 0, 11, 21, 0, 21, 100, 0, "221:BELCON DANGEROUS" },
    { 0, 11, 22, 0, 22, 100, 0, "222:POWER KINOKO GO!GO!" },
    { 0, 11, 23, 0, 23, 100, 0, "223:TIKITIKI AIR FIGHT!" },
    { 0, 11, 24, 0, 24, 100, 0, "224:PYONPYON BATTLE!" },
    { 0, 11, 25, 0, 25, 100, 0, "225:TOGEZOH CRASH" },
    { 0, 11, 26, 0, 26, 100, 0, "226:NIGEKOME SHELTER" },
    { 0, 12, 27, 0, 27, 100, 0, "227:PITTARI! SHOT" },
    { 0, 12, 28, 0, 28, 100, 0, "228:OKKOTI PARASOL" },
    { 0, 12, 29, 0, 29, 100, 0, "229:MATIGAI WO SAGSE!" },
    { 0, 12, 30, 0, 30, 100, 0, "230:OWASETE MONTAGE" },
    { 0, 14, 31, 0, 31, 100, 0, "231:DOSSUN PUZZLE" },
    { 0, 14, 32, 0, 32, 100, 0, "232:TATAITE DRUM" },
    { 0, 14, 33, 0, 33, 100, 0, "233:QUIZ PARTY" },
    { 0, 16, 34, 0, 34, 100, 0, "234:DAREKA WAKARUKANA" },
    { 0, 17, 35, 0, 35, 100, 0, "235:MOTORBOAT RACE" },
    { 0, 17, 36, 0, 36, 100, 0, "236:KUNEKUNE ROAD RACE" },
    { 0, 17, 37, 0, 37, 100, 0, "237:AOZORA BLOCK RACE" },
    { 0, 20, 38, 0, 38, 100, 0, "238:HARAPEKO PUKU2" },
    { 0, 20, 39, 0, 39, 100, 0, "239:TATAKE! MINI KOOPA" },
    { 0, 20, 40, 0, 40, 100, 0, "240:YUKIDAMA GOROGORO!" },
    { 0, 22, 41, 0, 41, 100, 0, "241:KAWASHITE BOBBLE" },
    { 0, 22, 42, 0, 42, 100, 0, "242:DOKI2 CARD DROP" },
    { 0, 22, 43, 0, 43, 100, 0, "243:HAYAOSHI HOUSE" },
    { 0, 23, 44, 0, 44, 100, 0, "244:GO!GO! MOKUBA" },
    { 0, 23, 45, 0, 45, 100, 0, "245:DANGEROUS ROULETTE" },
    { 0, 23, 46, 0, 46, 100, 0, "246:MEKUTTE HAYAOSHI!" },
    { 0, 23, 47, 0, 47, 100, 0, "247:AMEFURI FLOWER" },
    { 0, 23, 48, 0, 48, 100, 0, "248:EYEKUN MAWASHI" },
    { 0, 24, 49, 0, 49, 100, 0, "249:TARZAN RACE" },
    { 0, 25, 50, 0, 50, 100, 0, "250:HAYAUCHI MINIKOOPA" },
    { 0, 25, 51, 0, 51, 100, 0, "251:BOUSOU SYUPPOH" },
    { 0, 26, 52, 0, 52, 100, 0, "252:TONDEKE KOOPA HAMMER" },
    { 0, 27, 53, 0, 53, 100, 0, "253:ITAZURA MINI KOOPA" },
    { 0, 28, 54, 0, 54, 100, 0, "254:BIRIKYUU COASTER" },
    { 0, 28, 55, 0, 55, 100, 0, "255:BOLT DASH" },
    { 0, 28, 56, 0, 56, 100, 0, "256:KONO E HA NAANI?" },
    { 0, 30, 57, 0, 57, 100, 0, "257:GURU2 JUMP!" },
    { 0, 30, 58, 0, 58, 100, 0, "258:NIWATORI CATCH" },
    { 0, 30, 59, 0, 59, 100, 0, "259:NERAE! ITEM!!" },
    { 0, 30, 60, 0, 60, 100, 0, "260:ITEM HOMERUN" },
    { 0, 30, 61, 0, 61, 100, 0, "261:NERATTE BALOON" },
    { 0, 30, 62, 0, 62, 100, 0, "262:DOSSHI DE CATCH" },
    { 0, 30, 63, 0, 63, 100, 0, "263:FLYING.BURANKO" },
    { 0, 30, 64, 0, 64, 100, 0, "264:HAMMER ITEM" },
    { 0, 30, 66, 0, 65, 100, 0, "266:STARDUST BATTLE" },
    { 0, 32, 67, 0, 66, 100, 0, "267:HEIHO ROULETTE" },
    { 0, 32, 68, 0, 67, 100, 0, "268:NERATTE 7" },
    { 0, 33, 69, 0, 68, 100, 0, "269:KINOPIO?KOOPA?" },
    { 0, 33, 70, 0, 69, 100, 0, "270:CAKE DE BATTLE!" },
    { 0, 33, 71, 0, 104, 100, 0, "271:MOTERBOAT TRIAL" },
    { 0, 33, 72, 0, 31, 100, 0, "272:3PUNN DOSSUN" },
    { 0, 1, 11, 0, 118, 100, 0, "***:MESS" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
    { 1, 1, 11, 0, 1000, 100, 0, "***:" },
};
SelMenuCfg D_801090E0_selmenu2[33] = {
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
};
SelMenuSe D_801092F0_selmenu2[5] = { { 0, 0, 120 }, { 0, 0, 106 }, { 0, 0, 110 }, { 0, 0, 114 }, { 0, 0, 123 } };
u16 D_80109304_selmenu2[2][2] = { { 5, 13 }, { 4, 12 } };
SelMenuEntry D_8010930C_selmenu2[6] = {
    { 1, 3, 11, 0, 1000, 0, 0, ">PLAYER%d" },
    { 0, 4, 12, 0, 1000, 0, 0, "PAD%d:%s" },
    { 0, 4, 12, 0, 1000, 0, 0, "GRP :%d" },
    { 0, 4, 12, 0, 1000, 0, 0, "DIF :%s" },
    { 0, 4, 12, 0, 1000, 0, 0, "COIN:%d" },
    { 0, 4, 12, 0, 1000, 0, 0, "PADN:%d" },
};
char *D_8010936C_selmenu2[2] = { "HUMAN", "COM" };
char *D_80109374_selmenu2[4] = { "EASY", "NORMAL", "HARD", "VERYHARD" };
char *D_80109384_selmenu2[8] = { "MARIO", "LUIGI", "PEACH", "YOSI", "WARIO", "DONKEY", "WALUIGI", "DAISY" };
char *D_801093A4_selmenu2[3] = { "GAME", "BOARD", "DUEL" };
u8 D_801093B0_selmenu2 = 0;
char *D_801093B4_selmenu2[3] = { "EASY", "NORMAL", "HARD" };
s32 D_801093C0_selmenu2 = 0; /* the asm reads its low half as D_801093C2 */
s32 D_801093C4_selmenu2 = 0;
s32 D_801093C8_selmenu2 = 1;


INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801059A0_selmenu2);

/* selmenu func_80105F30_selmenu */
void func_80105F74_selmenu2(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z) {
    func_8000B5F0_main(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = x;
    Center.y = y;
    Center.z = z;
}

/* selmenu func_80105FC8 */
void func_8010600C_selmenu2(omObjData *obj) {
    s32 i;
    s8 x;
    s8 y;
    s32 last;

    for (i = 0; i < 4; i++) {
        D_80109CF8_selmenu2[i] = 0;
        if (CheckControllerRead(i) == 0) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        x = D_800CBB6E_main[i];
        y = D_800D20A1_main[i];
        if (D_800D5558_main[i] & 0x808) {
            D_80109CF8_selmenu2[i] |= 1;
        }
        if (D_800D5558_main[i] & 0x404) {
            D_80109CF8_selmenu2[i] |= 2;
        }
        if (D_800D5558_main[i] & 0x202) {
            D_80109CF8_selmenu2[i] |= 4;
        }
        if (D_800D5558_main[i] & 0x101) {
            D_80109CF8_selmenu2[i] |= 8;
        }
        if (y < -10) {
            last = D_80109C84_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 2;
            }
        }
        if (y > 10) {
            last = D_80109C84_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 1;
            }
        }
        if (x < -10) {
            last = D_80109C80_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 4;
            }
        }
        if (x > 10) {
            last = D_80109C80_selmenu2[i];
            if (last < 0) {
                last = -last;
            }
            if (last < 10) {
                D_80109CF8_selmenu2[i] |= 8;
            }
        }
        D_80109C80_selmenu2[i] = x;
        D_80109C84_selmenu2[i] = y;
        if (D_800D5558_main[i] & 0x2000) {
            D_80109CF8_selmenu2[i] |= 0x40;
        }
        if (((D_800CDA7C_main[i] & 0x808) != 0) | (y > 10)) {
            if (D_80109CFC_selmenu2[i] & 1) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 1) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 1;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 1;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if (((D_800CDA7C_main[i] & 0x404) != 0) | (y < -10)) {
            if (D_80109CFC_selmenu2[i] & 2) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 2) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 2;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 2;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if (((D_800CDA7C_main[i] & 0x202) != 0) | (x < -10)) {
            if (D_80109CFC_selmenu2[i] & 4) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 4) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 4;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 4;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if (((D_800CDA7C_main[i] & 0x101) != 0) | (x > 10)) {
            if (D_80109CFC_selmenu2[i] & 8) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 8) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 8;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 8;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else {
            D_80109D04_selmenu2[i] = 0;
        }
        if (D_800D5558_main[i] & 0x8000) {
            D_80109CF8_selmenu2[i] |= 0x10;
        }
        if (D_800D5558_main[i] & 0x4000) {
            D_80109CF8_selmenu2[i] |= 0x20;
        }
        if (D_800D5558_main[i] & 0x1000) {
            D_80109CF8_selmenu2[i] |= 0x80;
        }
        if ((D_800CDA7C_main[i] & 0x30) == 0x30) {
            omOvlReturnEx(0);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801067B4_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80106A54_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80106D94_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801078CC_selmenu2);

/* selmenu func_80107DEC_selmenu */
void func_80107D94_selmenu2(omObjData *obj) {
    obj->func = func_80107DA4_selmenu2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80107DA4_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108718_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108764_selmenu2);

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_801087E0_selmenu2);

/* selmenu func_801089C0_selmenu */
void func_80108910_selmenu2(u16 x, u16 y, char *str, u16 color, u16 shadow) {
    fontcolor = shadow;
    print8(x + 1, y + 1, str);
    fontcolor = color;
    print8(x, y, str);
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu2/116320", func_80108990_selmenu2);

/* selmenu func_80108AB4_selmenu */
void func_80108A04_selmenu2(void) {
    s32 i;

    GW_PLAYER *src;
    GW_PLAYER *dst;

    for (i = 0; i < 4; i++) {
        src = &D_80109B20_selmenu2[i];
        dst = &GwPlayer[i];
        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

/* selmenu func_80108B1C_selmenu */
void func_80108A6C_selmenu2(void) {
    u8 group[4];
    u8 used[4];
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        group[i] = D_80109B20_selmenu2[i].group;
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        do {
            j = rand8() & 3;
        } while (used[j] == 1);
        used[j] = 1;
        D_80109B20_selmenu2[i].group = group[j];
    }
}

/* selmenu func_80108BE8_selmenu */
void func_80108B38_selmenu2(void) {
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
        D_80109B20_selmenu2[i].pad = j;
    }
}

