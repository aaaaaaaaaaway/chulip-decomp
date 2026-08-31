typedef struct {
    unsigned char value;
    unsigned char pad[7];
} ByteSlot;

extern ByteSlot D_001ED4A8;
extern unsigned char D_001ED4A9;

void func_0015ED48(unsigned char a, unsigned char b) {
    D_001ED4A8.value = a;
    D_001ED4A9 = b;
}
