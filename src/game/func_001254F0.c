extern int D_001ED264;

void func_001254F0(int index, int a1, int a2, int a3, int a4, int a5, int a6, float *vector, int a8, int a9) {
    int offset;

    offset = index * 0x40;
    *(int *)(offset + D_001ED264) = -1;
    *(float *)(offset + D_001ED264 + 0x30) = vector[0];
    *(float *)(offset + D_001ED264 + 0x34) = vector[1];
    *(float *)(offset + D_001ED264 + 0x38) = vector[2];
    *(int *)(offset + D_001ED264 + 0xC) = a3;
    *(int *)(offset + D_001ED264 + 0x10) = a4;
    *(int *)(offset + D_001ED264 + 0x14) = -a5;
    *(int *)(offset + D_001ED264 + 0x18) = a6;
    *(int *)(offset + D_001ED264 + 0x1C) = a8;
    *(int *)(offset + D_001ED264 + 0x20) = a9;
    *(int *)(offset + D_001ED264 + 0x4) = a1;
    *(int *)(offset + D_001ED264 + 0x8) = a2;
}
