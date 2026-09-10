extern int D_001ED570[2];

void func_00161B28(int index, int a, int b);

void func_00161A80(int index, int value) {
    if (value == 0) {
        func_00161B28(index, 0, 0);
    }
    D_001ED570[index] = value;
}
