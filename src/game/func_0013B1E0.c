struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED3C8;

int func_00179360();

int func_0013B1E0(void) {
    return func_00179360(4096, ((short *)D_001ED3C8.a)[10], 127);
}
