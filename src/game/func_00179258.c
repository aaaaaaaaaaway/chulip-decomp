extern void func_0010A190(int x, int y);
extern void func_00107658(int x, int y);
extern void func_00110D10(int a, int x, int y);
extern void func_00110020(short a, int x);
extern void func_0010E6F8(short a, int x);
extern void func_0010F5E8(short a, int x);
extern void func_0010C148(short a, int x);

void func_00179258(unsigned short kind, unsigned short arg, short x, short y) {
    switch (kind) {
    case 5:
        func_0010A190(x, y);
        break;
    case 6:
        func_00107658(x, y);
        break;
    case 10:
        func_00110D10(arg, x, y);
        break;
    case 20:
        func_00110020(arg, x);
        break;
    case 21:
        func_0010E6F8(arg, x);
        break;
    case 22:
        func_0010F5E8(arg, x);
        break;
    case 23:
        func_0010C148(arg, x);
        break;
    case 3:
        break;
    }
}
