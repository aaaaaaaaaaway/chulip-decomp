struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED740;

int func_00173428(int arg0) {
    return ((unsigned short *)(((arg0 & 65535) << 1) + D_001ED740.a))[0];
}
