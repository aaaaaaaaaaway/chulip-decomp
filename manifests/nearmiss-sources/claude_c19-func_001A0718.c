extern char D_001EC370[];
extern char D_001EC380[];

extern void func_0019A778(char *fmt, char *arg);
extern void func_0019AF20(int arg);
extern void func_0019B0C0(void);
extern int func_001A0578(char *name, int arg);

int func_001A0718(char *path) {
    char buf[0x50];
    char *d;
    char *s;
    char *p;

    p = path;
    while (*p != 0) {
        p++;
    }
    if ((p - path) + 11 > 0x50) {
        func_0019A778(D_001EC380, path);
        return 0;
    }
    func_0019AF20(0);
    func_0019B0C0();
    d = buf;
    s = D_001EC370;
    while (*s != 0) {
        *d = *s;
        s++;
        d++;
    }
    s = path;
    while (*s != 0) {
        *d = *s;
        s++;
        d++;
    }
    *d = 0;
    return func_001A0578(buf, 0);
}
