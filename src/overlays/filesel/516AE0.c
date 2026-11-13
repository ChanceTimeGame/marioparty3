#include "common.h"
#include "game/vibrator.h"

#include "filesel.h"
#include "mallocblock.h"

/* Board summary in a save file view: party (flag 0x16) and mini-game/duel (flag 0x17) boards. */
typedef struct FsSaveBoard {
    /* 0x00 */ s16 chr[4];
    /* 0x08 */ s32 mode;  /* play-mode bit, inverted */
    /* 0x0C */ s32 board;
    /* 0x10 */ s32 length;
    /* 0x14 */ s32 turn;  /* clamped to 99 */
    /* 0x18 */ s32 total; /* clamped to 99 */
} FsSaveBoard; /* size = 0x1C */

/* Save file summary, the same memory as D_801142DC_filesel (UnkFileSelect) seen from 4 bytes
   earlier: func_801122B0_filesel writes D_801142D8_filesel + no * 0x84, so each entry starts with
   its EEPROM-error flag. The word after the third entry is FS_LAST_FILE. */
typedef struct FsSaveInfo {
    /* 0x00 */ s32 bad;    /* the save box failed to load (D_800D20EC_main bit) */
    /* 0x04 */ u8 used;    /* FS_FILE_USED */
    /* 0x05 */ u8 name[0x20]; /* 5 two-byte characters, then zeros */
    /* 0x25 */ char pad25[7];
    /* 0x2C */ u8 storyChr; /* GwStory.unk1 */
    /* 0x30 */ s32 story[7];
    /* 0x4C */ FsSaveBoard party;
    /* 0x68 */ FsSaveBoard duel;
} FsSaveInfo; /* size = 0x84 */

extern FsSaveInfo D_801142D8_filesel[3];
extern u8 D_801129A4_filesel[]; /* story chapter pairs */
extern s32 D_801146D8_filesel;
extern u8 D_800D20EC_main; /* saveload.c: bit per box that failed to load */

s32 func_8005086C_main(void);
s32 func_80050064_main(s32 write);

/* the file name in the common save data */
#define FS_GW_NAME ((u8 *)&GwCommon + 0x94)


/* camera zoom: D_801146B0_filesel */
typedef struct FsCam {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 dist;
    /* 0x1C */ s32 time;
    /* 0x20 */ s32 total;
} FsCam; /* size = 0x24 */

extern FsCam D_801146B0_filesel;
extern s32 D_801129A0_filesel; /* last stick direction (button mask) */
extern s32 D_801146D4_filesel; /* stick repeat counter */


/* model effect slot: D_80114598_filesel[3] */
typedef struct FsEffect {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ Vec start;
    /* 0x10 */ Vec end;
    /* 0x1C */ char unk1C[0x34];
    /* 0x50 */ s32 time; /* also the wobble angle of func_80111004 */
    /* 0x54 */ s32 angle;
    /* 0x58 */ s32 total;
} FsEffect; /* size = 0x5C */

extern FsEffect D_80114598_filesel[3];


/* model move slot: D_80114508_filesel[4] */
typedef struct FsMove {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 time;
    /* 0x08 */ s32 total;
    /* 0x0C */ Vec start;
    /* 0x18 */ Vec end;
} FsMove; /* size = 0x24 */

extern Vec D_80112910_filesel[][2];
extern Vec D_80112958_filesel[];
extern Vec D_8011297C_filesel[];
extern FsMove D_80114508_filesel[4];


extern Vec D_801128A4_filesel[];
extern Vec D_801128C8_filesel[][2];


extern Vec D_80112EA0_filesel; /* camera eye */
extern Vec D_80112EAC_filesel; /* camera target */
extern Vec D_80112EB8_filesel; /* camera up */




extern u16 D_80112D6C_filesel[];
extern u16 D_80112D7C_filesel[];
extern u16 D_80112D8C_filesel[];
extern u16 D_80112D9C_filesel[];
extern u16 D_80112DAC_filesel[];
extern u16 D_80112DBC_filesel[];
void func_8004FCF0_main(void);
s32 func_80050DDC_main(s16 srcBox, s16 dstBox);
s32 func_80050064_main(s32 write);
extern const char D_80112AE0_filesel[]; /* "1" */
extern const char D_80112AE4_filesel[]; /* "2" */
extern const char D_80112AE8_filesel[]; /* "3" */
extern const u8 D_80112AF0_filesel[8];  /* empty name */


/* filesel B: name entry state, D_80114470_filesel..D_801144D4_filesel (offsets from D_80114470) */
extern s32 D_80114470_filesel; /* name changed */



extern s32 D_801127B0_filesel[3];
extern s32 D_801127BC_filesel[8][2]; /* cursor positions */
extern f32 D_800A0A7C_main;

extern u8 *D_801127FC_filesel[18];
extern u8 *D_80112844_filesel[18];
extern u8 *D_8011288C_filesel[5];


#define UNK_VALUE FS_FILE_USED

extern u16 D_800D1244_main;

void func_801059A0_filesel(void) {
    ovlEventCall(D_801127A0_filesel, omovlevtno);
}

FS_FILE_END()

void func_801059D0_filesel(void) {
    Vec pos;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    func_800142A0_main(0x20);
    func_8004A208_main();
    func_8000B5F0_main(1);
    pos = D_801129C0_filesel;
    target = D_801129CC_filesel;
    up = D_801129D8_filesel;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCamSetPositionOrientation(0, &pos, &target, &up);
    func_80030030_main(1.0f);
    func_8004A950_main();
    pfInit();
    func_8005A6B0_main();
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x80, 0x80, 0x80);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
}

void func_80105BC0_filesel(void) {
    D_80112E90_filesel = 0;
    func_801059D0_filesel();
    func_80107C84_filesel();
}

FS_FILE_END()

void func_80105BF0_filesel(void) {
    func_80105C1C_filesel();
    func_801061D4_filesel();
    func_8010744C_filesel();
}

#ifdef NON_MATCHING
/* Same as opening's func_8010621C_opening: GCC hoists &D_801135D0_filesel into a register (retail
   addresses it through $at each iteration). */
void func_80105C1C_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_801135D0_filesel[i] = -1;
        D_80112ED0_filesel[i].espId = -1;
        D_80112ED0_filesel[i].x = D_80112ED0_filesel[i].y = 0;
        D_80112ED0_filesel[i].scaleX = D_80112ED0_filesel[i].scaleY = 0.0f;
        D_80112ED0_filesel[i].unk14 = 0.0f;
        D_80112ED0_filesel[i].unk18 = 0xFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105C1C_filesel);
#endif

s16 func_80105CB0_filesel(s32 no) {
    return D_801135D0_filesel[no];
}

s16 func_80105CC4_filesel(s32 no) {
    return D_80112ED0_filesel[no].espId;
}

void func_80105CE0_filesel(s32 no, s32 dataNum) {
    D_801135D0_filesel[no] = func_8000B838_main(dataNum);
}

void func_80105D18_filesel(s32 no) {
    if (D_801135D0_filesel[no] != -1) {
        HuSprKill(D_801135D0_filesel[no]);
    }
    D_801135D0_filesel[no] = -1;
}

void func_80105D70_filesel(s32 no, s16 animNo) {
    D_80112ED0_filesel[no].espId = InitEspriteSlot(D_801135D0_filesel[animNo], 0, 0);
    func_80105FBC_filesel(no, 160, 120);
}

void func_80105DD8_filesel(s32 no) {
    if (D_80112ED0_filesel[no].espId != -1) {
        func_8000C184_main(D_80112ED0_filesel[no].espId);
    }
    D_80112ED0_filesel[no].espId = -1;
}

void func_80105E48_filesel(s32 no, s32 dataNum) {
    func_80105CE0_filesel(no, dataNum);
    func_80105D70_filesel(no, no);
}

void func_80105E7C_filesel(s32 no, s32 dataNum) {
    func_80105E48_filesel(no, dataNum);
    func_8000BC48_main(D_80112ED0_filesel[no].espId, 0x4000);
}

void func_80105EC0_filesel(s32 no) {
    func_80105DD8_filesel(no);
    func_80105D18_filesel(no);
}

void func_80105EEC_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80105EC0_filesel(i);
    }
}

void func_80105F24_filesel(s32 no) {
    func_8000BB54_main(D_80112ED0_filesel[no].espId);
}

void func_80105F54_filesel(s32 no) {
    func_8000BB94_main(D_80112ED0_filesel[no].espId);
}

void func_80105F84_filesel(s32 no) {
    func_80105F24_filesel(no);
}

void func_80105FA0_filesel(s32 no) {
    func_80105F54_filesel(no);
}

void func_80105FBC_filesel(s32 no, s32 x, s32 y) {
    D_80112ED0_filesel[no].x = x;
    D_80112ED0_filesel[no].y = y;
    func_8000BBD4_main(D_80112ED0_filesel[no].espId, x, y);
}

void func_80106014_filesel(s32 no, s32 *x, s32 *y) {
    *x = D_80112ED0_filesel[no].x;
    *y = D_80112ED0_filesel[no].y;
}

void func_80106044_filesel(s32 no, f32 x, f32 y) {
    D_80112ED0_filesel[no].scaleX = x;
    D_80112ED0_filesel[no].scaleY = y;
    func_8000BE5C_main(D_80112ED0_filesel[no].espId, x, y);
}

void func_80106094_filesel(s32 no, u16 alpha) {
    func_8000BBFC_main(D_80112ED0_filesel[no].espId, alpha);
}

void func_801060CC_filesel(s32 no, u16 attr) {
    func_8000BC48_main(D_80112ED0_filesel[no].espId, attr);
}

void func_80106100_filesel(s32 no, u16 attr) {
    func_8000BC88_main(D_80112ED0_filesel[no].espId, attr);
}

void func_80106134_filesel(s32 no, u16 arg1) {
    func_8000BCC8_main(D_80112ED0_filesel[no].espId, arg1);
}

void func_80106168_filesel(s32 no, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_80112ED0_filesel[no].espId, 1);
    func_8000BD94_main(D_80112ED0_filesel[no].espId, arg1, arg2);
}

void func_801061D4_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_80113650_filesel[i].model = -1;
        D_80113650_filesel[i].motion = -1;
    }
}

void func_80106220_filesel(s32 no, s32 arg1, s32 dataNum) {
    s16 model = func_8000B108_main(arg1, dataNum);

    D_80113650_filesel[no].model = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void func_801062BC_filesel(s32 no, s32 dataNum, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(dataNum);
    D_80113650_filesel[no].motion = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_80106344_filesel(s32 no) {
    if (D_80113650_filesel[no].model != -1) {
        func_8001ACDC_main(D_80113650_filesel[no].model);
        D_80113650_filesel[no].model = -1;
    }
    if (D_80113650_filesel[no].motion != -1) {
        func_8002D4B8_main(D_80113650_filesel[no].motion);
        D_80113650_filesel[no].motion = -1;
    }
}

void func_801063F4_filesel(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80106344_filesel(i);
    }
}

s16 func_8010642C_filesel(s32 no) {
    return D_80113650_filesel[no].model;
}

s16 func_80106450_filesel(s32 no) {
    return D_80113650_filesel[no].motion;
}

void func_80106474_filesel(s32 no, f32 x, f32 y, f32 z) {
    D_80113650_filesel[no].rot.x = x;
    D_80113650_filesel[no].rot.y = y;
    D_80113650_filesel[no].rot.z = z;
    Hu3DModelRotSet(D_80113650_filesel[no].model, x, y, z);
}

void func_801064DC_filesel(s32 no, f32 x, f32 y, f32 z) {
    D_80113650_filesel[no].pos[0] = x;
    D_80113650_filesel[no].pos[1] = y;
    D_80113650_filesel[no].pos[2] = z;
    Hu3DModelPosSet(D_80113650_filesel[no].model, x, y, z);
}

void func_80106550_filesel(s32 no, f32 x, f32 y, f32 z) {
    D_80113650_filesel[no].scale.x = x;
    D_80113650_filesel[no].scale.y = y;
    D_80113650_filesel[no].scale.z = z;
    Hu3DModelScaleSet(D_80113650_filesel[no].model, x, y, z);
}

void func_801065B8_filesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80113650_filesel[no].pos[0];
    *y = D_80113650_filesel[no].pos[1];
    *z = D_80113650_filesel[no].pos[2];
}

void func_8010660C_filesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80113650_filesel[no].rot.x;
    *y = D_80113650_filesel[no].rot.y;
    *z = D_80113650_filesel[no].rot.z;
}

void func_80106654_filesel(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80113650_filesel[no].scale.x;
    *y = D_80113650_filesel[no].scale.y;
    *z = D_80113650_filesel[no].scale.z;
}

void func_8010669C_filesel(s32 no) {
    func_8001C258_main(D_80113650_filesel[no].model, 4, 4);
}

void func_801066DC_filesel(s32 no) {
    func_8001C258_main(D_80113650_filesel[no].model, 4, 0);
}

void func_8010671C_filesel(s32 no, s16 flag) {
    func_8001C814_main(D_80113650_filesel[no].model, -1, flag);
}

void func_80106760_filesel(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80113650_filesel[no].model, D_80113650_filesel[motNo].motion, arg2, arg3, arg4);
}

void func_801067D0_filesel(s32 no, s16 arg1) {
    func_8001C814_main(D_80113650_filesel[no].model, arg1, 0);
}

void func_80106814_filesel(s32 no, f32 speed) {
    func_8001C92C_main(D_80113650_filesel[no].model, speed);
}

void func_8010684C_filesel(s32 no, u32 time) {
    func_8001C6A8_main(D_80113650_filesel[no].model, time);
}

void func_801068B0_filesel(s32 no) {
    while (HmfModelData[D_80113650_filesel[no].model].unk40 !=
           D_800CCF58_main[HmfModelData[D_80113650_filesel[no].model].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_80106950_filesel(s32 no) {
    return HmfModelData[D_80113650_filesel[no].model].unk40 ==
           D_800CCF58_main[HmfModelData[D_80113650_filesel[no].model].unk02].unk02;
}

void func_801069D8_filesel(s32 no, s32 motNo, s16 flag) {
    s16 model = func_8010642C_filesel(no);
    s16 motion = func_80106450_filesel(motNo);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, flag);
}

void func_80106A48_filesel(s32 dataNum) {
    D_80114150_filesel = func_8000B838_main(dataNum);
    D_80114152_filesel = InitEspriteSlot(D_80114150_filesel, 0, 0);
    func_8000BC48_main(D_80114152_filesel, 0x4000);
    func_8000BBD4_main(D_80114152_filesel, 160, 120);
}

void func_80106AAC_filesel(void) {
    func_8000C184_main(D_80114152_filesel);
    HuSprKill(D_80114150_filesel);
}

u32 func_80106AD8_filesel(u32 mes) {
    u8 buf[0x100];
    s32 size;
    void *copy;
    u32 ret;

    if (mes <= 0x80000000) {
        ret = mes;
    } else {
        size = func_800452A0_main(buf, (void *)mes);
        copy = HuMemAlloc(size);
        bcopy(buf, copy, size);
        ret = (u32)copy;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_80106B40_filesel(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 id;
    u32 buf;

    switch (type) {
        case 1:
            buf = func_80106AD8_filesel(mes);
            id = func_80106ED8_filesel(buf, x, y, w, h, type);
            break;
        case 2:
            buf = func_80106AD8_filesel(mes);
            id = func_80107040_filesel(buf, x, y, w, h, type);
            break;
        case 3:
            buf = func_80106AD8_filesel(mes);
            id = func_801071E8_filesel(buf, x, y, type);
            break;
        case 4:
            buf = func_80106AD8_filesel(mes);
            id = func_801072B4_filesel(buf, x, y, type);
            break;
        case 5:
            buf = func_80106AD8_filesel(mes);
            id = func_80107380_filesel(buf, x, y, type);
            break;
        case 0:
        default:
            buf = func_80106AD8_filesel(mes);
            id = func_80106D8C_filesel(buf, x, y, w, h, type);
            break;
    }
    if (buf > 0x80000000) {
        D_80114158_filesel[no].unk_04 = buf;
    }
    D_80114158_filesel[no].unk_00 = id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106B40_filesel);
#endif

s16 func_80106D8C_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0, 0x40, 0x40);
    func_8005C02C_main(win, 7);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80106ED8_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 4);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 1);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107040_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 7, 0xFF, 0xFF, 0xFF);
    func_8005C060_main(win, 0, 0, 0, 0);
    func_8005C060_main(win, 3, 0, 0, 0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 6);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801071E8_filesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801072B4_filesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x14);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 0);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107380_filesel(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005FE54_main(win, 1);
    func_80060C14_main(win, 0);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

void func_8010744C_filesel(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80114158_filesel[i].unk_00 = -1;
        D_80114158_filesel[i].unk_04 = 0;
    }
}

void func_80107490_filesel(s32 no) {
    if (D_80114158_filesel[no].unk_08 == 3) {
        func_80060EA8_main(D_80114158_filesel[no].unk_00, 1);
        func_800610E0_main(D_80114158_filesel[no].unk_00);
    } else {
        func_8005FE90_main(D_80114158_filesel[no].unk_00);
        func_8005F364_main(D_80114158_filesel[no].unk_00);
        D_80114158_filesel[no].unk_00 = -1;
    }
    if (D_80114158_filesel[no].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[no].unk_04);
        D_80114158_filesel[no].unk_04 = 0;
    }
}

void func_80107574_filesel(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80114158_filesel[i].unk_00 != -1) {
            func_80107490_filesel(i);
        }
    }
}

void func_801075D8_filesel(s32 no, f32 x, f32 y) {
    func_8005BB18_main(D_80114158_filesel[no].unk_00, x, y);
}

void func_80107608_filesel(s32 no, f32 x, f32 y) {
    func_8005BA90_main(D_80114158_filesel[no].unk_00, x, y);
}

void func_80107670_filesel(s32 no) {
    func_8005FFA8_main(D_80114158_filesel[no].unk_00);
}

void func_801076A0_filesel(s32 no) {
    func_8005FE90_main(D_80114158_filesel[no].unk_00);
}

void func_801076D0_filesel(s32 arg0, u32 arg1) {
    u32 temp_v0;

    func_8005D294_main(D_80114158_filesel[arg0].unk_00);
    if (D_80114158_filesel[arg0].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[arg0].unk_04);
        D_80114158_filesel[arg0].unk_04 = 0;
    }

    temp_v0 = func_80106AD8_filesel(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        D_80114158_filesel[arg0].unk_04 = temp_v0;
    }
    func_8005B43C_main(D_80114158_filesel[arg0].unk_00, temp_v0, -1, -1);
}

void func_8010779C_filesel(s32 no, s8 arg1, s32 arg2) {
    func_800601BC_main(D_80114158_filesel[no].unk_00, arg2, arg1);
}

s32 func_801077D8_filesel(s32 no, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_80114158_filesel[no].unk_00, arg1, arg2);
}

s16 func_80107810_filesel(s32 no) {
    return D_80114158_filesel[no].unk_00;
}

void func_8010782C_filesel(s32 no) {
    while (func_8005E0C0_main(D_80114158_filesel[no].unk_00) != 0) {
        HuPrcVSleep();
    }
}

void func_80107880_filesel(s32 btn) {
    do {
        HuPrcVSleep();
    } while (!(btn & D_800D5558_main[0]));
}

void func_801078BC_filesel(s32 no, s16 arg1) {
    func_8005BE30_main(D_80114158_filesel[no].unk_00, arg1);
}

u16 func_801078F4_filesel(s32 val) {
    char buf[0x100];
    FsHmfCamView *view;

    HuPrcSleep(3);
    while (TRUE) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(buf, "\n%d\n", val);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            view = *(FsHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
            sprintf(buf, "POS:%4.2f,%4.2f,%4.2f", view->pos.x, view->pos.y, view->pos.z);
            print8(16, 180, buf);
            sprintf(buf, "A T:%4.2f,%4.2f,%4.2f", view->at.x, view->at.y, view->at.z);
            print8(16, 190, buf);
            sprintf(buf, "U P:%4.2f,%4.2f,%4.2f", view->up.x, view->up.y, view->up.z);
            print8(16, 200, buf);
        } else {
            sprintf(buf, "%d", val);
            print8(16, 220, buf);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_80107AA8_filesel(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 n;

    for (i = 0; i < 4; i++) {
        GwPlayer[i].pad = 0xFF;
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (CheckControllerRead(i) != 0) {
            GwPlayer[n].pad = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].pad == 0xFF) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    if (GwPlayer[k].pad == j) {
                        break;
                    }
                }
                if (k == 4) {
                    break;
                }
            }
            GwPlayer[i].pad = j;
        }
    }
}

void func_80107C50_filesel(omObjData *obj) {
    if (D_800D5558_main[0] & 0x4000) {
        func_8001F38C_main(0xFF, 0, 0);
    }
}

void func_80107C84_filesel(void) {
    func_80105BF0_filesel();
    func_801119F4_filesel();
    func_80111C30_filesel();
    D_80114468_filesel = omAddPrcObj(func_80107CF8_filesel, 0x5000, 0x2000, 0);
    D_8011446C_filesel = omAddObj(6, 0, 0, -1, func_80107C50_filesel);
}

#ifdef NON_MATCHING
/* Differs only in scheduling and register use: retail hoists 0.0f and 31.0f into FPRs out of the
   retry loop, keeps &D_800D09A9_main in s0, and builds the omovlhis entry with swapped temporaries. */
void func_80107CF8_filesel(void) {
    Vec world;
    Vec2f screen;
    Vec pos;
    s32 sel;
    s32 no;
    s32 result;
    omOvlHisData *his;
    u8 board;
    s32 ovl;

    func_8001F38C_main(0, 0x40, 0x40);
    func_8010F12C_filesel();
    func_80106A48_filesel(0x1F0000);
    HuPrcSleep(1);
    func_8010F168_filesel();
    HuAudSeqPlay(3);
    WipeCreateIn(11, 16);
    HuPrcSleep(16);
    do {
        func_8010F65C_filesel();
        func_8010F678_filesel(0);
        func_801083AC_filesel();
        func_80110C84_filesel();
        func_8010FBE0_filesel(0, 24);
        func_8010FBE0_filesel(1, 24);
        func_8010FBE0_filesel(2, 24);
        HuAudFXPlay(0x2F3);
        HuPrcSleep(24);
        func_801076D0_filesel(4, (u32)D_80112A64_filesel);
        func_80108C34_filesel();
        func_801088DC_filesel();
        func_801076D0_filesel(4, 0x2A00);
        do {
            sel = func_80108EB8_filesel();
            HuPrcVSleep();
        } while (sel < 0);
        no = sel;
        func_80108440_filesel();
        func_8010F65C_filesel();
        func_8010F678_filesel(1);
        func_8010D13C_filesel(no);
        func_8010D660_filesel(no);
        HuPrcSleep(3);
        func_801065B8_filesel(no, &pos.x, &pos.y, &pos.z);
        pos.z = 0.0f;
        if (pos.y < 120.0f) {
            pos.x = 0.0f;
            pos.y = 120.0f;
            func_8010F874_filesel(no);
            func_80110B7C_filesel(no, pos.x, pos.y, pos.z, 16);
            HuAudFXPlay(0x2F0);
            HuPrcSleep(16);
        } else {
            pos.x = 0.0f;
            pos.y = 120.0f;
            func_8010F874_filesel(no);
            func_80110B7C_filesel(no, pos.x, pos.y, pos.z, 32);
            HuAudFXPlay(0x2F0);
            HuPrcSleep(32);
        }
        func_801064DC_filesel(no, pos.x, pos.y, pos.z);
        func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
        func_8010F844_filesel(no);
        HuVecCopyXYZ(&world, pos.x, pos.y, pos.z);
        Hu3DCam3DToScreen(0, &world, &screen);
        func_8005BA90_main(func_80107810_filesel(no + 1), screen.x - 31.0f, screen.y);
        func_80105FBC_filesel(no + 13, screen.x, screen.y + 9.0f);
        func_801066DC_filesel(no);
        func_801066DC_filesel(no + 3);
        func_8010F844_filesel(no);
        func_801076D0_filesel(4, (u32)D_80112A64_filesel);
        func_80108C34_filesel();
        func_801076D0_filesel(4, 0x2A0C);
        func_8010DDC0_filesel(no);
        func_8010DFF4_filesel(no);
        while (TRUE) {
            if (D_800D5558_main[0] & 0x8000) {
                break;
            }
            if (D_800D5558_main[0] & 0x4000) {
                break;
            }
            HuPrcVSleep();
        }
        func_8005D294_main(D_80114188_filesel);
        HuAudFXPlay(0x138);
        result = func_8010CCA8_filesel(sel);
        if (result == -1) {
        func_8010DEEC_filesel();
        func_8010E1B4_filesel();
        func_8010F874_filesel(no);
        func_80110B7C_filesel(no, -1000.0f, 1000.0f, 0.0f, 30);
        HuAudFXPlay(0x2F0);
        HuPrcSleep(30);
        func_8010669C_filesel(0);
        func_8010669C_filesel(3);
        func_8010669C_filesel(1);
        func_8010669C_filesel(4);
        func_8010669C_filesel(2);
        func_8010669C_filesel(5);
        func_8010F874_filesel(0);
        func_8010F874_filesel(1);
        func_8010F874_filesel(2);
        func_8010DD54_filesel();
        func_8010DF58_filesel();
        HuPrcVSleep();
        }
    } while (result == -1);
    D_800D09A9_main = sel;
    func_800465F4_main(0);
    D_800D09A9_main = sel;
    func_80050CFC_main();
    HuAudFXPlay(0x155);
    func_8010F10C_filesel();
    func_8010F874_filesel(sel);
    func_80111944_filesel(40);
    func_80105F54_filesel(12);
    func_8010684C_filesel(sel, 0);
    func_801067D0_filesel(sel, 7);
    HuPrcSleep(20);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_80112684_filesel();
    WipeCreateOut(11, 20);
    HuAudSeqFadeOut(20);
    HuPrcSleep(20);
    func_8010F5C8_filesel();
    func_80106AAC_filesel();
    func_80107574_filesel();
    func_8005F524_main();
    omOvlKill();
    switch (result) {
        case 0:
            func_800465DC_main(1);
            omOvlCallEx(0x77, 1, 0x91);
            func_80112758_filesel();
            break;
        case 1:
            func_800465DC_main(0);
            func_80112758_filesel();
            if (_CheckFlag(0x28) != 0) {
                omOvlCallEx(0x77, 0, 0x81);
                omOvlHisChg(1, 0x7A, 0, 0x81);
            } else {
                board = GwStory.unk0;
                if (D_80112A68_filesel[board] != 0xFF) {
                    his = &omovlhis[++omovlhisidx];
                    his->overlayID = 0x7A;
                    his->event = 0;
                    his->stat = 0x82;
                    D_800CE20A_main = D_80112A68_filesel[board];
                    ovl = 0x75;
                } else {
                    ovl = 0x77;
                }
                omOvlCallEx(ovl, 0, 0x81);
                omOvlHisChg(1, 0x77, 0, 0x81);
            }
            break;
        case 2:
            func_80112758_filesel();
            func_800465DC_main(0);
            his = &omovlhis[++omovlhisidx];
            his->overlayID = 0x7A;
            his->event = 0;
            his->stat = 0x82;
            omOvlCallEx(0x78, 4, 0x81);
            omOvlHisChg(1, 0x77, 0, 0x81);
            break;
        default:
            while (TRUE) {
                HuPrcVSleep();
            }
    }
    omDelPrcObj(D_80114468_filesel);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107CF8_filesel);
#endif

void func_801083AC_filesel(void) {
    func_80105E48_filesel(1, 0x1F000D);
    func_80105F54_filesel(1);
    func_80105E48_filesel(2, 0x1F000E);
    func_80106168_filesel(2, 0, 0);
    func_801060CC_filesel(2, 0x800);
    func_80105F54_filesel(2);
    func_80105E48_filesel(3, 0x1F000F);
    func_80106168_filesel(3, 0, 0);
    func_801060CC_filesel(3, 0x800);
    func_80105F54_filesel(3);
}

void func_80108440_filesel(void) {
    func_80105EC0_filesel(1);
    func_80105EC0_filesel(2);
    func_80105EC0_filesel(3);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112A64_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112A68_filesel);

u32 func_8010846C_filesel(void) {
    s32 sel;
    s32 i;
    s32 file;

    sel = FS_LAST_FILE;
    if (sel >= 3) {
        sel = 2;
    }
    if (D_801142DC_filesel[FS_LAST_FILE].unk_00 != FS_FILE_USED) {
        for (i = 0; i < 3; i++) {
            if (D_801142DC_filesel[i].unk_00 == FS_FILE_USED) {
                sel = i;
                break;
            }
        }
    }
    func_80105F24_filesel(18);
    func_8010AB1C_filesel(18, sel);
    for (i = 0; i < 8; i++) {
        func_80106044_filesel(18, 1.0f, i * 0.125f);
        HuPrcVSleep();
    }
    func_80106044_filesel(18, 1.0f, 1.0f);
    func_801110F0_filesel(sel);
    while (TRUE) {
        while ((sel = func_80109570_filesel(sel)) == -1) {
            HuPrcVSleep();
        }
        switch (sel) {
            case 0:
            case 1:
            case 2:
                HuAudFXPlay(2);
                func_80105F54_filesel(18);
                return sel;
            case 3:
                HuAudFXPlay(2);
                func_80109B2C_filesel();
                break;
            case 4:
                HuAudFXPlay(2);
                func_8010A028_filesel();
                break;
            case 5:
            case 6:
            case 7:
                HuAudFXPlay(2);
                file = sel - 5;
                func_80105FA0_filesel(18);
                func_80108D74_filesel();
                func_80108A94_filesel();
                func_80105FA0_filesel(12);
                func_8010F874_filesel(0);
                func_8010F874_filesel(1);
                func_8010F874_filesel(2);
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_8010F874_filesel(i);
                        func_8010FF48_filesel(i, 16);
                    }
                }
                HuAudFXPlay(0x2F2);
                func_80110320_filesel(file, 32);
                HuAudFXPlay(0x2F0);
                HuPrcSleep(16);
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_8010669C_filesel(i);
                        func_8010669C_filesel(i + 3);
                    }
                }
                HuPrcSleep(16);
                func_80107670_filesel(0);
                func_8010F65C_filesel();
                func_8010F678_filesel(4);
                if (func_80109968_filesel(file) != 0) {
                    func_80107670_filesel(4);
                    func_80107608_filesel(4, 160.0f, 208.0f);
                    func_801076D0_filesel(4, 0x2A15);
                    HuPrcSleep(3);
                    SLCurBoxNoSet(file);
                    func_80112584_filesel(file);
                    func_80112184_filesel(file);
                    func_801076A0_filesel(4);
                    HuPrcSleep(3);
                }
                func_801076A0_filesel(0);
                func_8010F65C_filesel();
                func_8011072C_filesel(file, 32);
                HuAudFXPlay(0x2F1);
                HuPrcSleep(16);
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_8010FBE0_filesel(i, 16);
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (file != i) {
                        func_801066DC_filesel(i);
                        func_801066DC_filesel(i + 3);
                    }
                }
                HuPrcSleep(16);
                for (i = 0; i < 3; i++) {
                    func_8010F844_filesel(i);
                }
                func_8010F678_filesel(0);
                func_801088DC_filesel();
                func_80108C34_filesel();
                func_80105F84_filesel(18);
                break;
        }
        func_8010AB1C_filesel(18, sel);
        HuPrcVSleep();
    }
}

s32 func_80108834_filesel(void) {
    s32 i;
    s32 total;

    for (i = 0, total = 0; i < ARRAY_COUNT(D_801142DC_filesel); i++) {
        if (D_801142DC_filesel[i].unk_00 == UNK_VALUE) {
            total++;
        }
    }

    return total;
}

void func_80108878_filesel(void) {
    s32 n = func_80108834_filesel();

    if (n == 1 || n == 2) {
        func_80106168_filesel(2, 1, 0);
    } else {
        func_80106168_filesel(2, 0, 0);
    }
    if (n != 0) {
        func_80106168_filesel(3, 1, 0);
    } else {
        func_80106168_filesel(3, 0, 0);
    }
}

void func_801088DC_filesel(void) {
    Vec from;
    Vec to;
    Vec pos;
    f32 t;
    s32 i;

    for (i = 0; i < 3; i++) {
    }
    func_80105F24_filesel(1);
    func_80105F24_filesel(2);
    func_80105F24_filesel(3);
    func_80108878_filesel();
    for (i = 0; i < 11; i++) {
        t = i * 0.1f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        HuVecCopyXYZ(&from, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&to, 224.0f, 40.0f, 0.0f);
        pos.x = (to.x - from.x) * t + from.x;
        pos.y = (to.y - from.y) * t + from.y;
        func_80105FBC_filesel(1, pos.x, pos.y);
        func_80105FBC_filesel(2, pos.x - 22.0f, pos.y);
        func_80105FBC_filesel(3, pos.x + 26.0f, pos.y);
        HuPrcVSleep();
    }
}

void func_80108A94_filesel(void) {
    Vec from;
    Vec to;
    Vec pos;
    f32 t;
    s32 i;

    for (i = 0; i < 11; i++) {
        t = 1.0f - i * 0.1f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        HuVecCopyXYZ(&from, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&to, 224.0f, 40.0f, 0.0f);
        pos.x = (to.x - from.x) * t + from.x;
        pos.y = (to.y - from.y) * t + from.y;
        func_80105FBC_filesel(1, pos.x, pos.y);
        func_80105FBC_filesel(2, pos.x - 22.0f, pos.y);
        func_80105FBC_filesel(3, pos.x + 26.0f, pos.y);
        HuPrcVSleep();
    }
    func_80105F54_filesel(1);
    func_80105F54_filesel(2);
    func_80105F54_filesel(3);
}

void func_80108C34_filesel(void) {
    Vec from;
    Vec to;
    Vec pos;
    f32 t;
    s32 i;

    func_80107670_filesel(4);
    for (i = 0; i < 11; i++) {
        t = i * 0.1f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        HuVecCopyXYZ(&from, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&to, 160.0f, 192.0f, 0.0f);
        pos.x = (to.x - from.x) * t + from.x;
        pos.y = (to.y - from.y) * t + from.y;
        func_80107608_filesel(4, 160.0f, (96.0f - t * 96.0f) + 208.0f);
        HuPrcVSleep();
    }
}

void func_80108D74_filesel(void) {
    Vec from;
    Vec to;
    Vec cur;
    f32 t;
    s32 i;

    i = 0;
    do {
        t = 1.0f - i * 0.1f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        HuVecCopyXYZ(&from, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&to, 160.0f, 192.0f, 0.0f);
        cur.x = (to.x - from.x) * t + from.x;
        cur.y = (to.y - from.y) * t + from.y;
        func_80107608_filesel(4, 160.0f, (96.0f - t * 96.0f) + 208.0f);
        i++;
        HuPrcVSleep();
    } while (i < 11);
    func_801076A0_filesel(4);
}

// 255 - alpha is folded to ~alpha (retail keeps 255 in a register), shifting s3/s4 (masked 23); logic checked
#ifdef NON_MATCHING
s32 func_80108EB8_filesel(void) {
    Vec pos;
    Vec2f scr;
    Vec mpos;
    s16 models[2];
    s32 x;
    u32 file;
    s32 i;
    s32 alpha;
    s32 ret;
    s32 no;

    HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
    Hu3DCam3DToScreen(0, &pos, &scr);
    x = scr.x - 31.0f;
    func_8005BA90_main(func_80107810_filesel(1), x, 0xA8);
    func_80105FBC_filesel(13, x + 31, 0xB1);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    Hu3DCam3DToScreen(0, &pos, &scr);
    x = scr.x - 31.0f;
    func_8005BA90_main(func_80107810_filesel(2), x, 0xA8);
    func_80105FBC_filesel(14, x + 31, 0xB1);
    HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
    Hu3DCam3DToScreen(0, &pos, &scr);
    x = scr.x - 31.0f;
    func_8005BA90_main(func_80107810_filesel(3), x, 0xA8);
    func_80105FBC_filesel(15, x + 31, 0xB1);
    func_8010F844_filesel(0);
    func_8010F844_filesel(1);
    func_8010F844_filesel(2);
    func_801075D8_filesel(1, 1.0f, 1.0f);
    func_801075D8_filesel(2, 1.0f, 1.0f);
    func_801075D8_filesel(3, 1.0f, 1.0f);
    func_80107670_filesel(4);
    ret = func_8010846C_filesel();
    HuPrcVSleep();
    file = ret;
    no = ret;
    if (D_801142DC_filesel[file].unk_00 != FS_FILE_USED
        || (D_801142DC_filesel[file].unk_01[0] | D_801142DC_filesel[file].unk_01[1]) == 0) {
        /* empty file: enter a name */
        func_80108D74_filesel();
        func_80108A94_filesel();
        func_80105FA0_filesel(12);
        func_8010F874_filesel(0);
        func_8010F874_filesel(1);
        func_8010F874_filesel(2);
        for (i = 0; i < 3; i++) {
            if (file != i) {
                func_8010F874_filesel(i);
                func_8010FF48_filesel(i, 16);
            }
        }
        HuAudFXPlay(0x2F2);
        func_80110320_filesel(file, 32);
        HuAudFXPlay(0x2F0);
        HuPrcSleep(16);
        for (i = 0; i < 3; i++) {
            if (file != i) {
                func_8010669C_filesel(i);
                func_8010669C_filesel(i + 3);
            }
        }
        HuPrcSleep(16);
        func_80107670_filesel(0);
        func_8010F65C_filesel();
        func_8010F678_filesel(4);
        if (func_80109904_filesel(file) != 0) {
            func_801076A0_filesel(0);
            func_8010F65C_filesel();
            func_80107670_filesel(4);
            func_80107608_filesel(4, 160.0f, 208.0f);
            func_801076D0_filesel(4, 0x2A14);
            HuPrcSleep(3);
            SLCurBoxNoSet(file);
            func_8004FCF0_main();
            func_80112584_filesel(file);
            func_80112184_filesel(file);
            func_801076A0_filesel(4);
            HuPrcSleep(3);
            func_801065B8_filesel(file, &mpos.x, &mpos.y, &mpos.z);
            func_80106220_filesel(6, 0x1F002B, 0x6A9);
            func_80106220_filesel(7, 0x1F002C, 0x6A9);
            func_801064DC_filesel(6, mpos.x, mpos.y, mpos.z);
            func_80106550_filesel(6, 0.48f, 0.48f, 0.48f);
            func_801064DC_filesel(7, mpos.x, mpos.y, mpos.z);
            func_80106550_filesel(7, 0.48f, 0.48f, 0.48f);
            func_8010669C_filesel(file);
            func_8010669C_filesel(file + 3);
            func_80106344_filesel(file);
            func_80106220_filesel(no, 0x1F002A, 0x6A9);
            func_801064DC_filesel(file, mpos.x, mpos.y, mpos.z);
            func_80106550_filesel(file, 0.48f, 0.48f, 0.48f);
            func_8010684C_filesel(file, 0);
            func_8010671C_filesel(file, 1);
            func_8010669C_filesel(file);
            models[0] = func_8010642C_filesel(6);
            models[1] = func_8010642C_filesel(7);
            alpha = 255;
        func_8001FA68_main(models[0]);
            func_8001FA68_main(models[1]);
            func_801066DC_filesel(6);
            func_8010669C_filesel(7);
            for (i = 0, alpha = 255; i < 16; i++) {
                func_8001F9E4_main(models[0], alpha);
                alpha -= 16;
                HuPrcVSleep();
            }
            func_8010669C_filesel(6);
            func_801066DC_filesel(7);
            for (i = 0, alpha = 255; i < 16; i++) {
                func_8001F9E4_main(models[1], 255 - alpha);
                alpha -= 16;
                HuPrcVSleep();
            }
            func_8001F9E4_main(models[1], 255);
            func_801066DC_filesel(file);
            func_801066DC_filesel(file + 3);
            func_80106344_filesel(6);
            func_80106344_filesel(7);
            func_80105EC0_filesel(file + 13);
            func_8010F760_filesel(file, 1);
            func_80105FA0_filesel(file + 13);
            return ret;
        }
        func_801076A0_filesel(0);
        func_8010F65C_filesel();
        func_8011072C_filesel(file, 32);
        HuAudFXPlay(0x2F1);
        HuPrcSleep(16);
        for (i = 0; i < 3; i++) {
            if (file != i) {
                func_8010FBE0_filesel(i, 16);
            }
        }
        for (i = 0; i < 3; i++) {
            if (file != i) {
                func_801066DC_filesel(i);
                func_801066DC_filesel(i + 3);
            }
        }
        HuPrcSleep(16);
        for (i = 0; i < 3; i++) {
            func_8010F844_filesel(i);
        }
        func_8010F678_filesel(0);
        func_801076D0_filesel(4, 0x2A00);
        func_801088DC_filesel();
        func_80108C34_filesel();
        return -1;
    }
    /* existing save: load it */
    /* existing save: load it */
    SLCurBoxNoSet(file);
    func_80050800_main();
    func_80112184_filesel(file);
    func_80108D74_filesel();
    func_80108A94_filesel();
    for (i = 0; i < 3; i++) {
        if (file != i) {
            func_8010F874_filesel(i);
            func_8010FF48_filesel(i, 16);
        }
    }
    HuAudFXPlay(0x2F2);
    HuPrcSleep(16);
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108EB8_filesel);
#endif

#define CLAMP_BELOW(val, limit) ((val) < (limit) ? (val) : 0)

enum OptionsFileSelect {
    OPTION_FILE0 = 0,
    OPTION_FILE1 = 1,
    OPTION_FILE2 = 2,
    OPTION_FILES_END,
    OPTION_COPY = 3,
    OPTION_ERASE = 4,
    OPTION_FILES_NAME_BEGIN,
    OPTION_FILE0_NAME = 5,
    OPTION_FILE1_NAME = 6,
    OPTION_FILE2_NAME = 7,
    OPTION_MAX = 7,
};

// TODO: can the gotos be removed?
// main function for handling input when an option hasn't been select yet
u32 func_80109570_filesel(s32 arg0) {
    s32 temp_v0;
    u32 temp_v1;
    s32 animTimerAdjusted;
    s32 animTimer;
    u16 pressedInput;
    s32 cursorIndex;
    u32 selectedOption;
    s32 unkValue;

    animTimer = 0;

    if (arg0 < 0) {
        arg0 = 0;
    }

    selectedOption = arg0;
    cursorIndex = selectedOption;
    unkValue = UNK_VALUE;

    while (1) {
        pressedInput = D_800D1244_main;
        temp_v0 = func_80111B14_filesel(0);
        if (temp_v0 != -1) {
            pressedInput |= temp_v0;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            switch (selectedOption) {
                case OPTION_FILE0:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE1:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE2:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_COPY:
                case OPTION_ERASE:
                case OPTION_FILE0_NAME:
                case OPTION_FILE1_NAME:
                case OPTION_FILE2_NAME:
                    break;
                default:
                    goto checkIfCursorIndexChanged;
            }
            return selectedOption;
        }
        if ((D_800D5558_main[0] & B_BUTTON)) {
            if (selectedOption > OPTION_MAX) {
                goto checkIfCursorIndexChanged;
            }
        }
        switch (selectedOption) {
            case OPTION_FILE0:
            case OPTION_FILE1:
            case OPTION_FILE2:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    func_801076D0_filesel(4, 0x2A00);
                    func_80110FB0_filesel(selectedOption);
                    cursorIndex = selectedOption + 1;
                    if (pressedInput & L_JPAD) {
                        cursorIndex = selectedOption - 1;
                        // if less than 0, wrap index back around to file index 2
                        if (cursorIndex < 0) {
                            cursorIndex = OPTION_FILE2;
                        }
                    } else {
                        cursorIndex = CLAMP_BELOW(cursorIndex, OPTION_FILES_END);
                    }
                } else if (pressedInput & (U_JPAD | D_JPAD)) {
                    if (pressedInput & U_JPAD) {
                        cursorIndex = OPTION_COPY;
                        if ((temp_v1 - 1) < (OPTION_FILES_END - 1)) {
                            func_801076D0_filesel(4, 0x2A01);
                        } else {
                            func_801076D0_filesel(4, 0x2A03);
                        }
                        func_80110FB0_filesel(selectedOption);
                    } else {
                        if (D_801142DC_filesel[cursorIndex].unk_00 == unkValue) {
                            cursorIndex = selectedOption + OPTION_FILES_NAME_BEGIN;
                            func_80110FB0_filesel(selectedOption);
                        }
                    }
                }
                break;
            case OPTION_COPY:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    if (temp_v1 == 0) {
                        func_801076D0_filesel(4, 0x2A13);
                    } else {
                        func_801076D0_filesel(4, 0x2A07);
                    }
                    cursorIndex = OPTION_ERASE;
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = OPTION_FILE1;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_ERASE:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    cursorIndex = OPTION_FILES_END;
                    if ((temp_v1 - 1) < 2) {
                        func_801076D0_filesel(4, 0x2A01);
                    } else {
                        func_801076D0_filesel(4, 0x2A03);
                    }
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = 2;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_FILE0_NAME:
            case OPTION_FILE1_NAME:
            case OPTION_FILE2_NAME:
                func_801076D0_filesel(4, 0x2A11);
                if (pressedInput & L_JPAD) {
                    cursorIndex = selectedOption;
                    do {
                        cursorIndex -= 1;
                        if (cursorIndex < OPTION_FILES_NAME_BEGIN) {
                            cursorIndex = 7;
                        }
                    } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                } else {
                    if (pressedInput & R_JPAD) {
                        cursorIndex = selectedOption;
                        do {
                            // if cursor goes over max, wrap around back to file 0 name
                            if (++cursorIndex > OPTION_MAX) {
                                cursorIndex = OPTION_FILE0_NAME;
                            }
                        } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                    }
                }
                if (pressedInput & U_JPAD) {
                    cursorIndex = selectedOption - OPTION_FILES_NAME_BEGIN;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
        }

    checkIfCursorIndexChanged:
        if (selectedOption != cursorIndex) {
            // animate cursor to new position
            func_8010AB60_filesel(18, cursorIndex);
            selectedOption = cursorIndex;

            if (selectedOption < OPTION_FILES_END) {
                func_801110F0_filesel(selectedOption);
            }
        }
        func_8010AB1C_filesel(18, selectedOption);

        animTimerAdjusted = (animTimer < 0) ? animTimer + 7 : animTimer;
        animTimerAdjusted = (animTimerAdjusted >> 3);
        func_8010AB58_filesel(18, -animTimerAdjusted);

        animTimer = (animTimer < 20) ? animTimer + 1 : 0;

        HuPrcVSleep();
    }
    return selectedOption;
}

s32 func_80109904_filesel(s32 arg0) {
    u8 buf[32]; // TODO: figure out correct type of this
    s32 temp_s0;

    bzero(&buf, sizeof(buf));
    func_80112494_filesel(arg0, buf);
    HuPrcSleep(3);
    func_801076D0_filesel(4, 0x2A11);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

s32 func_80109968_filesel(s32 arg0) {
    s32 temp_s0;

    HuPrcSleep(3);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

u32 func_801099A8_filesel(u32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 enabled[3];
    s32 cur;
    s32 timer;
    u16 btn;
    s32 temp;

    cur = arg0;
    timer = 0;
    enabled[0] = arg1;
    enabled[1] = arg2;
    enabled[2] = arg3;
    func_8010AB60_filesel(0x12, cur);
    while (1) {
        HuPrcVSleep();
        func_8010AB1C_filesel(0x12, cur);
        func_8010AB58_filesel(0x12, -(timer / 8));
        timer = (timer < 20) ? timer + 1 : 0;
        btn = D_800D1244_main;
        temp = func_80111B14_filesel(0);
        if (temp != -1) {
            btn |= temp;
        }
        if (D_800D5558_main[0] & B_BUTTON) {
            return -1;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            HuAudFXPlay(3);
            if (enabled[cur] == 1) {
                break;
            }
        } else if (btn & L_JPAD) {
            do {
                cur--;
                if (cur < 0) {
                    cur = 2;
                }
            } while (enabled[cur] != 1);
            func_8010AB60_filesel(0x12, cur);
        } else if (btn & R_JPAD) {
            do {
                cur++;
                cur = CLAMP_BELOW(cur, 3);
            } while (enabled[cur] != 1);
            func_8010AB60_filesel(0x12, cur);
        }
    }
    return cur;
}

// register allocation only (masked 0, raw 23: the search counter and the fade alpha swap s1/s2)
#ifdef NON_MATCHING
void func_80109B2C_filesel(void) {
    Vec srcPos;
    Vec dstPos;
    u8 name[32];
    s32 err;
    s32 alpha;
    s32 src;
    s32 dst;
    s32 i;
    s16 model;
    s32 cnt;

    err = 0;
    cnt = func_80108834_filesel();
    if (cnt <= 0) {
        func_801076D0_filesel(4, 0x2A03);
        err = 1;
    } else if (cnt >= 3) {
        func_801076D0_filesel(4, 0x2A04);
        err = 1;
    }
    if (err) {
        func_80108878_filesel();
    } else {
        func_80106168_filesel(2, 2, 0);
        func_8010F65C_filesel();
        func_8010F678_filesel(2);
        for (i = 0; i < 3; i++) {
            if (D_801142DC_filesel[i].unk_00 == FS_FILE_USED) {
                break;
            }
        }
        src = i;
        func_801076D0_filesel(4, 0x2A02);
        src = func_801099A8_filesel(src, D_801142DC_filesel[0].unk_00 == FS_FILE_USED,
                                    D_801142DC_filesel[1].unk_00 == FS_FILE_USED,
                                    D_801142DC_filesel[2].unk_00 == FS_FILE_USED);
        if (src < 0) {
            goto cancel;
        }
        switch (src) {
            case 0:
                func_8010779C_filesel(4, 0, (s32)D_80112AE0_filesel);
                break;
            case 1:
                func_8010779C_filesel(4, 0, (s32)D_80112AE4_filesel);
                break;
            case 2:
                func_8010779C_filesel(4, 0, (s32)D_80112AE8_filesel);
                break;
        }
        for (i = 0; i < 3; i++) {
            if (D_801142DC_filesel[i].unk_00 != FS_FILE_USED) {
                break;
            }
        }
        func_801076D0_filesel(4, 0x2A05);
        dst = func_801099A8_filesel(i, src != 0 && D_801142DC_filesel[0].unk_00 != FS_FILE_USED,
                                    src != 1 && D_801142DC_filesel[1].unk_00 != FS_FILE_USED,
                                    src != 2 && D_801142DC_filesel[2].unk_00 != FS_FILE_USED);
        if (dst < 0) {
            goto cancel;
        }
        func_80107670_filesel(4);
        func_80107608_filesel(4, 160.0f, 208.0f);
        func_801076D0_filesel(4, 0x2A16);
        HuPrcSleep(3);
        func_80050DDC_main(src, dst);
        SLCurBoxNoSet(dst);
        i = 0;
        func_80050800_main();
        func_80112184_filesel(dst);
        HuPrcSleep(3);
        func_8010F874_filesel(dst);
        HuPrcSleep(3);
        func_8010671C_filesel(src, 0);
        func_8010684C_filesel(src, 0);
        HuAudFXPlay(0x2F6);
        func_801068B0_filesel(src);
        func_801065B8_filesel(src, &srcPos.x, &srcPos.y, &srcPos.z);
        func_801065B8_filesel(dst, &dstPos.x, &dstPos.y, &dstPos.z);
        func_80106220_filesel(6, 0x1F002B, 0x6A9);
        func_801064DC_filesel(6, dstPos.x, dstPos.y, dstPos.z);
        func_80106550_filesel(6, 0.8f, 0.8f, 0.8f);
        func_801066DC_filesel(6);
        func_80106344_filesel(dst);
        func_8010669C_filesel(dst + 3);
        func_80106220_filesel(dst, 0x1F002A, 0x6A9);
        func_801064DC_filesel(dst, srcPos.x, srcPos.y, srcPos.z);
        func_80106550_filesel(dst, 0.8f, 0.8f, 0.8f);
        func_8010684C_filesel(dst, 0);
        func_8010671C_filesel(dst, 1);
        func_8010669C_filesel(dst);
        model = func_8010642C_filesel(6);
        func_8001FA68_main(model);
        alpha = 255;
        do {
            func_8001F9E4_main(model, alpha);
            alpha -= 16;
            HuPrcVSleep();
            i++;
        } while (i < 16);
        func_8010669C_filesel(6);
        func_80106344_filesel(6);
        func_801066DC_filesel(dst);
        func_801066DC_filesel(dst + 3);
        func_80111660_filesel(src, dst, 16);
        HuPrcSleep(16);
        func_8010671C_filesel(src, 4);
        HuAudFXPlay(0x2F7);
        func_801068B0_filesel(src);
        HuPrcSleep(3);
        func_80112508_filesel(dst, (s32)name);
        func_80105EC0_filesel(dst + 13);
        func_8010F760_filesel(dst, 1);
        func_801076D0_filesel(dst + 1, (u32)name);
        func_8010F844_filesel(dst);
        func_80108878_filesel();
        func_801076D0_filesel(4, 0x2A06);
    }
    func_8010F65C_filesel();
    func_8010F678_filesel(0);
    return;
cancel:
    func_8010AB60_filesel(0x12, 3);
    func_80108878_filesel();
    func_8010F65C_filesel();
    func_8010F678_filesel(0);
    if ((u32)(func_80108834_filesel() - 1) < 3) {
        func_801076D0_filesel(4, 0x2A01);
    } else {
        func_801076D0_filesel(4, 0x2A03);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80109B2C_filesel);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE8_filesel);

void func_8010A028_filesel(void) {
    s32 timer;
    s32 i;
    s32 cur;
    s32 next;
    u16 btn;
    s32 temp;
    s16 model;
    s16 *win;

    timer = 0;
    func_80106168_filesel(3, 2, 0);
    func_8010F65C_filesel();
    func_8010F678_filesel(3);
    for (i = 0; i < 3; i++) {
        cur = i;
        if (D_801142DC_filesel[cur].unk_00 == FS_FILE_USED) {
            break;
        }
    }
    if (i == 3) {
        func_80108878_filesel();
        func_8010F65C_filesel();
        func_8010F678_filesel(0);
        func_801076D0_filesel(4, 0x2A13);
        return;
    }
    func_801076D0_filesel(4, 0x2A08);
    next = cur;
    func_8010AB60_filesel(0x12, cur);
    while (1) {
        HuPrcVSleep();
        func_8010AB1C_filesel(0x12, cur);
        func_8010AB58_filesel(0x12, -(timer / 8));
        timer = (timer < 20) ? timer + 1 : 0;
        btn = D_800D1244_main;
        temp = func_80111B14_filesel(0);
        if (temp != -1) {
            btn |= temp;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            if (D_801142DC_filesel[cur].unk_00 == FS_FILE_USED) {
                HuAudFXPlay(3);
                func_80105F54_filesel(0x12);
                HuPrcSleep(3);
                if (cur == 0) {
                    func_8010779C_filesel(4, 0, (s32)D_80112AE0_filesel);
                } else if (cur == 1) {
                    func_8010779C_filesel(4, 0, (s32)D_80112AE4_filesel);
                } else if (cur == 2) {
                    func_8010779C_filesel(4, 0, (s32)D_80112AE8_filesel);
                }
                func_8010779C_filesel(4, 1, (s32)"0");
                func_8010779C_filesel(4, 2, (s32)"0");
                func_8010779C_filesel(4, 3, (s32)"0");
                win = &D_80114188_filesel;
                func_8005B63C_main(*win, 0x11, 0);
                func_8005FE54_main(*win, 1);
                func_801076D0_filesel(4, 0x2A09);
                while (func_8005E0C0_main(D_80114188_filesel) != 0) {
                    HuPrcVSleep();
                }
                if (func_801077D8_filesel(4, 1, 0) == 0) {
                    func_801076D0_filesel(4, 0x2A0A);
                    while (func_8005E0C0_main(D_80114188_filesel) != 0) {
                        HuPrcVSleep();
                    }
                    if (func_801077D8_filesel(4, 1, 0) == 0) {
                        func_801076D0_filesel(4, 0x2A17);
                        HuPrcSleep(3);
                        SLCurBoxNoSet(cur);
                        D_801142DC_filesel[cur].unk_00 = 0;
                        GwCommon.unk_00 = 0;
                        func_80050064_main(1);
                        func_80105F54_filesel(0x12);
                        model = func_8010642C_filesel(cur);
                        func_801076A0_filesel(4);
                        func_8010F874_filesel(cur);
                        func_8010669C_filesel(cur + 3);
                        func_80106220_filesel(cur, 0x1F0029, 0x6A9);
                        switch (cur) {
                            case 0:
                                func_801064DC_filesel(0, -400.0f, 0.0f, 0.0f);
                                break;
                            case 1:
                                func_801064DC_filesel(1, 0.0f, 0.0f, 0.0f);
                                break;
                            case 2:
                                func_801064DC_filesel(2, 400.0f, 0.0f, 0.0f);
                                break;
                        }
                        func_80106550_filesel(cur, 0.6f, 0.6f, 0.6f);
                        func_80106550_filesel(cur + 3, 0.6f, 0.6f, 0.6f);
                        func_8010684C_filesel(cur, 0);
                        func_8010671C_filesel(cur, 1);
                        func_801066DC_filesel(cur);
                        func_801066DC_filesel(cur + 3);
                        RepeatVibrator(0, 30, 0, 30);
                        func_8011132C_filesel(cur);
                        HuAudFXPlay(0x2F8);
                        func_8010A7D8_filesel(model);
                        func_80105EC0_filesel(cur + 13);
                        func_8010F760_filesel(cur, 0);
                        func_80112494_filesel(cur, (u8 *)D_80112AF0_filesel);
                        func_801076D0_filesel(cur + 1, (u32)D_80112AF0_filesel);
                        HuPrcSleep(3);
                        func_801066DC_filesel(cur);
                        func_801066DC_filesel(cur + 3);
                        func_80106550_filesel(cur, 0.8f, 0.8f, 0.8f);
                        func_80106550_filesel(cur + 3, 0.8f, 0.8f, 0.8f);
                        HuPrcSleep(16);
                        func_8010F844_filesel(cur);
                        func_8005B63C_main(D_80114188_filesel, -1, 0x11);
                        func_801076D0_filesel(4, 0x2A0B);
                        func_80107670_filesel(4);
                        func_80105F24_filesel(0x12);
                        break;
                    }
                }
                func_8005B63C_main(D_80114188_filesel, -1, 0x11);
                func_801076D0_filesel(4, 0x2A08);
                break;
            }
        } else if (D_800D5558_main[0] & B_BUTTON) {
            if (func_80108834_filesel() == 0) {
                func_801076D0_filesel(4, 0x2A04);
            } else {
                func_801076D0_filesel(4, 0x2A07);
            }
            break;
        }
        switch (cur) {
            case 0:
            case 1:
            case 2:
                    if (btn & L_JPAD) {
                        next = cur;
                        do {
                            next--;
                            if (next < 0) {
                                next = 2;
                            }
                        } while (D_801142DC_filesel[next].unk_00 != FS_FILE_USED);
                    } else if (btn & R_JPAD) {
                        next = cur;
                        do {
                            next++;
                            next = CLAMP_BELOW(next, 3);
                        } while (D_801142DC_filesel[next].unk_00 != FS_FILE_USED);
                    }
                break;
        }
        if (cur != next) {
            func_8010AB60_filesel(0x12, next);
            cur = next;
        }
    }
    func_80105F24_filesel(0x12);
    func_8010AB60_filesel(0x12, 4);
    func_80108878_filesel();
    func_8010F65C_filesel();
    func_8010F678_filesel(0);
}

void func_8010A680_filesel(s32 no, f32 x, f32 y, f32 z) {
    s32 no2;
    s32 i;

    i = no;
    no2 = no + 3;
    if (D_801142DC_filesel[no].unk_00 != FS_FILE_USED) {
        func_80106220_filesel(i, 0x1F0029, 0x6A9);
    } else {
        func_80106220_filesel(i, 0x1F002A, 0x6A9);
    }
    func_801064DC_filesel(i, x, y, z);
    func_80106550_filesel(i, 0.8f, 0.8f, 0.8f);
    func_8010684C_filesel(i, 0);
    func_8010671C_filesel(i, 1);
    func_8010669C_filesel(i);
    func_80106220_filesel(no2, D_801127B0_filesel[no], 0x6A9);
    func_801064DC_filesel(no2, x, y, z);
    func_80106550_filesel(no2, 0.8f, 0.8f, 0.8f);
    func_8010684C_filesel(no2, 0);
    func_8010671C_filesel(no2, 1);
    func_8010669C_filesel(no2);
}

void func_8010A7D8_filesel(s16 arg0) {
    f32 t;
    f32 angle;
    f32 scale;

    func_8001C2FC_main(arg0, 0x22000, 0x20000);
    func_8001C448_main(arg0);
    func_8001C954_main(arg0);
    HuPrcVSleep();
    t = 0.0f;
    angle = 0.0f;
    scale = 1.0f;
    while (1) {
        if (t > 1.0f) {
            break;
        }
        D_800A0A7C_main = angle;
        func_8001D558_main(arg0, t, scale, 2);
        angle += 46.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        t += 0.1f;
        scale += (10.0f - scale) / 67.0f * 4.0f;
        HuPrcVSleep();
    }
    func_8001C258_main(arg0, 4, 4);
    func_8001ACDC_main(arg0);
    HuPrcSleep(3);
}

void func_8010A978_filesel(s32 arg0) {
    if (arg0 >= 6) {
        arg0 = 5;
    }
    func_80105FBC_filesel(0x13, arg0 * 10 + 0x68, 0x3D);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AF0_filesel);

void func_8010A9B4_filesel(s32 arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    Vec pos;
    Vec2f scr;
    s32 x;
    s32 y;

    x = D_801127BC_filesel[arg1][0];
    y = D_801127BC_filesel[arg1][1];
    switch (arg1) {
        case 0:
        case 1:
        case 2:
            func_801065B8_filesel(arg1, &pos.x, &pos.y, &pos.z);
            pos.x += 30.0f;
            pos.y += 300.0f;
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x;
            y = scr.y;
            break;
        case 3:
        case 4:
            x = D_801127BC_filesel[arg1][0];
            y = D_801127BC_filesel[arg1][1];
            break;
        case 5:
            HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x + 31.0f;
            y = 0xA8;
            break;
        case 6:
            HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x + 31.0f;
            y = 0xA8;
            break;
        case 7:
            HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x + 31.0f;
            y = 0xA8;
            break;
    }
    *arg2 = x;
    *arg3 = y;
}

void func_8010AB1C_filesel(s32 arg0, u32 arg1) {
    s32 x;
    s32 y;

    func_8010A9B4_filesel(arg0, arg1, &x, &y);
    func_80105FBC_filesel(arg0, x, y);
}

void func_8010AB58_filesel(s32 arg0, u32 arg1) {
}

void func_8010AB60_filesel(s32 arg0, u32 arg1) {
    s32 tx;
    s32 ty;
    s32 sx;
    s32 sy;
    s32 i;
    f32 t;

    func_8010A9B4_filesel(arg0, arg1, &tx, &ty);
    func_80106014_filesel(arg0, &sx, &sy);
    i = 0;
    do {
        t = i * 0.25f;
        func_80105FBC_filesel(arg0, sx + t * (tx - sx), sy + t * (ty - sy));
        i++;
        HuPrcVSleep();
    } while (i < 5);
    func_80105FBC_filesel(arg0, tx, ty);
}

s32 func_8010AC58_filesel(s32 arg0) {
    Vec2f base;
    u8 name[32];
    s16 win;
    s32 ret;

    base.x = 39.0f;
    base.y = 95.0f;
    func_80105E48_filesel(4, 0x1F0015);
    func_80106134_filesel(4, 5);
    func_80105FBC_filesel(4, 0xA0, 0x98);
    func_80105F24_filesel(4);
    func_80105E48_filesel(5, 0x1F0016);
    func_80106134_filesel(5, 5);
    func_80105FBC_filesel(5, 0xA0, 0x98);
    func_80105F54_filesel(5);
    func_80105E48_filesel(6, 0x1F0017);
    func_80106134_filesel(6, 5);
    func_80105FBC_filesel(6, 0xA0, 0x98);
    func_80105F54_filesel(6);
    func_80105E48_filesel(7, 0x1F0010);
    func_80106134_filesel(7, 4);
    func_80105FBC_filesel(7, base.x + 14.0f + 16.0f, base.y + 89.0f + 7.0f);
    func_80105F54_filesel(7);
    func_80105E48_filesel(8, 0x1F0011);
    func_80106134_filesel(8, 4);
    func_80105FBC_filesel(8, base.x + 56.0f + 16.0f, base.y + 89.0f + 7.0f);
    func_80105F54_filesel(8);
    func_80105E48_filesel(9, 0x1F0012);
    func_80106134_filesel(9, 4);
    func_80105FBC_filesel(9, base.x + 98.0f + 25.0f, base.y + 89.0f + 7.0f);
    func_80105F54_filesel(9);
    func_80105E48_filesel(10, 0x1F0013);
    func_80106134_filesel(10, 4);
    func_80105FBC_filesel(10, base.x + 168.0f + 7.0f, base.y + 89.0f + 7.0f);
    func_80105F54_filesel(10);
    func_80105E48_filesel(11, 0x1F0014);
    func_80106134_filesel(11, 4);
    func_80105FBC_filesel(11, base.x + 202.0f + 13.0f, base.y + 89.0f + 7.0f);
    func_80105F54_filesel(11);
    func_80105E48_filesel(0x11, 0x1F001A);
    func_80106134_filesel(0x11, 5);
    func_80105FBC_filesel(0x11, 0xA0, 0x71);
    func_80105F54_filesel(0x11);
    func_80105E48_filesel(0x13, 0x1F001B);
    func_80106134_filesel(0x13, 0);
    func_80106044_filesel(0x13, 1.0f, 1.0f);
    func_80105FBC_filesel(0x13, 0xA0, 0x71);
    func_80105F54_filesel(0x13);
    func_80105E48_filesel(0x30, 0x1F0023);
    func_80106134_filesel(0x30, 4);
    func_80105FBC_filesel(0x30, base.x + 14.0f + 20.0f - 4.0f, base.y + 89.0f + 10.0f - 3.0f);
    func_80105F54_filesel(0x30);
    func_80105E48_filesel(0x31, 0x1F0023);
    func_80106134_filesel(0x31, 4);
    func_80105FBC_filesel(0x31, base.x + 56.0f + 20.0f - 4.0f, base.y + 89.0f + 10.0f - 3.0f);
    func_80105F54_filesel(0x31);
    func_80105E48_filesel(0x32, 0x1F0024);
    func_80106134_filesel(0x32, 4);
    func_80105FBC_filesel(0x32, base.x + 98.0f + 28.0f - 3.0f, base.y + 89.0f + 10.0f - 3.0f);
    func_80105F54_filesel(0x32);
    func_80105E48_filesel(0x33, 0x1F0025);
    func_80106134_filesel(0x33, 4);
    func_80105FBC_filesel(0x33, base.x + 168.0f + 10.0f - 3.0f, base.y + 89.0f + 10.0f - 3.0f);
    func_80105F54_filesel(0x33);
    func_80105E48_filesel(0x34, 0x1F0026);
    func_80106134_filesel(0x34, 4);
    func_80105FBC_filesel(0x34, base.x + 202.0f + 16.0f - 3.0f, base.y + 89.0f + 10.0f - 3.0f);
    func_80105F54_filesel(0x34);
    D_80114470_filesel = 0;
    bzero(name, sizeof(name));
    func_80112508_filesel(arg0, (s32)name);
    func_80106B40_filesel(10, (u32)name, 0x68, 0x2E, 0x3E, 0x14, 2);
    win = func_80107810_filesel(10);
    func_8005B63C_main(win, 0x80000, 0x80000);
    func_8005FBF8_main(win, 0x80, 0x80, 0x80);
    func_8005C02C_main(win, 7);
    func_80105E48_filesel(0x10, 0x1F0020);
    func_80106044_filesel(0x10, 1.0f, 1.0f);
    func_80106094_filesel(0x10, 0x100);
    func_80105FBC_filesel(0x10, 0x87, 0x38);
    func_801076D0_filesel(10, (u32)name);
    func_801075D8_filesel(10, 1.0f, 1.0f);
    func_8010B554_filesel(name);
    ret = func_8010C9B4_filesel(arg0);
    if (ret != 0) {
        func_8010B598_filesel(name);
        if (name[0] == 0 && name[1] == 0) {
            ret = 0;
        } else {
            func_80112494_filesel(arg0, name);
            func_801076D0_filesel(arg0 + 1, (u32)name);
        }
    }
    func_80105FA0_filesel(0x13);
    func_801076A0_filesel(10);
    func_80105FA0_filesel(4);
    func_80105FA0_filesel(5);
    func_80105FA0_filesel(6);
    func_80105FA0_filesel(7);
    func_80105FA0_filesel(0x30);
    func_80105FA0_filesel(8);
    func_80105FA0_filesel(9);
    func_80105FA0_filesel(10);
    func_80105FA0_filesel(11);
    func_80105FA0_filesel(0x11);
    func_80105FA0_filesel(0x13);
    func_80105FA0_filesel(0x30);
    func_80105FA0_filesel(0x31);
    func_80105FA0_filesel(0x32);
    func_80105FA0_filesel(0x33);
    func_80105FA0_filesel(0x34);
    func_80107490_filesel(10);
    func_80105EC0_filesel(0x10);
    HuPrcSleep(3);
    func_80105EC0_filesel(4);
    func_80105EC0_filesel(5);
    func_80105EC0_filesel(6);
    func_80105EC0_filesel(7);
    func_80105EC0_filesel(8);
    func_80105EC0_filesel(9);
    func_80105EC0_filesel(10);
    func_80105EC0_filesel(11);
    func_80105EC0_filesel(0x11);
    func_80105EC0_filesel(0x13);
    func_80105EC0_filesel(0x30);
    func_80105EC0_filesel(0x31);
    func_80105EC0_filesel(0x32);
    func_80105EC0_filesel(0x33);
    func_80105EC0_filesel(0x34);
    return ret;
}

s32 func_8010B4D0_filesel(s32 arg0, s32 arg1) {
    u8 *p = D_801127FC_filesel[arg0];
    s32 hi = p[arg1 * 2] << 8;

    return p[arg1 * 2 + 1] | hi;
}

s32 func_8010B4FC_filesel(s32 arg0, s32 arg1) {
    u8 *p = D_80112844_filesel[arg0];
    s32 hi = p[arg1 * 2] << 8;

    return p[arg1 * 2 + 1] | hi;
}

s32 func_8010B528_filesel(s32 arg0, s32 arg1) {
    u8 *p = D_8011288C_filesel[arg1];
    s32 hi = p[arg0 * 2] << 8;

    return p[arg0 * 2 + 1] | hi;
}

void func_8010B554_filesel(void *arg0) {
    bzero(D_80114478_filesel.name, sizeof(D_80114478_filesel.name));
    bcopy(arg0, D_80114478_filesel.name, sizeof(D_80114478_filesel.name));
}

void func_8010B598_filesel(void *arg0) {
    bzero(arg0, sizeof(D_80114478_filesel.name));
    bcopy(D_80114478_filesel.name, arg0, sizeof(D_80114478_filesel.name));
}

s32 func_8010B5D4_filesel(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, s16 *arg4) {
    s32 x = 0x2F;
    s32 y = 0x67;

    switch (arg0) {
        case 4:
        case 5:
            x += 5;
            y += 12;
            if (arg1 >= 10) {
                x += 5;
            }
            if (arg1 >= 11) {
                if (arg1 < 15) {
                    x += (arg1 - 10) * 2;
                } else {
                    x += 10;
                }
            }
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        case 6:
            x += 0x2A;
            y += 12;
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        default:
            x = 0;
            y = 0;
            break;
    }
    *arg3 = x;
    *arg4 = y;
    return 0;
}

void func_8010B684_filesel(s32 arg0) {
    if (arg0 != -1) {
        func_80105F24_filesel(arg0);
    }
    if (arg0 != 4) {
        func_80105F54_filesel(4);
    }
    if (arg0 != 5) {
        func_80105F54_filesel(5);
    }
    if (arg0 != 6) {
        func_80105F54_filesel(6);
    }
}

void func_8010B6F4_filesel(s32 arg0) {
    if (arg0 != -1) {
        func_80105F24_filesel(arg0);
    }
    if (arg0 != 7) {
        func_80105F54_filesel(7);
        func_80105F54_filesel(0x30);
    } else {
        func_80105F24_filesel(0x30);
    }
    if (arg0 != 8) {
        func_80105F54_filesel(8);
        func_80105F54_filesel(0x31);
    } else {
        func_80105F24_filesel(0x31);
    }
    if (arg0 != 9) {
        func_80105F54_filesel(9);
        func_80105F54_filesel(0x32);
    } else {
        func_80105F24_filesel(0x32);
    }
    if (arg0 != 10) {
        func_80105F54_filesel(10);
        func_80105F54_filesel(0x33);
    } else {
        func_80105F24_filesel(0x33);
    }
    if (arg0 != 11) {
        func_80105F54_filesel(11);
        func_80105F54_filesel(0x34);
    } else {
        func_80105F24_filesel(0x34);
    }
    D_80114478_filesel.blink = 0;
}

void func_8010B80C_filesel(s32 arg0) {
    s32 cnt;
    s32 pos;
    s32 *p;
    f32 f;
    u8 alpha;

    cnt = D_80114478_filesel.blink;
    if (cnt < 0) {
        cnt = -cnt;
    }
    pos = D_80114478_filesel.blink >= 0;
    f = 1.0f;
    if (f > 1.0f) { /* dead clamp: retail does not fold f * 255 */
        f = 1.0f;
    }
    cnt++;
    if (pos) {
        alpha = f * 255.0f;
    } else {
        alpha = (1.0f - f) * 255.0f;
    }
    p = &D_80114478_filesel.blink;
    *p = cnt;
    if (pos < 0) {
        *p = -cnt;
    }
    if (arg0 != -1) {
        func_80106094_filesel(arg0, alpha);
    }
    if (arg0 != 7) {
        func_80106094_filesel(7, alpha);
    }
    if (arg0 != 8) {
        func_80106094_filesel(8, alpha);
    }
    if (arg0 != 9) {
        func_80106094_filesel(9, alpha);
    }
    if (arg0 != 10) {
        func_80106094_filesel(10, alpha);
    }
    if (arg0 != 11) {
        func_80106094_filesel(11, alpha);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B18_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B24_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B30_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B3C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B48_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B54_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B60_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B78_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B84_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B90_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BA8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BB4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BC0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BCC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BD8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BF0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BFC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C08_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C14_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C20_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C38_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C44_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C50_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C5C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C68_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C74_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C80_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C98_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CA4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CB0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CBC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CC8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D00_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D1C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D38_filesel);

s32 func_8010B998_filesel(s32 btn) {
    s32 len;

    if (btn & START_BUTTON) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
        return 0;
    }
    if (D_800D5558_main[0] & A_BUTTON) {
        switch (D_80114478_filesel.button) {
            case 7:
            case 8:
                HuAudFXPlay(1);
                D_80114478_filesel.group = 6;
                break;
            case 9:
                HuAudFXPlay(1);
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                break;
            case 10:
                D_80114478_filesel.name[D_80114478_filesel.len] = 0;
                if (D_80114478_filesel.len > 0) {
                    HuAudFXPlay(0x2EF);
                    D_80114478_filesel.len--;
                } else {
                    HuAudFXPlay(5);
                }
                D_80114478_filesel.name[D_80114478_filesel.len] = 0;
                func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
                func_8010A978_filesel(D_80114478_filesel.len + 1);
                break;
            case 11:
                HuAudFXPlay(2);
                if ((u16)((D_80114478_filesel.name[0] << 8) | D_80114478_filesel.name[1])) {
                    return 11;
                }
                bcopy(D_80114478_filesel.saved, D_80114478_filesel.name, sizeof(D_80114478_filesel.name));
                func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
                len = func_801125E8_filesel((s32)D_80114478_filesel.name);
                D_80114478_filesel.name[len] = 0;
                D_80114478_filesel.len = len;
                func_8010A978_filesel(len + 1);
                break;
        }
        func_8010B6F4_filesel(D_80114478_filesel.button);
        func_8010B684_filesel(D_80114478_filesel.group);
        return 0;
    }
    if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
        } else {
            if (D_80114478_filesel.button == 11) {
                return -1;
            }
            HuAudFXPlay(1);
            D_80114478_filesel.button = 11;
            func_8010BE14_filesel();
            func_8010B6F4_filesel(D_80114478_filesel.button);
        }
        func_8010B684_filesel(D_80114478_filesel.group);
        return 0;
    }
    if (btn & U_JPAD) {
        D_80114478_filesel.done = 0;
        func_8010B6F4_filesel(-1);
        D_80114478_filesel.line = 4;
        func_8010BDC4_filesel();
    } else if (btn & D_JPAD) {
        D_80114478_filesel.done = 0;
        func_8010B6F4_filesel(-1);
        D_80114478_filesel.line = 0;
        func_8010BDC4_filesel();
    } else if (btn & L_JPAD) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.button) {
            case 10:
                D_80114478_filesel.button = 11;
                break;
            case 11:
                D_80114478_filesel.button = 10;
                break;
        }
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & R_JPAD) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.button) {
            case 10:
                D_80114478_filesel.button = 11;
                break;
            case 11:
                D_80114478_filesel.button = 10;
                break;
        }
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & Z_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 5:
                D_80114478_filesel.group = 6;
                break;
            case 4:
                D_80114478_filesel.group = 6;
                break;
            case 6:
                D_80114478_filesel.group = 6;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & R_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 5:
                D_80114478_filesel.group = 6;
                break;
            case 4:
                D_80114478_filesel.group = 6;
                break;
            case 6:
                D_80114478_filesel.group = 6;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

void func_8010BDC4_filesel(void) {
    s16 x;
    s16 y;

    func_8010B5D4_filesel(D_80114478_filesel.group, D_80114478_filesel.col, D_80114478_filesel.line, &x, &y);
    func_80105FBC_filesel(0x11, x, y);
    func_80105F24_filesel(0x11);
}

void func_8010BE14_filesel(void) {
    func_80105F54_filesel(0x11);
}

s32 func_8010BE30_filesel(s32 btn) {
    if (btn & START_BUTTON) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        func_8010BDC4_filesel();
        if (btn & U_JPAD) {
            if (--D_80114478_filesel.line < 0) {
                D_80114478_filesel.line = 0;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 7;
                func_8010B6F4_filesel(7);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & D_JPAD) {
            if (++D_80114478_filesel.line >= 5) {
                D_80114478_filesel.line = 4;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 7;
                func_8010B6F4_filesel(7);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & L_JPAD) {
            if (--D_80114478_filesel.col < 0) {
                D_80114478_filesel.col = 17;
            }
            func_8010BDC4_filesel();
        } else if (btn & R_JPAD) {
            if (++D_80114478_filesel.col >= 18) {
                D_80114478_filesel.col = 0;
            }
            func_8010BDC4_filesel();
        }
    } else if (D_800D5558_main[0] & A_BUTTON) {
        if (D_80114478_filesel.len < 5) {
            HuAudFXPlay(0x2EE);
            D_80114478_filesel.name[D_80114478_filesel.len] =
                func_8010B4D0_filesel(D_80114478_filesel.col, D_80114478_filesel.line);
            D_80114478_filesel.len++;
            D_80114470_filesel = 1;
        }
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
        func_8010A978_filesel(D_80114478_filesel.len + 1);
        if (D_80114478_filesel.len >= 5) {
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
            D_80114470_filesel = 1;
        } else {
            HuAudFXPlay(1);
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (btn & Z_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 5:
                D_80114478_filesel.group = 4;
                break;
            case 6:
                D_80114478_filesel.group = 5;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & R_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 5;
                break;
            case 5:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 6:
                D_80114478_filesel.group = 4;
                break;
        }
        func_8010BDC4_filesel();
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

s32 func_8010C25C_filesel(s32 btn) {
    if (btn & START_BUTTON) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        func_8010BDC4_filesel();
        if (btn & U_JPAD) {
            if (--D_80114478_filesel.line < 0) {
                D_80114478_filesel.line = 0;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 8;
                func_8010B6F4_filesel(8);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & D_JPAD) {
            if (++D_80114478_filesel.line >= 5) {
                D_80114478_filesel.line = 4;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 8;
                func_8010B6F4_filesel(8);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & L_JPAD) {
            if (--D_80114478_filesel.col < 0) {
                D_80114478_filesel.col = 17;
            }
            func_8010BDC4_filesel();
        } else if (btn & R_JPAD) {
            if (++D_80114478_filesel.col >= 18) {
                D_80114478_filesel.col = 0;
            }
            func_8010BDC4_filesel();
        }
    } else if (D_800D5558_main[0] & A_BUTTON) {
        if (D_80114478_filesel.len < 5) {
            HuAudFXPlay(0x2EE);
            D_80114478_filesel.name[D_80114478_filesel.len] =
                func_8010B4FC_filesel(D_80114478_filesel.col, D_80114478_filesel.line);
            D_80114478_filesel.len++;
            D_80114470_filesel = 1;
        }
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
        func_8010A978_filesel(D_80114478_filesel.len + 1);
        if (D_80114478_filesel.len >= 5) {
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
            D_80114470_filesel = 1;
        } else {
            HuAudFXPlay(1);
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (btn & Z_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 5:
                D_80114478_filesel.group = 4;
                break;
            case 6:
                D_80114478_filesel.group = 5;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & R_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 5;
                break;
            case 5:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 6:
                D_80114478_filesel.group = 4;
                break;
        }
        func_8010BDC4_filesel();
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

s32 func_8010C688_filesel(s32 btn) {
    if (btn & 0x1000) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & 0xF00) {
        func_8010BDC4_filesel();
        if (btn & 0x800) {
            if (--D_80114478_filesel.line < 0) {
                D_80114478_filesel.line = 0;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 10;
                func_8010B6F4_filesel(10);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & 0x400) {
            if (++D_80114478_filesel.line >= 5) {
                D_80114478_filesel.line = 4;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 10;
                func_8010B6F4_filesel(10);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & 0x200) {
            if (--D_80114478_filesel.col < 0) {
                D_80114478_filesel.col = 12;
            }
            func_8010BDC4_filesel();
        } else if (btn & 0x100) {
            if (++D_80114478_filesel.col >= 13) {
                D_80114478_filesel.col = 0;
            }
            func_8010BDC4_filesel();
        }
    } else if (D_800D5558_main[0] & A_BUTTON) {
        if (D_80114478_filesel.len < 5) {
            HuAudFXPlay(0x2EE);
            D_80114478_filesel.name[D_80114478_filesel.len] = func_8010B528_filesel(D_80114478_filesel.col, D_80114478_filesel.line);
            D_80114478_filesel.len++;
            D_80114470_filesel = 1;
        }
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
        func_8010A978_filesel(D_80114478_filesel.len + 1);
        if (D_80114478_filesel.len >= 5) {
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
            D_80114470_filesel = 1;
        } else {
            HuAudFXPlay(1);
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (btn & 0x2000) {
        func_8010BDC4_filesel();
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & 0x10) {
        func_8010BDC4_filesel();
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D7C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DAC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DBC_filesel);

// struct base register choice (the stores and the loop index from D_80114490/D_8011447C in retail) and s-register order (masked 22)
#ifdef NON_MATCHING
s32 func_8010C9B4_filesel(u32 arg0) {
    s32 btn;
    s32 prev;
    s32 len;

    len = func_801125E8_filesel((s32)D_80114478_filesel.name);
    D_80114478_filesel.group = 6;
    D_80114478_filesel.done = 1;
    D_80114478_filesel.button = 11;
    D_80114478_filesel.col = 0;
    D_80114478_filesel.line = 0;
    D_80114478_filesel.blink = 0;
    D_80114478_filesel.len = len;
    switch (rand16() % 6) {
        case 1:
            bcopy(D_80112D7C_filesel, D_80114478_filesel.saved, 0x12);
            break;
        case 2:
            bcopy(D_80112D8C_filesel, D_80114478_filesel.saved, 0x12);
            break;
        case 3:
            bcopy(D_80112D9C_filesel, D_80114478_filesel.saved, 0x12);
            break;
        case 4:
            bcopy(D_80112DAC_filesel, D_80114478_filesel.saved, 0x12);
            break;
        case 5:
            bcopy(D_80112DBC_filesel, D_80114478_filesel.saved, 0x12);
            break;
        case 0:
        default:
            bcopy(D_80112D6C_filesel, D_80114478_filesel.saved, 0x12);
            break;
    }
    func_8010B684_filesel(D_80114478_filesel.group);
    func_8010B6F4_filesel(D_80114478_filesel.button);
    HuPrcVSleep();
    func_80105F24_filesel(0x13);
    func_80106134_filesel(0x13, 0);
    func_8010A978_filesel(D_80114478_filesel.len + 1);
    while (1) {
        prev = D_80114478_filesel.button;
        btn = D_800D1244_main;
        btn |= func_80111A08_filesel(0);
        if (D_80114478_filesel.done != 0) {
            btn = func_8010B998_filesel(btn);
            func_8010B80C_filesel(prev);
        } else {
            btn = func_8010C688_filesel(btn);
        }
        if (btn == 11) {
            if (((D_80114478_filesel.name[0] << 8) | D_80114478_filesel.name[1]) & 0xFFFF) {
            } else {
                switch (arg0) {
                    case 0:
                        bcopy(D_80112D6C_filesel, D_80114478_filesel.name, 0x12);
                        break;
                    case 1:
                        bcopy(D_80112D7C_filesel, D_80114478_filesel.name, 0x12);
                        break;
                    case 2:
                        bcopy(D_80112D8C_filesel, D_80114478_filesel.name, 0x12);
                        break;
                    case 3:
                        bcopy(D_80112D9C_filesel, D_80114478_filesel.saved, 0x12);
                        break;
                    case 4:
                        bcopy(D_80112DAC_filesel, D_80114478_filesel.saved, 0x12);
                        break;
                    case 5:
                        bcopy(D_80112DBC_filesel, D_80114478_filesel.saved, 0x12);
                        break;
                    default:
                        bcopy(D_80112D6C_filesel, D_80114478_filesel.saved, 0x12);
                        break;
                }
                D_80114470_filesel = 1;
            }
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            HuPrcSleep(3);
            D_80114470_filesel = 1;
            return 1;
        }
        if (btn == -1) {
            return -1;
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C9B4_filesel);
#endif

s32 func_8010CCA8_filesel(s32 no) {
    s32 timer = 0;
    f32 pos[4] = { 80.0f, 48.0f, 240.0f, 48.0f };
    s32 x;
    s32 y;
    s32 tx;
    s32 ty;
    f32 t;
    s32 i;
    s32 r;
    s32 sel;
    u32 btn;
    s32 ret;

    sel = 1;
    func_80105FBC_filesel(0x12, pos[2], pos[3]);
    func_80105F24_filesel(0x12);
    func_801076D0_filesel(4, 0x2A0E);
    while (1) {
        HuPrcVSleep();
        btn = D_800D1244_main;
        r = func_80111B14_filesel(0);
        if (r != -1) {
            btn |= r;
        }
        if (D_800D5558_main[0] & B_BUTTON) {
            ret = -1;
            break;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            func_80105FA0_filesel(0x12);
            if (sel == 0) {
                HuAudFXPlay(3);
                if (_CheckFlag(0x18) != 0) {
                    func_801076D0_filesel(4, 0x2A0F);
                    func_8010782C_filesel(4);
                    r = func_801077D8_filesel(4, 0, 0);
                    if (r == 0) {
                        ret = 1;
                        break;
                    }
                    if (r == 1) {
                        func_801076D0_filesel(4, 0x2A10);
                        func_8010782C_filesel(4);
                        if (func_801077D8_filesel(4, 0, 0) == 0) {
                            func_801076D0_filesel(4, (u32)D_80112A64_filesel);
                            HuPrcVSleep();
                            func_8005B63C_main(D_80114158_filesel[4].unk_00, 0x11, 0);
                            func_801076D0_filesel(4, 0x2A18);
                            func_8010782C_filesel(4);
                            func_801076D0_filesel(4, 0x2A19);
                            func_8010782C_filesel(4);
                            ret = func_801077D8_filesel(4, 1, 0) ? -1 : 2;
                            func_8005B63C_main(D_80114158_filesel[4].unk_00, -1, 0x11);
                            break;
                        }
                    }
                } else {
                    ret = 2;
                    break;
                }
                func_801076D0_filesel(4, 0x2A0D);
                func_80105F84_filesel(0x12);
            } else {
                HuAudFXPlay(3);
                ret = 0;
                break;
            }
        } else if (btn & 0x300) {
            sel = ((btn >> 9) ^ 1) & 1;
            if (sel == 0) {
                func_80106014_filesel(0x12, &x, &y);
                tx = pos[0];
                ty = pos[1];
                for (i = 0; i < 5; i++) {
                    t = i * 0.25f;
                    func_80105FBC_filesel(0x12, x + t * (tx - x), y + t * (ty - y));
                    HuPrcVSleep();
                }
                func_80105FBC_filesel(0x12, pos[0], pos[1]);
                func_801076D0_filesel(4, 0x2A0D);
            } else {
                func_80106014_filesel(0x12, &x, &y);
                tx = pos[2];
                ty = pos[3];
                for (i = 0; i < 5; i++) {
                    t = i * 0.25f;
                    func_80105FBC_filesel(0x12, x + t * (tx - x), y + t * (ty - y));
                    HuPrcVSleep();
                }
                func_80105FBC_filesel(0x12, pos[2], pos[3]);
                func_801076D0_filesel(4, 0x2A0E);
            }
        }
        func_8010AB58_filesel(0x12, -(timer / 8));
        timer = (timer < 20) ? timer + 1 : 0;
    }
    func_80105F54_filesel(0x12);
    func_80108D74_filesel();
    func_8010DEEC_filesel();
    func_8010E1B4_filesel();
    return ret;
}

// register allocation in the digit splits (masked 0)
#ifdef NON_MATCHING
void func_8010D13C_filesel(s32 arg0) {
    u8 a;
    u8 b;
    s32 x;
    s32 y;
    s16 spr;

    func_801126C0_filesel(D_801142DC_filesel[arg0].unk_44, &a, &b);
    x = 0x50;
    y = 0x68;
    func_80105E48_filesel(0x14, 0x1F0001);
    func_80105FBC_filesel(0x14, x, y);
    func_80106134_filesel(0x14, 6);
    func_80105F54_filesel(0x14);
    func_80105E48_filesel(0x15, 0x1F0004);
    func_80106134_filesel(0x15, 5);
    func_80105FBC_filesel(0x15, x, y - 0x10);
    func_80106168_filesel(0x15, D_801142DC_filesel[arg0].unk_28, 0);
    func_80105F54_filesel(0x15);
    {
    u8 tbl[6] = { 0, 1, 2, 3, 4, 5 };
    func_80105E48_filesel(0x16, 0x1F0003);
    func_80105FBC_filesel(0x16, x, y + 3);
    func_80106134_filesel(0x16, 6);
    func_80106168_filesel(0x16, tbl[D_801142DC_filesel[arg0].unk_40], 0);
    func_80105F54_filesel(0x16);
    }
    func_80105E48_filesel(0x17, 0x1F000C);
    func_80106134_filesel(0x17, 5);
    func_80105FBC_filesel(0x17, x, y + 0x11);
    func_80106168_filesel(0x17, (b >> 1) & 1, 0);
    func_80105F54_filesel(0x17);
    spr = func_80105CC4_filesel(0x17);
    if (b & 2) {
        func_8000BEAC_main(spr, 0xFF, 0x40, 0x40);
    } else {
        func_8000BEAC_main(spr, 0, 0xFF, 0xFF);
    }
    if (b & 2) {
        func_80105E48_filesel(0x18, 0x1F000A);
    } else {
        func_80105E48_filesel(0x18, 0x1F000B);
    }
    func_80106134_filesel(0x18, 5);
    func_80105FBC_filesel(0x18, x, y + 0x1C);
    func_80106168_filesel(0x18, a, 0);
    func_80105F54_filesel(0x18);
    if (_CheckFlag(0x18) == 0) {
        func_80105E48_filesel(0x19, 0x1F0009);
        func_80106134_filesel(0x19, 5);
        func_80105FBC_filesel(0x19, x, y - 4);
    } else if (_CheckFlag(0x28) == 0) {
        func_80105E48_filesel(0x19, 0x1F0005);
        func_80106134_filesel(0x19, 5);
        func_80105FBC_filesel(0x19, x - 2, y + 0x1C);
        func_80105FBC_filesel(0x18, x, y + 0x2C);
    } else {
        func_80105E48_filesel(0x19, 0x1F0006);
        func_80106134_filesel(0x19, 5);
        func_80105FBC_filesel(0x19, x - 0x10, y + 0x2C);
    }
    y += 0x2C;
    func_80105F54_filesel(0x19);
    func_80105E48_filesel(0x1A, 0x1F0007);
    func_80106134_filesel(0x1A, 5);
    func_80105FBC_filesel(0x1A, x + 8, y);
    func_80106168_filesel(0x1A, 1, 0);
    func_80106168_filesel(0x1A, D_801142DC_filesel[arg0].unk_38 % 10, 0);
    func_80105F54_filesel(0x1A);
    func_80105D70_filesel(0x1B, 0x1A);
    func_80106134_filesel(0x1B, 5);
    func_80105FBC_filesel(0x1B, x, y);
    func_80106168_filesel(0x1B, D_801142DC_filesel[arg0].unk_38 / 10, 0);
    func_80105F54_filesel(0x1B);
    func_80105D70_filesel(0x1C, 0x1A);
    func_80106134_filesel(0x1C, 5);
    func_80105FBC_filesel(0x1C, x + 0x20, y);
    func_80106168_filesel(0x1C, D_801142DC_filesel[arg0].unk_3C % 10, 0);
    func_80105F54_filesel(0x1C);
    func_80105D70_filesel(0x1D, 0x1A);
    func_80106134_filesel(0x1D, 5);
    func_80105FBC_filesel(0x1D, x + 0x18, y);
    func_80106168_filesel(0x1D, D_801142DC_filesel[arg0].unk_3C / 10, 0);
    func_80105F54_filesel(0x1D);
    func_80105E48_filesel(0x1E, 0x1F0028);
    func_80105FBC_filesel(0x1E, x + 0x10, y);
    func_8000BEAC_main(func_80105CC4_filesel(0x1E), 0, 0xFF, 0);
    func_80106134_filesel(0x1E, 5);
    func_80105F54_filesel(0x1E);
}
#else

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010D13C_filesel);
#endif

// register allocation in the digit splits (masked 0), as func_8010D13C_filesel
#ifdef NON_MATCHING
void func_8010D660_filesel(s32 arg0) {
    s32 x;
    s32 y;
    s32 ty;

    x = 0xF0;
    y = 0x68;
    func_80105E48_filesel(0x1F, 0x1F0002);
    func_80105FBC_filesel(0x1F, x, y);
    func_80105F54_filesel(0x1F);
    func_80105E48_filesel(0x20, 0x1F000C);
    func_80106134_filesel(0x20, 5);
    func_80105FBC_filesel(0x20, x, y - 0x15);
    func_80106168_filesel(0x20, 0, 0);
    func_80105F54_filesel(0x20);
    func_8000BEAC_main(func_80105CC4_filesel(0x20), 0, 0xFF, 0xFF);
    func_80105D70_filesel(0x28, 0x20);
    func_80106134_filesel(0x28, 5);
    func_80105FBC_filesel(0x28, x, y + 0x16);
    func_80106168_filesel(0x28, 1, 0);
    func_80105F54_filesel(0x28);
    func_8000BEAC_main(func_80105CC4_filesel(0x28), 0xFF, 0x40, 0x40);
    func_80105E48_filesel(0x21, 0x1F000B);
    func_80106134_filesel(0x21, 5);
    func_80105FBC_filesel(0x21, x, y - 0xB);
    func_80106168_filesel(0x21, D_801142DC_filesel[arg0].unk_72, 0);
    func_80105F54_filesel(0x21);
    func_80105E48_filesel(0x29, 0x1F000A);
    func_80106134_filesel(0x29, 5);
    func_80105FBC_filesel(0x29, x, y + 0x20);
    func_80106168_filesel(0x29, D_801142DC_filesel[arg0].unk_56, 0);
    func_80105F54_filesel(0x29);
    if (_CheckFlag(0x16) == 0) {
        func_80105E48_filesel(0x22, 0x1F0009);
        func_80106134_filesel(0x22, 5);
        func_80105FBC_filesel(0x22, x, y - 1);
    } else {
        func_80105E48_filesel(0x22, 0x1F0006);
        func_80106134_filesel(0x22, 5);
        func_80105FBC_filesel(0x22, x - 0x14, y + 5);
    }
    ty = y + 5;
    func_80105F54_filesel(0x22);
    func_80105E48_filesel(0x23, 0x1F0007);
    func_80106134_filesel(0x23, 5);
    func_80105FBC_filesel(0x23, x + 8, ty);
    func_80106168_filesel(0x23, D_801142DC_filesel[arg0].unk_78 % 10, 0);
    func_80105F54_filesel(0x23);
    func_80105D70_filesel(0x24, 0x23);
    func_80106134_filesel(0x24, 5);
    func_80105FBC_filesel(0x24, x, ty);
    func_80106168_filesel(0x24, D_801142DC_filesel[arg0].unk_78 / 10, 0);
    func_80105F54_filesel(0x24);
    func_80105D70_filesel(0x25, 0x23);
    func_80106134_filesel(0x25, 5);
    func_80105FBC_filesel(0x25, x + 0x20, ty);
    func_80106168_filesel(0x25, D_801142DC_filesel[arg0].unk_7C % 10, 0);
    func_80105F54_filesel(0x25);
    func_80105D70_filesel(0x26, 0x23);
    func_80106134_filesel(0x26, 5);
    func_80105FBC_filesel(0x26, x + 0x18, ty);
    func_80106168_filesel(0x26, D_801142DC_filesel[arg0].unk_7C / 10, 0);
    func_80105F54_filesel(0x26);
    func_80105E48_filesel(0x27, 0x1F0028);
    func_80105FBC_filesel(0x27, x + 0x10, ty);
    func_8000BEAC_main(func_80105CC4_filesel(0x27), 0, 0xFF, 0);
    func_80106134_filesel(0x27, 5);
    func_80105F54_filesel(0x27);
    if (_CheckFlag(0x17) == 0) {
        func_80105E48_filesel(0x2A, 0x1F0009);
        func_80106134_filesel(0x2A, 5);
        func_80105FBC_filesel(0x2A, x, y + 0x2A);
    } else {
        func_80105E48_filesel(0x2A, 0x1F0006);
        func_80106134_filesel(0x2A, 5);
        func_80105FBC_filesel(0x2A, x - 0x10, y + 0x30);
    }
    ty = y + 0x30;
    func_80105F54_filesel(0x2A);
    func_80105E48_filesel(0x2B, 0x1F0007);
    func_80106134_filesel(0x2B, 5);
    func_80105FBC_filesel(0x2B, x + 8, ty);
    func_80106168_filesel(0x2B, D_801142DC_filesel[arg0].unk_5C % 10, 0);
    func_80105F54_filesel(0x2B);
    func_80105D70_filesel(0x2C, 0x2B);
    func_80106134_filesel(0x2C, 5);
    func_80105FBC_filesel(0x2C, x, ty);
    func_80106168_filesel(0x2C, D_801142DC_filesel[arg0].unk_5C / 10, 0);
    func_80105F54_filesel(0x2C);
    func_80105D70_filesel(0x2D, 0x2B);
    func_80106134_filesel(0x2D, 5);
    func_80105FBC_filesel(0x2D, x + 0x20, ty);
    func_80106168_filesel(0x2D, D_801142DC_filesel[arg0].unk_60 % 10, 0);
    func_80105F54_filesel(0x2D);
    func_80105D70_filesel(0x2E, 0x2B);
    func_80106134_filesel(0x2E, 5);
    func_80105FBC_filesel(0x2E, x + 0x18, ty);
    func_80106168_filesel(0x2E, D_801142DC_filesel[arg0].unk_60 / 10, 0);
    func_80105F54_filesel(0x2E);
    if (D_801142DC_filesel[arg0].unk_60 != 20) {
        func_80105E48_filesel(0x2F, 0x1F0027);
        func_80105FBC_filesel(0x2F, x, y + 0x2C);
    } else {
        func_80105E48_filesel(0x2F, 0x1F0028);
        func_80105FBC_filesel(0x2F, x + 0x10, y + 0x30);
    }
    func_8000BEAC_main(func_80105CC4_filesel(0x2F), 0, 0xFF, 0);
    func_80106134_filesel(0x2F, 5);
    func_80105F54_filesel(0x2F);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010D660_filesel);
#endif

void func_8010DD54_filesel(void) {
    func_80105EC0_filesel(0x14);
    func_80105EC0_filesel(0x15);
    func_80105EC0_filesel(0x16);
    func_80105EC0_filesel(0x17);
    func_80105EC0_filesel(0x18);
    func_80105EC0_filesel(0x19);
    func_80105EC0_filesel(0x1E);
    func_80105EC0_filesel(0x1D);
    func_80105EC0_filesel(0x1C);
    func_80105EC0_filesel(0x1B);
    func_80105EC0_filesel(0x1A);
}

void func_8010DDC0_filesel(s32 arg0) {
    func_80105F84_filesel(0x14);
    if (_CheckFlag(0x18) == 0) {
        func_80105FA0_filesel(0x15);
        func_80105FA0_filesel(0x16);
        func_80105FA0_filesel(0x17);
        func_80105FA0_filesel(0x18);
        func_80105F84_filesel(0x19);
        func_80105FA0_filesel(0x1A);
        func_80105FA0_filesel(0x1B);
        func_80105FA0_filesel(0x1C);
        func_80105FA0_filesel(0x1D);
        func_80105FA0_filesel(0x1E);
        return;
    }
    func_80105F84_filesel(0x15);
    func_80105F84_filesel(0x16);
    func_80105F84_filesel(0x17);
    func_80105F84_filesel(0x18);
    func_80105F84_filesel(0x19);
    if (_CheckFlag(0x28) != 0) {
        func_80105F84_filesel(0x1E);
        func_80105F84_filesel(0x1C);
        func_80105F84_filesel(0x1D);
        func_80105F84_filesel(0x1A);
        if (D_801142DC_filesel[arg0].unk_38 / 10 != 0) {
            func_80105F84_filesel(0x1B);
        }
    }
}

void func_8010DEEC_filesel(void) {
    func_80105FA0_filesel(0x14);
    func_80105FA0_filesel(0x15);
    func_80105FA0_filesel(0x16);
    func_80105FA0_filesel(0x17);
    func_80105FA0_filesel(0x18);
    func_80105FA0_filesel(0x19);
    func_80105FA0_filesel(0x1A);
    func_80105FA0_filesel(0x1B);
    func_80105FA0_filesel(0x1C);
    func_80105FA0_filesel(0x1D);
    func_80105FA0_filesel(0x1E);
}

void func_8010DF58_filesel(void) {
    func_80105EC0_filesel(0x1F);
    func_80105EC0_filesel(0x28);
    func_80105EC0_filesel(0x20);
    func_80105EC0_filesel(0x21);
    func_80105EC0_filesel(0x22);
    func_80105EC0_filesel(0x27);
    func_80105EC0_filesel(0x26);
    func_80105EC0_filesel(0x25);
    func_80105EC0_filesel(0x24);
    func_80105EC0_filesel(0x23);
    func_80105EC0_filesel(0x29);
    func_80105EC0_filesel(0x2A);
    func_80105EC0_filesel(0x2F);
    func_80105EC0_filesel(0x2E);
    func_80105EC0_filesel(0x2D);
    func_80105EC0_filesel(0x2C);
    func_80105EC0_filesel(0x2B);
}

void func_8010DFF4_filesel(s32 arg0) {
    func_80105F84_filesel(0x1F);
    func_80105F84_filesel(0x28);
    func_80105F84_filesel(0x20);
    if (_CheckFlag(0x16) == 0) {
        func_80105FA0_filesel(0x21);
        func_80105F84_filesel(0x22);
        func_80105FA0_filesel(0x27);
        func_80105FA0_filesel(0x26);
        func_80105FA0_filesel(0x25);
        func_80105FA0_filesel(0x24);
        func_80105FA0_filesel(0x23);
    } else {
        func_80105F84_filesel(0x21);
        func_80105F84_filesel(0x22);
        func_80105F84_filesel(0x27);
        func_80105F84_filesel(0x25);
        func_80105F84_filesel(0x26);
        func_80105F84_filesel(0x23);
        if (D_801142DC_filesel[arg0].unk_78 / 10 != 0) {
            func_80105F84_filesel(0x24);
        }
    }
    if (_CheckFlag(0x17) == 0) {
        func_80105FA0_filesel(0x29);
        func_80105F84_filesel(0x2A);
        func_80105FA0_filesel(0x2C);
        func_80105FA0_filesel(0x2B);
        return;
    }
    func_80105F84_filesel(0x29);
    func_80105F84_filesel(0x2F);
    if (D_801142DC_filesel[arg0].unk_60 == 20) {
        func_80105F84_filesel(0x2D);
        func_80105F84_filesel(0x2E);
        func_80105F84_filesel(0x2B);
        func_80105F84_filesel(0x2A);
        if (D_801142DC_filesel[arg0].unk_5C / 10 != 0) {
            func_80105F84_filesel(0x2C);
        }
    }
}

void func_8010E1B4_filesel(void) {
    func_80105FA0_filesel(0x1F);
    func_80105FA0_filesel(0x28);
    func_80105FA0_filesel(0x20);
    func_80105FA0_filesel(0x21);
    func_80105FA0_filesel(0x22);
    func_80105FA0_filesel(0x27);
    func_80105FA0_filesel(0x26);
    func_80105FA0_filesel(0x25);
    func_80105FA0_filesel(0x24);
    func_80105FA0_filesel(0x23);
    func_80105FA0_filesel(0x29);
    func_80105FA0_filesel(0x2A);
    func_80105FA0_filesel(0x2F);
    func_80105FA0_filesel(0x2E);
    func_80105FA0_filesel(0x2D);
    func_80105FA0_filesel(0x2C);
    func_80105FA0_filesel(0x2B);
}

void func_8010E250_filesel(void *arg0, void *arg1, f32 dist, void *arg3, void *arg4, void *arg5) {
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

    rx = ((Vec *)arg1)->x;
    ry = ((Vec *)arg1)->y;
    rz = ((Vec *)arg1)->z;
    ((Vec *)arg3)->x = sindf(ry) * cosdf(rx) * dist + ((Vec *)arg0)->x;
    ((Vec *)arg3)->y = -sindf(rx) * dist + ((Vec *)arg0)->y;
    ((Vec *)arg3)->z = cosdf(ry) * cosdf(rx) * dist + ((Vec *)arg0)->z;
    ((Vec *)arg4)->x = ((Vec *)arg0)->x;
    ((Vec *)arg4)->y = ((Vec *)arg0)->y;
    ((Vec *)arg4)->z = ((Vec *)arg0)->z;
    ux = sindf(ry) * sindf(rx);
    uy = cosdf(rx);
    uz = cosdf(ry) * sindf(rx);
    dx = ((Vec *)arg4)->x - ((Vec *)arg3)->x;
    dy = ((Vec *)arg4)->y - ((Vec *)arg3)->y;
    dz = ((Vec *)arg4)->z - ((Vec *)arg3)->z;
    len = dx * dx + dy * dy + dz * dz;
    len = HuSqrtf(len);
    dx /= len;
    dy /= len;
    dz /= len;
    ((Vec *)arg5)->x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
                     + uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz))
                     + uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
    ((Vec *)arg5)->y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz))
                     + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
                     + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
    ((Vec *)arg5)->z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz))
                     + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
                     + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
}

void func_8010E740_filesel(s32 arg0) {
    D_80114500_filesel = arg0;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 0.0f;
    CZoom = 3000.0f;
    D_801144F8_filesel = 80.0f;
    D_801144FC_filesel = 8000.0f;
    D_801128A0_filesel = 20.0f;
    HuVecCopyXYZ(&D_801144D4_filesel, 10.0f, CRot.x, CRot.x); /* retail reads CRot.x (0.0f here) */
    HuVecCopyXYZ(&D_801144E0_filesel, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_801144EC_filesel, 0.0f, 1.0f, 0.0f);
    Hu3DCamSetPerspective(0, D_801128A0_filesel, D_801144F8_filesel, D_801144FC_filesel);
    Hu3DCamSetPositionOrientation(0, &D_801144D4_filesel, &D_801144E0_filesel, &D_801144EC_filesel);
    Hu3DCamUpdateMtx(0);
}

void func_8010E864_filesel(void) {
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

    while (1) {
        if (D_80114500_filesel == -1 || D_80114500_filesel == 0) {
            if (D_80114500_filesel == 0) {
                if (D_800CDA7C_main[0] & 0x2000) {
                    CZoom += D_800D20A1_main[0];
                    if (CZoom < 100.0f) {
                        CZoom = 100.0f;
                    } else if (CZoom > 8000.0f) {
                        CZoom = 8000.0f;
                    }
                } else {
                    CRot.x += D_800D20A1_main[0] * 0.1f;
                    if (CRot.x < 0.0f) {
                        CRot.x += 360.0f;
                    } else if (CRot.x >= 360.0f) {
                        CRot.x -= 360.0f;
                    }
                    CRot.y += D_800CBB6E_main[0] * 0.1f;
                    if (CRot.y < 0.0f) {
                        CRot.y += 360.0f;
                    } else if (CRot.y >= 360.0f) {
                        CRot.y -= 360.0f;
                    }
                }
            }
            rx = CRot.x;
            ry = CRot.y;
            rz = CRot.z;
            D_80112EA0_filesel.x = sindf(ry) * cosdf(rx) * CZoom + Center.x;
            D_80112EA0_filesel.y = -sindf(rx) * CZoom + Center.y;
            D_80112EA0_filesel.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
            D_80112EAC_filesel.x = Center.x;
            D_80112EAC_filesel.y = Center.y;
            D_80112EAC_filesel.z = Center.z;
            ux = sindf(ry) * sindf(rx);
            uy = cosdf(rx);
            uz = cosdf(ry) * sindf(rx);
            dx = D_80112EAC_filesel.x - D_80112EA0_filesel.x;
            dy = D_80112EAC_filesel.y - D_80112EA0_filesel.y;
            dz = D_80112EAC_filesel.z - D_80112EA0_filesel.z;
            len = dx * dx + dy * dy + dz * dz;
            len = HuSqrtf(len);
            dx /= len;
            dy /= len;
            dz /= len;
            D_80112EB8_filesel.x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
                                 + uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz))
                                 + uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
            D_80112EB8_filesel.y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz))
                                 + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
                                 + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
            D_80112EB8_filesel.z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz))
                                 + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
                                 + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
        } else {
            if (D_80114500_filesel != 1) {
                D_801144D4_filesel.y += D_800D20A1_main[0];
                /* retail clamps z after moving y */
                if (D_801144D4_filesel.z < -2000.0f) {
                    D_801144D4_filesel.z = -2000.0f;
                } else if (D_801144D4_filesel.z > 2000.0f) {
                    D_801144D4_filesel.z = 2000.0f;
                }
                D_801144D4_filesel.x += D_800CBB6E_main[0];
                if (D_801144D4_filesel.x < -2000.0f) {
                    D_801144D4_filesel.x = -2000.0f;
                } else if (D_801144D4_filesel.x > 2000.0f) {
                    D_801144D4_filesel.x = 2000.0f;
                }
            }
            HuVecCopy3F(&D_80112EA0_filesel, &D_801144D4_filesel);
            HuVecCopy3F(&D_80112EAC_filesel, &D_801144E0_filesel);
            HuVecCopy3F(&D_80112EB8_filesel, &D_801144EC_filesel);
        }
        Hu3DCamSetPositionOrientation(0, &D_80112EA0_filesel, &D_80112EAC_filesel, &D_80112EB8_filesel);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

void func_8010F10C_filesel(void) {
    omDelPrcObj(D_80114504_filesel);
}

void func_8010F12C_filesel(void) {
    func_8010E740_filesel(-1);
    D_80114504_filesel = omAddPrcObj(func_8010E864_filesel, 1, 0x2000, 0);
}

// the window width is kept in a register for the first window's stack argument, float register choice (masked ~20)
#ifdef NON_MATCHING
void func_8010F168_filesel(void) {
    Vec pos;
    Vec2f scr;
    s16 win;
    u16 w;
    f32 y;

    func_80106B40_filesel(0, 0x2A11, 0x18, 0x14, 0xC8, 0x18, 2);
    win = func_80107810_filesel(0);
    func_8005FBF8_main(win, 0x80, 0x80, 0x80);
    func_8005C02C_main(win, 7);
    func_801078BC_filesel(0, 0x78);
    func_801076A0_filesel(0);
    func_8010F678_filesel(0);
    func_80106B40_filesel(4, 0x2A00, 0xA0, 0xAF, 0, 0, 5);
    func_801076A0_filesel(4);
    func_80105E48_filesel(0x12, 0x88);
    func_80106134_filesel(0x12, 5);
    func_80105F54_filesel(0x12);
    w = 0x3E;
    HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
    Hu3DCam3DToScreen(0, &pos, &scr);
    y = 168.0f;
    func_80106B40_filesel(1, (u32)D_801142DC_filesel[0].unk_01, scr.x - (w >> 1), y, w, 0x14, 2);
    win = func_80107810_filesel(1);
    func_8005B63C_main(win, 0x80000, 0x80000);
    func_8005FBF8_main(win, 0xC0, 0xC0, 0xC0);
    func_8005C02C_main(win, 7);
    if ((D_801142DC_filesel[0].unk_01[0] | D_801142DC_filesel[0].unk_01[1]) == 0) {
        func_801076D0_filesel(1, (u32)D_80112AF0_filesel);
        func_8010F760_filesel(0, 0);
    } else {
        func_8010F760_filesel(0, 1);
    }
    func_8010F874_filesel(0);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    Hu3DCam3DToScreen(0, &pos, &scr);
    func_80106B40_filesel(2, (u32)D_801142DC_filesel[1].unk_01, scr.x - (w >> 1), y, w, 0x14, 2);
    win = func_80107810_filesel(2);
    func_8005B63C_main(win, 0x80000, 0x80000);
    func_8005FBF8_main(win, 0xC0, 0xC0, 0xC0);
    func_8005C02C_main(win, 7);
    if ((D_801142DC_filesel[1].unk_01[0] | D_801142DC_filesel[1].unk_01[1]) == 0) {
        func_801076D0_filesel(2, (u32)D_80112AF0_filesel);
        func_8010F760_filesel(1, 0);
    } else {
        func_8010F760_filesel(1, 1);
    }
    func_8010F874_filesel(1);
    HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
    Hu3DCam3DToScreen(0, &pos, &scr);
    func_80106B40_filesel(3, (u32)D_801142DC_filesel[2].unk_01, scr.x - (w >> 1), y, w, 0x14, 2);
    win = func_80107810_filesel(3);
    func_8005B63C_main(win, 0x80000, 0x80000);
    func_8005FBF8_main(win, 0x80, 0x80, 0x80);
    func_8005C02C_main(win, 7);
    if ((D_801142DC_filesel[2].unk_01[0] | D_801142DC_filesel[2].unk_01[1]) == 0) {
        func_801076D0_filesel(3, (u32)D_80112AF0_filesel);
        func_8010F760_filesel(2, 0);
    } else {
        func_8010F760_filesel(2, 1);
    }
    func_8010F874_filesel(2);
    func_8010A680_filesel(0, -400.0f, 0.0f, 0.0f);
    func_8010A680_filesel(1, -400.0f, 0.0f, 0.0f);
    func_8010A680_filesel(2, -400.0f, 0.0f, 0.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F168_filesel);
#endif

void func_8010F5C8_filesel(void) {
    func_80106344_filesel(0);
    func_80106344_filesel(1);
    func_80106344_filesel(2);
    func_80106344_filesel(3);
    func_80106344_filesel(4);
    func_80106344_filesel(5);
    func_80107490_filesel(1);
    func_80107490_filesel(2);
    func_80107490_filesel(3);
    func_80105EC0_filesel(0xD);
    func_80105EC0_filesel(0xE);
    func_80105EC0_filesel(0xF);
    func_80105EC0_filesel(0x12);
    func_80107490_filesel(0);
    func_8010F65C_filesel();
    func_80107490_filesel(4);
}

void func_8010F65C_filesel(void) {
    func_80105EC0_filesel(0xC);
}



INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112E08_filesel);

void func_8010F678_filesel(u32 arg0) {
    s32 dataNum;
    s32 x;
    s32 y;

    switch (arg0) {
    case 0:
        dataNum = 0x1F001C;
        x = 0x5B;
        y = 0x21;
        break;
    case 1:
        dataNum = 0x1F001D;
        x = 0x5E;
        y = 0x21;
        break;
    case 2:
        dataNum = 0x1F001E;
        x = 0x36;
        y = 0x21;
        break;
    case 3:
        dataNum = 0x1F001F;
        x = 0x3F;
        y = 0x21;
        break;
    case 4:
        dataNum = 0x1F0022;
        x = 0x79;
        y = 0x1E;
        break;
    default:
        dataNum = 0;
        y = 0;
        x = 0;
        break;
    }
    func_80105E7C_filesel(0xC, dataNum);
    func_80106044_filesel(0xC, 1.0f, 1.0f);
    func_80106094_filesel(0xC, 0x100);
    func_80105FBC_filesel(0xC, x, y);
}

void func_8010F760_filesel(s32 arg0, s32 arg1) {
    Vec pos;
    Vec2f screen;
    s32 x;
    s32 dataNum;

    dataNum = (arg1 != 0) ? 0x1F0020 : 0x1F0021;
    pos.x = D_801128A4_filesel[arg0].x;
    pos.y = D_801128A4_filesel[arg0].y;
    pos.z = D_801128A4_filesel[arg0].z;
    Hu3DCam3DToScreen(0, &pos, &screen);
    x = screen.x;
    arg0 += 0xD;
    func_80105E48_filesel(arg0, dataNum);
    func_80106044_filesel(arg0, 1.0f, 1.0f);
    func_80106094_filesel(arg0, 0x100);
    func_80105FBC_filesel(arg0, x, 0xB1);
}

void func_8010F844_filesel(s32 arg0) {
    func_80105F84_filesel(arg0 + 0xD);
    func_80107670_filesel(arg0 + 1);
}

void func_8010F874_filesel(s32 arg0) {
    func_80105FA0_filesel(arg0 + 0xD);
    func_801076A0_filesel(arg0 + 1);
}

// work[0] is loaded into a0 and copied to s1 after the time conversions (masked 6)
#ifdef NON_MATCHING
void func_8010F8A4_filesel(omObjData *obj) {
    s32 no;
    Vec pos;
    Vec rot;
    f32 total;
    f32 time;
    Vec *start;
    Vec *end;
    f32 t;
    f32 s;
    f32 scale;

    no = obj->work[0];
    total = obj->work[1];
    time = obj->work[2];
    start = &D_801128C8_filesel[no][0];
    end = &D_801128C8_filesel[no][1];
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    s = t * 0.9f + 0.1f;
    scale = s * 0.8f;
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    pos.x = (end->x - start->x) * s + start->x;
    pos.y = (end->y - start->y) * s + start->y;
    pos.z = (end->z - start->z) * s + start->z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, end->x, end->y, end->z);
        func_801064DC_filesel(no + 3, end->x, end->y, end->z);
        func_80106550_filesel(no, 0.8f, 0.8f, 0.8f);
        func_80106550_filesel(no + 3, 0.8f, 0.8f, 0.8f);
        omDelObj(obj);
        return;
    }
    time += 1.0f;
    obj->work[2] = time;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F8A4_filesel);
#endif

omObjData *func_8010FBE0_filesel(u32 arg0, u32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_8010F8A4_filesel);
    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
    func_801066DC_filesel(arg0);
    func_801066DC_filesel(arg0 + 3);
    return obj;
}

// float register allocation of the 0.9/0.1 constants (masked 4)
#ifdef NON_MATCHING
void func_8010FC58_filesel(omObjData *obj) {
    Vec pos;
    Vec rot;
    s32 no;
    Vec *start;
    Vec *end;
    f32 total;
    f32 time;
    f32 t;
    f32 scale;

    no = obj->work[0];
    start = &D_80112910_filesel[no][0];
    end = &D_80112910_filesel[no][1];
    total = obj->work[1];
    time = obj->work[2];
    t = time / total;
    t = 1.0f - t;
    if (t < 0.0f) {
        t = 0.0f;
    }
    scale = (t * 0.9f + 0.1f) * 0.8f;
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    pos.x = (end->x - start->x) * (t * 0.9f + 0.1f) + start->x;
    pos.y = (end->y - start->y) * (t * 0.9f + 0.1f) + start->y;
    pos.z = (end->z - start->z) * (t * 0.9f + 0.1f) + start->z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    if (time == total) {
        omDelObj(obj);
        func_8010669C_filesel(no);
        func_8010669C_filesel(no + 3);
        return;
    }
    time += 1.0f;
    obj->work[2] = time;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FC58_filesel);
#endif

void func_8010FF48_filesel(u32 arg0, u32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_8010FC58_filesel);
    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
}

void func_8010FFA0_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec rot;
    s32 no;
    f32 total;
    f32 time;
    f32 lo;
    f32 t;
    f32 scale;
    f32 u;
    f32 f;

    lo = 0.48f;
    no = obj->work[0];
    total = D_80114508_filesel[no].total;
    time = D_80114508_filesel[no].time;
    HuVecCopy3F(&start, &D_80112958_filesel[no]);
    HuVecCopyXYZ(&end, -400.0f, 340.0f, 0.0f);
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    scale = lo + (0.8f - lo) * (1.0f - t);
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    u = t - 0.8f;
    f = u * -1.6666666f * u + 1.0666666242811431;
    pos.x = (end.x - start.x) * t + start.x;
    pos.y = (end.y - start.y) * f + start.y;
    pos.z = (end.z - start.z) * t + start.z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, end.x, end.y, end.z);
        func_801064DC_filesel(no + 3, end.x, end.y, end.z);
        func_80106550_filesel(no, lo, lo, lo);
        func_80106550_filesel(no + 3, lo, lo, lo);
        func_80106474_filesel(no, 0.0f, 0.0f, 0.0f);
        func_80106474_filesel(no + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_80114508_filesel[no].time = time;
    }
}

void func_801102F0_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].obj);
}

void func_80110320_filesel(u32 arg0, s32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_8010FFA0_filesel);
    obj->work[0] = arg0;
    D_80114508_filesel[arg0].obj = obj;
    D_80114508_filesel[arg0].total = arg1;
    D_80114508_filesel[arg0].time = 0;
}

void func_801103A0_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec rot;
    s32 no;
    f32 total;
    f32 time;
    f32 lo;
    f32 t;
    f32 scale;
    f32 u;
    f32 f;

    lo = 0.48f;
    no = obj->work[0];
    total = D_80114508_filesel[no].total;
    time = D_80114508_filesel[no].time;
    HuVecCopy3F(&start, &D_8011297C_filesel[no]);
    HuVecCopyXYZ(&end, -400.0f, 340.0f, 0.0f);
    t = 1.0f - time / total;
    if (t < 0.0f) {
        t = 0.0f;
    }
    scale = lo + (0.8f - lo) * (1.0f - t);
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    u = t - 0.8f;
    f = u * -1.6666666f * u + 1.0666666242811431;
    pos.x = (end.x - start.x) * t + start.x;
    pos.y = (end.y - start.y) * f + start.y;
    pos.z = (end.z - start.z) * t + start.z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, start.x, start.y, start.z);
        func_801064DC_filesel(no + 3, start.x, start.y, start.z);
        func_80106550_filesel(no, 0.8f, 0.8f, 0.8f);
        func_80106550_filesel(no + 3, 0.8f, 0.8f, 0.8f);
        func_80106474_filesel(no, 0.0f, 0.0f, 0.0f);
        func_80106474_filesel(no + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_80114508_filesel[no].time = time;
    }
}

void func_801106FC_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].obj);
}

void func_8011072C_filesel(u32 arg0, s32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_801103A0_filesel);
    obj->work[0] = arg0;
    D_80114508_filesel[arg0].obj = obj;
    D_80114508_filesel[arg0].time = 0;
    D_80114508_filesel[arg0].total = arg1;
}

void func_801107AC_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec rot;
    s32 no;
    f32 total;
    f32 time;
    f32 t;
    f32 scale;
    f32 f;

    no = obj->work[0];
    total = D_80114508_filesel[no].total;
    time = D_80114508_filesel[no].time;
    HuVecCopy3F(&start, &D_80114508_filesel[no].start);
    HuVecCopy3F(&end, &D_80114508_filesel[no].end);
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    if (end.y - start.y < 0.0f) {
        scale = t * (0.8f - 0.48) + 0.48;
        func_80106550_filesel(no, scale, scale, scale);
        func_80106550_filesel(no + 3, scale, scale, scale);
    }
    if (end.y - start.y < 0.0f) {
        f = -((0.2f - t) * -1.6666666f * (0.2f - t) + 1.0666666f) + 1.0f;
    } else {
        f = (t - 0.8f) * -1.6666666f * (t - 0.8f) + 1.0666666f;
    }
    pos.x = (end.x - start.x) * t + start.x;
    pos.y = (end.y - start.y) * f + start.y;
    pos.z = (end.z - start.z) * t + start.z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, end.x, end.y, end.z);
        func_801064DC_filesel(no + 3, end.x, end.y, end.z);
        func_80106474_filesel(no, 0.0f, 0.0f, 0.0f);
        func_80106474_filesel(no + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_80114508_filesel[no].time = time;
    }
}

void func_80110B4C_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].obj);
}

omObjData *func_80110B7C_filesel(u32 arg0, f32 x, f32 y, f32 z, s32 time) {
    f32 px;
    f32 py;
    f32 pz;
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_801107AC_filesel);
    obj->work[0] = arg0;
    D_80114508_filesel[arg0].obj = obj;
    D_80114508_filesel[arg0].total = time;
    D_80114508_filesel[arg0].time = 0;
    func_801065B8_filesel(arg0, &px, &py, &pz);
    HuVecCopyXYZ(&D_80114508_filesel[arg0].start, px, py, pz);
    HuVecCopyXYZ(&D_80114508_filesel[arg0].end, x, y, z);
    return obj;
}

void func_80110C84_filesel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80114598_filesel[i].obj = NULL;
    }
}

void func_80110CC0_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].obj);
    D_80114598_filesel[arg0].obj = NULL;
}

void func_80110D0C_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    u32 no;
    s32 mdl;
    f32 r;
    f32 t;

    no = obj->work[0];
    mdl = no;
    r = (f32)D_80114598_filesel[no].time / (f32)D_80114598_filesel[no].total;
    t = (r > 1.0f) ? 1.0f : r;
    HuVecCopy3F(&start, &D_80114598_filesel[no].start);
    HuVecCopy3F(&end, &D_80114598_filesel[no].end);
    HuVecCopyXYZ(&pos, (end.x - start.x) * t + start.x, (end.y - start.y) * t + start.y,
                 (end.z - start.z) * t + start.z);
    func_801064DC_filesel(mdl, pos.x, pos.y, pos.z);
    if (t > 1.0f) {
        func_80110CC0_filesel(no);
    }
}

void func_80110E70_filesel(u32 arg0, omObjFunc func) {
    omObjData *obj;

    if (D_80114598_filesel[arg0].obj != NULL) {
        omDelObj(D_80114598_filesel[arg0].obj);
    }
    obj = omAddObj(6, 0, 0, -1, func);
    obj->work[0] = arg0;
    D_80114598_filesel[arg0].obj = obj;
}

/* Retail copies the slot's start into a local and builds the target in another local: the
   slot's start, end, time and total are never set (see func_80110D0C_filesel). */
void func_80110F04_filesel(s32 arg0, f32 x, f32 y, f32 z) {
    Vec pos;
    Vec end;

    func_80110E70_filesel(arg0, func_80110D0C_filesel);
    func_8010642C_filesel(arg0);
    func_801065B8_filesel(arg0, &pos.x, &pos.y, &pos.z);
    HuVecCopy3F(&pos, &D_80114598_filesel[arg0].start);
    HuVecCopyXYZ(&end, x, y, z);
}

void func_80110FB0_filesel(u32 arg0) {
    func_80110CC0_filesel(arg0);
    func_80106550_filesel(arg0, 0.8f, 0.8f, 0.8f);
    func_80106550_filesel(arg0 + 3, 0.8f, 0.8f, 0.8f);
}

void func_80111004_filesel(omObjData *obj) {
    u32 no;
    s32 angle;
    f32 s;
    f32 sx;
    f32 sy;

    no = obj->work[0];
    angle = D_80114598_filesel[no].time;
    angle += 27;
    if (angle > 360) {
        angle -= 360;
    }
    D_80114598_filesel[no].time = angle;
    s = sindf(angle) * 0.1f;
    sx = 0.8f + s;
    sy = 0.8f - s;
    func_80106550_filesel(no, sx, sy, sx);
    func_80106550_filesel(no + 3, sx, sy, sx);
}

void func_801110F0_filesel(u32 arg0) {
    func_80110E70_filesel(arg0, func_80111004_filesel);
    D_80114598_filesel[arg0].time = 0;
    func_8010642C_filesel(arg0);
}

void func_80111144_filesel(omObjData *obj) {
    u32 no;
    s32 mdl;
    s32 angle;
    s32 time;
    s32 total;
    f32 r;
    f32 t;
    f32 a;
    f32 b;

    no = obj->work[0];
    mdl = no;
    angle = D_80114598_filesel[no].angle;
    time = D_80114598_filesel[no].time;
    total = D_80114598_filesel[no].total;
    r = 1.0f - time * 0.022222223f;
    t = (r < 0.0f) ? 0.0f : r;
    angle += 27;
    if (angle > 360.0f) {
        angle = angle - 360.0f;
    }
    a = 0.0f;
    b = 0.0f;
    if (time >= total) {
        func_80110FB0_filesel(mdl);
    } else {
        a = sindf(angle) * 0.3f * t;
        b = 1.0f / (a + 1.0f) - 1.0f;
    }
    D_80114598_filesel[no].angle = angle;
    D_80114598_filesel[no].time = time + 1;
    func_80106550_filesel(no, a + 0.8f, b + 0.8f, a + 0.8f);
    func_80106550_filesel(no + 3, a + 0.8f, b + 0.8f, a + 0.8f);
}

void func_8011132C_filesel(s32 arg0) {
    func_80110E70_filesel(arg0, func_80111144_filesel);
    D_80114598_filesel[arg0].total = 45;
    D_80114598_filesel[arg0].time = 0;
    D_80114598_filesel[arg0].angle = 0;
    func_8010642C_filesel(arg0);
}

void func_8011139C_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].obj);
    D_80114598_filesel[arg0].obj = NULL;
}

void func_801113E8_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    u32 no;
    s32 time;
    f32 r;
    f32 t;
    f32 h;
    f32 scale;

    no = obj->work[0];
    time = D_80114598_filesel[no].time;
    r = (f32)time / (f32)D_80114598_filesel[no].total;
    t = (r > 1.0f) ? 1.0f : r;
    h = (t - 0.2f) * -1.6666666f * (t - 0.2f) + 1.0666666f - (-t + 1.0f);
    HuVecCopy3F(&start, &D_80114598_filesel[no].start);
    HuVecCopy3F(&end, &D_80114598_filesel[no].end);
    HuVecCopyXYZ(&pos, (end.x - start.x) * t + start.x, (end.y - start.y) * t + h * 400.0f + start.y,
                 (end.z - start.z) * t + start.z);
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    scale = (t * 0.7f + 0.3f) * 0.8f;
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    time++;
    D_80114598_filesel[no].time = time;
    if (r > 1.0f) {
        func_8011139C_filesel(no);
    }
}

void func_80111660_filesel(s32 arg0, s32 arg1, s32 arg2) {
    Vec tbl[3] = { { -400.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 400.0f, 0.0f, 0.0f } };

    func_80110E70_filesel(arg1, func_801113E8_filesel);
    func_8010642C_filesel(arg1);
    HuVecCopy3F(&D_80114598_filesel[arg1].start, &tbl[arg0]);
    D_80114598_filesel[arg1].start.y += 100.0f;
    HuVecCopy3F(&D_80114598_filesel[arg1].end, &tbl[arg1]);
    D_80114598_filesel[arg1].time = 0;
    D_80114598_filesel[arg1].total = arg2;
}

void func_80111790_filesel(omObjData *obj) {
    Vec pos;
    Vec rot;
    Vec eye;
    Vec at;
    Vec up;
    f32 total;
    f32 time;
    f32 t;
    f32 dist;

    total = D_801146B0_filesel.total;
    time = D_801146B0_filesel.time;
    HuVecCopy3F(&pos, &D_801146B0_filesel.pos);
    HuVecCopy3F(&rot, &D_801146B0_filesel.rot);
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    rot.x = t * -88.0f;
    dist = ((1.0f - t) * 0.75f + 0.25f) * 3000.0f;
    HuVecCopy3F(&D_801146B0_filesel.pos, &pos);
    HuVecCopy3F(&D_801146B0_filesel.rot, &rot);
    D_801146B0_filesel.dist = dist;
    func_8010E250_filesel(&pos, &rot, dist, &eye, &at, &up);
    Hu3DCamSetPositionOrientation(0, &eye, &at, &up);
    Hu3DCamUpdateMtx(0);
    if (time == total) {
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_801146B0_filesel.time = time;
    }
}

omObjData *func_80111944_filesel(u32 arg0) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_80111790_filesel);
    obj->work[0] = 0;
    obj->work[1] = arg0;
    obj->work[2] = 0;
    HuVecCopyXYZ(&D_801146B0_filesel.pos, 0.0f, 200.0f, 0.0f);
    HuVecCopyXYZ(&D_801146B0_filesel.rot, 0.0f, 0.0f, 0.0f);
    D_801146B0_filesel.dist = 3000.0f;
    D_801146B0_filesel.total = arg0;
    D_801146B0_filesel.time = 0;
    return obj;
}

void func_801119F4_filesel(void) {
    D_801129A0_filesel = 0;
    D_801146D4_filesel = 0;
}

/* Stick direction as a d-pad mask, repeated every 9 frames while held. */
// branch-likely on the first test and the load order of the stick bytes (masked 1)
#ifdef NON_MATCHING
s32 func_80111A08_filesel(s32 pad) {
    s32 ax;
    s32 ay;
    s32 y;
    s32 x;
    s32 dir;

    x = D_800CBB6E_main[pad];
    y = D_800D20A1_main[pad];
    if ((y != 0) | (x != 0)) {
        ax = x;
        if (x < 0) {
            ax = -ax;
        }
        ay = y;
        if (y < 0) {
            ay = -ay;
        }
        if (ay < ax) {
            if (ay * 2 < ax) {
                dir = 0x100;
                if (x < 0) {
                    dir = 0x200;
                }
            } else if (y > 0) {
                dir = 0x900;
                if (x < 0) {
                    dir = 0xA00;
                }
            } else {
                dir = 0x500;
                if (x < 0) {
                    dir = 0x600;
                }
            }
        } else if (ax * 2 < ay) {
            dir = 0x800;
            if (y < 0) {
                dir = 0x400;
            }
        } else if (y > 0) {
            dir = 0x900;
                if (x < 0) {
                    dir = 0xA00;
                }
        } else {
            dir = 0x500;
                if (x < 0) {
                    dir = 0x600;
                }
        }
        if (D_801129A0_filesel != dir || ++D_801146D4_filesel >= 9) {
            D_801129A0_filesel = dir;
            D_801146D4_filesel = 0;
            return dir;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111A08_filesel);
#endif

/* Stick direction as a d-pad mask, once per push. */
// retail keeps the two diagonal blocks separate; this C cross-jumps them (masked 45, logic checked)
#ifdef NON_MATCHING
s32 func_80111B14_filesel(s32 pad) {
    s32 ax;
    s32 ay;
    s32 y;
    s32 x;
    s32 dir;

    x = D_800CBB6E_main[pad];
    y = D_800D20A1_main[pad];
    if (D_801129A0_filesel != 0) {
        if ((x == 0) & (y == 0)) {
            D_801129A0_filesel = 0;
        }
        return 0;
    }
    if ((x != 0) | (y != 0)) {
        ax = x;
        if (x < 0) {
            ax = -ax;
        }
        ay = y;
        if (y < 0) {
            ay = -ay;
        }
        if (ay < ax) {
            if (ay * 2 < ax) {
                dir = 0x100;
                if (x < 0) {
                    dir = 0x200;
                }
            } else if (y > 0) {
                dir = 0x900;
                if (x < 0) {
                    dir = 0xA00;
                }
            } else {
                dir = 0x500;
                if (x < 0) {
                    dir = 0x600;
                }
            }
        } else if (ax * 2 < ay) {
            dir = 0x800;
            if (y < 0) {
                dir = 0x400;
            }
        } else if (y > 0) {
            dir = 0x900;
                if (x < 0) {
                    dir = 0xA00;
                }
        } else {
            dir = 0x500;
                if (x < 0) {
                    dir = 0x600;
                }
        }
        D_801129A0_filesel = dir;
    }
    return D_801129A0_filesel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111B14_filesel);
#endif

void func_80111C30_filesel(void) {
    s32 i;

    FS_LAST_FILE = 0;
    for (i = 0; i < 3; i++) {
        SLCurBoxNoSet(i);
        func_80050800_main();
        if (GwCommon.unk_00 == FS_FILE_USED && D_800D09A9_main == i) {
            FS_LAST_FILE = i;
        }
        func_801122B0_filesel(i);
        func_80112184_filesel(i);
    }
}

// the 99 clamps branch the other way (bnez/move vs beqz/li) and use other registers; logic checked
#ifdef NON_MATCHING
void func_80111CBC_filesel(s32 no) {
    s32 v;
    u8 a;
    u8 b;

    D_801142D8_filesel[no].storyChr = 0;
    D_801142D8_filesel[no].story[0] = 0;
    D_801142D8_filesel[no].story[1] = 0;
    D_801142D8_filesel[no].story[2] = 0;
    D_801142D8_filesel[no].story[3] = 99;
    D_801142D8_filesel[no].story[4] = 99;
    D_801142D8_filesel[no].story[5] = 0;
    D_801142D8_filesel[no].story[6] = 0;
    if (_CheckFlag(0x18) != 0) {
        func_80112758_filesel();
        D_801142D8_filesel[no].storyChr = GwStory.unk1;
        D_801142D8_filesel[no].story[6] = GwStory.unk0;
        func_801126C0_filesel(GwStory.unk0, &a, &b);
        D_801142D8_filesel[no].story[0] = b;
        D_801142D8_filesel[no].story[1] = a;
        D_801142D8_filesel[no].story[2] = (GwSystem.current_turn < 4) ? GwSystem.current_game_length : 3;
        D_801142D8_filesel[no].story[3] = ((v = GwSystem.current_turn) < 100) ? v : 99;
        D_801142D8_filesel[no].story[4] = ((v = GwSystem.total_turns) < 100) ? v : 99;
        D_801142D8_filesel[no].story[5] = GwStory.unk2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111CBC_filesel);
#endif

// the 99 clamps branch the other way (bnez/move vs beqz/li) and use other registers; logic checked
#ifdef NON_MATCHING
void func_80111E78_filesel(s32 no) {
    s32 v;

    D_801142D8_filesel[no].duel.mode = 0;
    D_801142D8_filesel[no].duel.board = 0;
    D_801142D8_filesel[no].duel.length = 0;
    D_801142D8_filesel[no].duel.turn = 0;
    D_801142D8_filesel[no].duel.total = 99;
    if (_CheckFlag(0x16) != 0) {
        func_8005086C_main();
        D_801142D8_filesel[no].duel.chr[0] = 0;
        D_801142D8_filesel[no].duel.chr[1] = 1;
        D_801142D8_filesel[no].duel.chr[2] = 2;
        D_801142D8_filesel[no].duel.chr[3] = 3;
        D_801142D8_filesel[no].duel.mode = (GwSystem.playMode ^ 1) & 1;
        D_801142D8_filesel[no].duel.board = GwSystem.current_board_index;
        D_801142D8_filesel[no].duel.length = (GwSystem.current_turn < 4) ? GwSystem.current_game_length : 3;
        D_801142D8_filesel[no].duel.turn = ((v = GwSystem.current_turn) < 100) ? v : 99;
        D_801142D8_filesel[no].duel.total = ((v = GwSystem.total_turns) < 100) ? v : 99;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111E78_filesel);
#endif

// the 99 clamps branch the other way (bnez/move vs beqz/li) and use other registers; logic checked
#ifdef NON_MATCHING
void func_80111FFC_filesel(s32 no) {
    s32 v;

    D_801142D8_filesel[no].party.mode = 0;
    D_801142D8_filesel[no].party.board = 0;
    D_801142D8_filesel[no].party.length = 0;
    D_801142D8_filesel[no].party.turn = 0;
    D_801142D8_filesel[no].party.total = 99;
    if (_CheckFlag(0x17) != 0) {
        func_80050974_main();
        D_801142D8_filesel[no].party.chr[0] = 0;
        D_801142D8_filesel[no].party.chr[1] = 1;
        D_801142D8_filesel[no].party.chr[2] = 2;
        D_801142D8_filesel[no].party.chr[3] = 3;
        D_801142D8_filesel[no].party.mode = (((u8)GwSystem.playMode >> 1) ^ 1) & 1;
        D_801142D8_filesel[no].party.board = GwSystem.current_board_index;
        D_801142D8_filesel[no].party.length = (GwSystem.current_turn < 4) ? GwSystem.current_game_length : 3;
        D_801142D8_filesel[no].party.turn = ((v = GwSystem.current_turn) < 100) ? v : 99;
        D_801142D8_filesel[no].party.total = ((v = GwSystem.total_turns) < 100) ? v : 99;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111FFC_filesel);
#endif

void func_80112184_filesel(s32 no) {
    s32 i;

    D_801142D8_filesel[no].used = GwCommon.unk_00;
    if (D_801142D8_filesel[no].used == FS_FILE_USED) {
        for (i = 0; i < 10; i += 2) {
            D_801142D8_filesel[no].name[i] = FS_GW_NAME[i];
            D_801142D8_filesel[no].name[i + 1] = FS_GW_NAME[i + 1];
        }
        if ((D_801142D8_filesel[no].name[0] | D_801142D8_filesel[no].name[1]) == 0) {
            D_801142D8_filesel[no].used = 0;
        }
    } else {
        D_801142D8_filesel[no].name[1] = 0;
        D_801142D8_filesel[no].name[0] = 0;
    }
    func_80111CBC_filesel(no);
    func_80111E78_filesel(no);
    func_80111FFC_filesel(no);
}

// register choice for no/mask and the name-terminator addressing (masked 28, logic checked)
#ifdef NON_MATCHING
void func_801122B0_filesel(s32 no) {
    s32 i;
    s32 mask;

    for (i = 0; i < 16; i++) {
        D_801142D8_filesel[no].name[i] = 0;
    }
    switch (no) {
    case 0:
        mask = 1;
        break;
    case 1:
        mask = 2;
        break;
    case 2:
        mask = 4;
        break;
    default:
        mask = 7;
        break;
    }
    D_801142D8_filesel[no].bad = (D_800D20EC_main & mask) != 0;
    i = 0;
    if (D_801142D8_filesel[no].bad != 0) {
        for (i = 0; i < 10; i++) {
            D_801142D8_filesel[no].name[i] = 0;
        }
    } else {
        for (i = 0; i < 10; i += 2) {
            if (((FS_GW_NAME[i] << 8) | FS_GW_NAME[i + 1]) == 0) {
                break;
            }
            D_801142D8_filesel[no].name[i] = FS_GW_NAME[i];
            D_801142D8_filesel[no].name[i + 1] = FS_GW_NAME[i + 1];
        }
        D_801142D8_filesel[no].name[i + 1] = 0;
        D_801142D8_filesel[no].name[i] = 0;
    }
    if (((D_801142D8_filesel[no].name[0] << 8) | D_801142D8_filesel[no].name[1]) == 0) {
        bzero(D_801142D8_filesel[no].name, 0x20);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801122B0_filesel);
#endif

s32 func_80112494_filesel(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_801142DC_filesel[arg0].unk_01[i] = arg1[i];
    }

    // terminate string
    D_801142DC_filesel[arg0].unk_01[i] = '\0';
    D_801142DC_filesel[arg0].unk_01[i + 1] = '\0';
    return i;
}

// register allocation of the name-pair test (raw only)
#ifdef NON_MATCHING
s32 func_80112508_filesel(s32 no, u8 *out) {
    s32 i;

    for (i = 0; i < 10; i += 2) {
        if (((D_801142D8_filesel[no].name[i] << 8) | D_801142D8_filesel[no].name[i + 1]) == 0) {
            break;
        }
        out[i] = D_801142D8_filesel[no].name[i];
        out[i + 1] = D_801142D8_filesel[no].name[i + 1];
    }
    out[i] = 0;
    out[i + 1] = 0;
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112508_filesel);
#endif

void func_80112584_filesel(u32 no) {
    SLCurBoxNoSet(no);
    func_80050800_main();
    bcopy(D_801142D8_filesel[no].name, FS_GW_NAME, 10);
    D_800D09A9_main = no;
    func_80050064_main(1);
}

/* Terminates a two-byte-character string after at most 5 characters; returns its length. */
// register allocation of i/len (raw only)
#ifdef NON_MATCHING
s32 func_801125E8_filesel(u8 *str) {
    s32 i;
    s32 len;

    len = 0;
    for (i = 0; i < 10; i += 2) {
        if ((((str + i)[0] << 8) | (str + i)[1]) == 0) {
            break;
        }
        len++;
    }
    (str + i)[1] = 0;
    (str + i)[0] = 0;
    return len;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801125E8_filesel);
#endif

void func_80112630_filesel(void) {
    s32 *p;

    if (D_801146D8_filesel == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }
    p = &D_801146D8_filesel;
    *p = (*p >= 11) ? 0 : *p + 1;
}

void func_80112684_filesel(void) {
    D_801146D8_filesel = 0;
    omAddObj(6, 0, 0, -1, (omObjFunc)func_80112630_filesel);
}

// callee-saved register choice for the three arguments (raw only)
#ifdef NON_MATCHING
void func_801126C0_filesel(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 k;

    *arg1 = D_801129A4_filesel[0];
    *arg2 = D_801129A4_filesel[1];
    if (_CheckFlag(0x18) != 0) {
        if (_CheckFlag(0x28) != 0) {
            k = arg0 * 2;
        } else {
            k = (arg0 - 1) * 2;
        }
        *arg1 = D_801129A4_filesel[k];
        *arg2 = D_801129A4_filesel[k + 1];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801126C0_filesel);
#endif

void func_80112758_filesel(void) {
    func_80050ABC_main();
    if (GwStory.unk0 == 0 && _CheckFlag(0x18) != 0) {
        _SetFlag(0x28);
    }
}

