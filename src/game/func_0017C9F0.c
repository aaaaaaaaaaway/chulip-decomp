extern int D_001ECF60;

int func_0017C240();
int func_001987E0();

typedef struct {
    char a;
    char b;
    char c;
} Cmd0017C9F0;

int func_0017C9F0(int arg0, int arg1, int arg2) {
    Cmd0017C9F0 buf;

    func_001987E0(D_001ECF60);
    buf.a = arg0;
    buf.b = arg1;
    buf.c = arg2;
    return func_0017C240(0x25, &buf, 3);
}
