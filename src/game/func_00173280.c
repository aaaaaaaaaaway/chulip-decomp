/* Search the cyclic entry range for the first result other than -1. */
extern unsigned short func_0014D918(void);
extern int func_0014D928(unsigned short type, unsigned short index, int mode);
int func_00173280(unsigned short type, unsigned short index) {
    short count = func_0014D918();
    short i;
    int result;
    for (i = 0; i < count; i++) {
        result = func_0014D928(type, index, 0);
        if (result != -1) return result;
        if (index >= count - 1) index = 0;
        else index++;
    }
    return 0;
}
