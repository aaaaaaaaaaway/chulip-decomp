extern int D_001ED090;
extern int D_001ED094;
extern int D_001ED098;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_00105F28(void);

void func_00105B08(int count) {
    int i;
    int j;


    D_001ED090 = func_00151A00(count * 0x2B0);
    D_001ED098 = 1;
    D_001ED094 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x2B0 + D_001ED090 + 0x14) = 0;
        for (j = 0; j < 10; j++) {
            *(int *)(i * 0x2B0 + D_001ED090 + (j << 6) + 0x30) = 1;
            *(int *)(i * 0x2B0 + D_001ED090 + (j << 6) + 0x34) = 0;
            *(int *)(i * 0x2B0 + D_001ED090 + (j << 6) + 0x40) = 0;
            *(int *)(i * 0x2B0 + D_001ED090 + (j << 6) + 0x44) = 0;
            *(int *)(i * 0x2B0 + D_001ED090 + (j << 6) + 0x48) = 0;
            *(float *)(i * 0x2B0 + D_001ED090 + (j << 6) + 0x4C) = 1.0f;
        }
    }
    func_00112EB0(func_00105F28, count, 0);
}
