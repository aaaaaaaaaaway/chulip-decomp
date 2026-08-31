struct S8_char { char a; char pad[7]; };

extern char D_001ED1DC;
extern struct S8_char D_001ED1DD;
void func_00115F18();
void func_00116438();
void func_00116AE8();
void func_00117360();

int func_00112EB0();

int func_001159E0(void) {
    D_001ED1DD.a = 0;
    D_001ED1DC = 0;
    func_00112EB0(func_00115F18, 0, 0);
    func_00112EB0(func_00116438, 0, 0);
    func_00112EB0(func_00116AE8, 0, 0);
    return func_00112EB0(func_00117360, 0, 0);
}
