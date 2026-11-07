#include "common.h"

typedef f32 Matrix4f[4][4];

void func_80089980_main(Matrix4f mf, Mtx* m);
void func_8008CCC0_main(Matrix4f a, Matrix4f b, Matrix4f dst);
void func_8008CE00_main(Matrix4f a, Matrix4f b, Matrix4f dst);
void func_8008CFA0_main(Matrix4f a, Matrix4f b, Matrix4f dst);
void func_8008D130_main(Matrix4f a, Matrix4f b, Matrix4f dst);

// NON_MATCHING: loop counters, retail keeps the row loop's i as its own counter where GCC
// reduces it to i*16 (masked 4-6; MP2 has the same residue)
#ifdef NON_MATCHING
/* guMtxCatF (Hudson), from MP2 src/B7010.c: dst = a * b (dst may be a or b) */
void func_8008CCC0_main(Matrix4f a, Matrix4f b, Matrix4f dst) {
    s32 i;
    s32 j;
    Matrix4f temp;
    f32 a0;
    f32 a1;
    f32 a2;
    f32 a3;

    for (i = 0; i < 4; i++) {
        a0 = a[i][0];
        a1 = a[i][1];
        a2 = a[i][2];
        a3 = a[i][3];
        for (j = 0; j < 4; j++) {
            temp[i][j] = a0 * b[0][j] + a1 * b[1][j] + a2 * b[2][j] + a3 * b[3][j];
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            dst[i][j] = temp[i][j];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8D8C0", func_8008CCC0_main);
#endif

/* guMtxCat: out = a * b in fixed point */
void func_8008CD90_main(Mtx* a, Mtx* b, Mtx* out) {
    Matrix4f fa;
    Matrix4f fb;

    func_80089980_main(fa, a);
    func_80089980_main(fb, b);
    func_8008CCC0_main(fa, fb, fa);
    func_800898F0_main((Mtx*)fa, out);
}

// NON_MATCHING: loop counters, retail keeps the row loop's i as its own counter where GCC
// reduces it to i*16 (masked 4-6; MP2 has the same residue)
#ifdef NON_MATCHING
/* dst = a * b for the first three columns; column 3 is kept from a (dst may be a or b) */
void func_8008CE00_main(Matrix4f a, Matrix4f b, Matrix4f dst) {
    s32 i;
    s32 j;
    Matrix4f temp;
    f32 a0;
    f32 a1;
    f32 a2;
    f32 a3;

    for (i = 0; i < 4; i++) {
        a0 = a[i][0];
        a1 = a[i][1];
        a2 = a[i][2];
        a3 = a[i][3];
        for (j = 0; j < 3; j++) {
            temp[i][j] = a0 * b[0][j] + a1 * b[1][j] + a2 * b[2][j] + a3 * b[3][j];
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            dst[i][j] = temp[i][j];
        }
        dst[i][3] = a[i][3];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8D8C0", func_8008CE00_main);
#endif

/* func_8008CE00_main in fixed point; only the first three columns of b are read */
void func_8008CEE0_main(Mtx* a, Mtx* b, Mtx* out) {
    Matrix4f fa;
    Matrix4f fb;
    s32 i;
    s32 j;
    u16* p;

    func_80089980_main(fa, a);
    p = (u16*)b;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            fb[i][j] = (s32)((p[j] << 16) | p[j + 16]) * (1.0f / 65536.0f);
        }
        p += 4;
    }
    func_8008CE00_main(fa, fb, fa);
    func_800898F0_main((Mtx*)fa, out);
}

// NON_MATCHING: loop counters, retail keeps the row loop's i as its own counter where GCC
// reduces it to i*16 (masked 4-6; MP2 has the same residue)
#ifdef NON_MATCHING
/* dst = a * b using only the 3x3 parts (rotation and scale; b's translation row is ignored, a's is transformed); column 3 is kept from a */
void func_8008CFA0_main(Matrix4f a, Matrix4f b, Matrix4f dst) {
    s32 i;
    s32 j;
    Matrix4f temp;
    f32 a0;
    f32 a1;
    f32 a2;

    for (i = 0; i < 4; i++) {
        a0 = a[i][0];
        a1 = a[i][1];
        a2 = a[i][2];
        for (j = 0; j < 3; j++) {
            temp[i][j] = a0 * b[0][j] + a1 * b[1][j] + a2 * b[2][j];
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            dst[i][j] = temp[i][j];
        }
        dst[i][3] = a[i][3];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8D8C0", func_8008CFA0_main);
#endif

/* func_8008CFA0_main in fixed point; only b's 3x3 part is read */
void func_8008D070_main(Mtx* a, Mtx* b, Mtx* out) {
    Matrix4f fa;
    Matrix4f fb;
    s32 i;
    s32 j;
    u16* p;

    func_80089980_main(fa, a);
    p = (u16*)b;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            fb[i][j] = (s32)((p[j] << 16) | p[j + 16]) * (1.0f / 65536.0f);
        }
        p += 4;
    }
    func_8008CFA0_main(fa, fb, fa);
    func_800898F0_main((Mtx*)fa, out);
}

// NON_MATCHING: loop counters, retail keeps the row loop's i as its own counter where GCC
// reduces it to i*16 (masked 4-6; MP2 has the same residue)
#ifdef NON_MATCHING
/* dst = a * b using only b's translation row (b's 3x3 part is taken as identity); column 3 is kept
   from a */
void func_8008D130_main(Matrix4f a, Matrix4f b, Matrix4f dst) {
    s32 i;
    s32 j;
    Matrix4f temp;
    f32 a3;

    for (i = 0; i < 4; i++) {
        a3 = a[i][3];
        for (j = 0; j < 3; j++) {
            temp[i][j] = a[i][j] + a3 * b[3][j];
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            dst[i][j] = temp[i][j];
        }
        dst[i][3] = a[i][3];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8D8C0", func_8008D130_main);
#endif

/* func_8008D130_main in fixed point; only b's translation row is read */
void func_8008D1F0_main(Mtx* a, Mtx* b, Mtx* out) {
    Matrix4f fa;
    Matrix4f fb;
    u16* p;

    func_80089980_main(fa, a);
    p = (u16*)b;
    fb[3][0] = (s32)((p[12] << 16) | p[28]) * (1.0f / 65536.0f);
    fb[3][1] = (s32)((p[13] << 16) | p[29]) * (1.0f / 65536.0f);
    fb[3][2] = (s32)((p[14] << 16) | p[30]) * (1.0f / 65536.0f);
    func_8008D130_main(fa, fb, fa);
    func_800898F0_main((Mtx*)fa, out);
}
