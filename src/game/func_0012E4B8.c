extern unsigned short D_001A69EC[];
extern unsigned short D_001A69EE[];
extern unsigned short D_001A69F0[];
extern unsigned short D_001A69F2[];
extern int D_001A69F4[];
extern int D_001A69F8[];
extern unsigned char D_001A69FC[];
extern unsigned short D_001A69FE[];

unsigned int func_0012E4B8(unsigned short field, int bias) {
    switch (field) {
    case 1:
        return D_001A69EC[0] + bias;
    case 2:
        return D_001A69EE[0] + bias;
    case 3:
        return D_001A69F0[0] + bias;
    case 4:
        return D_001A69F2[0] + bias;
    case 5:
        return D_001A69F4[0] + bias;
    case 6:
        return D_001A69F8[0] + bias;
    case 7:
        return D_001A69FC[0] + bias;
    case 9:
        return D_001A69FE[0] + bias;
    case 0:
    case 8:
    default:
        return 0xFFFFFFFF;
    }
}
