struct S8_char { char a; char pad[7]; };

extern struct S8_char D_001ED2D2;
extern struct S8_char D_001ED2D3;
extern struct S8_char D_001ED2D4;
extern char D_001ED2D5;

void func_001272D0(int arg0, int arg1, int arg2, int arg3) {
    D_001ED2D2.a = arg0;
    D_001ED2D3.a = arg1;
    D_001ED2D4.a = arg2;
    D_001ED2D5 = arg3;
}
