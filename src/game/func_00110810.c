extern int D_001ED17C;

int func_00192568(void);

void func_00110810(int index, int *spread, int *spread2, float *origin,
                   float *origin2, int *tail) {
    int i;

    *(int *)(index * 0x1320 + D_001ED17C) = 0;
    *(int *)(index * 0x1320 + D_001ED17C + 0x4) = 0;
    *(int *)(index * 0x1320 + D_001ED17C + 0x8) = 0x50;
    *(int *)(index * 0x1320 + D_001ED17C + 0x10) = spread[0];
    *(int *)(index * 0x1320 + D_001ED17C + 0x14) = spread[1];
    *(int *)(index * 0x1320 + D_001ED17C + 0x18) = spread[2];
    *(int *)(index * 0x1320 + D_001ED17C + 0x20) = spread2[0];
    *(int *)(index * 0x1320 + D_001ED17C + 0x24) = spread2[1];
    *(int *)(index * 0x1320 + D_001ED17C + 0x28) = spread2[2];
    *(float *)(index * 0x1320 + D_001ED17C + 0x30) = origin[0];
    *(float *)(index * 0x1320 + D_001ED17C + 0x34) = origin[1];
    *(float *)(index * 0x1320 + D_001ED17C + 0x38) = origin[2];
    *(float *)(index * 0x1320 + D_001ED17C + 0x40) = origin2[0];
    *(float *)(index * 0x1320 + D_001ED17C + 0x44) = origin2[1];
    *(float *)(index * 0x1320 + D_001ED17C + 0x48) = origin2[2];
    *(int *)(index * 0x1320 + D_001ED17C + 0x50) = tail[0];
    *(int *)(index * 0x1320 + D_001ED17C + 0x54) = tail[1];
    *(int *)(index * 0x1320 + D_001ED17C + 0x58) = tail[2];
    *(int *)(index * 0x1320 + D_001ED17C + 0x5C) = tail[3];

    for (i = 0; i < 0x64; i++) {
        int ofs;
        int r;

        r = func_00192568() - func_00192568();
        ofs = i * 0x30;
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x70) = origin[0] + (float)(r % spread[0]);
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x74) = origin[1] + (float)((func_00192568() - func_00192568()) % spread[1]);
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x78) = origin[2] + (float)((func_00192568() - func_00192568()) % spread[2]);
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x7C) = 1.0f;
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x80) = origin2[0] + (float)((func_00192568() - func_00192568()) % spread2[0]);
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x84) = origin2[1] + (float)((func_00192568() - func_00192568()) % spread2[1]);
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x88) = origin2[2] + (float)((func_00192568() - func_00192568()) % spread2[2]);
        *(float *)(index * 0x1320 + D_001ED17C + ofs + 0x8C) = 1.0f;
        *(int *)(index * 0x1320 + D_001ED17C + ofs + 0x64) = -(func_00192568() % 0x64);
        *(int *)(index * 0x1320 + D_001ED17C + ofs + 0x60) = 1;
    }
}
