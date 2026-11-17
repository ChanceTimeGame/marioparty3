#include "mstory2.h"

/* unreferenced: each scene file's .rodata starts with this Vec */
const Vec D_8011BE68_mstory2 = { -120.0f, 0.0f, 480.0f };

ObPath *func_80107B90_mstory2(Vec *points, s16 flags) {
    ObPath *path;
    Vec *prev;
    Vec *cur;
    ObPathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(ObPath), 0x7918);
    path->flags = flags;
    path->points = points;
    prev = points;
    cur = prev + 1;
    total = 0.0f;
    n = 0;
    while (cur->x != 9999.0f || cur->y != 9999.0f || cur->z != 9999.0f) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
        n++;
        cur++;
        prev++;
    }
    if (flags & 1) {
        dx = points->x - prev->x;
        dy = points->y - prev->y;
        dz = points->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    n++;
    path->count = n;
    seg = HuMemAllocTag(n * sizeof(ObPathSeg), 0x7918);
    path->segs = seg;
    prev = points;
    cur = prev + 1;
    pos = 0.0f;
    for (i = 0; i < n; i++, prev++, cur++, seg++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        if ((flags & 1) && i == n - 1) {
            dx = points->x - prev->x;
            dy = points->y - prev->y;
            dz = points->z - prev->z;
        }
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        seg->start = pos / total;
        seg->end = (pos + len) / total;
        if (seg->end > 1.0f) {
            seg->end = 1.0001f;
        }
        pos += len;
    }
    return path;
}

#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_80107E94_mstory2(ObPath *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    ObPathSeg *segs;
    Vec *pts;
    s16 i;

    if (t >= 1.0f) {
        out->x = path->points[path->count - 1].x;
        out->y = path->points[path->count - 1].y;
        out->z = path->points[path->count - 1].z;
        return;
    }
    for (i = 0, segs = path->segs; i < path->count; i++, segs++) {
        if (t <= segs->start) {
            break;
        }
    }
    i--;
    i = (i < 0) ? 0 : i;
    if (i >= path->count - 1) {
        i--;
    }
    segs = path->segs;
    if (path->flags & 1) {
        times[0] = (i == 0) ? -(1.0f - segs[path->count - 1].start) : segs[i - 1].start;
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[path->count - 1].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[0].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[0].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[0].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].z : pts[i + 2].z;
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = segs[i - 1].start;
        }
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[0].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].z : pts[i + 2].z;
    }
    out->z = func_80018ACC_main(p, times, t);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49DF30", func_80107E94_mstory2);
#endif

void func_8010873C_mstory2(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

// register residue only: retail keeps the partner in v0, KMC picks a0 (masked 0)
#ifdef NON_MATCHING
/* story step 1 (chapter 2): the scene's processes */
void func_8010876C_mstory2(void) {
    s16 partner;

    D_8011C75C_mstory2 = GwStory.unk1;
    partner = 4;
    if (D_8011C75C_mstory2 == 4) {
        partner = 1;
    }
    D_8011C75E_mstory2 = partner;
    func_80105FBC_mstory2();
    D_8011C75A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80109D04_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010AC1C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B7B8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C038_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C398_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80108A3C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C1E4_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801088A4_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C75A_mstory2, 4, 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49DF30", func_8010876C_mstory2);
#endif

void func_8010889C_mstory2(omObjData *obj) {
}

/* footstep sounds of actors 0 and 1 (actor 1's panned by its depth) on their walk loop's frame 0 */
void func_801088A4_mstory2(void) {
    s16 se;
    s8 pan;

    while (TRUE) {
        if (D_8011C680_mstory2[0].sfxOn == 1 && HmfModelData[D_8011C680_mstory2[0].obj->model[1]].unk40 == 0.0f) {
            CharFXPlay(D_8011C680_mstory2[0].sfxId, D_8011C75C_mstory2);
        }
        if (D_8011C680_mstory2[1].sfxOn == 1 && HmfModelData[D_8011C680_mstory2[1].obj->model[1]].unk40 == 0.0f) {
            se = CharFXPlay(D_8011C680_mstory2[1].sfxId, D_8011C75E_mstory2);
            if (HmfModelData[D_8011C680_mstory2[1].obj->model[1]].pos.z <= 0.0f) {
                pan = HmfModelData[D_8011C680_mstory2[1].obj->model[1]].pos.z / 15.0f + 127.0f;
            } else {
                pan = 127;
            }
            func_8004AAD0_main(se, pan);
        }
        HuPrcVSleep();
    }
}

void func_80108A3C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C680_mstory2[5].obj = obj;
    D_8011C680_mstory2[5].flags = 0;
    D_8011C680_mstory2[5].func = func_80108AB0_mstory2;
    while (TRUE) {
        D_8011C680_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

void func_80108AB0_mstory2(omObjData *unused) {
    StoryRot4 rot = D_8011BEB0_mstory2;

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &rot.v[0], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &rot.v[1], 10);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[1]].unk02, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C75C_mstory2 != 4) {
        func_8010614C_mstory2(0x5A0F);
    } else {
        func_801060F8_mstory2(0x5B00);
    }
    func_801060D4_mstory2();
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[0]].unk02, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &rot.v[2], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &rot.v[3], 10);
    D_8011C680_mstory2[5].func = func_80108C40_mstory2;
}

/* actor 5's main script for chapter 2: the hook item flies in and catches actor 0's model, the
   characters talk and walk, then the item flies off again and the scene ends */
void func_80108C40_mstory2(omObjData *unused) {
    s16 i = 0;
    Vec pos;
    ObPath *path[2];
    StoryTargets targets = D_8011BEE0_mstory2;
    s16 j;
    s16 k;
    f32 t;
    s32 wait;

    func_8001C258_main(D_8011C680_mstory2[4].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[2], 4, 0);
    func_800138EC_main(D_8011C680_mstory2[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    path[0] = func_80107B90_mstory2(D_8011B950_mstory2, 0);
    for (j = 0; j < 40.0f; j++) {
        if (j == 30) {
            func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[9]].unk02, 0, 10, 2);
        }
        t = j * 0.025f;
        func_80107E94_mstory2(path[0], t * t, &pos);
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010873C_mstory2(path[0]);
    D_8011C680_mstory2[0].func = func_8010A298_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[0].flags == 1) {
            pos.x -= 0.19999999f;
            pos.y -= 2.0f;
            pos.z += 1.0f;
            Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
            func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
            if (i++ == 30.0f) {
                i = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    func_8004AAD0_main(CharFXPlay(0x2BD, D_8011C75E_mstory2), 0x50);
    if (D_8011C75C_mstory2 != 4) {
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A11);
        func_801060D4_mstory2();
    } else {
        HuPrcSleep(30);
    }
    func_8001C258_main(D_8011C680_mstory2[1].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C680_mstory2[1].obj->model[2], 4, 0);
    func_8010622C_mstory2();
    HuPrcSleep(10);
    D_8011C680_mstory2[0].func = func_8010A3B4_mstory2;
    D_8011C680_mstory2[2].func = func_8010BACC_mstory2;
    while (TRUE) {
        pos.x += 1.0f;
        pos.y += 10.0f;
        pos.z -= 5.0f;
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        if (i++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011B980_mstory2[0].x = pos.x;
    D_8011B980_mstory2[0].y = pos.y;
    D_8011B980_mstory2[0].z = pos.z;
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &D_8011B9C8_mstory2, 5);
    D_8011C680_mstory2[3].func = func_8010C328_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[2].flags == 5) {
            break;
        }
        HuPrcVSleep();
    }
    func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
    HuPrcSleep(30);
    D_8011C680_mstory2[1].sfxOn = 1;
    D_8011C680_mstory2[1].sfxId = 0x28;
    func_8001C92C_main(D_8011C680_mstory2[0].obj->model[1], 0.25f);
    func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[10]].unk02, 0, 10, 2);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[2]].unk02, 0, 10, 2);
    func_80107824_mstory2(D_8011C680_mstory2[1].obj, &targets.v[0], 180, 1);
    D_8011C680_mstory2[1].sfxOn = 0;
    func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C92C_main(D_8011C680_mstory2[0].obj->model[1], 1.0f);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[3]].unk02, 0, 10, 2);
    HuPrcSleep(60);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011B9D4_mstory2, 5);
    if (D_8011C75C_mstory2 != 4) {
        D_8011C680_mstory2[1].func = func_8010B688_mstory2;
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A12);
        func_801060D4_mstory2();
        func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
        D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    } else {
        for (j = 0; j < 2; j++) {
            func_80106E48_mstory2(D_8011C680_mstory2[2].obj, &targets.v[3], 15, 0);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
            func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011BA1C_mstory2, 10);
            func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
            HuPrcSleep(10);
            func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[2]].unk02, 0, 10, 2);
            func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
            if (j == 0) {
                func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
                func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
            }
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[0]].unk02, 0, 10, 2);
            D_8011C680_mstory2[2].func = func_8010889C_mstory2;
            func_80106E2C_mstory2(D_8011C680_mstory2[2].obj, &targets.v[4], 8);
            func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &D_8011B9E0_mstory2[0], 10);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
            func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011B9D4_mstory2, 5);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
            D_8011C680_mstory2[3].func = func_8010889C_mstory2;
            D_8011C680_mstory2[0].func = func_8010889C_mstory2;
            func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &D_8011BA28_mstory2, 5);
            func_801070D8_mstory2(D_8011C680_mstory2[0].obj, &D_8011BA34_mstory2, 5);
            func_801060A4_mstory2();
            D_8011C680_mstory2[1].func = func_8010B738_mstory2;
            func_801060F8_mstory2(j + 0x5B01);
            func_801060D4_mstory2();
            func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[8]].unk02, 0, 10, 0);
            func_801072AC_mstory2(D_8011C680_mstory2[0].obj->model[1]);
        }
    }
    func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
    func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
    D_8011C680_mstory2[1].func = func_8010B110_mstory2;
    D_8011C680_mstory2[2].func = func_8010BD04_mstory2;
    D_8011C680_mstory2[3].func = func_8010C348_mstory2;
    path[1] = func_80107B90_mstory2(D_8011B980_mstory2, 0);
    for (k = 0; k < 50.0f; k++) {
        t = k * 0.02f;
        func_80107E94_mstory2(path[1], t * t, &pos);
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010873C_mstory2(path[1]);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[1], 4, 4);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[2], 4, 4);
    func_800138EC_main(D_8011C680_mstory2[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[2]);
    func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[1]].unk02, 0, 10, 2);
    if (D_8011C75C_mstory2 == 4) {
        D_8011C680_mstory2[2].func = func_8010C018_mstory2;
        HuPrcSleep(10);
        func_80106E2C_mstory2(D_8011C680_mstory2[2].obj, &targets.v[5], 60);
        wait = 30;
    } else {
        wait = 60;
    }
    HuPrcSleep(wait);
    D_8011C748_mstory2 = 1;
    targets.v[2].y = targets.v[1].y = HmfModelData[D_8011C680_mstory2[3].obj->model[1]].pos.y;
    func_80106E2C_mstory2(D_8011C680_mstory2[3].obj, &targets.v[1], 3);
    HuAudFXPlay(0x217);
    D_8011C680_mstory2[2].func = func_8010BDC4_mstory2;
    D_8011C680_mstory2[0].func = func_8010A784_mstory2;
    D_8011C680_mstory2[1].func = func_8010B200_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x2AC, 0);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x2AC, 1);
    D_8011C748_mstory2 = 0;
    func_80106E48_mstory2(D_8011C680_mstory2[3].obj, &targets.v[2], 5, 0);
    while (TRUE) {
        if (D_8011C680_mstory2[2].flags == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[1]].unk02, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2((D_8011C75C_mstory2 != 4) ? 0x5A13 : 0x5B03);
    func_801060D4_mstory2();
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[0]].unk02, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010A9F0_mstory2;
    D_8011C680_mstory2[1].func = func_8010B46C_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[0].flags == 10 && D_8011C680_mstory2[1].flags == D_8011C680_mstory2[0].flags) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_80105EA4_mstory2();
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    D_8011C680_mstory2[4].func = func_8010889C_mstory2;
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[5].func = func_8010889C_mstory2;
}

/* actor 0: the story character, with its hook item */
void func_80109D04_mstory2(void) {
    StoryMotions motions = D_8011BF28_mstory2;
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[0].obj = obj;
    D_8011C680_mstory2[0].flags = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].sfxOn = 0;
    D_8011C680_mstory2[0].sfxId = 0x1F;
    obj->model[1] = func_8000B108_main(D_800A178C_main[D_8011C75C_mstory2][0] | D_800A178C_main[D_8011C75C_mstory2][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(D_8011C75C_mstory2, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(D_8011C75C_mstory2, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(D_8011C75C_mstory2, 2));
    func_8000B460_main(obj, 3, motions.v[D_8011C75C_mstory2][0] | 0x1D0000);
    func_8000B460_main(obj, 4, motions.v[D_8011C75C_mstory2][1] | 0x1D0000);
    func_8000B460_main(obj, 5, func_80017BB8_main(D_8011C75C_mstory2, 0x72));
    func_8000B460_main(obj, 6, func_80017BB8_main(D_8011C75C_mstory2, 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(D_8011C75C_mstory2, 0x33));
    func_8000B460_main(obj, 8, motions.v[D_8011C75C_mstory2][2] | 0x1D0000);
    func_8000B460_main(obj, 9, func_80017BB8_main(D_8011C75C_mstory2, 0x9B));
    func_8000B460_main(obj, 10, func_80017BB8_main(D_8011C75C_mstory2, 0x9C));
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (D_8011C75C_mstory2 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xA4));
    D_8011C74A_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C74A_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C74A_mstory2[0], 0);
    D_8011C750_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C74A_mstory2[0], 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xA9));
    D_8011C74A_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C750_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C74A_mstory2[0], 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xAA));
    D_8011C74A_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    omPrcSetDestructor(0, func_8010A290_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A290_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE74_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE80_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE8C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE98_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BEB0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BEE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BF28_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BF88_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BF94_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFAC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFB8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFC4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFD0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFDC_mstory2);

void func_8010A298_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], obj->model[1], "item_hook");
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_801072AC_mstory2(model);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].flags = 1;
}

void func_8010A3B4_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 frame;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C92C_main(model, 1.0f);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C680_mstory2[0].func = func_8010A5FC_mstory2;
}

void func_8010A5FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010A61C_mstory2(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    D_8011C680_mstory2[0].sfxOn = 1;
    D_8011C680_mstory2[0].sfxId = 0x1F;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[2]);
    func_80106D58_mstory2(D_8011C680_mstory2[1].obj->model[1], D_8011C758_mstory2, D_8011C756_mstory2);
    D_8011C680_mstory2[0].sfxOn = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 10, 2);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[4]].unk02, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

/* actor 0 hops down: turns to face away, moves to z 500, then back to idle */
void func_8010A784_mstory2(omObjData *obj) {
    Vec rot = D_8011BFF4_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x - 5.0f, HmfModelData[obj->model[1]].pos.y, 500.0f };

    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80106E2C_mstory2(obj, &pos, 10);
    func_801072AC_mstory2(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010A9F0_mstory2(omObjData *obj) {
    Vec rot = D_8011C000_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, 1200.0f };

    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    D_8011C680_mstory2[2].func = func_8010BF7C_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x275, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[0].flags = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[1].flags == 10) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011C680_mstory2[0].sfxOn = 1;
    D_8011C680_mstory2[0].sfxId = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &pos, 60);
    D_8011C680_mstory2[0].sfxOn = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

/* actor 1: the partner (model by whether the player is character 4) */
void func_8010AC1C_mstory2(void) {
    s16 chrs[2] = { 4, 1 };
    s32 mots[2] = { 0x61, 0x44 };
    omObjData *obj;
    void *data;
    s16 idx;

    idx = D_8011C75C_mstory2 == 4;
    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[1].obj = obj;
    D_8011C680_mstory2[1].flags = 0;
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[1].sfxOn = 0;
    D_8011C680_mstory2[1].sfxId = 0x1F;
    obj->model[1] = func_8000B108_main(idx == 0 ? 0x500A0 : 0x300A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chrs[idx], 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chrs[idx], 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chrs[idx], 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chrs[idx], 0x13));
    func_8000B460_main(obj, 4, func_80017BB8_main(chrs[idx], 0x72));
    func_8000B460_main(obj, 5, mots[idx] | 0x1D0000);
    func_8000B460_main(obj, 6, func_80017BB8_main(chrs[idx], 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(chrs[idx], 0x33));
    func_8000B460_main(obj, 8, func_80017BB8_main(chrs[idx], 0x2F));
    if (D_8011C75C_mstory2 == 4) {
        func_8000B460_main(obj, 9, 0x1D0045);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C704_mstory2 = D_8011BE74_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C704_mstory2.x, D_8011C704_mstory2.y, D_8011C704_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C704_mstory2.x, D_8011C704_mstory2.y - -5.0f, D_8011C704_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA4));
    D_8011C752_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8011BA60_mstory2[idx]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C752_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C752_mstory2[0], 0);
    D_8011C758_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C752_mstory2[0], 0, D_8011BA60_mstory2[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA9));
    D_8011C752_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C758_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C752_mstory2[0], 0, D_8011BA60_mstory2[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xAA));
    D_8011C752_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    omPrcSetDestructor(0, func_8010B108_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B108_mstory2(void) {
}

void func_8010B110_mstory2(omObjData *obj) {
    D_8011C680_mstory2[1].sfxOn = 1;
    D_8011C680_mstory2[1].sfxId = 0x1F;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C680_mstory2[1].sfxOn = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].func = func_8010A61C_mstory2;
}

void func_8010B200_mstory2(omObjData *obj) {
    Vec rot = D_8011C00C_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x + 5.0f, HmfModelData[obj->model[1]].pos.y, 500.0f };

    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80106E2C_mstory2(obj, &pos, 10);
    func_801072AC_mstory2(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
}

void func_8010B46C_mstory2(omObjData *obj) {
    Vec rot = D_8011C000_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, 1200.0f };

    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x275, 1);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].flags = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[0].flags == 10) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011C680_mstory2[1].sfxOn = 1;
    D_8011C680_mstory2[1].sfxId = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &pos, 60);
    D_8011C680_mstory2[1].sfxOn = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010B688_mstory2(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
}

void func_8010B738_mstory2(omObjData *obj) {
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[9]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
}

const Vec D_8011BFF4_mstory2 = { 0.0f, 180.0f, 0.0f };

const Vec D_8011C000_mstory2 = { 0.0f, 0.0f, 0.0f };

const Vec D_8011C00C_mstory2 = { 0.0f, -180.0f, 0.0f };

/* actor 2 (model 0xA0075, mstory1's actor 1) */
void func_8010B7B8_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[2].obj = obj;
    D_8011C680_mstory2[2].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C710_mstory2 = D_8011BE80_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C710_mstory2.x, D_8011C710_mstory2.y, D_8011C710_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C710_mstory2.x, -5.0f, D_8011C710_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C740_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C740_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C740_mstory2[0], 0);
    D_8011C746_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, "c204n_0_DEF");
    data = DataRead(0xA0083);
    D_8011C740_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C746_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, "c204n_0_DEF");
    data = DataRead(0xA0080);
    D_8011C740_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    omPrcSetDestructor(0, func_8010BAC4_mstory2);
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    while (TRUE) {
        D_8011C680_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BAC4_mstory2(void) {
}

/* actor 2 jumps (13 frames), turns, and actor 1 reacts */
void func_8010BACC_mstory2(omObjData *obj) {
    Vec pos;
    Vec rot;
    s16 model;
    f32 y;
    s16 i;

    model = obj->model[1];
    rot = D_8011C024_mstory2;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &rot, 5);
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[8]].unk02, 0, 10, 0);
    HuPrcSleep(D_8011C75C_mstory2 != 4 ? 30 : 35);
    func_8004AAD0_main(CharFXPlay(0x28F, D_8011C75E_mstory2), 0x60);
    D_8011C680_mstory2[2].func = func_8010BCE4_mstory2;
    D_8011C680_mstory2[2].flags = 5;
}

/* face actor 1 */
void func_8010BCE4_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

/* sink to y 100 */
void func_8010BD04_mstory2(omObjData *obj) {
    while (TRUE) {
        if (!(HmfModelData[obj->model[1]].pos.y > 100.0f)) {
            break;
        }
        HmfModelData[obj->model[1]].pos.y -= 2.0f;
        HuPrcVSleep();
    }
    HmfModelData[obj->model[1]].pos.y = 100.0f;
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
}

void func_8010BDC4_mstory2(omObjData *obj) {
    Vec pos;
    Vec rot;
    s16 model;
    f32 y;
    s16 i;

    model = obj->model[1];
    rot = D_8011C030_mstory2;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[0]].unk02, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &rot, 10);
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    D_8011C680_mstory2[2].flags = 1;
}

/* turn, then keep facing actor 0 */
void func_8010BF7C_mstory2(omObjData *obj) {
    Vec rot = D_8011C03C_mstory2;

    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_801070D8_mstory2(obj, &rot, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C680_mstory2[2].obj, D_8011C680_mstory2[0].obj);
        HuPrcVSleep();
    }
}

/* face actor 0 */
void func_8010C018_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[0].obj);
}

/* actor 3 (model 0xA0122, twice the size) */
void func_8010C038_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[3].obj = obj;
    D_8011C680_mstory2[3].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C71C_mstory2 = D_8011BE8C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C71C_mstory2.x, D_8011C71C_mstory2.y, D_8011C71C_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C71C_mstory2.x, -5.0f, D_8011C71C_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8010C1DC_mstory2);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
    while (TRUE) {
        D_8011C680_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C1DC_mstory2(void) {
}

/* NON_MATCHING: scheduling only; retail computes ofs + 25 before the wrap test (in its branch
   delay slot) and the mul right after the call */
#ifdef NON_MATCHING
/* actor 3 bobs 25 above its height until D_8011C748_mstory2 is 1 */
void func_8010C1E4_mstory2(void) {
    Vec pos;
    omObjData *obj;
    f32 angle;
    f32 ofs;

    angle = 0.0f;
    obj = D_8011C680_mstory2[3].obj;
    pos.y = HmfModelData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = HmfModelData[obj->model[1]].pos.x;
        pos.z = HmfModelData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_8011C748_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + 25.0f + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49DF30", func_8010C1E4_mstory2);
#endif

/* face actor 1 */
void func_8010C328_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010C348_mstory2(omObjData *obj) {
    Vec rot = D_8011C000_mstory2;

    func_801070D8_mstory2(obj, &rot, 10);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
}

/* actor 4 (model 0x1D0003 and a second model 0xB0004) */
void func_8010C398_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[4].obj = obj;
    D_8011C680_mstory2[4].flags = 0;
    D_8011C680_mstory2[4].func = func_8010889C_mstory2;
    obj->model[1] = func_8000B108_main(0x1D0003, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C728_mstory2 = D_8011BE98_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C728_mstory2.x, D_8011C728_mstory2.y, D_8011C728_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8010C508_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C508_mstory2(void) {
}

const Vec D_8011C024_mstory2 = { 0.0f, 167.0f, 0.0f };

const Vec D_8011C030_mstory2 = { 0.0f, -135.0f, 0.0f };

const Vec D_8011C03C_mstory2 = { 0.0f, -53.39f, 0.0f };
Vec D_8011B950_mstory2[4] = { { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f } };
Vec D_8011B980_mstory2[6] = { { -100.0f, 300.0f, 300.0f }, { -200.0f, 400.0f, -100.0f }, { 0.0f, 200.0f, 100.0f }, { 9999.0f, 9999.0f, 9999.0f }, { 0.0f, 158.73f, 0.0f }, { 0.0f, 167.01f, 0.0f } };
Vec D_8011B9C8_mstory2 = { 0.0f, 158.46f, 0.0f };
Vec D_8011B9D4_mstory2 = { 0.0f, -70.43f, 0.0f };
Vec D_8011B9E0_mstory2[5] = { { 0.0f, -77.13f, 0.0f }, { 0.0f, -135.0f, 0.0f }, { 0.0f, 162.4f, 0.0f }, { 0.0f, -147.34f, 0.0f }, { 0.0f, 306.61f, 0.0f } };
Vec D_8011BA1C_mstory2 = { 0.0f, 90.0f, 0.0f };
Vec D_8011BA28_mstory2 = { 0.0f, 50.19f, 0.0f };
Vec D_8011BA34_mstory2 = { 0.0f, 100.78f, 0.0f };
char *D_8011BA40_mstory2[8] = { D_8011BFDC_mstory2, D_8011BFD0_mstory2, D_8011BFC4_mstory2, D_8011BFB8_mstory2, D_8011BFAC_mstory2, D_8011BFA0_mstory2, D_8011BF94_mstory2, D_8011BF88_mstory2 };
char *D_8011BA60_mstory2[4] = { D_8011BFAC_mstory2, D_8011BFD0_mstory2, NULL, NULL };
