typedef struct {
    short value;
    short pad[3];
} ShortSlot;

extern ShortSlot D_001ED4AE;
extern short D_001ED4B0;

void func_0015ED58(short a, short b) {
    D_001ED4AE.value = a;
    D_001ED4B0 = b;
}
