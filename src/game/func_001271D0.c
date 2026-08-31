struct S8_short { short a; char pad[6]; };

extern struct S8_short D_001ED2CA;
extern short D_001ED2CC;
extern struct S8_short D_001ED2CE;
extern struct S8_short D_001ED2D0;

void func_001271D0(int arg0, int arg1, int arg2) {
    D_001ED2CA.a = arg0;
    D_001ED2CE.a = arg1;
    D_001ED2D0.a = arg2;
    D_001ED2CC = 0;
}
