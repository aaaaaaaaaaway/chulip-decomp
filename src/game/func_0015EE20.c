typedef struct {
    unsigned char unknown00[0x100];
    char *choices[10];
    unsigned char unknown128, count;
    unsigned short unknown12A;
    short x, y;
} ChoiceMenu;
extern int D_001ED4B4, D_001ED4B8, D_001ED4BC;
float D_001ECD08 = 1.0f;
float D_001ECD0C = 0.5f;
extern int func_0015F0B0(char *, long, long);
extern int func_00161FE0(int, int);
extern void func_00179360(int, int, int);
extern void func_00112F40(void (*)(void));
extern void func_001272A8(float, float);
extern void func_00127270(short, short);
extern void func_001272D0(int, int, int, int);
extern void func_00127178(int, int, int);
extern void func_001271F0(short, short, unsigned short);
extern char *func_001273B8(char *, char *);

int func_0015EE20(char *packet, int unused, ChoiceMenu *menu) {
    char *cursor = packet + func_0015F0B0(packet, 0x47, 0x3001B) * 16;
    int i;
    if (func_00161FE0(0, 1) & 0x1000) {
        D_001ED4B4--;
        func_00179360(0x1000, 0x2A, 0x7F);
    } else if (func_00161FE0(0, 1) & 0x4000) {
        D_001ED4B4++;
        func_00179360(0x1000, 0x2A, 0x7F);
    }
    if (D_001ED4B4 < 0)
        D_001ED4B4 = 0;
    else if (D_001ED4B4 > menu->count - 1)
        D_001ED4B4 = menu->count - 1;
    if (D_001ED4B8 <= 0) {
        if (func_00161FE0(0, 1) & 0x20) {
            func_00179360(0x1000, 0x28, 0x7F);
            D_001ED4BC = D_001ED4B4;
            func_00112F40((void (*)(void))func_0015EE20);
            return 0;
        }
    } else {
        D_001ED4B8--;
    }
    func_001272A8(D_001ECD08, D_001ECD0C);
    func_00127270(1, 0);
    for (i = 0; i < menu->count; i++) {
        if (i == D_001ED4B4) {
            func_001272D0(200, 200, 128, 128);
            func_00127178(15, 45, 5);
        } else {
            func_001272D0(128, 128, 128, 32);
            func_00127178(0, 0, 0);
        }
        func_001271F0((float)menu->x, menu->y + i * (D_001ECD0C * 24.0f), 0xFFFF);
        cursor = func_001273B8(cursor, menu->choices[i]);
    }
    func_00127178(0, 0, 0);
    return (cursor - packet) / 16;
}
