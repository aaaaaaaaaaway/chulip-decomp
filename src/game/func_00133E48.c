struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED354;

int func_00133E48(int arg0, int arg1) {
    ((int *)((arg0 * 96) + D_001ED354.a))[2] = arg1;
    return 96;
}
