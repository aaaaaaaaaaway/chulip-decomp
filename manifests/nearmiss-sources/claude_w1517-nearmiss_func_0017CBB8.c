typedef struct Msg30 {
    int value;
    int kind;
    signed char a;
    signed char b;
} Msg30;

extern int D_001ECF60;

int func_001987E0(int handle);
int func_0017C240(int opcode, void *data, int size);

int func_0017CBB8(int value) {
    Msg30 msg;

    func_001987E0(D_001ECF60);
    msg.value = value;
    msg.kind = 2;
    msg.a = -0x40;
    msg.b = 0x1F;
    return func_0017C240(0x30, &msg, 10);
}
