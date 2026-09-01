extern int D_001ED35C;
extern int D_001ED360;

extern int func_00134BA0(int arg, int value);
extern void func_00112F40(int (*callback)(int));
extern int func_00134EC8(int arg);

int func_00134EC8(int arg) {
    int result;

    result = func_00134BA0(arg, D_001ED35C);
    switch (D_001ED360) {
    case 0:
        D_001ED35C = D_001ED35C + 1;
        if (D_001ED35C >= 5) {
            D_001ED360 = 1;
            D_001ED35C = 5;
        }
        break;
    case 1:
        break;
    case 2:
        D_001ED35C = D_001ED35C - 1;
        if (D_001ED35C < 0) {
            D_001ED35C = 0;
            func_00112F40(func_00134EC8);
        }
        break;
    }
    return result;
}
