typedef struct {
    unsigned char unknown00[0x54];
    unsigned short value54, limit56;
    unsigned short value58, limit5a;
    int value5c, value60;
    unsigned char value64, value65;
    unsigned short value66;
} PlayerStats;
extern PlayerStats D_001A6998;
unsigned long *func_00136AE8(void);

void func_0012FA20(signed char delta) {
    unsigned long *flags = func_00136AE8();
    if (delta < 0) {
        if (D_001A6998.value58 + delta <= 0) {
            D_001A6998.value58 = 0;
            *flags |= 0x100000UL;
        } else {
            *flags &= ~0x100000UL;
            D_001A6998.value58 += delta;
        }
    } else {
        *flags &= ~0x100000UL;
        if (D_001A6998.value58 + delta >= D_001A6998.limit5a)
            D_001A6998.value58 = D_001A6998.limit5a;
        else
            D_001A6998.value58 += delta;
    }
}
