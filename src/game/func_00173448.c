struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED700;

int func_00173448(int arg0) {
    return ((short *)(((arg0 & 65535) << 1) + D_001ED700.a))[0];
}
