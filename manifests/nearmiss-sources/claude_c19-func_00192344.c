typedef int Qword __attribute__((mode(TI)));

void *func_00192344(void *dst, void *src, unsigned int n) {
    char *d;
    char *s;

    d = (char *)dst;
    s = (char *)src;
    if (n >= 0x20) {
        if ((((unsigned int)s | (unsigned int)d) & 0xF) == 0) {
            do {
                *(Qword *)d = *(Qword *)s;
                s += 0x10;
                d += 0x10;
                *(Qword *)d = *(Qword *)s;
                s += 0x10;
                d += 0x10;
                n -= 0x20;
            } while (n >= 0x20);
            while (n >= 8) {
                *(long long *)d = *(long long *)s;
                s += 8;
                d += 8;
                n -= 8;
            }
        }
    }
    while (n-- != 0) {
        *d++ = *s++;
    }
    return dst;
}
