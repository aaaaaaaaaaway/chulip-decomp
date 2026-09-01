extern char D_001E6ED0[];
extern char D_001A3BE8[];
extern int D_001FBF50[];

void func_00192660(void *buf, void *name, int a);
int func_0019C778(void *buf, int a);
int func_001927FC(void *buf, void *p);
void func_0019CB80(int h, int a, int b);
void func_0019CDB8(int h, void *p, int n);
void func_0019CA00(int h);
void func_00198A20(int a);
void func_00192940(void *p, void *buf);
void *func_00151A00(int size);

int func_00125CD8(int arg0, int *out, unsigned short idx) {
    int buf[8];
    int h;
    int off;
    int size;
    int n;

    func_00192660(buf, D_001E6ED0, arg0);
    do {
        h = func_0019C778(buf, 1);
    } while (h < 0);
    if (func_001927FC(buf, D_001A3BE8) != 0) {
        func_0019CB80(h, 0, 0);
        func_0019CDB8(h, D_001FBF50, 0x100);
    }
    n = idx + 1;
    off = D_001FBF50[n * 2];
    size = D_001FBF50[n * 2 + 1];
    if (*out == 0) {
        *out = (int)func_00151A00(size);
    }
    func_0019CB80(h, off, 0);
    func_0019CDB8(h, (void *)*out, size);
    func_0019CA00(h);
    func_00198A20(0);
    func_00192940(D_001A3BE8, buf);
    return size;
}
