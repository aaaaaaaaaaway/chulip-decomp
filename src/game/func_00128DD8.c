struct S8_int { int a; char pad[4]; };

extern char D_001EC904;
extern struct S8_int D_001ED32C;
extern int D_001ED330;

int func_00151CA8();

void func_00128DD8(void) {
    func_00151CA8(D_001ED32C.a);
    func_00151CA8(D_001ED330);
    D_001EC904 = -1;
}
