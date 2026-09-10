/* Read one of two alternating image/auxiliary banks and signal completion. */
unsigned short D_001ECF88 = 0;
extern unsigned char D_001ED948;
extern unsigned char D_001ED949;
extern unsigned char *D_001ED950[2];
extern unsigned char *D_001ED958[2];
extern int D_001ED960;
extern int D_001ED964;
extern unsigned int D_001ED968;
extern char D_001EACB0[];
extern char D_001EACC8[];
int func_00192660(char *, const char *, ...);
int func_00125E00(char *, void *, int, int);
void func_0017F5C8(int, unsigned char);
void func_001174D0(int, int);
void func_001985E0(void);

void func_0017F470(void) {
    char path[32];
    char auxiliary[32];
    int bank;
    bank = D_001ED948 & 1;
    func_00192660(path, D_001EACB0, D_001ED949);
    func_00192660(auxiliary, D_001EACC8, D_001ED949);
    if (D_001ED948 * 0x77100U >= D_001ED968) {
        func_001985E0();
        return;
    }
    func_00125E00(path, D_001ED950[bank], D_001ED948 * 0x77100, 0x77100);
    func_00125E00(auxiliary, D_001ED958[bank], D_001ED948 * 0xf00, 0xf00);
    if (D_001ED948 == 0)
        func_0017F5C8(0, 0);
    else if (D_001ED948 == 1) {
        func_001174D0(D_001ED960, D_001ED964);
        D_001ECF88 |= 0x80;
    }
    if (bank == 0)
        D_001ECF88 = (D_001ECF88 & ~2) | 8;
    else
        D_001ECF88 = (D_001ECF88 & ~4) | 16;
    func_001985E0();
}
