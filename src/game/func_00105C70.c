extern int D_001ED090;
int func_00192568(void);

void func_00105C70(int index, int p2, int p3, int unused, int *p5) {
    int i;
    int off;

    *(int *)(index * 0x2B0 + D_001ED090 + 0x14) = 0;
    *(int *)(index * 0x2B0 + D_001ED090 + 0x0C) = 0;
    *(int *)(index * 0x2B0 + D_001ED090 + 0x10) = 0x3C;
    *(int *)(index * 0x2B0 + D_001ED090 + 0x08) = 1;
    *(int *)(index * 0x2B0 + D_001ED090 + 0x00) = p2;
    *(int *)(index * 0x2B0 + D_001ED090 + 0x04) = p3;
    for (i = 0; i < 0xA; i++) {
        off = i * 0x40;
        *(float *)(index * 0x2B0 + D_001ED090 + off + 0x40) = (float)((func_00192568() - func_00192568()) % 3);
        *(float *)(index * 0x2B0 + D_001ED090 + off + 0x44) = (float)((func_00192568() - func_00192568()) % 3);
        *(float *)(index * 0x2B0 + D_001ED090 + off + 0x48) = (float)((func_00192568() - func_00192568()) % 0x19);
        *(float *)(index * 0x2B0 + D_001ED090 + off + 0x4C) = 1.0f;
        *(int *)(index * 0x2B0 + D_001ED090 + off + 0x60) = p5[0];
        *(int *)(index * 0x2B0 + D_001ED090 + off + 0x64) = p5[1];
        *(int *)(index * 0x2B0 + D_001ED090 + off + 0x68) = p5[2];
        *(int *)(index * 0x2B0 + D_001ED090 + off + 0x6C) = p5[3];
    }
}
