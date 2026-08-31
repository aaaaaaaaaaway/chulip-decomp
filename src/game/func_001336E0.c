struct Slot64_001336E0 { unsigned char data[0x40]; };

extern int D_001EC984;
extern int D_001EC988;
extern struct Slot64_001336E0 D_001FEAF0[];
extern struct Slot64_001336E0 D_001A7740;

extern void func_0018A690(struct Slot64_001336E0 *dst, struct Slot64_001336E0 *src);
extern void func_0018A6F8(struct Slot64_001336E0 *dst);

void func_001336E0(struct Slot64_001336E0 *out) {
    D_001EC988 = D_001EC988 - 1;
    if (D_001EC984 >= 0) {
        func_0018A690(out, &D_001FEAF0[D_001EC988]);
        if (D_001EC988 == 0) {
            func_0018A6F8(&D_001A7740);
        } else {
            func_0018A690(&D_001A7740, out);
        }
    }
}
