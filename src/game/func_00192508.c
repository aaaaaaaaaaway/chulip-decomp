typedef char *va_list;
#define va_start(ap, last, named) \
    ((ap) = (va_list)__builtin_next_arg(last) - 8 * (8 - (named)))

typedef struct Stream Stream;

typedef struct Context {
    int unk0;
    int unk4;
    Stream *stream;
} Context;

struct Stream {
    char pad0[0x54];
    Context *owner;
};

extern Context *D_001E4EB4[];
extern void func_00193130(Stream *stream, const char *format, va_list ap);

void func_00192508(const char *format, ...) {
    va_list ap;
    Context *context;

    va_start(ap, format, 1);
    context = D_001E4EB4[0];
    context->stream->owner = context;
    func_00193130(context->stream, format, ap);
}
