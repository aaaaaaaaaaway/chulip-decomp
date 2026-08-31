typedef struct { int a; int b; } P;
extern void func_00198BD0(int, void *);

void func_001A0CC8(int a, char b) { P t; t.a = a; t.b = b; func_00198BD0(3, &t); }

void func_001A0CF8(int a) { int t = a; func_00198BD0(4, &t); }
