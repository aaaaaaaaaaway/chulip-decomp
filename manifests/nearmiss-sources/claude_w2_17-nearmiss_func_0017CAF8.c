extern int D_001ECF60;

int func_0017C240();
int func_001987E0();

typedef struct {
    int a;
    int b;
    char c;
    char d;
    char e;
    char f;
    char g;
    char h;
    char i;
} Cmd0017CAF8;

int func_0017CAF8(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    Cmd0017CAF8 buf;

    func_001987E0(D_001ECF60);
    buf.a = arg0;
    buf.b = 7;
    buf.c = arg1 | -0x60;
    buf.d = arg2;
    buf.e = arg3;
    buf.f = arg4;
    buf.g = arg5;
    buf.h = arg6 & 0x7F;
    buf.i = (arg6 >> 7) & 0x7F;
    return func_0017C240(0x30, &buf, 15);
}
