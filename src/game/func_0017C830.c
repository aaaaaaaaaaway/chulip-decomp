typedef struct {
    char kind;
    char slot;
    char text[0x7E];
} Msg0017C830;

extern int D_001ECF60;

int func_0017C2D0();
int func_001987C0();
int func_001987E0();
int func_00192940();
int func_00192A54();

int func_0017C830(int kind, int slot, char *name, char *text) {
    Msg0017C830 msg;
    int len;
    int ret;

    func_001987E0(D_001ECF60);
    func_0017C2D0(0x42, 0, 0);
    if (kind == 0 && slot == 0) {
        func_0017C2D0(0x14, 0, 0);
    }
    msg.kind = kind;
    msg.slot = slot;
    func_00192940(msg.text, name);
    len = func_00192A54(name);
    func_00192940(&msg.text[len + 1], text);
    len += 4;
    ret = func_0017C2D0(0x20, &msg, len + func_00192A54(text));
    func_001987C0(D_001ECF60);
    return ret;
}
