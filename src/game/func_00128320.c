extern void func_00158BB8(unsigned short index, int arg1);
extern void func_00158B40(unsigned short index, int arg1);

void func_00128320(void) {
    int i;

    for (i = 1; i < 0x1C0; i++) {
        func_00158BB8(i, 0);
        func_00158B40(i, 1);
    }
}
