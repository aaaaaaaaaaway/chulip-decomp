extern int D_001E3154[];
extern volatile int D_001E3160[];
extern volatile int D_001E3168[];
extern volatile int D_001E3170[];
extern volatile int D_001E3194[];
extern volatile int D_001E3198[];
extern int D_002DE900[];
extern int func_001987D0(int handle);

void func_0018EBD8(int *source) {
    D_001E3194[0] = *source;
    D_001E3198[0] = D_001E3194[0];
    if (D_001E3194[0] == 0xB) {
        D_001E3194[0] = 0;
        D_001E3170[0] = 0;
        return;
    }
    func_001987D0(D_001E3168[0]);
    if (D_001E3154[0] != 0 && D_002DE900[0] != 0) {
        func_001987D0(D_001E3160[0]);
    } else {
        D_001E3170[0] = 0;
    }
    D_001E3194[0] = 0;
}
