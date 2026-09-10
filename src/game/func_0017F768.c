extern unsigned char D_001ED948;
extern unsigned short D_001ECF88;
extern int D_001ED94C;
extern char D_002D9100[];

void func_0017F470(void);
int func_00137FD0();

void func_0017F768(unsigned char mode) {
    D_001ED948 = mode;
    if ((mode & 1) == 0) {
        D_001ECF88 |= 2;
    } else {
        D_001ECF88 |= 4;
    }
    D_001ED94C = func_00137FD0(func_0017F470, D_002D9100, 0x2000, 1, 0);
}
