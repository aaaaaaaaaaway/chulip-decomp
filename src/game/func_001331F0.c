struct Matrix_001331F0 { unsigned char data[0x40]; };

struct Entry_001331F0 {
    unsigned char pad_0x0[0x34];
    int field_0x34;
    unsigned char pad_0x38[8];
};

struct Object_001331F0 {
    int count;
    struct Entry_001331F0 *entries;
    unsigned char pad_0x8[8];
    float field_0x10[4];
    float field_0x20;
    float field_0x24;
    float field_0x28;
};

extern void func_0018A6F8(struct Matrix_001331F0 *m);
extern void func_0018A798(struct Matrix_001331F0 *dst, struct Matrix_001331F0 *src, float angle);
extern void func_0018A8E8(struct Matrix_001331F0 *dst, struct Matrix_001331F0 *src, float angle);
extern void func_0018A840(struct Matrix_001331F0 *dst, struct Matrix_001331F0 *src, float angle);
extern void func_00133688(struct Matrix_001331F0 *m);
extern void func_0018A650(struct Matrix_001331F0 *dst, struct Matrix_001331F0 *src, float *v);
extern void func_001337E0(struct Matrix_001331F0 *m);
extern void func_001332D8(struct Object_001331F0 *obj, int index);
extern void func_00133770(struct Matrix_001331F0 *m);
extern void func_001336E0(struct Matrix_001331F0 *m);

void func_001331F0(struct Object_001331F0 *obj) {
    struct Matrix_001331F0 matrix;
    int i;

    for (i = 0; i < obj->count; i++) {
        int offset = i * 0x40;

        if (((struct Entry_001331F0 *)((unsigned char *)obj->entries + offset))->field_0x34 == -1) {
            func_0018A6F8(&matrix);
            func_0018A798(&matrix, &matrix, obj->field_0x28);
            func_0018A8E8(&matrix, &matrix, obj->field_0x24);
            func_0018A840(&matrix, &matrix, obj->field_0x20);
            func_00133688(&matrix);
            func_0018A650(&matrix, &matrix, obj->field_0x10);
            func_001337E0(&matrix);
            func_001332D8(obj, i);
            func_00133770(&matrix);
            func_001336E0(&matrix);
        }
    }
}
