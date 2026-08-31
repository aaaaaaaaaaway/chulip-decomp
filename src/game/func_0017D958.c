extern unsigned int D_001ECF8C;

int func_0017D958(int size, int enable) {
    unsigned int result;
    unsigned int next;

    if (enable != 0) {
        result = D_001ECF8C;
        next = ((result + size + 31) >> 5) << 5;
        D_001ECF8C = next;
        if (next >= 10817) {
            result = 10816 - size;
        }
    } else {
        result = 10816;
    }
    return result;
}
