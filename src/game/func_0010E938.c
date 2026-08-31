extern char *D_001ED158[];

void func_0010E938(int index, float x, float y, float z) {
    *(float *)(D_001ED158[0] + index * 0x630 + 0x10) = x;
    *(float *)(D_001ED158[0] + index * 0x630 + 0x14) = y;
    *(float *)(D_001ED158[0] + index * 0x630 + 0x18) = z;
}
