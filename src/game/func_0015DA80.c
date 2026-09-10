extern unsigned char *func_00136AE8(void);
extern unsigned char D_001ECC90, D_001ECCA0;
extern void func_0015B208(unsigned char);
extern void func_00153D68(unsigned char, unsigned char);
extern void func_0015A8C0(unsigned char);
extern void func_0015DC38(void);
void func_0015DA80(void) {
    unsigned char *actor = func_00136AE8();
    if (D_001ECC90 != 255)
        func_0015B208(D_001ECC90);
    if (D_001ECCA0 != 255) {
        if (D_001ECCA0 == 254)
            func_0015A8C0(2);
        else {
            func_00153D68(0, D_001ECCA0);
            func_0015A8C0(0);
        }
    }
    func_0015DC38();
    *(unsigned long *)actor = (*(unsigned long *)actor & ~4UL) | (1UL << 34);
}
