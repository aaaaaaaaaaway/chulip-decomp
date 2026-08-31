struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED0B4;
extern int D_001ED0B8;
extern struct S8_int D_001ED0BC;
void func_001076F0();

int func_00112F40();
int func_00151CA8();

void func_00107618(void) {
    D_001ED0BC.a = 1;
    D_001ED0B8 = 0;
    func_00112F40(func_001076F0);
    func_00151CA8(D_001ED0B4.a);
    D_001ED0B4.a = 0;
}
