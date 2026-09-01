typedef struct {
    int count0;
    int count1;
    unsigned char *dst0;
    unsigned char *dst1;
    unsigned char src0[0x40];
    unsigned char src1[0x40];
} Transfer;

extern int D_001E3194[];
extern void func_0018EBD8(int *arg);

void func_0018EE10(Transfer *packet) {
    Transfer *uncached;
    unsigned char *dst;
    int i;

    uncached = (Transfer *)((unsigned int)packet | 0x20000000);
    if (uncached->count0 > 0) {
        dst = uncached->dst0;
        for (i = 0; i < uncached->count0; i++) {
            dst[i] = uncached->src0[i];
        }
    }
    if (uncached->count1 > 0) {
        dst = uncached->dst1;
        for (i = 0; i < uncached->count1; i++) {
            dst[i] = uncached->src1[i];
        }
    }
    func_0018EBD8(D_001E3194);
}
