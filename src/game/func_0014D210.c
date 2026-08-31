int func_0014D210(int mask) {
    int i;

    for (i = 0; i < 8; i++) {
        if (mask & (0x200 >> i)) {
            return 8 - i;
        }
    }
    return 0;
}
