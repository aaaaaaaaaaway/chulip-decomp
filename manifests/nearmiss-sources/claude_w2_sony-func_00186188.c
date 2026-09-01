typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    int pad;
    unsigned long mant;
} DoubleParts;

int func_00186188(DoubleParts *a, DoubleParts *b) {
    if (a->cls < 2) {
        return 1;
    }
    if (b->cls < 2) {
        return 1;
    }
    if ((a->cls ^ 4) == 0) {
        if ((b->cls ^ 4) == 0) {
            return b->sign - a->sign;
        }
        return a->sign ? -1 : 1;
    }
    if ((b->cls ^ 4) == 0) {
        return b->sign ? 1 : -1;
    }
    if ((a->cls ^ 2) == 0) {
        if ((b->cls ^ 2) == 0) {
            return 0;
        }
        return b->sign ? 1 : -1;
    }
    if ((b->cls ^ 2) == 0) {
        return a->sign ? -1 : 1;
    }
    if (a->sign != b->sign) {
        return a->sign ? -1 : 1;
    }
    if (b->exp < a->exp) {
        return a->sign ? -1 : 1;
    }
    if (a->exp < b->exp) {
        return a->sign ? 1 : -1;
    }
    if (b->mant < a->mant) {
        return a->sign ? -1 : 1;
    }
    if (a->mant < b->mant) {
        return a->sign ? 1 : -1;
    }
    return 0;
}
