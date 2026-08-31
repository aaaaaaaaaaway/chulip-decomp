struct Pair8 { int a; int b; };
extern struct Pair8 D_001ED810;

int func_001787D8(short bit) {
    int mask;
    int result;
    mask = 1 << bit;
    result = 1;
    if ((D_001ED810.a & mask) == 0) {
        result = 0;
    }
    return result;
}
