struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED290;
extern int D_001ED294;

int func_00126B20(int arg0) {
    D_001ED290.a = 0;
    D_001ED294 = arg0;
    return (arg0 + 32);
}
