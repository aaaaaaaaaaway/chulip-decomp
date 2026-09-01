extern void func_0011FAD8(int which, int value);
extern void func_00120ED0(int value);
extern void func_00124230(int which, int value);
extern void func_001121C0(void);
extern void func_00112AA0(void);
extern void func_001519F0(void);

void func_00178800(int which, unsigned char enable) {
    int value = enable ? 1 : -1;

    switch (which) {
    case 1:
        func_0011FAD8(0, value);
        break;
    case 2:
        func_0011FAD8(1, value);
        break;
    case 3:
        func_00120ED0(value);
        break;
    case 4:
        func_00124230(0, value);
        break;
    case 5:
        func_00124230(1, value);
        break;
    case 6:
        func_001121C0();
        func_00112AA0();
        func_001519F0();
        func_00124230(2, value);
        func_001519F0();
        break;
    case 7:
        func_0011FAD8(3, value);
        break;
    }
}
