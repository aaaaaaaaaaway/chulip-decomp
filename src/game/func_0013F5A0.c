struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED3C8;

int func_001595F8();

int func_0013F5A0(void) {
    return func_001595F8(((unsigned short *)D_001ED3C8.a)[10], ((short *)D_001ED3C8.a)[11], ((short *)D_001ED3C8.a)[12]);
}
