struct Matrix_001332D8 { unsigned char data[0x40]; };

struct Entry_001332D8 {
    float pos[4];
    float rot[9];
    int parent;
    unsigned char pad_0x38[8];
};

struct Bone_001332D8 {
    unsigned char pad_0x0[0x10];
    struct Matrix_001332D8 local;
    struct Matrix_001332D8 world;
};

struct Object_001332D8 {
    int count;
    struct Entry_001332D8 *entries;
    struct Bone_001332D8 *bones;
};

/* Provisional single-source provider; original TU boundaries are unproved. */
float D_001EC98C __attribute__((section(".sdata"))) = 0.0f;
extern struct Matrix_001332D8 D_001FE570;
extern struct Matrix_001332D8 D_001FE5B0;

extern void func_0018A680(float *dst, float *rot);
extern void func_0018AF68(float *dst, float *src, float scale);
extern void func_0018A6F8(struct Matrix_001332D8 *m);
extern void func_0018A798(struct Matrix_001332D8 *dst, struct Matrix_001332D8 *src, float a);
extern void func_0018A8E8(struct Matrix_001332D8 *dst, struct Matrix_001332D8 *src, float a);
extern void func_0018A840(struct Matrix_001332D8 *dst, struct Matrix_001332D8 *src, float a);
extern void func_0018A400(struct Matrix_001332D8 *dst, struct Matrix_001332D8 *a, struct Matrix_001332D8 *b);
extern void func_0018A650(struct Matrix_001332D8 *dst, struct Matrix_001332D8 *src, float *v);
extern void func_0018A690(struct Matrix_001332D8 *dst, struct Matrix_001332D8 *src);
extern int func_00133750(struct Matrix_001332D8 *m);
extern int func_00133838(struct Matrix_001332D8 *m);
extern void func_00133688(struct Matrix_001332D8 *m);
extern void func_001337E0(struct Matrix_001332D8 *m);
extern void func_00133770(struct Matrix_001332D8 *m);
extern void func_001336E0(struct Matrix_001332D8 *m);

void func_001332D8(struct Object_001332D8 *obj, int index) {
    float angles[4];
    float scaled[4];
    struct Matrix_001332D8 m;
    float trans[4];
    struct Entry_001332D8 *entry;
    struct Bone_001332D8 *bone;
    int i;

    entry = obj->entries + index;
    bone = obj->bones + index;
    func_0018A680(angles, entry->rot);
    func_0018AF68(scaled, angles, 0.31830987f);
    for (i = 0; i < 3; i++) {
        int turns = (int)scaled[i];

        if (turns < 0) {
            turns = turns - 1;
        } else {
            turns = turns + 1;
        }
        turns = turns / 2;
        if (turns != 0) {
            angles[i] = angles[i] - (float)turns * 6.2831855f;
        }
    }
    func_0018A6F8(&m);
    func_0018A798(&m, &m, angles[2]);
    func_0018A8E8(&m, &m, angles[1]);
    func_0018A840(&m, &m, angles[0]);
    func_00133750(&D_001FE570);
    func_0018A400(&D_001FE570, &D_001FE570, &m);
    if (D_001EC98C != 0.0f) {
        func_0018AF68(trans, entry->pos, D_001EC98C);
        func_0018A650(&m, &m, trans);
    } else {
        func_0018A650(&m, &m, entry->pos);
    }
    func_00133838(&D_001FE5B0);
    func_0018A400(&D_001FE5B0, &D_001FE5B0, &m);
    func_0018A690(&bone->local, &D_001FE5B0);
    func_0018A690(&bone->world, &D_001FE570);
    for (i = 0; i < obj->count; i++) {
        entry = obj->entries + i;
        if (entry->parent != -1 && entry->parent == index) {
            func_00133688(&D_001FE570);
            func_001337E0(&D_001FE5B0);
            func_001332D8(obj, i);
            func_00133770(&D_001FE5B0);
            func_001336E0(&D_001FE570);
        }
    }
}
