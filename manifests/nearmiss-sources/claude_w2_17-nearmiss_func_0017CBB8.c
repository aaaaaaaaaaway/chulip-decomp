extern int D_001ECF60;

int func_0017C240();
int func_001987E0();

typedef struct {
    int a;
    int b;
    char c;
    char d;
} Cmd0017CBB8;

int func_0017CBB8(int arg0) {
    Cmd0017CBB8 buf;

    func_001987E0(D_001ECF60);
    buf.a = arg0;
    buf.b = 2;
    buf.c = -0x40;
    buf.d = 0x1F;
    return func_0017C240(0x30, &buf, 10);
}
