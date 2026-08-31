struct Slot64_00133688 { unsigned char data[0x40]; };

extern int D_001EC988;
extern struct Slot64_00133688 D_001FEAF0[];
extern struct Slot64_00133688 D_001A7740;

extern void func_0018A690(struct Slot64_00133688 *dst, void *src);

void func_00133688(void *src) {
    func_0018A690(&D_001FEAF0[D_001EC988], src);
    func_0018A690(&D_001A7740, src);
    D_001EC988 = D_001EC988 + 1;
}
