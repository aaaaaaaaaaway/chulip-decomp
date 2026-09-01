extern int D_001E5338[];
extern int func_00199DA0(void);
extern int func_00199B80(int a, int b);

int func_00198D68(int mode, int a, int b) {
    if ((unsigned int)(mode - 1) < 2) {
        if (D_001E5338[0] == 0) {
            if (func_00199DA0() == 0) {
                return -1;
            }
            D_001E5338[0] = 1;
        }
        return func_00199B80(a, b);
    }
    return -1;
}
