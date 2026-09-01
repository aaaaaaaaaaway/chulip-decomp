extern unsigned short D_001ECC80;
extern unsigned short D_002AB980[];

void func_0015B970(unsigned short value) {
    unsigned short index = D_001ECC80;

    D_001ECC80 = index + 1;
    D_002AB980[index] = value;
}
