int func_00150160(long *p, int x0, int y0, int x1, int y1,
                  int u0, int v0, int u1, int v1, int w, int rgba) {
    p[0] = 0x6400000000008001;
    p[1] = 0x535310;
    p[2] = 0x156;
    p[3] = rgba;
    p[4] = (u0 + 8) | ((v0 + 8) << 16);
    p[5] = (((x0 + 0x800) << 4) | ((y0 + 0x1000) << 19)) | ((long)w << 32);
    p[6] = (u1 + 8) | ((v1 + 8) << 16);
    p[7] = (((x1 + 0x800) << 4) | ((y1 + 0x1000) << 19)) | ((long)w << 32);
    return 4;
}
