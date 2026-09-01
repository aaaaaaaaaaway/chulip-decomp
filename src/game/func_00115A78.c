long func_00115A78(long *dst, int x0, int y0, int x1, int y1,
                   int u0, int v0, int u1, int v1, int z, int extra, long flags) {
    dst[0] = 0x6400000000000001L;
    dst[1] = 0x535310L;
    dst[2] = flags | 0x156;
    dst[3] = extra;
    dst[4] = (u0 + 8) | ((v0 + 8) << 16);
    dst[5] = (long)(((x0 + 0x800) << 4) | ((y0 + 0x1000) << 19)) | ((long)z << 32);
    dst[6] = (u1 + 8) | ((v1 + 8) << 16);
    dst[7] = (long)(((x1 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)z << 32);
    return 4;
}
