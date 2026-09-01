typedef struct {
    int a;
    int b;
    int c;
    int pad;
    long q;
    long tail;
} Sample;

extern void func_001859D8(long *value, Sample *out);
extern void func_00187110(int a, int b, int c, int d);

void func_00186548(long value) {
    Sample out;
    long local = value;
    long fraction;
    int scaled;

    func_001859D8(&local, &out);
    scaled = (int)((out.q << 2) >> 32);
    fraction = out.q & 0x3FFFFFFF;
    func_00187110(out.a, out.b, out.c, fraction ? (scaled | 1) : scaled);
}
