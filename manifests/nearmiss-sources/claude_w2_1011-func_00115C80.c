long func_00115C80(long *dst,
                   int x1, int y1, int x2, int y2, int x3, int y3, int x4,
                   int y4, int u1, int v1, int u2, int v2, int u3, int v3,
                   int u4, int v4, int z, int c1, int c2) {
    dst[0]  = 0xD400000000000001L;
    dst[1]  = 0x5315315315310L;
    dst[2]  = 0x15CL;
    dst[6]  = c1;
    dst[3]  = c2;
    dst[4]  = (u1 + 8) | ((v1 + 8) << 16);
    dst[5]  = (long)(((x1 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)z << 32);
    dst[7]  = (u2 + 8) | ((v2 + 8) << 16);
    dst[8]  = (long)(((x2 + 0x800) << 4) | ((y2 + 0x1000) << 19)) | ((long)z << 32);
    dst[10] = (u3 + 8) | ((v3 + 8) << 16);
    dst[11] = (long)(((x3 + 0x800) << 4) | ((y3 + 0x1000) << 19)) | ((long)z << 32);
    dst[13] = (u4 + 8) | ((v4 + 8) << 16);
    dst[14] = (long)(((x4 + 0x800) << 4) | ((y4 + 0x1000) << 19)) | ((long)z << 32);
    dst[12] = c1;
    dst[9]  = c2;
    return 0xB;
}
