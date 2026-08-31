struct Pair8 { unsigned int field_0x0; unsigned int field_0x4; };

extern struct Pair8 D_001ED400;
extern void *D_001ECB00;
extern void *D_001ECAC0;
extern void *D_001ECB2C;

extern void *func_00151A00(int size);

void func_0014B410(void) {
    if (D_001ECB00 == 0) {
        D_001ECB00 = func_00151A00(0x2000);
    }
    if (D_001ED400.field_0x0 == 0) {
        D_001ED400.field_0x0 = ((unsigned int)func_00151A00(0x60000) & 0x0FFFFFFF) | 0x20000000;
    }
    if (D_001ECAC0 == 0) {
        D_001ECAC0 = func_00151A00(0x9CF0);
    }
    if (D_001ECB2C == 0) {
        D_001ECB2C = func_00151A00(0x51000);
    }
}
