extern int func_00198BB0(int);

extern void func_00198C20(void);

int func_001A06B8(void) { int m = func_00198BB0(4) & 0x10000; return m != 0; }

int func_001A06E0(void) { if (func_00198BB0(4) & 0x40000) { func_00198C20(); return 1; } return 0; }
