extern int D_001ED550[2];
extern int D_001ED558[2];
extern int D_001ED560[2];

int func_00161FE0(int index, int which) {
    int value;

    switch (which) {
    case 0:  value = D_001ED550[index]; break;
    case 1:  value = D_001ED558[index]; break;
    case 2:  value = D_001ED560[index]; break;
    default: value = 0; break;
    }
    if (value & 0x40) {
        value ^= 0x40;
        value |= 0x20;
    } else if (value & 0x20) {
        value ^= 0x20;
        value |= 0x40;
    }
    return value;
}
