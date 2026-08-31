extern unsigned char D_002D8800[];

void func_00162078(int index, unsigned char *dst) {
    unsigned char *src;
    int i;

    src = &D_002D8800[index * 16];
    for (i = 0; i < 16; i++) {
        dst[i] = *src++;
    }
}
