extern char *D_002D81B0[];
extern char *D_001ED884;

void func_0017A198(int *a, int *b, int *c, int d, int e);
int func_00181EB8(int a);
void func_00161700(char *p, int a, char *b);
void func_00161808(char *p, int a, int b, int c, int d);
void func_001613D8(char *p, int *v);
void func_00161738(char *p, int a, int b, int c);
void func_001616A0(char *p, int a, int b, int c);
void func_00161530(char *p, char *q, int a, int b);
void func_00161620(char *p, int a);
void func_00181F20(int a);

char *func_00179F70(char *base, int n, int m, int arg3, int flag) {
    int a[4];
    int b[4];
    int c[4];
    char *dl;
    int t;
    int k;
    char *p1;
    char *p2;
    char *p3;

    p3 = base + n * 0x30;
    p1 = base + n * 16;
    p2 = base + n * 32;
    k = m * 4;
    func_0017A198(a, b, c, arg3, m);
    dl = D_002D81B0[1];
    t = func_00181EB8(1);
    func_00161700(dl, 1, D_001ED884 + 0x10);
    dl += 0x10;
    func_00161808(dl, t, 1, 4, 4);
    dl += 0x10;
    func_001613D8(dl, a);
    dl += 0x10;
    func_00161738(dl, 0, func_00181EB8(3), 3);
    dl += 0x10;
    func_001613D8(dl, c);
    dl += 0x10;
    func_001613D8(dl, b);
    dl += 0x10;
    func_001613D8(dl, a);
    dl += 0x10;
    func_001616A0(dl, 0, 1, 4);
    dl += 0x10;
    t = func_00181EB8(k);
    func_00161530(dl, base, t, m);
    dl += 0x10;
    func_00161530(dl, p1, t + 1, m);
    dl += 0x10;
    func_00161530(dl, p2, t + 2, m);
    dl += 0x10;
    func_00161530(dl, p3, t + 3, m);
    dl += 0x10;
    if (flag != 0) {
        func_00161620(dl, 0);
        dl += 0x10;
    }
    D_002D81B0[1] = dl;
    func_00181F20(k);
    return base + m * 16;
}
