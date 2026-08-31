struct S8_int { int a; char pad[4]; };

extern volatile struct S8_int D_001ED438;
extern volatile struct S8_int D_001ED43C;
extern volatile struct S8_int D_001ED44C;
extern volatile struct S8_int D_001ED450;

void func_0014FFC8(int arg0, int arg1) {
    if (D_001ED438.a == 0) {
        D_001ED44C.a = arg0;
        D_001ED450.a = arg1;
        D_001ED43C.a = 0;
        D_001ED438.a = 5;
    }
}
