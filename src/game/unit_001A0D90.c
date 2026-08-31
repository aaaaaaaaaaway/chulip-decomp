typedef struct { int a; int b; } P;
extern void func_00198BD0(int, void *);

void func_001A0D90(int a, char b) { P t; t.a = a; t.b = b; func_00198BD0(-7, &t); }

void func_001A0DC0(int a) { int t = a; func_00198BD0(-8, &t); }
