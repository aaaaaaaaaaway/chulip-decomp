struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED700;

void func_001734C0(int arg0, int arg1) {
    ((short *)((arg0 << 1) + D_001ED700.a))[0] = arg1;
}
