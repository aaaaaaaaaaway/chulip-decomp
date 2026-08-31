struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED264;

void func_001255D8(int arg0, int arg1) {
    ((int *)((arg0 << 6) + D_001ED264.a))[0] = arg1;
}
