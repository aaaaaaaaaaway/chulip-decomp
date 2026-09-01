extern char D_001E9A90[];

void func_001273B8(char *dst, const char *src);

void func_001525E0(char *dst, int count, int value) {
    char buf[0x80];
    char *p;
    int i;
    int v;

    v = value < 0 ? -value : value;
    buf[0x7F] = 0;
    buf[0x7E] = 0;
    p = &buf[0x7E];
    i = 0;
    do {
        p--;
        i++;
        *p = D_001E9A90[v % 10];
        v /= 10;
    } while (i < count);
    func_001273B8(dst, p);
}
