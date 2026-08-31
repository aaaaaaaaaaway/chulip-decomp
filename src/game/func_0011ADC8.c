typedef struct { int value; int pad; } Slot;

extern Slot D_001ED204;
extern int D_001ED208;
extern Slot D_001ED20C;

void func_0011AE00(void);
void func_00112F40(void (*handler)(void));

void func_0011ADC8(void) {
    D_001ED204.value = -1;
    D_001ED20C.value = 0;
    D_001ED208 = 0;
    func_00112F40(func_0011AE00);
}
