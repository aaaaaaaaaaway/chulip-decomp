/* Convert a float to an unsigned 64-bit integer.
 *
 * The Emotion Engine has no double-precision unit, so every step goes
 * through the soft-float support routines: widen to double, split off the
 * high word by scaling with 2^-32 and truncating, then fold the remaining
 * low part back in.
 */

extern double func_00187140(float x);       /* float  -> double           */
extern int func_001862A0(double a, double b);  /* double compare          */
extern double func_00185D78(double a, double b);  /* double multiply      */
extern double func_00185D10(double a, double b);  /* double subtract      */
extern double func_00185CB8(double a, double b);  /* double add           */
extern double func_00185810(long v);        /* signed 64-bit -> double    */
extern unsigned int func_00186440(double a);   /* double -> unsigned 32   */

unsigned long func_00185718(float original_a) {
    double a;
    double b;
    double c;
    unsigned long v;

    a = func_00187140(original_a);
    if (func_001862A0(a, 0.0) < 0) {
        return 0;
    }
    b = func_00185D78(a, 2.3283064365386962890625e-10);
    v = (unsigned long)func_00186440(b);
    v <<= 32;
    if ((long)v >= 0) {
        c = func_00185810((long)v);
    } else {
        c = func_00185810((long)((v & 1) | (v >> 1)));
        c = func_00185CB8(c, c);
    }
    a = func_00185D10(a, c);
    if (func_001862A0(a, 0.0) < 0) {
        v -= func_00186440(func_00185D10(0.0, a));
    } else {
        v += func_00186440(a);
    }
    return v;
}
