extern int D_001ED170;
extern int D_001ED178;
int func_00192568(void);

void func_00110020(short index) {
    int j;
    int base;
    int src;
    int off;

    base = index * 0x810;
    src = index * 0x18;
    for (j = 0; j < 0x20; j++) {
        off = j * 0x40;
        *(float *)(base + D_001ED170 + off + 0x10) = (float)*(int *)(src + D_001ED178);
        *(float *)(base + D_001ED170 + off + 0x14) = (float)*(int *)(src + D_001ED178 + 4);
        *(float *)(base + D_001ED170 + off + 0x18) = (float)*(int *)(src + D_001ED178 + 8);
        *(float *)(base + D_001ED170 + off + 0x1C) = 1.0f;
        *(float *)(base + D_001ED170 + off + 0x2C) = 1.0f;
        *(float *)(base + D_001ED170 + off + 0x30) = (float)(*(int *)(src + D_001ED178 + 0xC) + func_00192568() % 0x14 - 0xA);
        *(float *)(base + D_001ED170 + off + 0x34) = (float)(*(int *)(src + D_001ED178 + 0x10) + func_00192568() % 0x14 - 0xA);
        *(float *)(base + D_001ED170 + off + 0x38) = (float)(*(int *)(src + D_001ED178 + 0x14) + func_00192568() % 0x14 - 0xA);
        *(float *)(base + D_001ED170 + off + 0x3C) = 1.0f;
        *(int *)(base + D_001ED170 + off + 0x40) = 0x20 - func_00192568() % 0x20;
    }
    *(int *)(index * 0x810 + D_001ED170) = 1;
}
