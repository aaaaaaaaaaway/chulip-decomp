typedef struct {
    int kind;
    int sign;
    int exponent;
    int pad;
    long mantissa;
} DoubleParts;

void func_001859D8(const double *value, DoubleParts *out) {
    unsigned long bits = *(const unsigned long *)value;
    unsigned long mantissa = bits & (((unsigned long)-1) >> 12);
    unsigned int sign = (unsigned int)(bits >> 63);
    unsigned int exponent = (unsigned int)(bits >> 52) & 0x7FF;

    out->sign = sign;
    if (exponent == 0) {
        out->kind = 2;
        return;
    }
    if (exponent == 0x7FF) {
        if (mantissa == 0) {
            out->kind = 4;
            return;
        }
        if (mantissa & ((unsigned long)0x8000 << 36)) {
            out->kind = 1;
        } else {
            out->kind = 0;
        }
        out->mantissa = mantissa;
        return;
    }
    out->mantissa = (mantissa << 8) | ((unsigned long)0x8000 << 45);
    out->exponent = exponent - 0x3FF;
    out->kind = 3;
}
