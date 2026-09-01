typedef struct { int pad0[5]; int f14; int f18; int pad1[2]; int f24; } S;

typedef struct { int pad[7]; int f1C; int f20; } S_1;

int func_0019B1B0(S *p) { int i = p->f24 % p->f18; int r = p->f14 + i * 64; p->f24 = i + 1; return r; }

int func_0019B1E0(S_1 *p, int i) { if (i < 0 || i >= p->f20) return func_0019B1B0(p); return p->f1C + i * 64; }
