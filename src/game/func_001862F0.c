typedef struct {
    int kind;
    int sign;
    int exponent;
    int pad;
    unsigned long mantissa;
} DoubleParts;

extern double func_001858A8(DoubleParts *parts);

double func_001862F0(int value) {
    DoubleParts parts;
    unsigned long mantissa;
    unsigned long shifted;
    int exponent;

    parts.kind = 3;
    parts.sign = (unsigned int)value >> 31;
    if (value == 0) {
        parts.kind = 2;
    } else {
        parts.exponent = 0x3C;
        if (parts.sign != 0) {
            if (value == 0x80000000) {
                return -2147483648.0;
            }
            parts.mantissa = -value;
        } else {
            parts.mantissa = value;
        }
        mantissa = parts.mantissa;
        if (mantissa <= 0x0FFFFFFFFFFFFFFFUL) {
            exponent = parts.exponent;
            do {
                shifted = mantissa << 1;
                exponent--;
                mantissa = shifted;
            } while (shifted <= 0x0FFFFFFFFFFFFFFFUL);
            parts.exponent = exponent;
            parts.mantissa = shifted;
        }
    }
    return func_001858A8(&parts);
}
