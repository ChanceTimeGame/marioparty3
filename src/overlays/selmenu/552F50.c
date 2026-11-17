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
extern s16 D_8010A070_selmenu; /* page */
extern s16 D_8010A072_selmenu; /* row */
extern s16 D_8010A078_selmenu[10]; /* row remembered per page */
extern GW_PLAYER D_8010A098_selmenu[4];

void func_80107DFC_selmenu(omObjData *obj);
void func_80108814_selmenu(s32 dir);

/* .data */
SelMenuEntry D_80108C90_selmenu[100] = { /* [page * 10 + row] */
    { 0, 1, 11, 0, 1, 100, 0, "201:PUKUPUKU FISHING" },
    { 0, 2, 11, 0, 2, 100, 0, "202:HIYAHIYA YASHINOMI" },
    { 0, 3, 11, 0, 3, 100, 0, "203:TERASHITE SEARCH LIGHT" },
    { 0, 4, 11, 0, 4, 100, 0, "204:GOROGORO IWAKOROGASHI" },
    { 0, 5, 11, 0, 5, 100, 0, "205:BOMHEI KOUKATAI" },
    { 0, 6, 11, 0, 6, 100, 0, "206:DOKO?DOKO? KAKURENBO" },
    { 0, 7, 11, 0, 7, 100, 0, "207:DOTABATA RELAY" },
    { 0, 8, 11, 0, 8, 100, 0, "208:ISOGE WANWAN" },
    { 0, 9, 11, 0, 9, 100, 0, "209:SUIJYOU SKI" },
    { 0, 10, 11, 0, 10, 100, 0, "210:WAVE*WAVE" },
    { 0, 11, 11, 0, 11, 100, 0, "211:MOGOMOGU PIZZA HOUSE" },
    { 0, 12, 11, 0, 12, 100, 0, "212:ATECHAE! MINI KOOPA" },
    { 0, 13, 11, 0, 13, 100, 0, "213:GO!GO! ROCKET" },
    { 0, 14, 11, 0, 14, 100, 0, "214:BOBBLE HINO YOUJIN!" },
    { 0, 15, 11, 0, 15, 100, 0, "215:BURABURA BURANKO" },
    { 0, 16, 11, 0, 16, 100, 0, "216:TRUCK KIKI IPPATSU" },
    { 0, 17, 11, 0, 17, 100, 0, "217:PIT RACE" },
    { 0, 18, 11, 0, 18, 100, 0, "218:KAKONDE KUREYON" },
    { 0, 19, 11, 0, 19, 100, 0, "219:MAKIWARI" },
    { 0, 20, 11, 0, 20, 100, 0, "220:NUIGURUMI FACTORY" },
    { 0, 21, 11, 0, 21, 100, 0, "221:BELCON DANGEROUS" },
    { 0, 22, 11, 0, 22, 100, 0, "222:POWER KINOKO GO!GO!" },
    { 0, 23, 11, 0, 23, 100, 0, "223:TIKITIKI AIR FIGHT!" },
    { 0, 24, 11, 0, 24, 100, 0, "224:PYONPYON BATTLE!" },
    { 0, 25, 11, 0, 25, 100, 0, "225:NOKONOKO ISLAND" },
    { 0, 26, 11, 0, 26, 100, 0, "226:NIGEKOME SHELTER" },
    { 0, 27, 11, 0, 27, 100, 0, "227:PITTARI! PATTER" },
    { 0, 28, 11, 0, 28, 100, 0, "228:OKKOTI PARASOL" },
    { 0, 29, 11, 0, 29, 100, 0, "229:MATIGAI WO SAGSE!" },
    { 0, 30, 11, 0, 30, 100, 0, "230:OWASETE MONTAGE" },
    { 0, 31, 11, 0, 31, 100, 0, "231:DOSSUN PUZZLE" },
    { 0, 32, 11, 0, 32, 100, 0, "232:TATAITE DRUM" },
    { 0, 33, 11, 0, 33, 100, 0, "233:QUIZ PARTY" },
    { 0, 34, 11, 0, 34, 100, 0, "234:ATEKKO CHARACTER" },
    { 0, 35, 11, 0, 35, 100, 0, "235:MOTORBOAT RACE" },
    { 0, 36, 11, 0, 36, 100, 0, "236:KUNEKUNE ROAD RACE" },
    { 0, 37, 11, 0, 37, 100, 0, "237:AOZORA BLOCK RACE" },
    { 0, 38, 11, 0, 38, 100, 0, "238:BATAASHI RACE" },
    { 0, 39, 11, 0, 39, 100, 0, "239:TATAKE! MINI KOOPA" },
    { 0, 40, 11, 0, 40, 100, 0, "240:YUKIDAMA GOROGORO!" },
    { 0, 41, 11, 0, 41, 100, 0, "241:KAWASHITE BOBBLE" },
    { 0, 42, 11, 0, 42, 100, 0, "242:CAPSULE MINI KOOPA" },
    { 0, 43, 11, 0, 43, 100, 0, "243:HAYAOSHI HOUSE" },
    { 0, 44, 11, 0, 44, 100, 0, "244:MOKUBA RACE" },
    { 0, 45, 11, 0, 45, 100, 0, "245:DANGEROUS ROULETTE" },
    { 0, 46, 11, 0, 46, 100, 0, "246:MEKUTTE HAYAOSHI!" },
    { 0, 47, 11, 0, 47, 100, 0, "247:AMEHURI FLOWER" },
    { 0, 48, 11, 0, 48, 100, 0, "248:AIKUN MAWASHI" },
    { 0, 49, 11, 0, 49, 100, 0, "249:TARZAN RACE" },
    { 0, 50, 11, 0, 50, 100, 0, "250:HIRAITA GATE NI PON!" },
    { 0, 51, 11, 0, 51, 100, 0, "251:BOUSOU!? SHUPPO-" },
    { 0, 52, 11, 0, 52, 100, 0, "252:TONDEKE KOOPA HAMMER" },
    { 0, 53, 11, 0, 53, 100, 0, "253:ITAZURA MINI KOOPA" },
    { 0, 54, 11, 0, 54, 100, 0, "254:TUBE COASTER" },
    { 0, 55, 11, 0, 55, 100, 0, "255:BOLT DASH" },
    { 0, 56, 11, 0, 56, 100, 0, "256:KONO E HA NAANI?" },
    { 0, 57, 11, 0, 57, 100, 0, "257:JUMP DE CLOCK" },
    { 0, 58, 11, 0, 58, 100, 0, "258:KIGURUMI KOOPA" },
    { 0, 59, 11, 0, 59, 100, 0, "259:NERAE! ITEM!!" },
    { 0, 60, 11, 0, 60, 100, 0, "260:ITEM HITTER" },
    { 0, 61, 11, 0, 61, 100, 0, "261:NERATTE BALOON" },
    { 0, 62, 11, 0, 62, 100, 0, "262:DOSSHI DE CATCH!" },
    { 0, 63, 11, 0, 63, 100, 0, "263:BURABURA BURANKO" },
    { 0, 64, 11, 0, 64, 100, 0, "264:ITEM THROWIN" },
    { 1, 65, 11, 0, 1000, 100, 0, "265:" },
    { 0, 66, 11, 0, 65, 100, 0, "266:STARDUST BATTLE" },
    { 0, 67, 11, 0, 66, 100, 0, "267:HEIHO ROULETTE" },
    { 0, 68, 11, 0, 67, 100, 0, "268:OTITARA DAMEYO" },
    { 0, 69, 11, 0, 68, 100, 0, "269:KINOPIO?KOOPA?" },
    { 0, 70, 11, 0, 69, 100, 0, "270:WANWAN BATTLE" },
    { 0, 71, 11, 0, 70, 100, 0, "271:MOTORBOAT TRIAL" },
    { 1, 1, 11, 0, 1000, 100, 0, "272:" },
    { 1, 1, 11, 0, 1000, 100, 0, "273:" },
    { 1, 1, 11, 0, 1000, 100, 0, "274:" },
    { 1, 1, 11, 0, 1000, 100, 0, "275:" },
    { 1, 1, 11, 0, 1000, 100, 0, "276:" },
    { 1, 1, 11, 0, 1000, 100, 0, "277:" },
    { 1, 1, 11, 0, 1000, 100, 0, "278:" },
    { 1, 1, 11, 0, 1000, 100, 0, "279:" },
    { 1, 1, 11, 0, 1000, 100, 0, "280:" },
    { 0, 1, 11, 0, 91, 100, 0, "281:DUEL01" },
    { 0, 1, 11, 0, 92, 100, 0, "282:DULE02" },
    { 0, 1, 11, 0, 93, 100, 0, "283:DUEL03" },
    { 0, 1, 11, 0, 94, 100, 0, "284:DUEL04" },
    { 1, 1, 11, 0, 1000, 100, 0, "285:" },
    { 1, 1, 11, 0, 1000, 100, 0, "286:" },
    { 1, 1, 11, 0, 1000, 100, 0, "287:" },
    { 1, 1, 11, 0, 1000, 100, 0, "288:" },
    { 1, 1, 11, 0, 1000, 100, 0, "289:" },
    { 1, 1, 11, 0, 1000, 100, 0, "290:" },
    { 1, 1, 11, 0, 1000, 100, 0, "291:" },
    { 1, 1, 11, 0, 1000, 100, 0, "292:" },
    { 1, 1, 11, 0, 1000, 100, 0, "293:" },
    { 0, 1, 11, 0, 115, 100, 0, "294:RESULT3" },
    { 0, 1, 11, 0, 106, 100, 0, "295:CHANCE" },
    { 0, 1, 11, 0, 114, 100, 0, "296:RESULT2" },
    { 0, 1, 11, 0, 112, 100, 0, "297:INST" },
    { 0, 1, 11, 0, 113, 100, 0, "298:RESULT" },
    { 0, 1, 11, 0, 126, 100, 0, "299:SAMPLE" },
    { 0, 1, 11, 0, 86, 100, 0, "300*MCHAR" },
};
SelMenuCfg D_801092D0_selmenu[71] = { /* SelMenuEntry.cfg - 1 */
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
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
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
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
};

SelMenuSe D_80109740_selmenu[5] = { { 1, 0, 120 }, { 9, 0, 106 }, { 2, 0, 110 }, { 4, 0, 114 }, { 76, 0, 123 } };
s16 D_80109754_selmenu = 5;
s16 D_80109756_selmenu = 13;
s16 D_80109758_selmenu[2] = { 4, 12 };
SelMenuEntry D_8010975C_selmenu[6] = {
    { 1, 3, 11, 0, 1000, 0, 0, ">PLAYER%d" },
    { 0, 4, 12, 0, 1000, 0, 0, "PAD%d:%s" },
    { 0, 4, 12, 0, 1000, 0, 0, "GRP :%d" },
    { 0, 4, 12, 0, 1000, 0, 0, "DIF :%s" },
    { 0, 4, 12, 0, 1000, 0, 0, "COIN:%d" },
    { 0, 4, 12, 0, 1000, 0, 0, "PADN:%d" },
};
char *D_801097BC_selmenu[2] = { "HUMAN", "COM" };
char *D_801097C4_selmenu[4] = { "EASY", "NORMAL", "HARD", "VERYHARD" };
char *D_801097D4_selmenu[8] = { "MARIO", "LUIGI", "PEACH", "YOSI", "WARIO", "DONKEY", "WALUIGI", "DAISY" };
char *D_801097F4_selmenu[3] = { "GAME", "BOARD", "DUEL" };
u8 D_80109800_selmenu = 0;
char *D_80109804_selmenu[3] = { "EASY", "NORMAL", "HARD" };
s32 D_80109810_selmenu = 0; /* the asm reads its low half as D_80109812 */
s32 D_80109814_selmenu = 0;
s32 D_80109818_selmenu = 1;

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
    SelMenuCfg *cfg = &D_801092D0_selmenu[D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].cfg - 1];

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
