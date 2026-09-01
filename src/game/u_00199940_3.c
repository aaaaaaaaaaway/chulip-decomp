typedef struct { int f0; int f4; void *f8; void *fC; int f10; } S;

typedef struct { int f0; int f4; char *f8; char *fC; } Q;

extern S D_002E0A00;

S *func_00199940(int a) { D_002E0A00.f0 = a; D_002E0A00.f4 = 0; D_002E0A00.fC = &D_002E0A00.f10; D_002E0A00.f8 = &D_002E0A00.f10; return &D_002E0A00; }

void func_00199968(Q *q) { q->f4++; q->fC = q->fC + 1; if (q->fC == (char *)q + (q->f0 + 0x10)) q->fC = (char *)q + 0x10; }

void func_001999A8(Q *q) { q->f4--; q->f8 = q->f8 + 1; if (q->f8 == (char *)q + (q->f0 + 0x10)) q->f8 = (char *)q + 0x10; }
