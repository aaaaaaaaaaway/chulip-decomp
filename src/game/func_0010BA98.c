extern int D_001ED11C;

void func_0010BA98(int index, float *pos, float *delta, int flag, int *extra) {
    *(float *)(index * 0x70 + D_001ED11C + 0x10) = pos[0];
    *(float *)(index * 0x70 + D_001ED11C + 0x14) = pos[1];
    *(float *)(index * 0x70 + D_001ED11C + 0x18) = pos[2];
    *(float *)(index * 0x70 + D_001ED11C + 0x1C) = 1.0f;
    *(int *)(index * 0x70 + D_001ED11C + 0x20) = extra[0];
    *(int *)(index * 0x70 + D_001ED11C + 0x24) = extra[1];
    *(int *)(index * 0x70 + D_001ED11C + 0x28) = extra[2];
    *(int *)(index * 0x70 + D_001ED11C + 0x2C) = extra[3];
    *(int *)(index * 0x70 + D_001ED11C + 0x30) = 0x1F4;
    *(float *)(index * 0x70 + D_001ED11C + 0x40) = pos[0] + delta[0];
    *(float *)(index * 0x70 + D_001ED11C + 0x44) = pos[1] + delta[1];
    *(float *)(index * 0x70 + D_001ED11C + 0x48) = pos[2] + delta[2];
    *(float *)(index * 0x70 + D_001ED11C + 0x4C) = 1.0f;
    *(int *)(index * 0x70 + D_001ED11C + 0x50) = 0;
    *(int *)(index * 0x70 + D_001ED11C + 0x54) = 0;
    *(int *)(index * 0x70 + D_001ED11C + 0x58) = 0;
    *(int *)(index * 0x70 + D_001ED11C + 0x5C) = 0;
    *(int *)(index * 0x70 + D_001ED11C + 0x60) = flag;
}
