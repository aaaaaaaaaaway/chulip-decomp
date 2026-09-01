extern unsigned short D_001ECF80;
extern unsigned short D_002DB500[];

void func_0017E528(unsigned short id);

void func_0017E668(void) {
    int count = 0;

    if (D_001ECF80 != 0) {
        unsigned short *entry = D_002DB500;

        do {
            func_0017E528(*entry);
            entry++;
            count++;
        } while (count < D_001ECF80);
    }
    D_001ECF80 = 0;
}
