typedef struct {
    int x;
    int y;
    int z;
    int w;
} Vec0017AA90;

int func_0018A3D0();

void func_0017AA90(void *matrix, Vec0017AA90 *src, Vec0017AA90 *dst, int start, int count) {
    int i;

    for (i = start; i < start + count; i++) {
        func_0018A3D0(&dst[i], matrix, &src[i]);
    }
}
