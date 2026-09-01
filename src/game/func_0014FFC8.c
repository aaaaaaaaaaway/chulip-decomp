extern volatile int D_001ED438;
extern volatile int D_001ED43C;
extern volatile int D_001ED44C;
extern volatile int D_001ED450;

void func_0014FFC8(int arg0, int arg1) {
    if (D_001ED438 == 0) {
        D_001ED44C = arg0;
        D_001ED450 = arg1;
        D_001ED43C = 0;
        D_001ED438 = 5;
    }
}
