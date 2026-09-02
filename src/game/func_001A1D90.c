extern int func_001862A0(double a, double b);
extern double func_00185D78(double a, double b);
extern double func_00185D10(double a, double b);
extern double func_00185CB8(double a, double b);
extern double func_00185810(long value);
extern unsigned int func_00186440(double value);

unsigned long func_001A1D90(double a)
{
    double converted;
    unsigned long value;

    if (func_001862A0(a, 0.0) < 0) {
        return 0;
    }

    value = (unsigned long)func_00186440(
        func_00185D78(a, 2.3283064365386962890625e-10));
    value <<= 32;

    if ((long)value >= 0) {
        converted = func_00185810((long)value);
    } else {
        converted = func_00185810((long)((value & 1) | (value >> 1)));
        converted = func_00185CB8(converted, converted);
    }

    a = func_00185D10(a, converted);
    if (func_001862A0(a, 0.0) < 0) {
        value -= func_00186440(func_00185D10(0.0, a));
    } else {
        value += func_00186440(a);
    }

    return value;
}
