/* Drain the pending ID list, then clear its count. */
extern unsigned short D_001ECF80;
extern unsigned short D_002DB500[];
void func_0017E528(unsigned short id);

void func_0017E668(void) {
    int i;

    for (i = 0; i < D_001ECF80; i++) {
        func_0017E528(D_002DB500[i]);
    }
    D_001ECF80 = 0;
}
