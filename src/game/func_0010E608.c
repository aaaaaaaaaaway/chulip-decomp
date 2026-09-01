extern int D_001ED158;
extern int D_001ED15C;
extern int D_001ED160;

void func_0010E608(int source) {
    int count;
    int in;
    int out;

    count = 0;
    D_001ED160 = source;
    if (D_001ED15C > 0) {
        in = 0;
        out = 0;
        do {
            count++;
            *(float *)(out + D_001ED158 + 0x10) = (float)*(int *)(in + D_001ED160);
            *(float *)(out + D_001ED158 + 0x14) = (float)*(int *)(in + D_001ED160 + 4);
            *(float *)(out + D_001ED158 + 0x18) = (float)*(int *)(in + D_001ED160 + 8);
            in += 0x1C;
            *(float *)(out + D_001ED158 + 0x1C) = 1.0f;
            out += 0x630;
        } while (count < D_001ED15C);
    }
}
