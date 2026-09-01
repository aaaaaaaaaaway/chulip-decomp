typedef struct {
    int kind;
    int sign;
    int exponent;
    int mantissa;
} FloatParts;

void func_001866B0(const float *value, FloatParts *out) {
    unsigned int bits = *(const unsigned int *)value;
    unsigned int mantissa = bits & 0x7FFFFF;
    unsigned int sign = bits >> 31;
    unsigned int exponent = (bits >> 23) & 0xFF;

    out->sign = sign;
    if (exponent == 0) {
        out->kind = 2;
        return;
    }
    if (exponent == 0xFF) {
        if (mantissa == 0) {
            out->kind = 4;
            return;
        }
        if (mantissa & 0x100000) {
            out->kind = 1;
        } else {
            out->kind = 0;
        }
        out->mantissa = mantissa;
        return;
    }
    out->mantissa = (mantissa << 7) | 0x40000000;
    out->exponent = exponent - 0x7F;
    out->kind = 3;
}
