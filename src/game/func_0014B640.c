void func_0014B640(int *dst, unsigned int color, const int *src) {
    int mixed[3];

    mixed[0] = (((color >> 16) & 0xFF) + src[0]) >> 1;
    mixed[1] = (((color >> 8) & 0xFF) + src[1]) >> 1;
    mixed[2] = ((color & 0xFF) + src[2]) >> 1;
    if (mixed[0] < src[0]) {
        dst[0] = mixed[0];
    } else {
        dst[0] = src[0];
    }
    if (mixed[1] < src[1]) {
        dst[1] = mixed[1];
    } else {
        dst[1] = src[1];
    }
    if (mixed[2] < src[2]) {
        dst[2] = mixed[2];
    } else {
        dst[2] = src[2];
    }
}
