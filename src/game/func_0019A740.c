/* EABI stdarg: the eight argument registers are spilled into a save area just
   below the incoming argument pointer, so va_start steps back over the slots
   that are not consumed by named parameters. */
typedef char *va_list;
#define va_start(ap, last, named) \
    ((ap) = (va_list)__builtin_next_arg(last) - 8 * (8 - (named)))

extern void func_0019A178(void *stream, va_list ap);

void func_0019A740(void *stream, ...) {
    va_list ap;

    va_start(ap, stream, 1);
    func_0019A178(stream, ap);
}
