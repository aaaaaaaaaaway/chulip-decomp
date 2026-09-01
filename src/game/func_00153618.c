typedef struct Src {
    int a, b, c, d, e;
} Src;

typedef struct Out {
    int index;
    int unused_04;
    Src *src;
    int unused_0C;
    int zero_10;
    int mask_14;
    int mask_18;
    int mask_1C;
} Out;

extern Src *D_001A8B60[];
extern int D_001A8B80[];

void func_00153618(int index, Out *out) {
    Src *src;

    if (out == 0) {
        return;
    }
    out->index = index;
    src = D_001A8B60[index];
    out->zero_10 = 0;
    out->src = src;
    out->mask_14 = D_001A8B80[1] & ((src->a << 14) | (src->b << 15) | (src->c << 28));
    out->mask_18 = D_001A8B80[2] & src->d;
    out->mask_1C = D_001A8B80[3] & src->e;
}
