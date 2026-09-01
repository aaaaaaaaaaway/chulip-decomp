struct Callback { int (*fn)(char *, int, int); int arg0; int arg1; };
extern struct Callback D_001EDE90[];
extern int D_001ED1B0;
extern char *D_001ED1AC;
void func_00198A20(int a);
int func_001885A0(int a);
void func_001888F0(int a, char *b);
void func_00187280(int a, int b);

void func_00113138(void) {
    int i;
    char *p;
    struct Callback *q;

    i = 0;
    p = D_001ED1AC;
    if (D_001ED1B0 > 0) {
        q = D_001EDE90;
        do {
            if (q->fn != 0) {
                p += q->fn(p, q->arg0, q->arg1) * 16;
            }
            i++;
            q++;
        } while (i < D_001ED1B0);
    }
    *(short *)p = 0;
    p[3] = 0x70;
    func_00198A20(0);
    func_001888F0(func_001885A0(2), D_001ED1AC);
    func_00187280(0, 0);
}
