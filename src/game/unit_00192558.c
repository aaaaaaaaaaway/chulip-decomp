extern int *D_001E4EB4[];

void func_00192558(int a) { D_001E4EB4[0][22] = a; }

int func_00192568(void) { int *p = D_001E4EB4[0]; p[22] = p[22] * 0x41C64E6D + 0x3039; return p[22] & 0x7FFFFFFF; }
