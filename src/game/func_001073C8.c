extern int D_001ED0B4;
extern int D_001ED0B8;
extern int D_001ED0BC;
extern int func_00151A00(int size);
extern void func_00112F40(void (*fn)(void));
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_001076F0(void);

void func_001073C8(void) {
    int i;
    int n = 1;

    D_001ED0B4 = func_00151A00(n * 0x30);
    D_001ED0B8 = n;
    D_001ED0BC = n;
    for (i = 0; i < n; i++) {
        *(int *)(i * 0x30 + D_001ED0B4) = 0;
        *(int *)(i * 0x30 + D_001ED0B4 + 0x8) = 0;
        *(int *)(i * 0x30 + D_001ED0B4 + 0x10) = 0;
        *(int *)(i * 0x30 + D_001ED0B4 + 0x14) = 0;
        *(int *)(i * 0x30 + D_001ED0B4 + 0x18) = 0;
        *(float *)(i * 0x30 + D_001ED0B4 + 0x1C) = 1.0f;
    }

    func_00112F40(func_001076F0);
    func_00112EB0(func_001076F0, n, 0);
}
