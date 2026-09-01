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
    char pad0[0x3C - 4];
    void (*__cleanup)(Reent *);
};
typedef struct { int f0; int st_mode; char pad[0x70 - 8]; } Stat;

extern int func_00198258(Reent *r, int fd, Stat *st);
extern unsigned char *func_00191B38(Reent *r, int size);
extern int func_00198F50(int fd);
extern void func_001960F8(Reent *r);
extern int func_00198058(void);

void func_00196B98(FileT *fp) {
    Stat st;
    int size;
    int couldbetty;
    unsigned char *p;

    if ((fp->_flags & 2) != 0) {
        fp->_bf_base = fp->_p = fp->_nbuf;
        fp->_bf_size = 1;
        return;
    }
    if (fp->_file < 0 || func_00198258(fp->_data, fp->_file, &st) < 0) {
        couldbetty = 0;
        size = 0x400;
        fp->_flags = fp->_flags | 0x800;
    } else {
        couldbetty = ((st.st_mode & 0xF000) == 0x2000);
        size = 0x400;
        if ((st.st_mode & 0xF000) == 0x8000 && fp->_seek == (void *)func_00198058) {
            fp->_blksize = size;
            fp->_flags = fp->_flags | 0x400;
        } else {
            fp->_flags = fp->_flags | 0x800;
        }
    }
    p = func_00191B38(fp->_data, size);
    if (p == 0) {
        fp->_flags = fp->_flags | 2;
        fp->_bf_base = fp->_p = fp->_nbuf;
        fp->_bf_size = 1;
        return;
    }
    fp->_data->__cleanup = func_001960F8;
    fp->_flags = fp->_flags | 0x80;
    fp->_bf_base = fp->_p = p;
    fp->_bf_size = size;
    if (couldbetty && func_00198F50(fp->_file)) {
        fp->_flags = fp->_flags | 1;
    }
}
