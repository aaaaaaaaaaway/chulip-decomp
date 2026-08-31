extern int D_002A3080[];
extern void func_00151CA8(int handle);

void func_00151810(int index) {
    int *slot = &D_002A3080[index];

    if (*slot != 0) {
        func_00151CA8(*slot);
        *slot = 0;
    }
}
