extern char D_001A88C8[];
extern char D_001E9640[];
extern char D_001ECB50[];
extern char D_001ECB58[];
extern void func_00192660();
extern void func_001902E0(int arg0, int arg1, char *arg2);
extern void func_00190848(int arg0, int arg1, int *out);
extern void func_001923F4(char *dst, int fill, int size);
extern int func_0014E550(char *path, char *buf, int size);
extern int func_0014E650(void);
extern int func_0014E7D0(void);
int func_0014EC08(void) {
    char path[0x100];
    int temp;
    char buf[0x1004];
    int status;
    int i;
    func_00192660(path, D_001ECB58, D_001A88C8);
    func_001902E0(0, 0, path);
    func_00190848(0, 0, &status);
    if (status == 0) {
        func_001923F4(buf, 0, 0x1004);
        for (i = 0; i < 3; i++) {
            if (i == 0) {
                func_00192660(path, D_001ECB50, D_001A88C8, D_001A88C8);
            } else {
                func_00192660(path, D_001E9640, D_001A88C8, D_001A88C8, i);
            }
            status = func_0014E550(path, buf, 0x1004);
            if (status == (-3)) {
                return -8;
            }
            if (status < 0) {
                return -2;
            }
        }

        status = func_0014E650();
        temp = 0;
        return (status >= temp) ? (0) : (status);
    }
    if (status == (-4)) {
        if (func_0014E7D0() < 0) {
            status = func_0014E650();
            if (status < 0) {
                return status;
            }
        }
        return 0;
    }
    if (status == (-3)) {
        return -8;
    }
    return -2;
}
