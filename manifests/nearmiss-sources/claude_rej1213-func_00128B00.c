extern int func_001927FC(unsigned char *a, unsigned char *b);

unsigned char func_00128B00(unsigned char *a, unsigned char *b) {
    if (*a == '.') {
        a = a + 8;
    } else if (*b == '.') {
        b = b + 8;
    }
    return func_001927FC(a, b);
}
