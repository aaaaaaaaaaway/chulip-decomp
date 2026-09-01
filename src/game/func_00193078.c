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

extern int func_00193130(File *stream, const char *format, va_list ap);
extern int func_00195E48(File *stream);

int func_00193078(File *fp, const char *format, va_list ap) {
    int ret;
    File f;
    char buf[0x400];

    f._data = fp->_data;
    f._flags = fp->_flags & ~2;
    f._file = fp->_file;
    f._cookie = fp->_cookie;
    f._write = fp->_write;
    f._p = (unsigned char *)buf;
    f._w = 0x400;
    f._bf._base = (unsigned char *)buf;
    f._bf._size = 0x400;
    f._lbfsize = 0;
    ret = func_00193130(&f, format, ap);
    if (ret >= 0) {
        if (func_00195E48(&f) != 0) {
            ret = -1;
        }
    }
    if ((f._flags & 0x40) != 0) {
        fp->_flags |= 0x40;
    }
    return ret;
}
