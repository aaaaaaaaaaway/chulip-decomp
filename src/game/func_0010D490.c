extern char *D_001ED144[];

void func_0010D490(int index, float x, float y, float z) {
    *(float *)(D_001ED144[0] + index * 0x660 + 0x40) = x;
    *(float *)(D_001ED144[0] + index * 0x660 + 0x44) = y;
    *(float *)(D_001ED144[0] + index * 0x660 + 0x48) = z;
}
