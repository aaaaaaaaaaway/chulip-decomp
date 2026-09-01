int func_00115C80(long *p, int x0, int y0, int x1, int y1, int x2, int y2, int x3,
                  int y3, int u0, int v0, int u1, int v1, int u2, int v2, int u3,
                  int v3, int z, int c1, int c0) {
    p[0] = 0xD400000000000001L;
    p[1] = 0x5315315315310L;
    p[2] = 0x15CL;
    p[3] = c0;
    p[4] = (u0 + 8) | ((v0 + 8) << 16);
    p[5] = (long)(((x0 + 0x800) << 4) | ((y0 + 0x1000) << 19)) | ((long)z << 32);
    p[6] = c1;
    p[7] = (u1 + 8) | ((v1 + 8) << 16);
    p[8] = (long)(((x1 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)z << 32);
    p[9] = c0;
    p[10] = (u2 + 8) | ((v2 + 8) << 16);
    p[11] = (long)(((x2 + 0x800) << 4) | ((y2 + 0x1000) << 19)) | ((long)z << 32);
    p[12] = c1;
    p[13] = (u3 + 8) | ((v3 + 8) << 16);
    p[14] = (long)(((x3 + 0x800) << 4) | ((y3 + 0x1000) << 19)) | ((long)z << 32);
    return 11;
}
