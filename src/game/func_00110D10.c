extern int D_001ED17C;

void func_00110D10(int index, int field, int value) {
    switch (field) {
    case 0:
        *(int *)(index * 0x1320 + D_001ED17C + 4) = value;
        break;
    case 1:
        *(float *)(index * 0x1320 + D_001ED17C + 0x44) += (float)value;
        break;
    }
}
