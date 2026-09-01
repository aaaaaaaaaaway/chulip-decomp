typedef struct Msg30 {
    int value;
    int kind;
    signed char a;
    signed char b;
    signed char c;
    signed char d;
    signed char e;
    signed char f;
    signed char g;
} Msg30;

extern int D_001ECF60;

int func_001987E0(int handle);
int func_0017C240(int opcode, void *data, int size);

int func_0017CA50(int value, int a, int b, int c, int d, int e) {
    Msg30 msg;

    func_001987E0(D_001ECF60);
    msg.value = value;
    msg.kind = 7;
    msg.a = a | -0x60;
    msg.b = b;
    msg.c = c;
    msg.d = d;
    msg.e = e;
    msg.f = 0;
    msg.g = 0;
    return func_0017C240(0x30, &msg, 0xF);
}
