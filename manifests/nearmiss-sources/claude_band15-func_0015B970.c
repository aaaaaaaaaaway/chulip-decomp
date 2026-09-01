extern unsigned short D_001ECC80;
extern short D_002AB980[];

void func_0015B970(short value) {
    unsigned short index = D_001ECC80;

    D_001ECC80 = index + 1;
    D_002AB980[index] = value;
}
