extern int D_001ED1D8;
extern float D_001F9DC0[];

void func_0018A680(float *state, int value);

void func_001157D8(int value, int enable) {
    if (enable) {
        D_001ED1D8 = 1;
        func_0018A680(D_001F9DC0, value);
        D_001F9DC0[3] = 1.0f;
    } else {
        D_001ED1D8 = 0;
    }
}
