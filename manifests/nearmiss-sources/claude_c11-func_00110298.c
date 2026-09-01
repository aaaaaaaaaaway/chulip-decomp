extern int D_001ED170;
extern int D_001ED174;

void func_00110298(void) {
    int i;
    int j;
    int k;
    int ofs;

    for (i = 0; i < D_001ED174; i++) {
        if (*(int *)(i * 0x810 + D_001ED170) != 0) {
            for (j = 0; j < 0x20; j++) {
                if (*(int *)(i * 0x810 + D_001ED170 + j * 0x40 + 0x40) > 0) {
                    *(int *)(i * 0x810 + D_001ED170 + j * 0x40 + 0x40) -= 1;
                    ofs = j * 0x40;
                    for (k = 0; k < 3; k++) {
                        *(float *)(i * 0x810 + D_001ED170 + ofs + 0x20) =
                            *(float *)(i * 0x810 + D_001ED170 + ofs + 0x10);
                        *(float *)(i * 0x810 + D_001ED170 + ofs + 0x10) +=
                            *(float *)(i * 0x810 + D_001ED170 + ofs + 0x30);
                        *(float *)(i * 0x810 + D_001ED170 + ofs + 0x30) *= 0.9f;
                        ofs += 4;
                    }
                    *(float *)(i * 0x810 + D_001ED170 + j * 0x40 + 0x34) += 1.5f;
                }
            }
        }
    }
}
