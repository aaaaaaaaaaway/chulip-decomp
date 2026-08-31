struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED0F8;

void func_0010A1D8(int arg0) {
    ((int *)D_001ED0F8.a)[0] = arg0;
}

void func_0010A1E8(void) {
    ((int *)D_001ED0F8.a)[3] = -((int *)D_001ED0F8.a)[3];
}
