struct S8_int { int a; char pad[4]; };

extern int D_001ED104;
extern int D_001ED108;
extern struct S8_int D_001ED10C;
void func_0010AB90();

int func_00112F40();
int func_00151CA8();

int func_0010AB58(void) {
    D_001ED10C.a = 1;
    D_001ED108 = 0;
    func_00112F40(func_0010AB90);
    return func_00151CA8(D_001ED104);
}
