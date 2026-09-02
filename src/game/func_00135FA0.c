typedef struct { float x, y, z, w; } Vec4;
typedef struct { float m[3][4][4]; } MatrixSet;

typedef struct Node {
    unsigned char unknown_000[0x100];
    MatrixSet sets[3];
} Node;

typedef struct Owner {
    unsigned char unknown_00[0x10];
    Node *node;
} Owner;

extern MatrixSet D_001FF1A0[];
extern Vec4 D_001A7790[];
extern Vec4 D_001A7830[];
extern Vec4 D_001A7D30[];

extern void func_0018A680(void *dst, const void *src);
extern void func_0018AAB8(float *dst, const Vec4 *a, const Vec4 *b, const Vec4 *c);
extern void func_0018AB78(float *dst, const Vec4 *a, const Vec4 *b, const Vec4 *c, const Vec4 *d);
extern float func_001018C8(void);

void func_00135FA0(Owner **owner, unsigned char mode) {
    Vec4 color;
    Vec4 a;
    Vec4 b;
    Vec4 c;
    Vec4 d;
    Vec4 e;
    Vec4 f;
    Vec4 rot;
    unsigned int i;
    float angle;

    color.x = 0.26f;
    color.y = 0.26f;
    color.z = 0.26f;
    color.w = 1.0f;

    if (mode == 0) {
        func_0018A680(&rot, &D_001A7830[1]);
        angle = func_001018C8() + 3.1415927f;
        rot.x = angle;
        if (3.1415927f < angle) {
            rot.y -= 6.2831855f;
        }
        angle = rot.x;
        rot.x = 3.1415927f;
        rot.y = angle;
        rot.z = 0.0f;

        for (i = 0; i < 3; i++) {
            func_0018A680(&a, &rot);
            func_0018A680(&b, &rot);
            func_0018A680(&c, &rot);
            func_0018AAB8((*owner)->node->sets[i].m[0][0], &a, &b, &c);
            (*owner)->node->sets[i].m[0][3][3] = 1.0f;
            func_0018AB78((*owner)->node->sets[i].m[2][0], &color, &color,
                          &color, &D_001A7D30[1]);
        }
    } else {
        for (i = 0; i < 3; i++) {
            func_0018A680(&a, &D_001A7830[mode * 4 + 1]);
            func_0018A680(&b, D_001FF1A0[i].m[1][1]);
            func_0018A680(&c, D_001FF1A0[i].m[2][1]);
            func_0018A680(&d, &D_001A7830[mode * 4]);
            func_0018A680(&e, D_001FF1A0[i].m[1][0]);
            func_0018A680(&f, D_001FF1A0[i].m[2][0]);
            func_0018AAB8((*owner)->node->sets[i].m[0][0], &a, &b, &c);
            (*owner)->node->sets[i].m[0][3][3] = 1.0f;
            func_0018AB78((*owner)->node->sets[i].m[2][0], &d, &e, &f,
                          &D_001A7790[0]);
        }
    }
}
