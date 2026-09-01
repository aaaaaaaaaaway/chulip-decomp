extern long D_001FFB40[];

int func_00136B80(unsigned char field) {
    switch (field) {
    case 0:
        return (int)D_001FFB40[0] & 1;
    case 22:
        return (int)(D_001FFB40[0] >> 15) & 1;
    case 15:
        return (int)(D_001FFB40[0] >> 13) & 1;
    case 16:
        return (int)(D_001FFB40[0] >> 14) & 1;
    case 18:
        return (int)(D_001FFB40[0] >> 18) & 1;
    case 19:
        return (int)(D_001FFB40[0] >> 19) & 1;
    case 20:
        return (int)(D_001FFB40[0] >> 20) & 1;
    case 21:
        return (int)(D_001FFB40[0] >> 21) & 1;
    case 23:
        return (int)(D_001FFB40[0] >> 16) & 1;
    case 6:
        return (int)(D_001FFB40[0] >> 4) & 1;
    case 24:
        return (int)(D_001FFB40[0] >> 28) & 1;
    case 25:
        return (int)(D_001FFB40[0] >> 29) & 1;
    case 26:
        return (int)(D_001FFB40[0] >> 31) & 1;
    case 27:
        return (int)((unsigned long)D_001FFB40[0] >> 37) & 1;
    case 28:
        return (int)((unsigned long)D_001FFB40[0] >> 39) & 1;
    case 29:
        return (int)(D_001FFB40[0] >> 22) & 1;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 17:
        break;
    }
    return 0;
}
