struct Slot64_001337E0 { unsigned char data[0x40]; };

extern int D_001EC984;
extern struct Slot64_001337E0 D_001FE5F0[];
extern struct Slot64_001337E0 D_001A7700;

extern void func_0018A690(struct Slot64_001337E0 *dst, void *src);

void func_001337E0(void *src) {
    func_0018A690(&D_001FE5F0[D_001EC984], src);
    func_0018A690(&D_001A7700, src);
    D_001EC984 = D_001EC984 + 1;
}
