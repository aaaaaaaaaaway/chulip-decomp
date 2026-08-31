extern char *D_001ED164[];

void func_0010F5F0(int index, float x, float y, float z) {
    *(float *)(D_001ED164[0] + index * 0xC30 + 0x10) = x;
    *(float *)(D_001ED164[0] + index * 0xC30 + 0x14) = y;
    *(float *)(D_001ED164[0] + index * 0xC30 + 0x18) = z;
}
