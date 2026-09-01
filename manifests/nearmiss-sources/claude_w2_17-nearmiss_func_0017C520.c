typedef struct {
    int flags;
    int id;
    unsigned short lo;
    unsigned short hi;
    int x;
    int y;
} Cmd0017C520;

extern int D_001ECF60;
extern int D_001ECF64;

int func_0017C240();
int func_001987E0();

int func_0017C520(int id, int value, int x, int y) {
    Cmd0017C520 cmd;
    int arg;

    arg = value;
    func_001987E0(D_001ECF60);
    if (id == D_001ECF64) {
        return func_0017C240(2, &arg, 4);
    }
    {
        cmd.flags = 0;
        cmd.id = id | 0x100;
        cmd.lo = arg;
        cmd.hi = arg;
        cmd.x = x;
        cmd.y = y;
        D_001ECF64 = id;
        return func_0017C240(3, &cmd, 0x14);
    }
}
