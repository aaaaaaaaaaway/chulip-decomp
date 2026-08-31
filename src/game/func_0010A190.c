void func_0010A1D8(int value);
void func_0010A1E8(void);

void func_0010A190(int mode, int value) {
    switch (mode) {
    case 0:
        func_0010A1E8();
        break;
    case 1:
        func_0010A1D8(value);
        break;
    }
}
