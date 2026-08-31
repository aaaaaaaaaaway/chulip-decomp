struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED170;

int func_00110000(int arg0, int arg1) {
    ((int *)((arg0 * 2064) + D_001ED170.a))[0] = arg1;
    return 2064;
}
