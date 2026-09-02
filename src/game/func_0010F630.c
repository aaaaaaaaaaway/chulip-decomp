extern int D_001ED164;
extern int D_001ED168;
int func_00192568(void);

void func_0010F630(void) {
    int i;
    int j;
    int k;
    int off;
    int pos;
    int vel;
    int row;
    int base;

    for (i = 0; i < D_001ED168; i++) {
        for (j = 0; j < 0x40; j++) {
            base = i * 0xC30;
            off = j * 0x30;
            if (*(int *)(base + D_001ED164 + off + 0x50) > 0) {
                *(int *)(base + D_001ED164 + off + 0x50) -= 1;
                if (*(int *)(base + D_001ED164) != 0 &&
                    *(int *)(base + D_001ED164 + off + 0x50) <= 0) {
                    *(int *)(base + D_001ED164 + off + 0x50) = 0x60 - func_00192568() % 0x30;
                    *(float *)(base + D_001ED164 + off + 0x30) = *(float *)(base + D_001ED164 + 0x10);
                    *(float *)(base + D_001ED164 + off + 0x34) = *(float *)(base + D_001ED164 + 0x14);
                    *(float *)(base + D_001ED164 + off + 0x38) = *(float *)(base + D_001ED164 + 0x18);
                    *(float *)(base + D_001ED164 + off + 0x40) =
                        (*(float *)(base + D_001ED164 + 0x20) + (float)(func_00192568() % 0x14) - 10.0f) * 0.3f;
                    *(float *)(base + D_001ED164 + off + 0x44) =
                        (*(float *)(base + D_001ED164 + 0x24) + (float)(func_00192568() % 0x14) - 10.0f) * 0.3f;
                    *(float *)(base + D_001ED164 + off + 0x48) =
                        (*(float *)(base + D_001ED164 + 0x28) + (float)(func_00192568() % 0x14) - 10.0f) * 0.3f;
                }
                for (k = 0; k < 3; k++) {
                    pos = i * 0xC30 + D_001ED164 + 0x30;
                    *(float *)(pos + (j * 0x30 + k * 4)) += *(float *)(i * 0xC30 + D_001ED164 + (j * 0x30 + k * 4) + 0x40);
                    vel = i * 0xC30 + D_001ED164 + 0x40;
                    *(float *)(vel + (j * 0x30 + k * 4)) *= 0.93f;
                }
                row = j * 0x30;
                *(float *)(i * 0xC30 + D_001ED164 + row + 0x44) -= 0.2f;
            }
        }
    }
}
