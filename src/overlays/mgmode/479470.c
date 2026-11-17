#include "common.h"
#include "mallocblock.h"
#include "math.h"
#include "game/process.h"
#include "game/vibrator.h"
#include "gcc/string.h"

/* 47D880.c's sprite list. */
typedef struct MgModeSprDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ u16 prio;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
} MgModeSprDef; // Size 0xC

typedef struct MgModeSpr {
    /* 0x00 */ s16 sprite;
    /* 0x02 */ u16 grp;
} MgModeSpr; // Size 0x4

#define MG_SPR_NONE ((MgModeSpr*)-1)

/* gamemes.c's GAMEMES (not in a header). */
typedef struct MgGameMes {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 len;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[16];
    /* 0x40 */ s16 strSprId[16];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} MgGameMes; // Size 0x74

/* The minigame info table (stride 0x14); unk06 holds the picture file. */
typedef struct MgInfo {
    /* 0x00 */ char unk00[6];
    /* 0x06 */ u16 pic;
    /* 0x08 */ char unk08[0xC];
} MgInfo; // Size 0x14

typedef struct MgCB890 {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s16 unk04; /* coin rate */
} MgCB890;

MgModeSpr* func_80116794_mgmode(MgModeSprDef* defs);
void func_801168E0_mgmode(MgModeSpr* list);
void func_80116968_mgmode(MgModeSpr* list, s16 idx, s16 x, s16 y);
void func_801169A0_mgmode(MgModeSpr* list, s16 idx);
void func_801169C8_mgmode(MgModeSpr* list, s16 idx);
void func_80116A48_mgmode(MgModeSpr* list, s16 idx, f32 x, f32 y);
void func_80116AA8_mgmode(MgModeSpr* list, s16 idx, s16 arg2);
void func_80116AEC_mgmode(MgModeSpr* list, s16 idx, u16 arg2);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
void func_80116D4C_mgmode(void);
void func_80118888_mgmode(s16 arg0);
void func_801188A4_mgmode(s16 arg0);
void func_80118624_mgmode(s16 dst, s16 src);

void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
s16 func_8003A37C_main(MgGameMes* gMes, char* str, u8 flag, s16 x, s16 arg4);
void GMesSprKill(MgGameMes* gMes);
void func_80088800_main(f32* mtx, f32 x, f32 y, f32 z);

extern MgInfo D_800A6D40_main[];
extern MgCB890 D_800CB890_main;
extern s16 D_800D1FE0_main; /* coins to spend */
extern s16 D_800D1F2C_main; /* the round, 0..7 */
extern s16 D_800D0418_main[]; /* the eight rounds' categories, then minigames */
extern u8 D_800D2008_main;

extern MgModeSpr* D_801194C0_mgmode;
extern s16 D_801194C4_mgmode;
extern s32 D_801194C8_mgmode;
extern s16 D_801195BC_mgmode[];
extern MgModeSpr* D_801195D0_mgmode;
extern MgModeSprDef D_8011A270_mgmode[];
extern MgModeSprDef D_8011A2C4_mgmode[];
extern char D_8011B510_mgmode[];
extern u8* D_8011B610_mgmode[3];
extern s16 D_8011B61C_mgmode;
extern s16 D_8011B61E_mgmode;
extern s16 D_8011B624_mgmode;
extern s16 D_8011B6A8_mgmode;
extern s16 D_8011B790_mgmode;
extern s16 D_8011B792_mgmode;
extern s16 D_8011B794_mgmode;
extern s16 D_8011B796_mgmode;
extern s16 D_8011B798_mgmode;
extern s16 D_8011B79C_mgmode;
extern s16 D_8011B808_mgmode;
extern MgGameMes D_8011B810_mgmode;
extern s16 D_8011B8A8_mgmode[];
extern s16 D_8011B8B8_mgmode[];

void func_80114614_mgmode(s16 idx);
void func_80114804_mgmode(s16 rate, s16 count, s16 total);
void func_80115A9C_mgmode(s32 x, s32 y, s32 coins);
void func_80115BB8_mgmode(s16 n);
void func_80115CAC_mgmode(s16 n);
void func_80115CDC_mgmode(MgModeSpr* list, s16 first, s16 n, s16 digits);
void func_80115E9C_mgmode(s32 mes, s16 x, s16 y);
void func_80116024_mgmode(void);
void func_801160A0_mgmode(s16 alpha);
void func_80116260_mgmode(void);
void func_801162B4_mgmode(f32 cx, f32 angle);

/* The model table (47D880.c's MgModeModelDef); entries 8..14 take the player's character models. */
typedef struct MgModeModelDef {
    /* 0x00 */ s32 dir;
    /* 0x04 */ s32 file;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 motion;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} MgModeModelDef; // Size 0x24

/* A model part (func_8001D33C_main; MP3 hmfman.c HmfMotionObjM). */
typedef struct MgHmfPart {
    /* 0x00 */ char unk00[0x58];
    /* 0x58 */ HuMtx4F mtx;
} MgHmfPart;

/* TextWindow up to the button field at 0xA8 (not in the shared header). */
typedef struct MgTextWin {
    /* 0x00 */ char unk00[0xA8];
    /* 0xA8 */ u16 btn;
} MgTextWin;

typedef struct MgPair {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} MgPair;

#define MG_NO_CB ((void (*)(s16*))-1)
#define MG_WIN_WAIT(win)                    \
    while (func_8005E0C0_main(win) != 0) { \
        HuPrcVSleep();                      \
    }

s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
MgHmfPart* func_8001D33C_main(s16 model, char* name);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src);

void func_8011667C_mgmode(MgModeModelDef* defs);
void func_80116E24_mgmode(s16 arg0);
void func_80116ED4_mgmode(s16 presetIdx, s16 duration, s16 easeType, void (*callback)(s16*));
void func_801181F4_mgmode(s16 arg0);
void func_8011822C_mgmode(MgPair* pairs);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
void func_801182B4_mgmode(s16 arg0);
s16 func_80118678_mgmode(f32 x, f32 y, f32 z, f32 spread);
void func_80118CD8_mgmode(void);

extern s16 D_800CE29C_main; /* the minigame picked for the round */
extern u8 D_80118EB1_mgmode;
extern s16 D_80118EB4_mgmode;
extern s32 D_801194CC_mgmode;
extern MgPair D_801195B0_mgmode[];
extern u8 D_801195C4_mgmode[4];
extern u8 D_801195C8_mgmode[8];
extern MgModeModelDef D_80119FA0_mgmode[];
extern HuMtx4F D_8011B4D0_mgmode;
extern s16 D_8011B620_mgmode;
extern s16 D_8011B622_mgmode;
extern s16 D_8011B788_mgmode;
extern s16 D_8011B78A_mgmode;
extern s16 D_8011B78C_mgmode;
extern s16 D_8011B78E_mgmode;
extern s16 D_8011B79A_mgmode;
extern s16 D_8011B800_mgmode;
extern s16 D_8011B884_mgmode;
extern f32 D_8011B888_mgmode;
extern s16 D_8011B950_mgmode;
extern void* D_8011B954_mgmode;
extern u8 D_8011B958_mgmode;
extern s16 D_8011B95A_mgmode;
/* A camera preset (read through D_8011B954_mgmode by 47DD90). */
typedef struct MgCamData {
    /* 0x00 */ Vec rot;
    /* 0x0C */ Vec center;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk_1C;
} MgCamData; /* size 0x20 */
extern MgCamData D_801194D0_mgmode[];

void func_80112CF4_mgmode(void);
void func_80112F98_mgmode(void);
void func_80113204_mgmode(void);
void func_801134C0_mgmode(void);
s32 func_801136EC_mgmode(void);
s32 func_80114048_mgmode(void);
void func_801141EC_mgmode(s32 pop);
void func_80114344_mgmode(void);
void func_80114404_mgmode(void);
void func_801146D8_mgmode(void);
s16 func_801149F4_mgmode(void);
s16 func_80114C80_mgmode(void);
void func_80114EBC_mgmode(void);
void func_80114FA0_mgmode(void);
void func_801152C0_mgmode(void);
void func_80115590_mgmode(void);
void func_80115848_mgmode(void);
void func_80115BE8_mgmode(void);
void func_80115C5C_mgmode(s16 n);
void func_80115E20_mgmode(void);
void func_80115E4C_mgmode(void);
void func_8011611C_mgmode(void);

/* The minigame shop: opens the coin-spend window, runs the round (or the door-opening entry from
   event 3), then loops on the two camera stops: at stop 2, A asks about playing a round (and
   plays it); at stop 3, A asks to leave through the door. */
#ifdef NON_MATCHING
/* Registers only: retail keeps the door part in s1 and its matrix in s2 (swapped here); masked 0, logic checked against the asm. */
void func_80112200_mgmode(void) {
    s16 size[2];
    s16 choice;
    s16 changed;
    s16 i;
    MgHmfPart* door;

    func_800604A8_main(size, 0x5800, 0x5813);
    D_8011B6A8_mgmode = func_80061188_main(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    func_8005FE54_main(D_8011B6A8_mgmode, 1 << D_8011B808_mgmode);
    func_8005BE30_main(D_8011B6A8_mgmode, 10);
    func_80115E4C_mgmode();
    func_8011611C_mgmode();
    D_8011B954_mgmode = D_801194D0_mgmode;
    D_8011B888_mgmode = 2500.0f;
    D_8011B622_mgmode = GwPlayer[D_8011B800_mgmode].chr;
    D_80119FA0_mgmode[8].dir = func_80017BB8_main(D_8011B622_mgmode, 0xA1);
    D_80119FA0_mgmode[9].dir = func_80017BB8_main(D_8011B622_mgmode, 0x2);
    D_80119FA0_mgmode[10].dir = func_80017BB8_main(D_8011B622_mgmode, 0x33);
    D_80119FA0_mgmode[11].dir = func_80017BB8_main(D_8011B622_mgmode, 0x3A);
    D_80119FA0_mgmode[12].dir = func_80017BB8_main(D_8011B622_mgmode, 0x2F);
    D_80119FA0_mgmode[13].dir = func_80017BB8_main(D_8011B622_mgmode, 0x37);
    D_80119FA0_mgmode[14].dir = func_80017BB8_main(D_8011B622_mgmode, 0x9B);
    func_8011667C_mgmode(D_80119FA0_mgmode);
    func_8001C8A8_main(D_8011B8A8_mgmode[4], 2);
    func_8001C8A8_main(D_8011B8A8_mgmode[8], 2);
    D_8011B620_mgmode = func_80017790_main(D_8011B8A8_mgmode[8], 1, D_8011B622_mgmode,
                                           func_80017B6C_main(D_8011B622_mgmode, 1, 0));
    func_8001C514_main(D_8011B8A8_mgmode[8]);
    func_8001C258_main(D_8011B8A8_mgmode[18], 0x180, 0);
    func_8001C448_main(D_8011B8A8_mgmode[18]);
    func_8001C514_main(D_8011B8A8_mgmode[18]);
    Hu3DModelPosSet(D_8011B8A8_mgmode[18], -208.0f, 0.0f, -332.0f);
    func_8001C8A8_main(D_8011B8A8_mgmode[15], 2);
    D_8011B624_mgmode = func_80118678_mgmode(2.0f, 400.0f, -332.0f, 50.0f);
    func_8002367C_main(D_8011B4D0_mgmode, func_8001D33C_main(D_8011B8A8_mgmode[0], "door")->mtx);
    if (omovlevtno == 3) {
        func_8001F304_main(D_8011B8A8_mgmode[4], D_8011B78A_mgmode);
        func_8001C814_main(D_8011B8A8_mgmode[4], 2, 2);
        func_80116E24_mgmode(0);
        WipeCreateIn(255, 0);
        door = func_8001D33C_main(D_8011B8A8_mgmode[0], "door");
        RepeatVibrator(D_8011B808_mgmode, 5, 0, 5);
        HuAudFXPlay(0x2EB);
        for (i = 0; i < 19; i++) {
            HuPrcVSleep();
            func_8002367C_main(door->mtx, D_8011B4D0_mgmode);
            func_80017D24_main(door->mtx, 0.0f, i * 5, 0.0f);
        }
        func_80116ED4_mgmode(1, 10, 1, MG_NO_CB);
        HuPrcSleep(5);
        func_8002367C_main(door->mtx, D_8011B4D0_mgmode);
        func_80116ED4_mgmode(2, 20, 1, MG_NO_CB);
        HuAudFXPlay(0x2A1);
    } else {
        D_8011B884_mgmode = 1;
        if (func_801136EC_mgmode() != 0) {
            func_80112F98_mgmode();
            func_80115848_mgmode();
        }
        func_80113204_mgmode();
        if (D_801194CC_mgmode != 0) {
            HuAudSeqPlay(0x4D);
        }
        func_8001F304_main(D_8011B8A8_mgmode[4], D_8011B78A_mgmode);
        func_8001C814_main(D_8011B8A8_mgmode[4], 2, 2);
        D_8011B884_mgmode = 0;
    }
    func_8011822C_mgmode(D_801195B0_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5800, -1, -1);
    func_80061388_main(D_8011B6A8_mgmode);
    while (TRUE) {
        HuPrcVSleep();
        func_8011829C_mgmode(5);
        switch (D_8011B958_mgmode) {
            case 2:
                changed = 0;
                if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
                    HuAudFXPlay(2);
                    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
                    func_801182B4_mgmode(0);
                    while (TRUE) {
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5803, -1, -1);
                        MG_WIN_WAIT(D_8011B6A8_mgmode);
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5804, -1, -1);
                        MG_WIN_WAIT(D_8011B6A8_mgmode);
                        if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) != 0) {
                            choice = -1;
                            break;
                        }
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5805, -1, -1);
                        MG_WIN_WAIT(D_8011B6A8_mgmode);
                        choice = func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0);
                        if (choice == -1) {
                            continue;
                        }
                        if (choice == 0) {
                            func_8005B43C_main(D_8011B6A8_mgmode, 0x5806, -1, -1);
                            MG_WIN_WAIT(D_8011B6A8_mgmode);
                        }
                        break;
                    }
                    if (choice != -1) {
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5807, -1, -1);
                        MG_WIN_WAIT(D_8011B6A8_mgmode);
                        func_80112CF4_mgmode();
                    }
                    func_801182B4_mgmode(1);
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5800, -1, -1);
                    func_80061388_main(D_8011B6A8_mgmode);
                } else if ((D_800C9520_main[D_8011B808_mgmode] & 0x200) ||
                           (D_800D5558_main[D_8011B808_mgmode] & 0x4000)) {
                    HuAudFXPlay(1);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_8011829C_mgmode(20);
                    func_801182A8_mgmode(1);
                    func_80116ED4_mgmode(3, 20, 1, MG_NO_CB);
                    changed = 1;
                } else if (D_800C9520_main[D_8011B808_mgmode] & 0x100) {
                    HuAudFXPlay(1);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_8011829C_mgmode(30);
                    func_801182A8_mgmode(1);
                    func_80116ED4_mgmode(5, 15, 0, MG_NO_CB);
                    func_80116ED4_mgmode(3, 15, 1, MG_NO_CB);
                    changed = 1;
                }
                if (changed) {
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5801, -1, -1);
                    func_80061388_main(D_8011B6A8_mgmode);
                }
                break;
            case 3:
                changed = 0;
                if (D_800D5558_main[D_8011B808_mgmode] & 0x8000) {
                    HuAudFXPlay(2);
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5802, -1, -1);
                    MG_WIN_WAIT(D_8011B6A8_mgmode);
                    if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) != 0) {
                        func_8005B43C_main(D_8011B6A8_mgmode, 0x5801, -1, -1);
                        MG_WIN_WAIT(D_8011B6A8_mgmode);
                        break;
                    }
                    func_801182B4_mgmode(0);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    HuPrcSleep(10);
                    door = func_8001D33C_main(D_8011B8A8_mgmode[0], "door");
                    RepeatVibrator(D_8011B808_mgmode, 5, 0, 5);
                    HuAudFXPlay(0x2EB);
                    for (i = 0; i < 19; i++) {
                        HuPrcVSleep();
                        func_8002367C_main(door->mtx, D_8011B4D0_mgmode);
                        func_80017D24_main(door->mtx, 0.0f, i * 5, 0.0f);
                    }
                    func_80116ED4_mgmode(4, 20, 1, MG_NO_CB);
                    D_80118EB1_mgmode = 1;
                    D_80118EB4_mgmode = 0x80;
                    HuAudSeqFadeOut(60);
                    while (TRUE) {
                        HuPrcVSleep();
                    }
                } else if (D_800C9520_main[D_8011B808_mgmode] & 0x100) {
                    HuAudFXPlay(1);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_8011829C_mgmode(20);
                    func_801182A8_mgmode(0);
                    func_80116ED4_mgmode(2, 20, 1, MG_NO_CB);
                    changed = 1;
                } else if (D_800C9520_main[D_8011B808_mgmode] & 0x200) {
                    HuAudFXPlay(1);
                    func_80061A5C_main(D_8011B6A8_mgmode, 0);
                    func_8011829C_mgmode(30);
                    func_801182A8_mgmode(0);
                    func_80116ED4_mgmode(5, 15, 0, MG_NO_CB);
                    func_80116ED4_mgmode(2, 15, 1, MG_NO_CB);
                    changed = 1;
                }
                if (changed) {
                    func_8005B43C_main(D_8011B6A8_mgmode, 0x5800, -1, -1);
                    func_80061388_main(D_8011B6A8_mgmode);
                }
                break;
        }
        if (HmfModelData[D_8011B8A8_mgmode[4]].unk02 != D_8011B78A_mgmode &&
            HmfModelData[D_8011B8A8_mgmode[4]].unk04 != D_8011B78A_mgmode) {
            func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B78A_mgmode, 0, 8, 2);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112200_mgmode);
#endif

/* Plays a round: the shopkeeper hops across while the curtain rises, the player walks up, picks
   the minigame and coins, and walks back. */
void func_80112CF4_mgmode(void) {
    f32 t;
    f32 r;
    s16 i;

    func_80061A5C_main(D_8011B6A8_mgmode, 0);
    func_8001C258_main(D_8011B8A8_mgmode[18], 4, 0);
    Hu3DModelScaleSet(D_8011B8A8_mgmode[18], 1.0f, 0.0f, 1.0f);
    func_80116ED4_mgmode(6, 20, 1, MG_NO_CB);
    r = 144.0f;
    Hu3DModelPosSet(D_8011B8A8_mgmode[4], -352.0f, 637.5f, -332.0f);
    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B78C_mgmode, 0, 10, 0);
    for (i = 0; i < 11; i++) {
        if (i < 6) {
            Hu3DModelScaleSet(D_8011B8A8_mgmode[18], 1.0f, sindf(i / 5.0f * 90.0f), 1.0f);
        }
        t = i / 10.0f * 90.0f;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.x = sindf(t) * r + -352.0;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.y = cosdf(t) * 200.0f + 63.75f;
        HmfModelData[D_8011B8A8_mgmode[4]].rot.y = cosdf(t) * 75.0f + 15.0f;
        HuPrcVSleep();
    }
    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
    HuAudFXPlay(0x51A);
    func_80115590_mgmode();
    func_80112F98_mgmode();
    func_80115848_mgmode();
    func_80113204_mgmode();
}

/* Starts ten coins and round 0, draws the round's minigames, picks one, takes the coins to spend
   (B asks to quit) and jumps to the minigame; never returns once it starts. */
void func_80112F98_mgmode(void) {
    s16 i;

    D_800D1FE0_main = 10;
    D_800D1F2C_main = 0;
    func_801134C0_mgmode();
    func_80115C5C_mgmode(D_800D1FE0_main);
    HuPrcVSleep();
    func_801141EC_mgmode(1);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5808, -1, -1);
    func_80061388_main(D_8011B6A8_mgmode);
    D_800CE29C_main = func_801149F4_mgmode();
    func_8005B6BC_main(D_8011B6A8_mgmode, D_800CE29C_main + 0x4700, 0);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x580A, -1, -1);
    MG_WIN_WAIT(D_8011B6A8_mgmode);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x580B, -1, -1);
    D_800CB890_main.unk04 = -1;
    do {
        D_800CB890_main.unk04 = func_80114C80_mgmode();
        if (D_800CB890_main.unk04 < 0) {
            func_8005B43C_main(D_8011B6A8_mgmode, 0x5813, -1, -1);
            MG_WIN_WAIT(D_8011B6A8_mgmode);
            if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) == 0) {
                return;
            }
            func_8005B43C_main(D_8011B6A8_mgmode, 0x580B, -1, -1);
        }
    } while (D_800CB890_main.unk04 < 0);
    D_800D1FE0_main -= D_800CB890_main.unk04;
    GwPlayer[0].gameCoin = D_800CB890_main.unk04;
    GwPlayer[0].group = 0;
    for (i = 1; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    _SetFlag(13);
    GwSystem.minigame_index = (u8)D_800CE29C_main + 1;
    omOvlHisChg(0, 0x69, 5, 0x84);
    D_80118EB1_mgmode = 1;
    D_8011B95A_mgmode = 0x70;
    D_8011B950_mgmode = 0;
    D_80118EB4_mgmode = 2;
    while (TRUE) {
        HuPrcVSleep();
    }
}

/* Ends a round: closes the panels and the minigame picture, the shopkeeper hops back and the
   curtain falls. */
void func_80113204_mgmode(void) {
    f32 t;
    f32 r;
    s16 i;

    func_80061A5C_main(D_8011B6A8_mgmode, 0);
    func_80116024_mgmode();
    func_80115BE8_mgmode();
    func_80116D4C_mgmode();
    D_801194C4_mgmode = -1;
    func_80114344_mgmode();
    func_80115E20_mgmode();
    HuAudFXPlay(0x519);
    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B78E_mgmode, 0, 8, 0);
    r = 144.0f;
    for (i = 0; i < 9; i++) {
        if (i < 6) {
            Hu3DModelScaleSet(D_8011B8A8_mgmode[18], 1.0f, cosdf(i / 5.0f * 90.0f), 1.0f);
        }
        t = i / 8.0f * 90.0f;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.x = cosdf(t) * r + -352.0;
        HmfModelData[D_8011B8A8_mgmode[4]].pos.y = sindf(t) * 100.0f + 63.75f;
        HmfModelData[D_8011B8A8_mgmode[4]].rot.y = -sindf(t) * 100.0f + 15.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(D_8011B8A8_mgmode[4], -436.0f, 0.0f, 92.0f);
    HmfModelData[D_8011B8A8_mgmode[4]].rot.y = 100.0f;
    func_8001C624_main(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 0);
    func_80116ED4_mgmode(2, 20, 1, MG_NO_CB);
    func_8001C258_main(D_8011B8A8_mgmode[18], 4, 4);
}

/* Draws the eight rounds' minigame categories: no category twice in a row, each at most
   D_801195C4[c] times, first and last different; after 100 failed draws takes D_801195C8.
   Then maps each category to its minigame (D_801195BC). */
#ifdef NON_MATCHING
/* Retail zero-extends each rand8() & 3 into the u8 category at the assignment (andi 0xff) and then uses it unextended; here the extension moves to the uses. Logic checked against the asm. */
void func_801134C0_mgmode(void) {
    u8 count[4] = { 0, 0, 0, 0 };
    s16 tries = 0;
    s16 i;
    u8 c;

    do {
        for (i = 0; i < 4; i++) {
            count[i] = 0;
        }
        i = 1;
        c = rand8() & 3;
        D_800D0418_main[0] = c;
        count[c]++;
        for (; i < 8; i++) {
            do {
                c = rand8() & 3;
            } while (D_800D0418_main[i - 1] == c);
            count[c]++;
            if (D_801195C4_mgmode[c] < count[c]) {
                break;
            }
            D_800D0418_main[i] = c;
        }
        if (i == 8 && D_800D0418_main[0] != D_800D0418_main[7]) {
            break;
        }
        tries++;
    } while (tries < 100);
    if (tries == 100) {
        for (i = 0; i < 8; i++) {
            D_800D0418_main[i] = D_801195C8_mgmode[i];
        }
    }
    for (i = 0; i < 8; i++) {
        D_800D0418_main[i] = D_801195BC_mgmode[D_800D0418_main[i]];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801134C0_mgmode);
INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/479470", D_8011A688_mgmode);
#endif

/* A round: advances the round number, shows the drawn minigame and the coin panel, adds the
   bonus coins; with no coins left asks to try again (returns 1 for yes), with 1000 or more ends
   the shop (the first time a coin block drops); otherwise picks the next minigame and the coins
   to spend and jumps to it (B asks to quit; returns 0). */
s32 func_801136EC_mgmode(void) {
    s32 choice;
    s16 first = 0;
    s16 i;

    D_800D1F2C_main++;
    D_800D1F2C_main %= 8;
    func_80116E24_mgmode(6);
    func_801141EC_mgmode(0);
    D_801194C4_mgmode = func_80116B20_mgmode();
    func_8000BCC8_main(D_801194C4_mgmode, 15);
    func_8000BC48_main(D_801194C4_mgmode, 0x5008);
    func_8000BBD4_main(D_801194C4_mgmode, 184, 132);
    func_80116C18_mgmode(D_800A6D40_main[D_800CE29C_main].pic & 0x7FF);
    func_80115E9C_mgmode(D_800CE29C_main + 0x4700, 184, 62);
    func_80115C5C_mgmode(D_800D1FE0_main);
    Hu3DModelPosSet(D_8011B8A8_mgmode[4], -208.0f, 63.75f, -332.0f);
    HmfModelData[D_8011B8A8_mgmode[4]].rot.y = 15.0f;
    func_8001C258_main(D_8011B8A8_mgmode[8], 4, 0);
    Hu3DModelPosSet(D_8011B8A8_mgmode[8], 2.0f, 0.0f, -332.0f);
    func_8001C258_main(D_8011B8A8_mgmode[17], 4, 0);
    Hu3DModelPosSet(D_8011B8A8_mgmode[17], 2.0f, 63.75f, -332.0f);
    WipeCreateIn(255, 10);
    func_8001C258_main(D_8011B8A8_mgmode[18], 4, 0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80114EBC_mgmode();
    func_8005B43C_main(D_8011B6A8_mgmode, 0x580C, -1, -1);
    func_80061388_main(D_8011B6A8_mgmode);
    func_80114404_mgmode();
    while (!(D_800D5558_main[D_8011B808_mgmode] & 0xC000)) {
        HuPrcVSleep();
    }
    if (D_800D1FE0_main <= 0) {
        func_8005B43C_main(D_8011B6A8_mgmode, 0x5811, -1, -1);
        MG_WIN_WAIT(D_8011B6A8_mgmode);
        func_8001C624_main(D_8011B8A8_mgmode[8], D_8011B79A_mgmode, 0, 4, 0);
        func_8004AC5C_main(GwPlayer[0].chr + 0x26C, 0);
        func_8005B43C_main(D_8011B6A8_mgmode, 0x5812, -1, -1);
        MG_WIN_WAIT(D_8011B6A8_mgmode);
        choice = func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0);
        func_80114614_mgmode(8);
        func_801146D8_mgmode();
        func_8001C624_main(D_8011B8A8_mgmode[8], D_8011B790_mgmode, 0, 8, 2);
        if ((s16)choice == 0) {
            func_80115E20_mgmode();
            func_80061A5C_main(D_8011B6A8_mgmode, 0);
            return 1;
        }
        goto walk_back;
    }
    if (D_800D1FE0_main >= 1000) {
        omAddPrcObj(func_801152C0_mgmode, 0x3F00, 0x800, 0);
        func_8005B43C_main(D_8011B6A8_mgmode, 0x580D, -1, -1);
        MG_WIN_WAIT(D_8011B6A8_mgmode);
        while (D_801194C8_mgmode == 0) {
            HuPrcVSleep();
        }
        D_801194C8_mgmode = 0;
        if (_CheckFlag(0x1F) != 0) {
            func_8005B6BC_main(D_8011B6A8_mgmode, GwPlayer[D_8011B800_mgmode].chr + 0x1C00, 0);
            func_8005B43C_main(D_8011B6A8_mgmode, 0x5810, -1, -1);
            MG_WIN_WAIT(D_8011B6A8_mgmode);
        } else {
            _SetFlag(0x1F);
            func_8005B43C_main(D_8011B6A8_mgmode, 0x580E, -1, -1);
            MG_WIN_WAIT(D_8011B6A8_mgmode);
            func_80114FA0_mgmode();
            func_8005B43C_main(D_8011B6A8_mgmode, 0x580F, -1, -1);
            MG_WIN_WAIT(D_8011B6A8_mgmode);
            func_8005B6BC_main(D_8011B6A8_mgmode, GwPlayer[D_8011B800_mgmode].chr + 0x1C00, 0);
            func_8005B43C_main(D_8011B6A8_mgmode, 0x5810, -1, -1);
            MG_WIN_WAIT(D_8011B6A8_mgmode);
            func_80114614_mgmode(8);
            first = 1;
        }
        func_801146D8_mgmode();
        func_80115848_mgmode();
        HuAudSeqFadeOut(60);
        D_801194CC_mgmode = 1;
        if (first) {
            func_80118CD8_mgmode();
        }
        return 0;
    }
    if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
        HuAudFXPlay(4);
        if (func_80114048_mgmode() != 0) {
            goto quit;
        }
    }
    func_8001C624_main(D_8011B8A8_mgmode[8], D_8011B790_mgmode, 0, 10, 2);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x5809, -1, -1);
    MG_WIN_WAIT(D_8011B6A8_mgmode);
    if (func_8005B68C_main(D_8011B6A8_mgmode) & 8) {
        func_80061388_main(D_8011B6A8_mgmode);
    }
    func_801146D8_mgmode();
    D_800CE29C_main = func_801149F4_mgmode();
    func_8005B6BC_main(D_8011B6A8_mgmode, D_800CE29C_main + 0x4700, 0);
    func_8005B43C_main(D_8011B6A8_mgmode, 0x580A, -1, -1);
    MG_WIN_WAIT(D_8011B6A8_mgmode);
    if (func_8005B68C_main(D_8011B6A8_mgmode) & 8) {
        func_80061388_main(D_8011B6A8_mgmode);
    }
    if (((MgTextWin*)&D_800CC69C_main[D_8011B6A8_mgmode])->btn & 0x4000) {
        HuAudFXPlay(4);
        if (func_80114048_mgmode() != 0) {
            goto quit;
        }
    }
    func_8005B43C_main(D_8011B6A8_mgmode, 0x580B, -1, -1);
    if (func_8005B68C_main(D_8011B6A8_mgmode) & 8) {
        func_80061388_main(D_8011B6A8_mgmode);
    }
    D_800CB890_main.unk04 = -1;
    do {
        D_800CB890_main.unk04 = func_80114C80_mgmode();
        if (D_800CB890_main.unk04 < 0) {
            if (func_80114048_mgmode() != 0) {
                goto quit;
            }
            func_8005B43C_main(D_8011B6A8_mgmode, 0x580B, -1, -1);
            if (func_8005B68C_main(D_8011B6A8_mgmode) & 8) {
                func_80061388_main(D_8011B6A8_mgmode);
            }
        }
    } while (D_800CB890_main.unk04 < 0);
    D_800D1FE0_main -= D_800CB890_main.unk04;
    GwPlayer[0].gameCoin = D_800CB890_main.unk04;
    GwPlayer[0].group = 0;
    for (i = 1; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    _SetFlag(13);
    GwSystem.minigame_index = (u8)D_800CE29C_main + 1;
    omOvlHisChg(0, 0x69, 5, 0x84);
    D_80118EB1_mgmode = 1;
    D_8011B95A_mgmode = 0x70;
    D_8011B950_mgmode = 0;
    D_80118EB4_mgmode = 2;
    while (TRUE) {
        HuPrcVSleep();
    }
quit:
    func_801146D8_mgmode();
    func_8001C624_main(D_8011B8A8_mgmode[8], D_8011B790_mgmode, 0, 8, 2);
walk_back:
    func_80115848_mgmode();
    return 0;
}

/* Asks to spend the coins (message 0x5813); with 11 or more coins asks again (0x5814) in a
   centred window. Returns 1 for yes. */
s32 func_80114048_mgmode(void) {
    s16 size[2];
    s16 win;
    s32 choice;
    s32 ret = 0;

    func_8005B43C_main(D_8011B6A8_mgmode, 0x5813, -1, -1);
    while (func_8005E0C0_main(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    if ((s16)func_8005E1D8_main(D_8011B6A8_mgmode, 0, 0) == 0) {
        if (D_800D1FE0_main < 11) {
            ret = 1;
        } else {
            func_80061A5C_main(D_8011B6A8_mgmode, 0);
            func_80060394_main(1, size, 0x5814);
            win = func_80061188_main(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
            func_8005FE54_main(win, 1 << D_8011B808_mgmode);
            func_80061388_main(win);
            func_8005B43C_main(win, 0x5814, -1, -1);
            while (func_8005E0C0_main(win) != 0) {
                HuPrcVSleep();
            }
            choice = func_8005E1D8_main(win, 0, 0);
            func_80061A5C_main(win, 0);
            func_8005F364_main(win);
            if ((s16)choice == 0) {
                ret = 1;
            }
        }
    }
    return ret;
}

/* Shows the coin panel, optionally popping it in. */
void func_801141EC_mgmode(s32 pop) {
    f32 t;
    f32 sx;
    f32 sy;
    s16 i;

    if (D_801194C0_mgmode == MG_SPR_NONE) {
        D_801194C0_mgmode = func_80116794_mgmode(D_8011A2C4_mgmode);
        if (pop) {
            HuAudFXPlay(0x243);
            func_80116A48_mgmode(D_801194C0_mgmode, 0, 0.0f, 0.0f);
            HuPrcSleep(5);
            for (i = 0; i < 11; i++) {
                t = i / 10.0f;
                sx = sindf(t * 90.0f);
                sy = cosdf(t * 270.0f + 90.0f);
                if (sy < 0.0f) {
                    sy = -sy;
                }
                func_80116A48_mgmode(D_801194C0_mgmode, 0, sx, sy);
                HuPrcVSleep();
            }
        }
        func_80116AEC_mgmode(D_801194C0_mgmode, 0, 20);
    }
}

void func_80114344_mgmode(void) {
    f32 s;
    s16 i;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        s = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_801194C0_mgmode, 0, s, s);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_801194C0_mgmode);
    D_801194C0_mgmode = MG_SPR_NONE;
}

/* Counts the bonus coins into the total, then plays the win or lose motion and voice. */
#ifdef NON_MATCHING
/* Masked 12: scheduling of the rate*i products and operand order of the coin sums; logic checked against the asm. */
void func_80114404_mgmode(void) {
    s16 rate = D_800CB890_main.unk04;
    s16 count = GwPlayer[0].bonusCoin;
    s16 total;
    s16 voice;
    s16 i;

    func_801169A0_mgmode(D_801194C0_mgmode, 1);
    func_80116968_mgmode(D_801194C0_mgmode, 1, 184, 46);
    func_801169A0_mgmode(D_801194C0_mgmode, 2);
    func_80116968_mgmode(D_801194C0_mgmode, 2, 184, 98);
    func_80115A9C_mgmode(184, 122, D_800D1FE0_main);
    func_80114804_mgmode(rate, 0, 0);
    func_80115BB8_mgmode(D_800D1FE0_main);
    func_80115CAC_mgmode(D_800D1FE0_main);
    HuPrcSleep(10);
    for (i = 0; i <= count; i++) {
        total = rate * i;
        func_80114804_mgmode(rate, i, total);
        func_80115BB8_mgmode(total + D_800D1FE0_main);
        func_80115CAC_mgmode(total + D_800D1FE0_main);
        HuAudFXPlay(9);
        HuPrcSleep(2);
    }
    D_800D1FE0_main += count * rate;
    if (count == 0) {
        func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B796_mgmode, 0, 8, 0);
        voice = GwPlayer[0].chr + 0x287;
    } else {
        func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B794_mgmode, 0, 8, 0);
        voice = GwPlayer[0].chr + 0x275;
    }
    func_8004AC5C_main(voice, 0);
    func_80114614_mgmode(8);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114404_mgmode);
#endif

/* Waits until model slot idx has finished its motion. */
void func_80114614_mgmode(s16 idx) {
    while (func_8001C7D0_main(D_8011B8A8_mgmode[idx]) != -1.0f ||
           HmfModelData[D_8011B8A8_mgmode[idx]].unk40 <
               D_800CCF58_main[HmfModelData[D_8011B8A8_mgmode[idx]].unk02].unk02) {
        HuPrcVSleep();
    }
}

void func_801146D8_mgmode(void) {
    f32 s;
    s16 i;
    s16 j;

    for (i = 0; i < 10; i++) {
        s = 1.0f - i / 10.0f;
        for (j = 1; j < 21; j++) {
            func_80116A48_mgmode(D_801194C0_mgmode, j, s, s);
        }
        HuPrcVSleep();
    }
    for (j = 1; j < 21; j++) {
        func_801169C8_mgmode(D_801194C0_mgmode, j);
        func_80116A48_mgmode(D_801194C0_mgmode, j, 1.0f, 1.0f);
    }
}

/* Shows "rate x count = total" with the panel's digit sprites. */
void func_80114804_mgmode(s16 rate, s16 count, s16 total) {
    s16 i;

    if (total >= 10000) {
        total = 9999;
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 3, rate, 3);
    for (i = 0; i < 3; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 3, i * 16 + 104, 70);
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 8, count, 2);
    for (i = 0; i < 2; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 8, i * 16 + 168, 70);
    }
    func_80115CDC_mgmode(D_801194C0_mgmode, 11, total, 4);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 11, i * 16 + 216, 70);
    }
    func_801169A0_mgmode(D_801194C0_mgmode, 7);
    func_80116968_mgmode(D_801194C0_mgmode, 7, 152, 70);
    func_801169A0_mgmode(D_801194C0_mgmode, 10);
    func_80116AA8_mgmode(D_801194C0_mgmode, 10, 3);
    func_80116968_mgmode(D_801194C0_mgmode, 10, 200, 70);
}

/* Fades in the minigame picture, spins through the four categories' minigames for 30 frames and
   lands on this round's; returns it. */
#ifdef NON_MATCHING
/* Same u8 extension placement as func_801134C0; logic checked against the asm. */
s16 func_801149F4_mgmode(void) {
    s16 i;
    s16 prev;
    s16 mg;
    u8 c;

    if (D_801194C4_mgmode == -1) {
        D_801194C4_mgmode = func_80116B20_mgmode();
        func_8000BCC8_main(D_801194C4_mgmode, 15);
        func_8000BC48_main(D_801194C4_mgmode, 0x5008);
        func_8000BBD4_main(D_801194C4_mgmode, 184, 132);
        for (i = 0; i < 10; i++) {
            func_8000BBFC_main(D_801194C4_mgmode, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    prev = -1;
    c = rand8() & 3;
    func_80116C18_mgmode(D_800A6D40_main[D_801195BC_mgmode[c]].pic & 0x7FF);
    func_80115E9C_mgmode(D_801195BC_mgmode[c] + 0x4700, 184, 62);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        if (c == prev) {
            do {
                c = rand8() & 3;
            } while (c == prev);
        }
        prev = c;
        func_80116024_mgmode();
        func_80116C18_mgmode(D_800A6D40_main[D_801195BC_mgmode[c]].pic & 0x7FF);
        func_80115E9C_mgmode(D_801195BC_mgmode[c] + 0x4700, 184, 62);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    mg = D_800D0418_main[D_800D1F2C_main];
    func_80116024_mgmode();
    func_80116C18_mgmode(D_800A6D40_main[mg].pic & 0x7FF);
    func_80115E9C_mgmode(mg + 0x4700, 184, 62);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return mg;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801149F4_mgmode);
#endif

/* Lets the player pick how many coins to spend (D-pad: +-10, +-1); A confirms a non-zero amount,
   B returns -1. */
#ifdef NON_MATCHING
/* 175 vs 179: retail keeps the A test as a bitwise and and recomputes n + step for the last bound check (and has an 8-byte larger frame); logic checked against the asm. */
s16 func_80114C80_mgmode(void) {
    s16 n = 0;
    s16 step;

    func_80115A9C_mgmode(184, 126, 0);
    while (TRUE) {
        HuPrcVSleep();
        if ((D_800D5558_main[D_8011B808_mgmode] >> 15) & (n != 0)) {
            HuAudFXPlay(0x247);
            break;
        }
        if (D_800D5558_main[D_8011B808_mgmode] & 0x4000) {
            HuAudFXPlay(4);
            n = -1;
            break;
        }
        if (D_800D0590_main[D_8011B808_mgmode] & 0x200) {
            step = 10;
        } else if (D_800D0590_main[D_8011B808_mgmode] & 0x100) {
            step = -10;
        } else if (D_800D0590_main[D_8011B808_mgmode] & 0x800) {
            step = 1;
        } else {
            step = -((D_800D0590_main[D_8011B808_mgmode] & 0x400) != 0);
        }
        if (step != 0) {
            HuAudFXPlay(0x246);
        }
        if (((n == D_800D1FE0_main) | (n == 100)) && step > 0) {
            n = 0;
        } else if (n + step >= 100 || n + step > D_800D1FE0_main || n + step < 0) {
            n = D_800D1FE0_main;
            if (n > 100) {
                n = 100;
            }
        } else {
            n += step;
        }
        func_80115BB8_mgmode(n);
        func_80115CAC_mgmode(D_800D1FE0_main - n);
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114C80_mgmode);
#endif

void func_80114EBC_mgmode(void) {
    s16 alpha;
    s16 i;

    for (i = 0; i < 10; i++) {
        alpha = (1.0f - i / 10.0f) * 255.0f;
        func_8000BBFC_main(D_801194C4_mgmode, alpha);
        func_801160A0_mgmode(alpha);
        HuPrcVSleep();
    }
    func_80116024_mgmode();
    func_80116D4C_mgmode();
    D_801194C4_mgmode = -1;
}

/* A coin block drops onto the player, who jumps and hits it. */
void func_80114FA0_mgmode(void) {
    s16 block = D_8011B8B8_mgmode[7];
    s16 shadow;
    s16 i;
    f32 y;
    f32 scale;

    shadow = func_8000CED8_main(0xB0004, 0x2A9);
    func_8001C8A8_main(shadow, 2);
    func_8000D018_main(shadow, 50.0f);
    func_8000CD00_main(shadow, 2.0f, 20.0f, 0.0f);
    func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B790_mgmode, 0, 8, 0);
    func_8001C258_main(block, 4, 0);
    Hu3DModelPosSet(block, 2.0f, 500.0f, -382.0f);
    func_8000CFA4_main(shadow, 2.0f, 500.0f, -332.0f);
    Hu3DModelRotSet(block, 30.0f, 80.0f, 3.0f);
    func_80088800_main(HmfModelData[block].mtx, 0.0f, 0.0f, 20.0f);
    scale = 1.0f;
    HuAudFXPlay(0x249);
    for (i = 0; i < 51; i++) {
        y = (1.0f - sindf(i / 50.0f * 90.0f)) * 400.0f + 100.0f;
        HmfModelData[block].pos.y = y;
        func_8000CFA4_main(shadow, 2.0f, y + 30.0f, -332.0f);
        if (i == 10) {
            func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B79C_mgmode, 0, 8, 0);
        }
        if (i == 40) {
            func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B794_mgmode, 0, 8, 0);
            RepeatVibrator(D_8011B808_mgmode, 20, 0, 20);
        }
        if (i >= 31) {
            scale -= 0.1f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            Hu3DModelScaleSet(block, scale, scale, scale);
        }
        HuPrcVSleep();
    }
    func_8001C258_main(block, 4, 4);
    func_8000D044_main(shadow);
}

/* Process: opens the iris mask, plays the jump, waits for D_801194C8 to clear, closes it. */
void func_801152C0_mgmode(void) {
    s16 i;

    D_801194C8_mgmode = 0;
    HuAudFXPlay(0x248);
    func_80116260_mgmode();
    HuSprAttrReset(D_8011B61E_mgmode, 0, 0x8000);
    for (i = 0; i < 31; i++) {
        if (i == 15) {
            func_80118888_mgmode(D_8011B624_mgmode);
        }
        if (i == 25) {
            func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B798_mgmode, 0, 8, 0);
            func_8004AC5C_main(GwPlayer[0].chr + 0x263, 0);
        }
        func_80055458_main(D_8011B61E_mgmode, 0, (f32)i / 30.0f * 220.0f);
        func_801162B4_mgmode(186.0f, sindf((f32)i / 30.0f * 90.0f) * 10.0f);
        HuPrcVSleep();
    }
    func_80114614_mgmode(8);
    D_801194C8_mgmode = 1;
    do {
        HuPrcVSleep();
    } while (D_801194C8_mgmode != 0);
    for (i = 0; i < 11; i++) {
        func_80055458_main(D_8011B61E_mgmode, 0, (1.0f - (f32)i / 30.0f) * 220.0f);
        HuPrcVSleep();
    }
    HuSprAttrSet(D_8011B61E_mgmode, 0, 0x8000);
    func_801188A4_mgmode(D_8011B624_mgmode);
    omDelPrcObj(NULL);
}

/* The player walks from the door to the block spot and turns to face the camera. */
#ifdef NON_MATCHING
/* 194 vs 197: float register allocation (retail keeps 15.0f/8.0f in their own callee-saved registers); logic checked against the asm. */
void func_80115590_mgmode(void) {
    s16 shadow = D_8011B8B8_mgmode[9];
    s16 player = D_8011B8B8_mgmode[0];
    s16 i;
    f32 t;
    f32 yaw;
    f32 dx;
    f32 dz;

    func_8001C258_main(player, 4, 0);
    func_8001C258_main(shadow, 4, 0);
    func_8001F304_main(player, D_8011B792_mgmode);
    func_8001C814_main(player, 2, 2);
    dx = 198.0f;
    dz = 210.0f;
    yaw = atan2df(dx, dz) + 180.0f;
    Hu3DModelPosSet(player, 200.0f, 0.0f, -122.0f);
    Hu3DModelRotSet(player, 0.0f, yaw, 0.0f);
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        Hu3DModelPosSet(player, dx * t + 2.0f, 0.0f, dz * t + -332.0f);
        func_80118624_mgmode(shadow, player);
        if (i < 12 && i % 5 == 0) {
            func_8004AC5C_main(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    func_8001C624_main(player, D_8011B790_mgmode, 0, 8, 2);
    for (i = 0; i < 9; i++) {
        HmfModelData[player].rot.y = (1.0f - i / 8.0f) * yaw;
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115590_mgmode);
#endif

/* The player turns round and walks back to the door. */
#ifdef NON_MATCHING
/* 162 vs 166: float register allocation as func_80115590; logic checked against the asm. */
void func_80115848_mgmode(void) {
    s16 shadow = D_8011B8B8_mgmode[9];
    s16 player = D_8011B8B8_mgmode[0];
    s16 i;
    f32 t;
    f32 yaw;
    f32 dx;
    f32 dz;

    func_8001C624_main(D_8011B8B8_mgmode[0], D_8011B792_mgmode, 0, 8, 2);
    dx = -198.0f;
    dz = -210.0f;
    yaw = atan2df(dx, dz) + 180.0f;
    for (i = 0; i < 9; i++) {
        HmfModelData[player].rot.y = i / 8.0f * yaw;
        HuPrcVSleep();
    }
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        Hu3DModelPosSet(player, dx * t + 200.0f, 0.0f, dz * t + -122.0f);
        func_80118624_mgmode(shadow, player);
        if (i < 12 && i % 5 == 0) {
            func_8004AC5C_main(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    func_8001C258_main(player, 4, 4);
    func_8001C258_main(shadow, 4, 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115848_mgmode);
#endif

/* Places the coin counter (label, icon, four digits) at (x, y) showing coins. */
#ifdef NON_MATCHING
/* Register allocation only (retail copies y to a second register). */
void func_80115A9C_mgmode(s32 x, s32 y, s32 coins) {
    s16 i;
    s32 left = x - 40;

    func_80116968_mgmode(D_801194C0_mgmode, 15, left, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 15);
    func_80116968_mgmode(D_801194C0_mgmode, 16, x - 24, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 16);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 17, left + (i * 16 + 32), y);
    }
    func_80115BB8_mgmode(coins);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115A9C_mgmode);
#endif

void func_80115BB8_mgmode(s16 n) {
    func_80115CDC_mgmode(D_801194C0_mgmode, 17, n, 4);
}

void func_80115BE8_mgmode(void) {
    s16 i;

    func_801169C8_mgmode(D_801194C0_mgmode, 15);
    func_801169C8_mgmode(D_801194C0_mgmode, 16);
    for (i = 0; i < 4; i++) {
        func_801169C8_mgmode(D_801194C0_mgmode, i + 17);
    }
}

void func_80115C5C_mgmode(s16 n) {
    if (D_801195D0_mgmode == MG_SPR_NONE) {
        D_801195D0_mgmode = func_80116794_mgmode(D_8011A270_mgmode);
        func_80115CAC_mgmode(n);
    }
}

void func_80115CAC_mgmode(s16 n) {
    func_80115CDC_mgmode(D_801195D0_mgmode, 2, n, 4);
}

/* Shows n (at most 9999) right-aligned in sprites first.. of list, digits wide; leading blanks
   are hidden. */
void func_80115CDC_mgmode(MgModeSpr* list, s16 first, s16 n, s16 digits) {
    char buf[8];
    s16 skip;
    s16 i;

    if (n >= 10000) {
        n = 9999;
    }
    sprintf(buf, "%4d", n);
    skip = 4 - digits;
    for (i = 0; i < digits; i++) {
        if ((u8)buf[skip + i] < '0') {
            func_801169C8_mgmode(list, first + i);
        } else {
            func_801169A0_mgmode(list, first + i);
            func_80116AA8_mgmode(list, first + i, (u8)buf[skip + i] & 0xF);
        }
    }
}

void func_80115E20_mgmode(void) {
    func_801168E0_mgmode(D_801195D0_mgmode);
    D_801195D0_mgmode = MG_SPR_NONE;
}

void func_80115E4C_mgmode(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        D_8011B810_mgmode.strSprId[i] = D_8011B810_mgmode.strGId[i] = -1;
    }
}

/* Shows message mes without its control codes as a sprite string at (x, y). */
void func_80115E9C_mgmode(s32 mes, s16 x, s16 y) {
    char* str;
    s16 len;
    s16 n;
    s16 i;

    str = func_800364DC_main((void*)mes);
    len = strlen(str);
    n = 0;
    for (i = 0; i <= len; i++) {
        if ((u8)str[i] >= '0') {
            D_8011B510_mgmode[n++] = str[i];
        }
    }
    D_8011B510_mgmode[n] = 0;
    func_800365E8_main(str);
    D_8011B810_mgmode.len = n;
    func_8003A37C_main(&D_8011B810_mgmode, D_8011B510_mgmode, 0, -1, -1);
    for (i = 0; i < D_8011B810_mgmode.len; i++) {
        HuSprPriSet(D_8011B810_mgmode.strGId[0], i + 1, 10);
        HuSprScaleSet(D_8011B810_mgmode.strGId[0], i + 1, 0.7f, 1.0f);
    }
    func_80054904_main(D_8011B810_mgmode.strGId[0], 0, x, y);
}

void func_80116024_mgmode(void) {
    s16 i;

    if (D_8011B810_mgmode.strGId[0] != -1) {
        GMesSprKill(&D_8011B810_mgmode);
        for (i = 0; i < 16; i++) {
            D_8011B810_mgmode.strSprId[i] = D_8011B810_mgmode.strGId[i] = -1;
        }
    }
}

void func_801160A0_mgmode(s16 alpha) {
    s16 i;

    for (i = 0; i < D_8011B810_mgmode.len; i++) {
        func_80055458_main(D_8011B810_mgmode.strGId[0], i + 1, alpha);
    }
}

/* Creates the full-screen iris mask sprite and its three 4-bit 320x120 frame buffers. */
void func_8011611C_mgmode(void) {
    HuSprite* spr;

    D_8011B61C_mgmode = func_8000B838_main(0x12003D);
    D_8011B61E_mgmode = HuSprGrpCreate(5, 0);
    func_80055024_main(D_8011B61E_mgmode, 0, D_8011B61C_mgmode, 0);
    HuSprAttrReset(D_8011B61E_mgmode, 0, 0xFFFF);
    HuSprAttrSet(D_8011B61E_mgmode, 0, 0x9008);
    func_80054904_main(D_8011B61E_mgmode, 0, 160, 120);
    HuSprPriSet(D_8011B61E_mgmode, 0, 15);
    HuSprScaleSet(D_8011B61E_mgmode, 0, 1.0f, 2.0f);
    spr = HuSprGet(D_8011B61E_mgmode, 0);
    HuMemFree(spr->unk_84->unk00->unk00);
    D_8011B610_mgmode[0] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[1] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[2] = HuMemAllocTag(0x4B00, 0x7918);
    spr->unk_84->unk00->unk00 = D_8011B610_mgmode[0];
    func_80116260_mgmode();
}

void func_80116260_mgmode(void) {
    memset(D_8011B610_mgmode[0], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[1], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[2], 0xFF, 0x4B00);
}

#define MG_PIX_CLR(p, x) (*(p) = ((x) & 1) ? (*(p) & 0xF0) : (*(p) & 0xF))
#define MG_PIX_SET(p, x, c) (*(p) = ((x) & 1) ? (*(p) | (c)) : (*(p) | ((c) << 4)))

/* Draws the iris mask into this frame's buffer: a wedge centred on cx, open by angle, with a
   two-pixel rim. */
#ifdef NON_MATCHING
/* 215 vs 235: the nibble ternaries compile to more branches than retail; logic checked against the asm. */
void func_801162B4_mgmode(f32 cx, f32 angle) {
    u8* p = D_8011B610_mgmode[D_800D2008_main];
    u8* q;
    f32 s = sindf(angle);
    f32 w;
    s16 l;
    s16 r;
    s16 x;
    s16 y;

    for (y = 0; y < 120; y++) {
        w = s * (y + 100);
        l = cx - w;
        r = cx + w;
        for (x = 0; x < 320; x++) {
            if ((l < x) & (x < r)) {
                MG_PIX_CLR(p, x);
            } else {
                MG_PIX_SET(p, x, 0xF);
            }
            p += x & 1;
        }
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + l - 1) / 2];
        MG_PIX_CLR(q, l - 1);
        MG_PIX_SET(q, l - 1, 0xA);
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + r + 1) / 2];
        MG_PIX_CLR(q, r + 1);
        MG_PIX_SET(q, r + 1, 0xA);
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + l) / 2];
        MG_PIX_CLR(q, l);
        MG_PIX_SET(q, l, 4);
        q = &D_8011B610_mgmode[D_800D2008_main][(y * 320 + r) / 2];
        MG_PIX_CLR(q, r);
        MG_PIX_SET(q, r, 4);
    }
    HuSprGet(D_8011B61E_mgmode, 0)->unk_84->unk00->unk00 = D_8011B610_mgmode[D_800D2008_main];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801162B4_mgmode);
#endif

/* .data (0x801194C0) */
MgModeSpr* D_801194C0_mgmode = (MgModeSpr*)-1;
s16 D_801194C4_mgmode = -1;
s32 D_801194C8_mgmode = 0;
s32 D_801194CC_mgmode = 0;
MgCamData D_801194D0_mgmode[7] = {
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 87.0f, -395.0f }, 1490.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 87.0f, -395.0f }, 960.0f, 40.0f },
    { { 10.0f, 88.0f, 0.0f }, { -395.6f, 126.8f, 0.9f }, 440.0f, 40.0f },
    { { 6.0f, 180.0f, 0.0f }, { 1.6f, 98.0f, 717.7f }, 360.0f, 40.0f },
    { { 0.0f, 184.0f, 0.0f }, { 11.7f, 90.9f, 978.7f }, 120.0f, 40.0f },
    { { 8.0f, 356.0f, 0.0f }, { 38.7f, 126.8f, -118.8f }, 610.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { -41.0f, 202.8f, -80.4f }, 320.0f, 40.0f },
};
MgPair D_801195B0_mgmode[3] = { { 97, 142 }, { 160, 120 }, { -1, -1 } };
s16 D_801195BC_mgmode[4] = { 66, 67, 68, 69 };
u8 D_801195C4_mgmode[4] = { 2, 1, 3, 2 };
u8 D_801195C8_mgmode[8] = { 2, 0, 3, 2, 3, 1, 2, 0 };
MgModeSpr* D_801195D0_mgmode = (MgModeSpr*)-1;
