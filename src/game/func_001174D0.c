struct S8_int { int a; char pad[4]; };

extern char D_001ED1DC;
extern struct S8_int D_001ED1EC;
extern struct S8_int D_001ED1F0;

void func_001174D0(int arg0, int arg1) {
    D_001ED1EC.a = arg0;
    D_001ED1F0.a = arg1;
    D_001ED1DC = 1;
}
