extern int D_001ECB70, D_001ECB74, D_001ECB78, D_001ECB7C;
extern int D_001ECB80, D_001ECB84, D_001ECB88, D_001ECB98, D_001ECBA0;
extern char *D_001ECB94, *D_001ECB9C;
extern char D_001E96E8[], D_001E9740[], D_001E9778[], D_001E97F0[], D_001E9848[];
extern char D_001A89C8[], D_001A8A58[], D_001E98A0[], D_001E98B8[];
extern char D_001E98D0[], D_001E98F0[], D_001E9910[], D_001E9928[], D_001E9940[];
extern char D_001E9958[], D_001E9980[], D_001E9998[];
extern int func_00161FE0(int, int);
extern int func_001500D8(void), func_001500C8(void), func_00150110(int), func_001500F8(int);
extern void func_00150008(int, int, int), func_00150050(int, int, int);
extern void func_00179360(int, int, int);
void func_001505C0(void) {
    int buttons = func_00161FE0(0, 1);
    int device = func_001500D8();
    int result = func_001500C8();
    int changed, check;
    D_001ECB88 = 0;
    D_001ECB98 = 0;
    switch (device) {
    case 0:
        D_001ECB98 = 1;
        D_001ECB9C = D_001E96E8;
        break;
    case 1:
        D_001ECB98 = 1;
        D_001ECB9C = D_001E9740;
        break;
    case 4:
        D_001ECB88 = 1;
        D_001ECB94 = D_001E9778;
        break;
    case 5:
        D_001ECB88 = 1;
        D_001ECB94 = D_001E97F0;
        break;
    case 6:
        D_001ECB88 = 1;
        D_001ECB94 = D_001E9848;
        break;
    }
    switch (D_001ECBA0) {
    case 0:
        if (buttons & 0x40) {
            func_00179360(0x1000, 0x29, 0x7F);
            D_001ECB7C = 3;
            break;
        }
        if ((unsigned int)device < 2) {
            D_001ECB80 = 0;
            break;
        }
        D_001ECB80 = 1;
        changed = 0;
        if ((buttons & 0x1000) && D_001ECB84 > 0) {
            --D_001ECB84;
            changed = 1;
        }
        if ((buttons & 0x4000) && D_001ECB84 < 2) {
            ++D_001ECB84;
            changed = 1;
        }
        if (changed == 1)
            func_00179360(0x1000, 0x2A, 0x7F);
        if (buttons & 0x20) {
            if (D_001ECB78 == 0) {
                check = func_00150110(0x35);
                if (check < 0)
                    D_001ECBA0 = 0;
                else if (check > 0) {
                    D_001ECBA0 = 2;
                    func_00179360(0x1000, 0x28, 0x7F);
                } else {
                    D_001ECBA0 = 1;
                    func_00179360(0x1000, 0x28, 0x7F);
                }
            } else if (D_001ECB78 == 1) {
                if (func_001500F8(D_001ECB84)) {
                    D_001ECBA0 = 3;
                    func_00179360(0x1000, 0x28, 0x7F);
                } else
                    func_00179360(0x1000, 0x29, 0x7F);
            }
        }
        break;
    case 1:
        if ((unsigned int)device - 2 >= 2) {
            D_001ECBA0 = 0;
            break;
        }
        D_001ECB88 = 2;
        D_001ECB94 = D_001A89C8;
        if (buttons & 0x60) {
            func_00179360(0x1000, 0x28, 0x7F);
            D_001ECBA0 = 0;
        }
        break;
    case 2:
        if ((unsigned int)device - 2 >= 2) {
            D_001ECBA0 = 0;
            break;
        }
        D_001ECB88 = 3;
        if (device == 2)
            D_001ECB94 = D_001A8A58;
        else
            D_001ECB94 = D_001E98A0;
        if (buttons & 0x40) {
            func_00179360(0x1000, 0x29, 0x7F);
            D_001ECBA0 = 0;
        }
        if (buttons & 0x20) {
            func_00179360(0x1000, 0x28, 0x7F);
            func_00150008(D_001ECB84, D_001ECB70, D_001ECB74);
            D_001ECBA0 = 5;
        }
        break;
    case 3:
        if ((unsigned int)device - 2 >= 2)
            D_001ECBA0 = 0;
        D_001ECB88 = 3;
        D_001ECB94 = D_001E98B8;
        if (buttons & 0x40) {
            func_00179360(0x1000, 0x29, 0x7F);
            D_001ECBA0 = 0;
        }
        if (buttons & 0x20) {
            func_00179360(0x1000, 0x28, 0x7F);
            func_00150050(D_001ECB84, D_001ECB70, D_001ECB74);
            D_001ECBA0 = 5;
        }
        break;
    case 5:
        if (result == 0)
            break;
        if (result == 1 && D_001ECB78 == 1) {
            D_001ECBA0 = 7;
            break;
        }
        if (result == -9) {
            D_001ECBA0 = 0;
            break;
        }
        if ((unsigned int)device < 2)
            D_001ECB80 = 0;
        else
            D_001ECB80 = 1;
        D_001ECB88 = 2;
        switch (result) {
        case 1:
            D_001ECB94 = D_001E98D0;
            break;
        case -2:
            D_001ECB94 = D_001E98F0;
            break;
        case -3:
            D_001ECB94 = D_001E9910;
            break;
        case -4:
            D_001ECB94 = D_001E9928;
            break;
        case -5:
            D_001ECB94 = D_001E9940;
            break;
        case -6:
            D_001ECB94 = D_001E9958;
            break;
        case -7:
            D_001ECB94 = D_001E9980;
            break;
        case -8:
            D_001ECB94 = D_001A89C8;
            break;
        }
        if (buttons & 0x60) {
            func_00179360(0x1000, 0x28, 0x7F);
            D_001ECBA0 = 0;
        }
        break;
    case 7:
        if (result == -9 || device == 0 || device == 1)
            D_001ECB80 = 0;
        D_001ECB88 = 2;
        D_001ECB94 = D_001E9998;
        D_001ECB98 = 0;
        if (buttons & 0x60) {
            func_00179360(0x1000, 0x28, 0x7F);
            D_001ECB7C = 0;
            D_001ECBA0 = 0;
        }
        break;
    }
}
