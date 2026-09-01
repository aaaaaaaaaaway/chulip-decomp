typedef char *va_list;
#define va_start(ap, last, named) \
    ((ap) = (va_list)__builtin_next_arg(last) - 8 * (8 - (named)))

typedef struct Reent Reent;

typedef struct File {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
    struct { unsigned char *_base; int _size; } _bf;
    int _lbfsize;
    void *_cookie;
    int (*_read)();
    int (*_write)();
    int (*_seek)();
    int (*_close)();
    struct { unsigned char *_base; int _size; } _ub;
    unsigned char *_up;
    int _ur;
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    struct { unsigned char *_base; int _size; } _lb;
    int _blksize;
    int _offset;
    Reent *_data;
} File;

extern Reent *D_001E4EB4[];
extern int func_00193130(File *stream, const char *format, va_list ap);

int func_00192660(char *str, const char *format, ...) {
    va_list ap;
    File f;
    int ret;

    va_start(ap, format, 2);
    f._flags = 0x208;
    f._p = (unsigned char *)str;
    f._bf._base = (unsigned char *)str;
    f._w = 0x7FFFFFFF;
    f._bf._size = 0x7FFFFFFF;
    f._data = D_001E4EB4[0];
    ret = func_00193130(&f, format, ap);
    *f._p = 0;
    return ret;
}
