long func_00115E88(long *dst, int ax, int ay, int bx, int by, long z, long extra) {
    dst[0] = 0x4400000000000001L;
    dst[1] = 0x5510L;
    dst[2] = 9L;
    dst[3] = extra;
    dst[4] = (long)(((ax + 0x800) << 4) | ((ay + 0x1000) << 19)) | (z << 32);
    dst[5] = (long)(((bx + 0x800) << 4) | ((by + 0x1000) << 19)) | (z << 32);
    return 4;
}
