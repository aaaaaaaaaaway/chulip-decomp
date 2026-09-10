extern int D_001ED238;
extern int D_001ED23C;

void func_0011FC30(int index, int value) {
    *(float *)(index * 16 + D_001ED238 + 0xC) = (float)value;
    *(float *)(index * 16 + D_001ED23C + 0xC) = (float)value;
}
