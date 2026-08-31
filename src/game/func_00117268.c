struct S8_char { char a; char pad[7]; };

extern char D_001ED1E0;
extern struct S8_char D_001ED1E1;
extern int D_001ED1E8;

void func_00117268(int arg0, int arg1) {
    D_001ED1E0 = arg1;
    if ((arg0 & 255) != 0) {
        D_001ED1E1.a = 1;
    } else {
        D_001ED1E1.a = 0;
    }
    D_001ED1E8 = 0;
    return;
}
