extern unsigned char D_001ECD48;
extern unsigned char D_001ECD49;
extern unsigned short D_001ECD4A;
extern unsigned short D_001ECD4C;
extern unsigned short D_001ECD4E;
unsigned long *func_00136AE8();
void func_00162178(void) {
    unsigned long *state;
    int temp;
    int saved_temp;
    state = func_00136AE8();
    D_001ECD48 = 0;
    D_001ECD49 = 0;
    D_001ECD4A = 0;
    saved_temp = 0xFFDFFFFF;
    temp = 0xFFFBFFFF;
    D_001ECD4C = 0;
    D_001ECD4E = 0;
    *state = ((*state) & temp) & saved_temp;
}
