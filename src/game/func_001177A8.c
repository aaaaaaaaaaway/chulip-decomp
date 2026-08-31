extern int D_001EC8C8;

void func_00117788(void *p);
int func_00117A90(void *p);

int func_001177A8(void *p) {
    int result;

    func_00117788(p);
    result = 0;
    if (D_001EC8C8 == 2) {
        result = func_00117A90(p);
    } else {
        *(long long *)p = 0;
    }
    return result;
}
