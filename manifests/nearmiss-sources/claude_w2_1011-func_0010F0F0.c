extern int D_001ED164;
extern int D_001ED168;
extern int D_001ED16C;

void func_0010F0F0(int source) {
    int count;
    int in;
    int out;
    count = 0;
    D_001ED16C = source;
    if (D_001ED168 > 0) {
        out = 0;
        in = 0;
        do {
            count++;
            *(int *)(out + D_001ED164 + 0x04) = 0x80808080;
            *(float *)(out + D_001ED164 + 0x10) = (float)*(int *)(in + D_001ED16C);
            *(float *)(out + D_001ED164 + 0x14) = (float)*(int *)(in + D_001ED16C + 4);
            *(float *)(out + D_001ED164 + 0x18) = (float)*(int *)(in + D_001ED16C + 8);
            *(float *)(out + D_001ED164 + 0x1C) = 1.0f;
            *(float *)(out + D_001ED164 + 0x20) = (float)*(int *)(in + D_001ED16C + 0xC);
            *(float *)(out + D_001ED164 + 0x24) = (float)*(int *)(in + D_001ED16C + 0x10);
            *(float *)(out + D_001ED164 + 0x28) = (float)*(int *)(in + D_001ED16C + 0x14);
            in += 0x18;
            *(float *)(out + D_001ED164 + 0x2C) = 1.0f;
            out += 0xC30;
        } while (count < D_001ED168);
    }
}
