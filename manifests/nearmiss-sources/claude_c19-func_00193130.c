typedef struct Reent {
    char pad0[0x38];
    int __sdidinit;
} Reent;
typedef struct {
    char pad0[0x54];
    Reent *_data;
} FileT;

extern Reent *D_001E4EB4[];
extern void func_00196118(Reent *r);
extern int func_001931A8(Reent *r, FileT *fp, char *fmt, void *ap);

int func_00193130(FileT *fp, char *fmt, void *ap) {
    if (fp->_data == 0) {
        fp->_data = D_001E4EB4[0];
    }
    if (fp->_data->__sdidinit == 0) {
        func_00196118(fp->_data);
    }
    return func_001931A8(fp->_data, fp, fmt, ap);
}
