struct S { int a, b, c; volatile float f; };
extern struct S *D_001ED238;
extern struct S *D_001ED23C;

void func_0011FC30(int i, int v) {
    (D_001ED238 + i)->f = (float)v;
    (D_001ED23C + i)->f = (float)v;
}
