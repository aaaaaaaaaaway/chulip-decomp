extern unsigned char D_001ED538;
extern unsigned char D_001ED539;
extern unsigned char D_001ED53A;
extern unsigned char D_001ED53B;
extern unsigned char D_001ED53C;
extern unsigned char D_001ED53D;

void func_00189E10(int arg, int zero, unsigned char *state);

void func_00161AD0(int arg) {
    D_001ED53D = 0xFF;
    D_001ED53A = 0xFF;
    D_001ED53B = 0xFF;
    D_001ED53C = 0xFF;
    D_001ED539 = 1;
    D_001ED538 = 0;
    func_00189E10(arg, 0, &D_001ED538);
}
