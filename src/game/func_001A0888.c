typedef struct { int f0; int f4; int f8; int pad[5]; } A;
extern int D_001E5BAC[];
extern int D_001E5BB0[];
extern int func_001987A0(A *);
void func_001A0888(void)
{
    A a;
    A b;

    a.f4 = 1;
    a.f8 = 1;
    b.f4 = 1;
    b.f8 = 1;
    D_001E5BAC[0] = func_001987A0(&a);
    D_001E5BB0[0] = func_001987A0(&b);
}
