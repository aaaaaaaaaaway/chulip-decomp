typedef struct {
    int id;
    char text[0x7C];
} Msg0017C6A8;

extern int D_001ECF60;

int func_0017C2D0();
int func_001987C0();
int func_001987E0();
int func_00192940();
int func_00192A54();

int func_0017C6A8(int id, char *text) {
    Msg0017C6A8 msg;
    int ret;

    func_001987E0(D_001ECF60);
    func_0017C2D0(0x42, 0, 0);
    msg.id = id;
    func_00192940(msg.text, text);
    ret = func_0017C2D0(0x10, &msg, func_00192A54(text) + 5);
    func_001987C0(D_001ECF60);
    return ret;
}
