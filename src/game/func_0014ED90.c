extern char D_001A88C8[];
extern char D_001E9640[];
extern char D_001ECB50[];

extern void func_00192660();
extern void func_00190F70(int arg0, int arg1, char *arg2);
extern int func_00190848(int arg0, int arg1, int *out);
extern void func_001901A8(int arg0, int arg1, char *arg2, int arg3);
extern void func_00190658(int fd, const void *buf, int size);
extern void func_00190318(int fd);

int func_0014ED90(int index, const char *data, int size) {
    char path[0x100];
    int result;
    int fd;
    int checksum;
    int done;
    int i;

    if (index == 0) {
        func_00192660(path, D_001ECB50, D_001A88C8, D_001A88C8);
    } else {
        func_00192660(path, D_001E9640, D_001A88C8, D_001A88C8, index);
    }
    checksum = 0;
    result = 0;
    while (result < size) {
        checksum += data[result];
        result++;
    }
    func_00190F70(0, 0, path);
    func_00190848(0, 0, &result);
    func_001901A8(0, 0, path, 0x202);
    func_00190848(0, 0, &fd);
    if (fd < 0) {
        return fd == -3 ? -8 : -3;
    }
    func_00190658(fd, &checksum, 4);
    func_00190848(0, 0, &done);
    if (done == 4) {
        func_00190658(fd, data, size);
        func_00190848(0, 0, &done);
        if (done == size) {
            func_00190318(fd);
            func_00190848(0, 0, &done);
            return done >= 0 ? 1 : -3;
        }
    }
    func_00190318(fd);
    func_00190848(0, 0, &result);
    if (done == -3) {
        func_00190F70(0, 0, path);
        func_00190848(0, 0, &result);
        return -8;
    }
    return -3;
}
