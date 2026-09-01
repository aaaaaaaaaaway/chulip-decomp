extern char *D_001ED0F8;

void func_0010A030(int a, int b, int c, float *d, float *e, int *f, float g) {
    int i;

    *(int *)(D_001ED0F8 + 0x00) = 0;
    *(int *)(D_001ED0F8 + 0x08) = 0;
    *(int *)(D_001ED0F8 + 0x04) = a;
    *(int *)(D_001ED0F8 + 0x18) = 0;
    *(int *)(D_001ED0F8 + 0x0C) = 1;
    *(float *)(D_001ED0F8 + 0x40) = g;
    *(int *)(D_001ED0F8 + 0x44) = 0;
    *(int *)(D_001ED0F8 + 0x10) = b;
    *(int *)(D_001ED0F8 + 0x14) = c;
    *(float *)(D_001ED0F8 + 0x50) = d[0];
    *(float *)(D_001ED0F8 + 0x54) = d[1];
    *(float *)(D_001ED0F8 + 0x58) = d[2];
    *(float *)(D_001ED0F8 + 0x5C) = 1.0f;
    *(float *)(D_001ED0F8 + 0x60) = e[0];
    *(float *)(D_001ED0F8 + 0x64) = e[1];
    *(float *)(D_001ED0F8 + 0x68) = e[2];
    *(float *)(D_001ED0F8 + 0x6C) = 1.0f;
    *(int *)(D_001ED0F8 + 0x70) = f[0];
    *(int *)(D_001ED0F8 + 0x74) = f[1];
    *(int *)(D_001ED0F8 + 0x78) = f[2];
    *(int *)(D_001ED0F8 + 0x7C) = f[3];
    for (i = 0; i < 9; i++) { ((int *)D_001ED0F8)[i + 7] = 1; }
}
