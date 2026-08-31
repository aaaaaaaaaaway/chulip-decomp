typedef struct { int pad[7]; int f1C; int f20; } S;
extern int func_0019B1B0(S *);
int func_0019B1E0(S *p, int i) { if (i < 0 || i >= p->f20) return func_0019B1B0(p); return p->f1C + i * 64; }
