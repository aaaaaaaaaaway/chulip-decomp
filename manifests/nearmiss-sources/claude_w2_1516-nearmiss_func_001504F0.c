extern signed char D_001E96D0[];

char *func_001504F0(char *out, int value) {
    const signed char *table = D_001E96D0;
    const signed char *digit;

    if (value >= 10) {
        out = func_001504F0(out, value / 10);
    }
    digit = &table[(value % 10) * 2];
    out[0] = digit[0];
    out[1] = digit[1];
    return out + 2;
}
