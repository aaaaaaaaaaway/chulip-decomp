int func_00196CE8(void *reent, int *pwc, const char *s, int n) {
    int dummy;
    unsigned char *t = (unsigned char *)s;
    if (pwc == 0) {
        pwc = &dummy;
    }
    if (s == 0) {
        return 0;
    }
    if (n == 0) {
        return -1;
    }
    *pwc = (int)*t;
    return (*t != 0);
}
