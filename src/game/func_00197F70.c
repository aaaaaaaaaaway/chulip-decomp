/* newlib __sread */
typedef struct {
    char pad0[0xC];
    unsigned short flags;
    short file;
    char pad10[0x40];
    int offset;
    void *data;
} FileStream;

extern long func_00198318(void *data, int fd, char *buf, int count);

int func_00197F70(FileStream *fp, char *buf, int count) {
    int ret;

    ret = func_00198318(fp->data, fp->file, buf, count);
    if (ret >= 0) {
        fp->offset += ret;
    } else {
        fp->flags &= 0xEFFF;
    }
    return ret;
}
