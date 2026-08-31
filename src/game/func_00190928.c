extern int *D_002DEBE8[];
extern int *D_002DEBEC[];
extern int *D_002DEBF0[];
void func_00190928(unsigned int addr)
{
    int *p = (int *)(addr | 0x20000000);

    if (D_002DEBE8[0] != 0) *D_002DEBE8[0] = p[0];
    if (D_002DEBEC[0] != 0) *D_002DEBEC[0] = p[1];
    if (D_002DEBF0[0] != 0) *D_002DEBF0[0] = p[36];
}
