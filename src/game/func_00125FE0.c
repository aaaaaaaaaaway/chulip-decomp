extern char D_001E6ED0[];
extern char D_001E6EE0[];
extern char D_001E6EF0[];

extern void func_00192660(char *buffer, const char *format, int value);
extern int func_0019C778(const char *path, int mode);
extern int func_0019CB80(int fd, int offset, int whence);
extern int func_0019CDB8(int fd, void *buffer, int length);
extern void func_0019CA00(int fd);
extern void func_00198A20(int a);

int func_00125FE0(int value, void *buffer, int offset, int length) {
    char path[0x20];
    int fd;
    int read;
    int size;

    size = length == -1 ? 0x800000 : length;
    func_00192660(path, D_001E6EF0, value);
    fd = func_0019C778(path, 1);
    func_0019CB80(fd, offset, 0);
    read = func_0019CDB8(fd, buffer, size);
    if (read < 0) {
        func_00192660(path, D_001E6EE0, read);
    }
    func_0019CA00(fd);
    func_00198A20(0);
    return read;
}
