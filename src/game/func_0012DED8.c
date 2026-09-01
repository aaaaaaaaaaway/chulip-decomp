extern char D_001A6998[];
extern char D_001A69AD[];
extern char D_001A69C2[];
extern char D_001A69D7[];
extern unsigned short D_001A69EC[];
extern unsigned short D_001A69EE[];
extern unsigned short D_001A69F0[];
extern unsigned short D_001A69F2[];
extern int D_001A69F4[];
extern int D_001A69F8[];
extern unsigned char D_001A69FC[];
extern unsigned short D_001A69FE[];

extern int func_00192940(void *destination, void *source);

unsigned int func_0012DED8(unsigned short field, char *buffer) {
    switch (field) {
    case 0:
        if (buffer != 0) {
            func_00192940(buffer, D_001A6998);
        }
        break;
    case 13:
        if (buffer != 0) {
            func_00192940(buffer, D_001A69AD);
        }
        break;
    case 14:
        if (buffer != 0) {
            func_00192940(buffer, D_001A69C2);
        }
        break;
    case 15:
        if (buffer != 0) {
            func_00192940(buffer, D_001A69D7);
        }
        break;
    case 1:
        return D_001A69EC[0];
    case 2:
        return D_001A69EE[0];
    case 3:
        return D_001A69F0[0];
    case 4:
        return D_001A69F2[0];
    case 5:
        return D_001A69F4[0];
    case 6:
        return D_001A69F8[0];
    case 7:
        return D_001A69FC[0];
    case 9:
        return D_001A69FE[0];
    case 8:
    case 10:
    case 11:
    case 12:
        break;
    }
    return 0xFFFFFFFF;
}
