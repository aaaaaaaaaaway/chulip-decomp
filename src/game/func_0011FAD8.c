extern int D_001ED234;
extern int D_001ED244;
extern int D_001ED24C;
extern int D_001ED254;
extern int D_001ED260;

void func_0011FAD8(int which, int value) {
    switch (which) {
    case -1:
        D_001ED260 = value;
        D_001ED234 = value;
        D_001ED244 = value;
        D_001ED24C = value;
    case 3:
        D_001ED254 = value;
        break;
    case 0:
        D_001ED234 = value;
        break;
    case 1:
        D_001ED244 = value;
        break;
    case 2:
        D_001ED24C = value;
        break;
    case 4:
        D_001ED260 = value;
        break;
    case 5:
        break;
    }
}
