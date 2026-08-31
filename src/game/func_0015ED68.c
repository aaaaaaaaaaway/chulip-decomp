typedef struct {
    unsigned char value;
    unsigned char pad[7];
} ByteSlot;

extern ByteSlot D_001ED4AA;
extern ByteSlot D_001ED4AB;
extern unsigned char D_001ED4AC;

void func_0015ED68(unsigned char a, unsigned char b, unsigned char c) {
    D_001ED4AA.value = a;
    D_001ED4AB.value = b;
    D_001ED4AC = c;
}
