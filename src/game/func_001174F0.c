struct S8_int { int a; char pad[4]; };

extern char D_001ED1DC;
extern struct S8_int D_001ED1EC;
extern struct S8_int D_001ED1F0;

void func_001174F0(void) {
    D_001ED1EC.a = 0;
    D_001ED1F0.a = 0;
    D_001ED1DC = 0;
}
