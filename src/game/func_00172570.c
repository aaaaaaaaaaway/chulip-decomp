struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED790;

int func_00172570(int arg0) {
    return ((unsigned short *)(((arg0 & 255) * 22) + D_001ED790.a))[8];
}
