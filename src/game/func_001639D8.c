extern unsigned char D_002D89C0[];

void func_00178DE8(unsigned short index);
void func_001923F4(void *dst, int value, int size);

void func_001639D8(void) {
    int i;

    for (i = 0; i < 0x20; i++) {
        if (D_002D89C0[i] == 1) {
            func_00178DE8(i);
        }
    }
    func_001923F4(D_002D89C0, 0, 0x20);
}
