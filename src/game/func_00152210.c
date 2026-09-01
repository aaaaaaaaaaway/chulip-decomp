int func_00152210(long *p, int x0, int y0, int x1, int y1,
                  int u0, int v0, int u1, int v1, int w, int rgba) {
    int ua = u0 + 8;
    int ub = u1 + 8;
    p[0] = 0x6400000000008001;
    p[1] = 0x535310;
    p[2] = 0x156;
    p[3] = rgba;
    p[4] = ua | ((v0 + 8) << 16);
    p[5] = (((x0 + 0x800) << 4) | ((y0 + 0x1000) << 19)) | ((long)w << 32);
    p[6] = ub | ((v1 + 8) << 16);
    p[7] = (((x1 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)w << 32);
    return 4;
}
