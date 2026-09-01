extern int D_001ED09C;
int func_00192568(void);

void func_00106338(int index, int p2, int p3, int unused, int *p5, int p6, float f) {
    int base;

    base = index * 0x80;
    *(int *)(base + D_001ED09C + 0x00) = 0;
    *(int *)(base + D_001ED09C + 0x10) = 0;
    *(int *)(base + D_001ED09C + 0x14) = 0x3C;
    *(int *)(base + D_001ED09C + 0x0C) = 1;
    *(int *)(base + D_001ED09C + 0x04) = p2;
    *(int *)(base + D_001ED09C + 0x08) = p3;
    *(float *)(base + D_001ED09C + 0x1C) = f;
    *(int *)(base + D_001ED09C + 0x18) = p6;
    *(int *)(base + D_001ED09C + 0x30) = p5[0];
    *(int *)(base + D_001ED09C + 0x34) = p5[1];
    *(int *)(base + D_001ED09C + 0x38) = p5[2];
    *(int *)(base + D_001ED09C + 0x3C) = p5[3];
    *(float *)(base + D_001ED09C + 0x50) = (float)((func_00192568() - func_00192568()) % 5);
    *(float *)(base + D_001ED09C + 0x54) = (float)((func_00192568() - func_00192568()) % 0x19);
    *(float *)(base + D_001ED09C + 0x58) = (float)((func_00192568() - func_00192568()) % 5);
    *(float *)(base + D_001ED09C + 0x5C) = 1.0f;
}
