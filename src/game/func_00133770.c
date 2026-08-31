struct Slot64_00133770 { unsigned char data[0x40]; };

extern int D_001EC984;
extern struct Slot64_00133770 D_001FE5F0[];
extern struct Slot64_00133770 D_001A7700;

extern void func_0018A690(struct Slot64_00133770 *dst, struct Slot64_00133770 *src);
extern void func_0018A6F8(struct Slot64_00133770 *dst);

void func_00133770(struct Slot64_00133770 *out) {
    D_001EC984 = D_001EC984 - 1;
    if (D_001EC984 >= 0) {
        func_0018A690(out, &D_001FE5F0[D_001EC984]);
        if (D_001EC984 == 0) {
            func_0018A6F8(&D_001A7700);
        } else {
            func_0018A690(&D_001A7700, out);
        }
    }
}
