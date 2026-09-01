extern int D_001E5338[];
extern int func_00199DA0(int arg);
extern int func_00199CD0(int arg0, int arg1);

int func_00198DE8(int flag, int arg0, int arg1) {
    if (flag != 0) {
        return -1;
    }
    if (D_001E5338[0] == 0) {
        if (func_00199DA0(arg0) != 0) {
            D_001E5338[0] = 1;
        } else {
            return -1;
        }
    }
    return func_00199CD0(arg0, arg1);
}
