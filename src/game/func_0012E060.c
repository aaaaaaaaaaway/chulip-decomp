extern char D_001A6998[];
extern char D_001A69AD[];
extern unsigned short D_001A69EC[];
extern unsigned short D_001A69EE[];
extern unsigned short D_001A69F0[];
extern unsigned short D_001A69F2[];
extern int D_001A69F4[];
extern int D_001A69F8[];
extern unsigned char D_001A69FC[];
extern unsigned short D_001A69FE[];

extern int func_00192940(void *destination, void *source);
extern void *func_0012DFF0(char *buffer);

void func_0012E060(unsigned short field, unsigned int value, char *buffer) {
    switch (field) {
    case 0:
        if (buffer == 0) {
            break;
        }
        func_00192940(D_001A6998, buffer);
        func_00192940(D_001A6998 + 0x2A, func_0012DFF0(buffer));
        break;
    case 13:
        if (buffer == 0) {
            break;
        }
        func_00192940(D_001A69AD, buffer);
        func_00192940(D_001A69AD + 0x2A, func_0012DFF0(buffer));
        break;
    case 1:
        D_001A69EC[0] = value;
        break;
    case 2:
        D_001A69EE[0] = value;
        break;
    case 3:
        D_001A69F0[0] = value;
        break;
    case 4:
        D_001A69F2[0] = value;
        break;
    case 5:
        if (0x7FFF < value) {
            D_001A69F4[0] = 0x7FFF;
        } else {
            D_001A69F4[0] = value;
        }
        break;
    case 6:
        D_001A69F8[0] = value;
        break;
    case 7:
        D_001A69FC[0] = value;
        break;
    case 9:
        D_001A69FE[0] = value;
        break;
    case 8:
    case 10:
    case 11:
    case 12:
        break;
    }
}
