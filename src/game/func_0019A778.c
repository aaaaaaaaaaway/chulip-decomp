typedef char *va_list;
#define va_start(ap, last, named) \
    ((ap) = (va_list)__builtin_next_arg(last) - 8 * (8 - (named)))

typedef void (*Handler)(void);

extern void func_00199E98(void);
extern Handler D_001E5AF0[];
extern void func_0019A178(void *stream, va_list ap);

void func_0019A778(void *stream, ...) {
    va_list ap;
    Handler saved;

    saved = D_001E5AF0[0];
    D_001E5AF0[0] = func_00199E98;
    va_start(ap, stream, 1);
    func_0019A178(stream, ap);
    D_001E5AF0[0] = saved;
}
