struct S8_short { short a; char pad[6]; };

extern struct S8_short D_001ED2B0;
extern struct S8_short D_001ED2B4;
extern short D_001ED2B8;
extern struct S8_short D_001ED2B2;
extern struct S8_short D_001ED2B6;
extern short D_001ED2BA;

void func_00127160(int arg0, int arg1, int arg2) {
    D_001ED2B4.a = arg1;
    D_001ED2B0.a = arg0;
    D_001ED2B8 = arg2;
}

void func_00127178(int arg0, int arg1, int arg2) {
    D_001ED2B6.a = arg1;
    D_001ED2B2.a = arg0;
    D_001ED2BA = arg2;
}
