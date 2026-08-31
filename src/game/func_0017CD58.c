struct Pair8 {
    int lo;
    int hi;
};

extern struct Pair8 D_001ED978;
extern int func_00151A00(int size);

void func_0017CD58(void) {
    D_001ED978.lo = func_00151A00(0x40000);
}
