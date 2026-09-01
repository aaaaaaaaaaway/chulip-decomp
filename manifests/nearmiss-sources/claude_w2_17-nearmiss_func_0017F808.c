extern int D_001ECFA0;
extern int D_001ED988;
extern int D_001ED990;
extern int D_002DB540[];

int func_0017F898();
int func_0017F9B8();
int func_0017FBB0();
int func_0017FE98();

void func_0017F808(void) {
    int i;

    D_001ED990 = -1;
    D_001ED988 = D_001ECFA0;
    D_001ECFA0 = 1;
    for (i = 0x3F; i >= 0; i--) {
        D_002DB540[i] = 0;
    }
    func_0017F898();
    func_0017F9B8(func_0017FBB0, 0, 0);
    func_0017F9B8(func_0017FE98, 0, 0);
}
