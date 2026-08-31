typedef struct { char pad0[0xE]; short fE; char pad1[0x44]; int f54; } S;
extern void func_00198200(int, int);
void func_001980C0(S *p) { func_00198200(p->f54, p->fE); }
