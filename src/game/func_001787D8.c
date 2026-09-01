extern int D_001ED810;

int func_001787D8(short bit) {
    int mask;
    int result;
    mask = 1 << bit;
    result = 1;
    if ((D_001ED810 & mask) == 0) {
        result = 0;
    }
    return result;
}
