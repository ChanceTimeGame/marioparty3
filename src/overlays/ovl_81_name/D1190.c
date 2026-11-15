#include "common.h"
#include "ovl_81.h"
#include "game/board.h"

// duel n5: space images, the space table and its events (party mode's FA250.c tail, for two players)
#define MBD_SPACE_TYPES 19

extern SpaceData* D_801050A4_name_81;
extern LinkData* D_801050A8_name_81;

extern u16 D_801050A0_name_81; // total spaces
extern u16 D_801050A2_name_81; // total links
extern u8* D_801050B0_name_81[MBD_SPACE_TYPES]; // space images
extern s16 D_801050FC_name_81;
extern u16 D_801050FE_name_81; // spaces drawn
extern u8 D_80105100_name_81[MBD_SPACE_TYPES];
extern event_list_entry* D_80105114_name_81;
extern event_list_entry* D_80105118_name_81;
extern event_list_entry* D_8010511C_name_81;
extern event_list_entry* D_80105120_name_81;
extern s32 D_80105124_name_81;
extern f32 D_80105128_name_81[8];
extern s32 D_80105148_name_81;
extern s16 D_80105150_name_81[];
extern s16 D_8010534E_name_81;
extern s16 D_80105350_name_81[];
extern s16 D_80105370_name_81;
extern s32 D_80105378_name_81[MBD_SPACE_TYPES];
extern s16 D_801053C8_name_81[];
extern void* D_80101060_name_81; // board space file
extern u8 (*D_80101064_name_81)[SPACES_MAX]; // space ids by type
extern s32 D_80101068_name_81[MBD_SPACE_TYPES];
extern s32 D_801010B4_name_81[MBD_SPACE_TYPES];
extern Gfx D_80101140_name_81[];
extern u8 D_101100[];
extern s16 MTXBufNum;
extern Mtx* MTXBuf;

void func_80017CD0_main(Mtx*, f32, f32, f32);
void func_80089980_main(Mtx*, Mtx*);
f32 MBDBackMdlScaleGet(void);
void MBDCameraPos3DGet(Vec2f* arg0);
void func_800ECD0C_name_81(s16, s16, s16);
SpaceData* MBDMasuGet(s16 spaceIdx);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
s16 MBDMasuLinkNumGet(u16 linkIdx);
void func_800EA698_name_81(s16 arg0);
s16 func_800EA6A4_name_81(void);
void func_800EA1FC_name_81(s16 arg0, u16 arg1);

void func_800E93C0_name_81(s16 arg0) {
    s32 *tbl;
    s32 i;

    D_801050FC_name_81 = arg0;
    if (GwSystem.current_board_index == 5) {
        tbl = D_801010B4_name_81;
    } else {
        tbl = D_80101068_name_81;
    }
    for (i = 0; i < MBD_SPACE_TYPES; i++) {
        if (tbl[i] != 0) {
            D_801050B0_name_81[i] = DataRead(tbl[i]);
        } else {
            D_801050B0_name_81[i] = NULL;
        }
    }
}

void func_800E9468_name_81(void) {
    s32 i;

    for (i = 0; i < MBD_SPACE_TYPES; i++) {
        if (D_801050B0_name_81[i] != NULL) {
            DataClose(D_801050B0_name_81[i]);
        }
        D_801050B0_name_81[i] = NULL;
    }
}

void func_800E94D0_name_81(void) {
    s32 i;

    func_800E93C0_name_81(0);
    D_80101060_name_81 = NULL;
    D_80105148_name_81 = 0;
    for (i = 0; i < MBD_SPACE_TYPES; i++) {
        D_80105378_name_81[i] = 0;
    }
}

void func_800E9524_name_81(void) {
    D_80105148_name_81 = 0;
}

void func_800E9530_name_81(f32 arg0) {
    if (D_80105148_name_81 != 8) {
        D_80105128_name_81[D_80105148_name_81++] = arg0;
    }
}

void func_800E9564_name_81(void) {
    func_800E9468_name_81();
}

void func_800E9580_name_81(s16 arg0) {
    func_800E9468_name_81();
    func_800E93C0_name_81(arg0);
}

void func_800E95B0_name_81(s32 arg0, s16 arg1) {
    D_801053C8_name_81[arg0] = arg1;
}

void func_800E95C4_name_81(Gfx** gfxPos, Mtx* arg1, s32 arg2) {
    Mtx sp10;
    Vec2f sp50;
    s16 sp5E;
    SpaceData* space;
    Mtx* mtx;
    u8* vtx;
    s32 i, j;

    if (!(arg2 & 0xFF) && (D_801050FE_name_81 != 0) && (D_80101064_name_81 != NULL)) {
        sp5E = func_8004D6AC_main(0xC8, 0xC8, 0xC8);
        gSPDisplayList((*gfxPos)++, D_80101140_name_81);
        func_80012640_main(0, gfxPos);
        func_800127C4_main(0, gfxPos);
        MBDCameraPos3DGet(&sp50);
        vtx = D_101100;
        for (i = 0; i < MBD_SPACE_TYPES; i++) {
            if (D_801050B0_name_81[i] != NULL) {
                // +4: palette colour count, +0x10: palette then texels
                if (((u32 *)D_801050B0_name_81[i])[1] <= 16) {
                    gDPLoadTLUT_pal16((*gfxPos)++, 0, D_801050B0_name_81[i] + 0x10);
                    gDPLoadTextureBlock_4b((*gfxPos)++,
                                           D_801050B0_name_81[i] + 0x10 + ((((u32 *)D_801050B0_name_81[i])[1] + 3) >> 2) * 8,
                                           G_IM_FMT_CI, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                } else {
                    gDPLoadTLUT_pal256((*gfxPos)++, D_801050B0_name_81[i] + 0x10);
                    gDPLoadTextureBlock((*gfxPos)++,
                                        D_801050B0_name_81[i] + 0x10 + ((((u32 *)D_801050B0_name_81[i])[1] + 3) >> 2) * 8,
                                        G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                }
                for (j = 0; j < D_801050A0_name_81; j++) {
                    s32 spaceId = D_80101064_name_81[i][j];
                    if (spaceId == 0xFF) {
                        break;
                    }
                    space = MBDMasuGet(spaceId);
                    func_80089980_main(&sp10, &arg1[1]);
                    func_80017C10_main(&sp10, space->coords.x, space->coords.y, space->coords.z);
                    func_80017CD0_main(&sp10, space->rot.x * 0.8f, 1.0f, space->rot.z * 0.8f);
                    mtx = &MTXBuf[MTXBufNum++];
                    func_800898F0_main(&sp10, mtx);
                    gSPMatrix((*gfxPos)++, OS_K0_TO_PHYSICAL(mtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex((*gfxPos)++, vtx, 4, 0);
                    gSP1Quadrangle((*gfxPos)++, 0, 1, 2, 3, 0);
                }
            }
        }
        func_8004D6E8_main(sp5E);
    }
}

u16* func_800E9B00_name_81(u16* base, s32 offset) {
    return (u16*)((u8*)base + *(u16*)((u8*)base + offset));
}

s32 func_800E9B10_name_81(s32 arg0, s16 arg1) {
    f32 sp10[3];
    SpaceData* space;
    LinkData* link;
    u16* src;
    u16* links;
    s16* dst;
    s32 i;
    s32 j;

    D_80101060_name_81 = DataRead((arg0 << 0x10) | arg1);
    if (D_80101060_name_81 != NULL) {
        D_80105114_name_81 = NULL;
        D_80105118_name_81 = NULL;
        D_8010511C_name_81 = NULL;
        D_80105120_name_81 = NULL;
        src = D_80101060_name_81;
        D_801050A0_name_81 = src[0];
        D_801050A2_name_81 = src[1];
        D_801050A4_name_81 = HuMemMemoryAllocTemp(D_801050A0_name_81 * sizeof(SpaceData));
        src = func_800E9B00_name_81(D_80101060_name_81, 4);
        space = D_801050A4_name_81;
        for (i = 0; i < D_801050A0_name_81; i++) {
            space->unk_00 = 1;
            space->unk_02 = *src++;
            space->space_type = *src++;
            sp10[0] = space->coords.x = ((f32*)src)[0] * 5.0f * MBDBackMdlScaleGet();
            sp10[1] = space->coords.y = ((f32*)src)[1] * 5.0f * MBDBackMdlScaleGet();
            sp10[2] = space->coords.z = ((f32*)src)[2] * 5.0f * MBDBackMdlScaleGet();
            src += 6;
            space->rot.x = MBDBackMdlScaleGet();
            space->rot.y = MBDBackMdlScaleGet();
            space->rot.z = MBDBackMdlScaleGet();
            space->event_list = NULL;
            space++;
        }
        (void)sp10;
        D_801050A8_name_81 = HuMemMemoryAllocTemp(D_801050A2_name_81 * sizeof(LinkData));
        links = func_800E9B00_name_81(D_80101060_name_81, 6);
        link = D_801050A8_name_81;
        for (i = 0; i < D_801050A2_name_81; i++) {
            src = func_800E9B00_name_81(links, i * 2);
            link->chainIndicies = *src++;
            link->spaces = HuMemMemoryAllocTemp(link->chainIndicies * sizeof(s16));
            dst = link->spaces;
            for (j = 0; j < link->chainIndicies; j++) {
                *dst++ = *src++;
            }
            link++;
        }
        DataClose(D_80101060_name_81);
        func_8001F95C_main(1, &func_800E95C4_name_81);
        D_801050FE_name_81 = 1;
    }
    D_8010534E_name_81 = 0;
    D_80105370_name_81 = 0;
    return 0;
}

void func_800E9D9C_name_81(void) {
    LinkData* link;
    s32 i;

    if (D_80101060_name_81 != NULL) {
        D_80101060_name_81 = NULL;
        D_801050FE_name_81 = 0;
        HuMemMemoryFreeTemp(D_801050A4_name_81);
        link = D_801050A8_name_81;
        for (i = 0; i < D_801050A2_name_81; i++, link++) {
            HuMemMemoryFreeTemp(link->spaces);
        }
        HuMemMemoryFreeTemp(D_801050A8_name_81);
        func_8001F95C_main(1, NULL);
    }
    if (D_80101064_name_81 != NULL) {
        HuMemMemoryFreeTemp(D_80101064_name_81);
        D_80101064_name_81 = NULL;
    }
}

SpaceData* MBDMasuGet(s16 spaceIdx) {
    return &D_801050A4_name_81[spaceIdx];
}

s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx) {
    return D_801050A8_name_81[linkIdx].spaces[spaceIdx];
}

s16 MBDMasuLinkNumGet(u16 linkIdx) {
    return D_801050A8_name_81[linkIdx].chainIndicies;
}

s16 func_800E9ECC_name_81(s16 arg0, s16 arg1) {
    s32 i;

    for (i = 0; i < MBDMasuLinkNumGet(arg1); i++) {
        if (MBDMasuLinkMasuIdGet(arg1, i) == arg0) {
            return i;
        }
    }
    return -1;
}

void func_800E9F4C_name_81(s16 arg0, s8* chainOut, s8* linkOut) {
    s32 chain;
    s32 link;

    for (chain = 0; chain < D_801050A2_name_81; chain++) {
        for (link = 0; link < MBDMasuLinkNumGet(chain); link++) {
            if (MBDMasuLinkMasuIdGet(chain, link) == arg0) {
                *chainOut = chain;
                *linkOut = link;
                return;
            }
        }
    }
}

s32 func_800EA010_name_81(s16 arg0, s8* arg1, s8* arg2) {
    s16 link;
    s32 i;

    for (i = 0; i < D_801050A2_name_81; i++) {
        if (*arg1 == i) {
            continue;
        }
        link = func_800E9ECC_name_81(arg0, i);
        if (link != -1) {
            *arg1 = i;
            *arg2 = link;
            return 0;
        }
    }
    return -1;
}

void func_800EA0C0_name_81(void) {
    LinkData* chain;
    s16* space;
    s16 i;
    s16 j;
    s16 k;

    chain = D_801050A8_name_81;
    for (i = 0; i < D_801050A2_name_81; i++) {
        space = chain->spaces;
        for (j = 0; j < chain->chainIndicies; j++) {
            if (MBDMasuGet(*space)->space_type == 9) {
                for (k = 0; k < 2; k++) {
                    func_800ECD0C_name_81(k, i, j);
                }
                return;
            }
            space++;
        }
        chain++;
    }
    for (k = 0; k < 2; k++) {
        func_800ECD0C_name_81(k, 0, 0);
    }
}

void func_800EA1FC_name_81(s16 spaceIdx, u16 newSpaceType) {
    MBDMasuGet(spaceIdx)->space_type = newSpaceType;
}

void func_800EA22C_name_81(u16 linkNo, u16 curSpaceType, u8 newSpaceType) {
    s32 linkSpaceCount;
    SpaceData* space;
    s32 i;

    linkSpaceCount = MBDMasuLinkNumGet(linkNo);
    for (i = 0; i < linkSpaceCount; i++) {
        space = MBDMasuGet(MBDMasuLinkMasuIdGet(linkNo, i));
        if (space->space_type == curSpaceType) {
            space->space_type = newSpaceType;
        }
    }
}

void func_800EA2C8_name_81(void) {
    SpaceData* space;
    f32 base;
    f32 scale;
    Process* proc = HuPrcCurrentGet();

    space = MBDMasuGet((s16)(s32)proc->user_data);
    base = space->rot.x;
    scale = base + 0.03f;
    if (D_80101060_name_81 != NULL) {
        while (1) {
            HuPrcVSleep();
            scale -= 0.005f;
            if (scale <= base) {
                scale = base;
            }
            space->rot.x = scale;
            space->rot.z = scale;
            if ((scale <= base) || (D_80101060_name_81 == NULL)) {
                break;
            }
        }
    }
    omDelPrcObj(NULL);
}

void func_800EA388_name_81(s16 arg0) {
    omAddPrcObj(func_800EA2C8_name_81, 0xEF00, 0, 0)->user_data = (void*)(s32)arg0;
}

void func_800EA3CC_name_81(s16 arg0, event_list_entry* arg1) {
    switch (arg0) {
        case -2:
            D_80105114_name_81 = arg1;
            break;
        case -3:
            D_80105118_name_81 = arg1;
            break;
        case -4:
            D_8010511C_name_81 = arg1;
            break;
        case -5:
            D_80105120_name_81 = arg1;
            break;
        default:
            MBDMasuGet(arg0)->event_list = arg1;
            break;
    }
}

void func_800EA46C_name_81(event_table_entry* arg0) {
    event_table_entry* entry;

    for (entry = arg0; entry->space_index != -1; entry++) {
        func_800EA3CC_name_81(entry->space_index, entry->event_list);
    }
}

s32 func_800EA4D4_name_81(s16 arg0, s16 arg1) {
    event_list_entry* entry;
    Process* proc;
    s16 prevSpace;
    s32 ret;

    switch (arg0) {
        case -2: entry = D_80105114_name_81; break;
        case -3: entry = D_80105118_name_81; break;
        case -4: entry = D_8010511C_name_81; break;
        case -5: entry = D_80105120_name_81; break;
        default: entry = MBDMasuGet(arg0)->event_list; break;
    }

    ret = 0;
    prevSpace = func_800EA6A4_name_81();
    func_800EA698_name_81(arg0);
    if (entry != NULL) {
        while (entry->activation_type != 0) {
            if (entry->activation_type == arg1) {
                D_80105124_name_81 = 0;
                switch (entry->execution_type) {
                    case 1:
                        entry->event_fn();
                        break;
                    case 2:
                        proc = HuPrcCurrentGet();
                        HuPrcChildLink(proc, omAddPrcObj(entry->event_fn, 0x4800, 0, 0));
                        HuPrcChildWait();
                        break;
                }
                ret |= D_80105124_name_81;
            }
            entry++;
        }
    }
    func_800EA698_name_81(prevSpace);
    return ret;
}

void func_800EA68C_name_81(s32 arg0) {
    D_80105124_name_81 = arg0;
}

void func_800EA698_name_81(s16 arg0) {
    GwSystem.current_space_index = arg0;
}

s16 func_800EA6A4_name_81(void) {
    return GwSystem.current_space_index;
}

void func_800EA6B0_name_81(s16* arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        D_80105150_name_81[i] = *arg0++;
    }
    D_8010534E_name_81 = i;
}

void func_800EA708_name_81(s16* arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        D_80105350_name_81[i] = *arg0++;
    }
    D_80105370_name_81 = i;
}

// GwSystem.unk_17[0..18]: space ids; unk_17[19..37]: owner player + 1 (0 = free)
#define MBD_OWN_MASU(i) (((u8*)GwSystem.unk_17)[i])
#define MBD_OWN_PLAYER(i) (GwSystem.unk_17[19 + (i)])
void func_800EA760_name_81(void) {
    s32 i;

    for (i = 0; i < 19; i++) {
        MBD_OWN_PLAYER(i) = 0;
    }
}

void func_800EA788_name_81(s8 spaceIdx, s32 player) {
    s32 i;

    for (i = 0; i < 19; i++) {
        if (MBD_OWN_PLAYER(i) == 0) {
            MBD_OWN_MASU(i) = spaceIdx;
            MBD_OWN_PLAYER(i) = player + 1;
            return;
        }
    }
}

void func_800EA7D4_name_81(void) {
    s32 i;

    for (i = 0; i < 19; i++) {
        if (MBD_OWN_PLAYER(i) != 0) {
            func_800EA1FC_name_81(MBD_OWN_MASU(i), GwPlayer[MBD_OWN_PLAYER(i) - 1].chr + 11);
        }
    }
}

s32 func_800EA848_name_81(s16 spaceIdx) {
    s32 i;

    for (i = 0; i < 19; i++) {
        if (MBD_OWN_PLAYER(i) != 0 && MBD_OWN_MASU(i) == spaceIdx) {
            return MBD_OWN_PLAYER(i) - 1;
        }
    }
    return -1;
}

void func_800EA898_name_81(s32 oldPlayer, s32 newPlayer) {
    s32 i;

    for (i = 0; i < 19; i++) {
        if (MBD_OWN_PLAYER(i) - 1 == oldPlayer) {
            MBD_OWN_PLAYER(i) = newPlayer + 1;
        }
    }
}

void func_800EA8DC_name_81(void) {
    s32 i;

    for (i = 0; i < 19; i++) {
        if (MBD_OWN_PLAYER(i) != 0) {
            func_800EA1FC_name_81(MBD_OWN_MASU(i), 6);
            MBD_OWN_PLAYER(i) = 0;
        }
    }
}

s32 func_800EA940_name_81(s32 player) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 19; i++) {
        count += MBD_OWN_PLAYER(i) == player + 1;
    }
    return count;
}

void func_800EA97C_name_81(void) {
    s32 count;
    s32 i, j;

    if (D_80101064_name_81 != NULL) {
        HuMemMemoryFreeTemp(D_80101064_name_81);
    }
    D_80101064_name_81 = HuMemMemoryAllocTemp(MBD_SPACE_TYPES * SPACES_MAX);
    for (i = 0; i < MBD_SPACE_TYPES; i++) {
        count = 0;
        for (j = 0; j < D_801050A0_name_81; j++) {
            if (MBDMasuGet(j)->space_type == i) {
                D_80101064_name_81[i][count] = j;
                count++;
            }
        }
        D_80101064_name_81[i][count] = 0xFF;
        D_80105100_name_81[i] = count;
    }
}

s32 func_800EAA7C_name_81(s32 spaceType) {
    s32 i;
    s32 count = 0;

    for (i = 0; i < D_801050A0_name_81; i++) {
        count += MBDMasuGet(i)->space_type == spaceType;
    }
    return count;
}

u8 func_800EAAF8_name_81(s32 arg0, s32 arg1) {
    return D_80101064_name_81[arg0][arg1];
}
