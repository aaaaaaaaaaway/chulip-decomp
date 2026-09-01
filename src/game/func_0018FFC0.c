extern int D_001E4BC4[];
extern int func_001987B0(int handle);

int func_0018FFC0(void) {
    if (D_001E4BC4[0] >= 0) {
        func_001987B0(D_001E4BC4[0]);
        D_001E4BC4[0] = -1;
    }
    return 1;
}
