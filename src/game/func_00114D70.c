long func_00114D70(long *dst, int a2, int a3, int a4, int a5, int a6,
                   int a7, int a8, int a9, int a10, int a11, int a12,
                   int a13, int a14) {
    dst[0] = 0x1000000000008005L;
    dst[1] = 0xEL;
    dst[2] = (long)a2 | ((long)a3 << 16) | ((long)a4 << 24) | ((long)a7 << 32) | ((long)a8 << 48) | ((long)a9 << 56);
    dst[3] = 0x50L;
    dst[4] = (long)a5 | ((long)a6 << 16) | ((long)a10 << 32) | ((long)a11 << 48) | ((long)a14 << 59);
    dst[5] = 0x51L;
    dst[6] = (long)a12 | ((long)a13 << 32);
    dst[7] = 0x52L;
    dst[8] = 2L;
    dst[9] = 0x53L;
    dst[10] = 0L;
    dst[11] = 0x3FL;
    return 6;
}
