int func_00194870(char *buf, int value, int prefix) {
    char tmp[0x134];
    char *p;
    char *end;
    char *out;

    buf[0] = prefix;
    if (value < 0) {
        buf[1] = '-';
        value = -value;
    } else {
        buf[1] = '+';
    }
    out = buf + 2;
    p = tmp + 0x134;
    end = p;
    if (value >= 10) {
        do {
            *--p = value % 10 + '0';
            value = value / 10;
        } while (value >= 10);
        *--p = value + '0';
        while (p < end) {
            *out++ = *p++;
        }
    } else {
        *out++ = '0';
        *out++ = value + '0';
    }
    return out - buf;
}
