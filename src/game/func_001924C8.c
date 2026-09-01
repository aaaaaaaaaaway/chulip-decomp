typedef char *va_list;
#define va_start(ap, last, named) \
    ((ap) = (va_list)__builtin_next_arg(last) - 8 * (8 - (named)))

typedef struct {
    int unk0;
    int unk4;
    int flags;
} Stream;

extern void func_001931A8(Stream *stream, int flags, const char *format, va_list ap);

void func_001924C8(Stream *stream, const char *format, ...) {
    va_list ap;

    va_start(ap, format, 2);
    func_001931A8(stream, stream->flags, format, ap);
}
