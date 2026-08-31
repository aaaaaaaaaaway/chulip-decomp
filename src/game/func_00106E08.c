struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED0A8;
extern int D_001ED0AC;
extern struct S8_int D_001ED0B0;
void func_00106E48();

int func_00112F40();
int func_00151CA8();

void func_00106E08(void) {
    D_001ED0B0.a = 1;
    D_001ED0AC = 0;
    func_00112F40(func_00106E48);
    func_00151CA8(D_001ED0A8.a);
    D_001ED0A8.a = 0;
}
