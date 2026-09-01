typedef struct {
    int cls;
    int sign;
    int exp;
    int pad;
    long mant;
} DoubleParts;

void func_001859D8(long *px, DoubleParts *out) {
    long bits;
    long mant;
    long exp;

    bits = *px;
    out->sign = (unsigned long)bits >> 63;
    mant = bits & 0x000FFFFFFFFFFFFF;
    exp = (unsigned int)((unsigned long)bits >> 52) & 0x7FF;
    if (exp == 0) {
        out->cls = 2;
        return;
    }
    if (exp == 0x7FF) {
        if (mant == 0) {
            out->cls = 4;
            return;
        }
        if ((mant & 0x0008000000000000) == 0) {
            out->cls = 0;
        } else {
            out->cls = 1;
        }
        out->mant = mant;
        return;
    }
    out->mant = (mant << 8) | 0x1000000000000000;
    out->exp = exp - 0x3FF;
    out->cls = 3;
}
