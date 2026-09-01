extern int D_001ED138;
int func_00192568(void);

void func_0010C7E0(int index, int p2, int p3) {
    int i;
    int off;

    *(int *)(index * 0x5D0 + D_001ED138 + 0x00) = 0;
    *(int *)(index * 0x5D0 + D_001ED138 + 0x04) = p2;
    *(int *)(index * 0x5D0 + D_001ED138 + 0x08) = p3;
    *(int *)(index * 0x5D0 + D_001ED138 + 0x0C) = 0;
    *(int *)(index * 0x5D0 + D_001ED138 + 0x10) = 0x3C;
    *(int *)(index * 0x5D0 + D_001ED138 + 0x14) = 1;
    for (i = 0; i < 0x1E; i++) {
        off = i * 0x30;
        *(float *)(index * 0x5D0 + D_001ED138 + off + 0x40) = (float)((func_00192568() - func_00192568()) % 2);
        *(float *)(index * 0x5D0 + D_001ED138 + off + 0x44) = (float)((func_00192568() - func_00192568()) % 5);
        *(float *)(index * 0x5D0 + D_001ED138 + off + 0x48) = (float)((func_00192568() - func_00192568()) % 2);
        *(float *)(index * 0x5D0 + D_001ED138 + off + 0x4C) = 1.0f;
        *(int *)(index * 0x5D0 + D_001ED138 + off + 0x30) = -(func_00192568() % 0x64);
    }
}
