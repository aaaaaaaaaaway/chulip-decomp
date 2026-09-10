extern void (*D_001E5AF0)(int);
extern unsigned long func_001A1D90(double);
extern int func_00199F80(unsigned long);
extern void func_0019A740(char *, ...);

/* The caller handles zero separately. The retail path converts the scaled
   value to an unsigned integer before passing it to the bit-field helper. */
void func_0019A010(double value) {
    int exponent = 0;
    int digits;
    if (value < 0.0) {
        value = 0.0 - value;
        D_001E5AF0('-');
    }
    if (value < 0.1) {
        while (value < 0.1) {
            value = value * 10.0;
            --exponent;
        }
    } else if (value >= 1.0) {
        while (value >= 1.0) {
            value = value / 10.0;
            ++exponent;
        }
    }
    digits = func_00199F80(func_001A1D90(value * 1000000.0));
    func_0019A740("0.%d", digits);
    if (exponent >= 0)
        func_0019A740("e+%d", exponent);
    else
        func_0019A740("e%d", exponent);
}
