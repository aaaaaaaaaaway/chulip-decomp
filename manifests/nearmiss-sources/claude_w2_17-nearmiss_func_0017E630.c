extern unsigned short D_001ECF80;
extern short D_002DB500[];

void func_0017E630(unsigned short value) {
    if (value != 0) {
        D_002DB500[D_001ECF80++] = value;
    }
}
