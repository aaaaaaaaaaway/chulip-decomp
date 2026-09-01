int *func_001A08D0(int key) {
    int *p;

    p = (int *)0x80000000;
    while (*p != key) {
        p++;
    }
    return p;
}
