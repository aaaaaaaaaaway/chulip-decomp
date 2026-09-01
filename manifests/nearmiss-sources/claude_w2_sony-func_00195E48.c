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


struct Reent {
    int _errno;
    char pad4[0x34];
    int __sdidinit;
};

extern Reent *D_001E4EB4[];
extern int func_00196A10(Reent *ptr, int (*func)(File *));
extern void func_00196118(Reent *ptr);

int func_00195E48(File *fp) {
    unsigned char *p;
    int n;
    int t;
    int flags;

    if (fp == 0) {
        return func_00196A10(D_001E4EB4[0], func_00195E48);
    }
    if (fp->_data == 0) {
        fp->_data = D_001E4EB4[0];
    }
    if (fp->_data->__sdidinit == 0) {
        func_00196118(fp->_data);
    }
    flags = fp->_flags;
    if ((flags & 8) == 0) {
        return 0;
    }
    p = fp->_bf._base;
    if (p == 0) {
        return 0;
    }
    n = fp->_p - p;
    fp->_p = p;
    if ((flags & 3) != 0) {
        fp->_w = 0;
    } else {
        fp->_w = fp->_bf._size;
    }
    while (n > 0) {
        t = (*fp->_write)(fp->_cookie, p, n);
        if (t <= 0) {
            fp->_flags |= 0x40;
            return -1;
        }
        p += t;
        n -= t;
    }
    return 0;
}
