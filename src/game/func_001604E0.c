struct Packet16 {
    int word[4];
};

struct HudBox {
    char pad_0x0[4];
    int enabled;
    char pad_0x8[0x18];
    int x;
    int y;
    int arg2;
    int arg3;
};

extern int D_001ED4DC;
extern int D_001ED4E0;
extern char D_001ECD38[];

extern int func_001610F0(struct Packet16 *out, int x, int y, int a, int b);
extern int func_00161FE0(int index, int which);
extern void func_00179360(int a, int b, int c);
extern void func_0015F4A8(void);
extern void func_001272A8(float a, float b);
extern void func_001271F0(short x, short y, int flags);
extern void func_001272D0(int r, int g, int b, int a);
extern struct Packet16 *func_001273B8(struct Packet16 *out, char *text);
extern int func_00160D18(struct Packet16 *out, int x, int y);

int func_001604E0(struct Packet16 *out, struct HudBox *box) {
    struct Packet16 *end;
    int total;
    int x;
    int y;

    total = func_001610F0(out, box->x, box->y, box->arg2, box->arg3);
    out += total;
    if (box->enabled != 1) {
        return 0;
    }
    if (D_001ED4DC == 3) {
        if (func_00161FE0(0, 1) & 0x1000) {
            func_00179360(0x1000, 0x2A, 0x7F);
            D_001ED4E0 = 2;
        }
        if (func_00161FE0(0, 1) & 0x20) {
            func_00179360(0x1000, 0x28, 0x7F);
            func_0015F4A8();
        }
    }
    x = box->x + 6;
    y = box->y + 1;
    func_001272A8(0.9f, 0.45f);
    func_001271F0((short)x, (short)y, 0xFFF0);
    if (D_001ED4DC == 3) {
        func_001272D0(0xC8, 0xC8, 0x80, 0x80);
    } else {
        func_001272D0(0x80, 0x80, 0x80, 0x80);
    }
    end = func_001273B8(out, D_001ECD38);
    total += ((char *)end - (char *)out) / 16;
    if (D_001ED4DC == 3) {
        total += func_00160D18(end, x + 6, y + 1);
    }
    return total;
}
