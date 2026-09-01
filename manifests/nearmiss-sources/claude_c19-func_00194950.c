typedef struct Reent Reent;
typedef struct FileT {
    unsigned char *_p;
    int _r;
    int _w;
    unsigned short _flags;
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
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    unsigned char *_lb_base;
    int _lb_size;
    int _blksize;
    int _offset;
    Reent *_data;
} FileT;
struct Reent {
    int _errno;
    char pad0[0x38 - 4];
    int __sdidinit;
};

extern Reent *D_001E4EB4[];
extern void func_00196118(Reent *r);
extern void func_001961A8(Reent *r, void *p);
extern void func_00196B98(FileT *fp);

int func_00194950(FileT *fp) {
    if (fp->_data == 0) {
        fp->_data = D_001E4EB4[0];
    }
    if (fp->_data->__sdidinit == 0) {
        func_00196118(fp->_data);
    }
    if ((fp->_flags & 8) == 0) {
        if ((fp->_flags & 0x10) == 0) {
            return -1;
        }
        if ((fp->_flags & 4) != 0) {
            if (fp->_ub_base != 0) {
                if (fp->_ub_base != fp->_ubuf) {
                    func_001961A8(fp->_data, fp->_ub_base);
                }
                fp->_ub_base = 0;
            }
            fp->_flags = fp->_flags & ~0x24;
            fp->_r = 0;
            fp->_p = fp->_bf_base;
        }
        fp->_flags = fp->_flags | 8;
    }
    if (fp->_bf_base == 0) {
        func_00196B98(fp);
    }
    if ((fp->_flags & 1) != 0) {
        fp->_w = 0;
        fp->_lbfsize = -fp->_bf_size;
    } else {
        fp->_w = (fp->_flags & 2) ? 0 : fp->_bf_size;
    }
    return 0;
}
