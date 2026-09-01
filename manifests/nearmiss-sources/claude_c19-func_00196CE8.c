int func_00196CE8(void *reent, int *pwc, unsigned char *s, unsigned int n) {
    int dummy;
    int *p;

    p = (pwc != 0) ? pwc : &dummy;
    if (s == 0) {
        return 0;
    }
    if (n == 0) {
        return -1;
    }
    *p = *s;
    return *s != 0;
}
