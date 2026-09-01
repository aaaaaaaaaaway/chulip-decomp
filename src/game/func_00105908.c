extern unsigned short D_001ED088;
extern unsigned short D_001ED08A;
extern int D_001ED08C;

void func_00105908(float *src, unsigned short count) {
    int off;
    int i;
    int base;

    D_001ED08A = D_001ED088;
    base = D_001ED088 & 0xFFFF;
    if (count != 0) {
        off = base * 0x2C;
        i = count;
        do {
            i--;
            *(float *)(off + D_001ED08C + 0x04) = src[0];
            *(float *)(off + D_001ED08C + 0x08) = src[1];
            *(float *)(off + D_001ED08C + 0x0C) = src[2];
            *(float *)(off + D_001ED08C + 0x10) = src[3];
            *(float *)(off + D_001ED08C + 0x14) = src[4];
            *(float *)(off + D_001ED08C + 0x18) = src[5];
            *(float *)(off + D_001ED08C + 0x1C) = src[6];
            *(float *)(off + D_001ED08C + 0x20) = src[7];
            *(float *)(off + D_001ED08C + 0x24) = src[8];
            *(float *)(off + D_001ED08C + 0x28) = -src[9];
            src += 10;
            *(unsigned short *)(off + D_001ED08C) |= 0x400;
            off += 0x2C;
        } while (i != 0);
    }
    D_001ED088 = count + D_001ED088;
}
