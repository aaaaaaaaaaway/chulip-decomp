extern int D_001ED164;
extern int D_001ED168;
extern int D_001ED16C;

void func_0010F0F0(int source) {
    int i;

    D_001ED16C = source;
    for (i = 0; i < D_001ED168; i++) {
        *(int *)(i * 0xC30 + D_001ED164 + 0x4) = 0x80808080;
        *(float *)(i * 0xC30 + D_001ED164 + 0x10) = (float)*(int *)(i * 0x18 + D_001ED16C);
        *(float *)(i * 0xC30 + D_001ED164 + 0x14) = (float)*(int *)(i * 0x18 + D_001ED16C + 4);
        *(float *)(i * 0xC30 + D_001ED164 + 0x18) = (float)*(int *)(i * 0x18 + D_001ED16C + 8);
        *(float *)(i * 0xC30 + D_001ED164 + 0x1C) = 1.0f;
        *(float *)(i * 0xC30 + D_001ED164 + 0x20) = (float)*(int *)(i * 0x18 + D_001ED16C + 0xC);
        *(float *)(i * 0xC30 + D_001ED164 + 0x24) = (float)*(int *)(i * 0x18 + D_001ED16C + 0x10);
        *(float *)(i * 0xC30 + D_001ED164 + 0x28) = (float)*(int *)(i * 0x18 + D_001ED16C + 0x14);
        *(float *)(i * 0xC30 + D_001ED164 + 0x2C) = 1.0f;
    }
}
