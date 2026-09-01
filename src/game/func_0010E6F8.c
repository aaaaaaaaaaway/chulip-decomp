extern int D_001ED158;
extern int D_001ED160;
int func_00192568(void);

void func_0010E6F8(short index) {
    int j;
    int base;
    int off;

    base = index * 0x630;
    for (j = 0; j < 0x20; j++) {
        off = j * 0x30;
        *(float *)(base + D_001ED158 + off + 0x30) = *(float *)(base + D_001ED158 + 0x10);
        *(float *)(base + D_001ED158 + off + 0x34) = *(float *)(base + D_001ED158 + 0x14);
        *(float *)(base + D_001ED158 + off + 0x38) = *(float *)(base + D_001ED158 + 0x18);
        *(float *)(base + D_001ED158 + off + 0x3C) = 1.0f;
        *(float *)(base + D_001ED158 + off + 0x40) = (float)(func_00192568() % 0x28 - 0x14);
        *(float *)(base + D_001ED158 + off + 0x44) = (float)(func_00192568() % 0x14 - 0x14);
        *(float *)(base + D_001ED158 + off + 0x48) = (float)(func_00192568() % 0x28 - 0x14);
        *(float *)(base + D_001ED158 + off + 0x4C) = 1.0f;
        *(int *)(base + D_001ED158 + off + 0x50) = 0x20 - func_00192568() % 0x20;
    }
    *(int *)(index * 0x630 + D_001ED158 + 4) =
        *(unsigned char *)(index * 0x1C + D_001ED160 + 0x0C) |
        (*(unsigned char *)(index * 0x1C + D_001ED160 + 0x10) << 8) |
        (*(unsigned char *)(index * 0x1C + D_001ED160 + 0x14) << 16) |
        (*(unsigned char *)(index * 0x1C + D_001ED160 + 0x18) << 24);
    *(int *)(index * 0x630 + D_001ED158) = 1;
}
