typedef struct {
    unsigned char data[0x40];
} Block64 __attribute__((aligned(16)));

void func_0018A690(Block64 *dst, const Block64 *src) {
    *dst = *src;
}
