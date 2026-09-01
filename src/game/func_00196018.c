typedef struct FileT {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
    unsigned char *_bf_base;
    int _bf_size;
    int _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    unsigned char *_ub_base;
    int _ub_size;
    unsigned char *_up;
    int _ur;
    int _ubuf[1];
    unsigned char *_lb_base;
    int _lb_size;
    int _blksize;
    int _offset;
    struct Reent *_data;
} FileT;
typedef struct Glue {
    struct Glue *_next;
    int _niobs;
    FileT *_iobs;
} Glue;
typedef struct Reent {
    int _errno;
    char pad0[0x38 - 4];
    int __sdidinit;
    char pad1[0x1D8 - 0x3C];
    Glue __sglue;
} Reent;

extern void func_00196118(Reent *d);
extern Glue *func_00195FA8(Reent *d, int n);

FileT *func_00196018(Reent *d) {
    FileT *fp;
    int n;
    Glue *g;

    if (d->__sdidinit == 0) {
        func_00196118(d);
    }
    for (g = &d->__sglue;; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++) {
            if (fp->_flags == 0) {
                goto found;
            }
        }
        if (g->_next == 0 && (g->_next = func_00195FA8(d, 4)) == 0) {
            break;
        }
    }
    d->_errno = 12;
    return 0;

found:
    fp->_flags = 1;
    fp->_file = -1;
    fp->_data = d;
    fp->_p = 0;
    fp->_w = 0;
    fp->_r = 0;
    fp->_bf_base = 0;
    fp->_bf_size = 0;
    fp->_lbfsize = 0;
    fp->_ub_base = 0;
    fp->_ub_size = 0;
    fp->_lb_base = 0;
    fp->_lb_size = 0;
    return fp;
}
