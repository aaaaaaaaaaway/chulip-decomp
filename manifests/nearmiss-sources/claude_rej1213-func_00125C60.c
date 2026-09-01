extern char D_001E6ED0[];

extern void func_00192660(char *dst, const char *format, const char *name);
extern int func_0019C778(char *path, int mode);
extern int func_0019CB80(int handle, int offset, int origin);
extern void func_0019CA00(int handle);

int func_00125C60(const char *name) {
    char path[0x20];
    int handle;
    int size;

    func_00192660(path, D_001E6ED0, name);
    do {
        handle = func_0019C778(path, 1);
    } while (handle < 0);
    size = func_0019CB80(handle, 0, 2);
    func_0019CA00(handle);
    return size;
}
