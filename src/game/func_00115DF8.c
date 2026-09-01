long func_00115DF8(long *dst, int x0, int y0, int x1, int y1, int z, unsigned int extra) {
    dst[0] = 0x6400000000000001L;
    dst[1] = 0x555510L;
    dst[2] = 0xCL;
    dst[3] = extra;
    dst[4] = (long)(((x0 + 0x800) << 4) | ((y0 + 0x1000) << 19)) | ((long)z << 32);
    dst[5] = (long)(((x1 + 0x800) << 4) | ((y0 + 0x1000) << 19)) | ((long)z << 32);
    dst[6] = (long)(((x0 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)z << 32);
    dst[7] = (long)(((x1 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)z << 32);
    return 4;
}
