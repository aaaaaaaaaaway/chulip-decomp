typedef struct { int pad[3]; int f0C; int f10; } S;
extern S D_002E0F18;
int func_0019AB20(int a, int b) { int old = D_002E0F18.f0C; D_002E0F18.f0C = a; D_002E0F18.f10 = b; return old; }
