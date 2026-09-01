extern int D_001ED0C0;
extern int D_001ED0C4;
extern int D_001ED0C8;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_001081E0(void);

void func_00107A50(int count) {
    int i;
    int j;

    D_001ED0C0 = func_00151A00(count * 0xB70);
    D_001ED0C8 = 1;
    D_001ED0C4 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0xB70 + D_001ED0C0) = 0;
        for (j = 0; j < 30; j++) {
            *(int *)(i * 0xB70 + D_001ED0C0 + (j << 6) + 0x34) = 0;
            *(int *)(i * 0xB70 + D_001ED0C0 + (j << 6) + 0x40) = 0;
            *(int *)(i * 0xB70 + D_001ED0C0 + (j << 6) + 0x44) = 0;
            *(int *)(i * 0xB70 + D_001ED0C0 + (j << 6) + 0x48) = 0;
            *(float *)(i * 0xB70 + D_001ED0C0 + (j << 6) + 0x4C) = 1.0f;
        }
    }
    func_00112EB0(func_001081E0, count, 0);
}
