typedef struct { int pad[5]; int f14; int f18; } S;
extern S D_002E0F18;
int func_0019AB08(int a, int b) { int old = D_002E0F18.f14; D_002E0F18.f14 = a; D_002E0F18.f18 = b; return old; }
