typedef struct {
    int f0; int f4; int f8; short fC; short fE; int f10; int f14; int f18; void *f1C;
    void *f20; void *f24; void *f28; void *f2C;
    int pad[9];
    int f54;
} F;
extern void func_00197F70(void);
extern void func_00197FD8(void);
extern void func_00198058(void);
extern void func_001980C0(void);
void func_00195F50(F *p, short a, short b, int c)
{
    p->f54 = c;
    p->fC = a;
    p->fE = b;
    p->f20 = (void *)func_00197F70;
    p->f24 = (void *)func_00197FD8;
    p->f28 = (void *)func_00198058;
    p->f2C = (void *)func_001980C0;
    p->f4 = 0;
    p->f8 = 0;
    p->f10 = 0;
    p->f18 = 0;
    p->f1C = p;
    p->f0 = 0;
}
