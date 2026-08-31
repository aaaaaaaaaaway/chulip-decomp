extern void func_00190EA8(int a, int b);
extern int func_00190848(int a, int b, int *c);
int func_0014F1E0(void) {
    int status;
    int i;
    for (i = 0; i < 4; i++) {
        func_00190EA8(0, 0);
        func_00190848(0, 0, &status);
        if (status == 0) { return 0; }
    }
    return -5;
}
