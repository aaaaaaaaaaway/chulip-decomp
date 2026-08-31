typedef struct { int f0; int f4; char *f8; char *fC; } Q;
void func_001999A8(Q *q) { q->f4--; q->f8 = q->f8 + 1; if (q->f8 == (char *)q + (q->f0 + 0x10)) q->f8 = (char *)q + 0x10; }
