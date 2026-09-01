long func_00113670(long *dst, int ax, int ay, int bx, int by,
                   int u0, int v0, int u1, int v1, int z, int extra) {
    int ua = u0 + 8;
    int ub = u1 + 8;
    dst[0] = 0x6400000000008001L;
    dst[1] = 0x535310L;
    dst[2] = 0x156L;
    dst[3] = extra;
    dst[4] = ua | ((v0 + 8) << 16);
    dst[5] = (long)(((ax + 0x800) << 4) | ((ay + 0x1000) << 19)) | ((long)z << 32);
    dst[6] = ub | ((v1 + 8) << 16);
    dst[7] = (long)(((bx + 0x800) << 4) | ((by + 0x1000) << 19)) | ((long)z << 32);
    return 4;
}
