extern int D_001ED0F8;

#define STATE ((char *)D_001ED0F8)

void func_0010A030(int a, int b, int c, float *d, float *e, int *f, float g)
{
    int i;
    int address;

    *(int *)(STATE + 0x00) = 0;
    *(int *)(STATE + 0x08) = 0;
    *(int *)(STATE + 0x04) = a;
    *(int *)(STATE + 0x18) = 0;
    *(int *)(STATE + 0x0C) = 1;
    *(float *)(STATE + 0x40) = g;
    *(int *)(STATE + 0x44) = 0;
    *(int *)(STATE + 0x10) = b;
    *(int *)(STATE + 0x14) = c;
    *(float *)(STATE + 0x50) = d[0];
    *(float *)(STATE + 0x54) = d[1];
    *(float *)(STATE + 0x58) = d[2];
    *(float *)(STATE + 0x5C) = 1.0f;
    *(float *)(STATE + 0x60) = e[0];
    *(float *)(STATE + 0x64) = e[1];
    *(float *)(STATE + 0x68) = e[2];
    *(float *)(STATE + 0x6C) = 1.0f;
    *(int *)(STATE + 0x70) = f[0];
    *(int *)(STATE + 0x74) = f[1];
    *(int *)(STATE + 0x78) = f[2];
    *(int *)(STATE + 0x7C) = f[3];

    for (i = 0; i < 9; i++) {
        address = D_001ED0F8;
        address += i * 4;
        *(int *)(address + 0x1C) = 1;
    }
}
