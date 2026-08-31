typedef struct { int pad0[5]; int f14; int f18; int pad1[2]; int f24; } S;
int func_0019B1B0(S *p) { int i = p->f24 % p->f18; int r = p->f14 + i * 64; p->f24 = i + 1; return r; }
