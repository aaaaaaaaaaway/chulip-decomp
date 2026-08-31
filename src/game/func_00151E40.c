extern int D_001ECBDC;
extern void func_00151CA8(int handle);

void func_00151E40(void) {
    int handle = D_001ECBDC;

    if (handle != 0) {
        func_00151CA8(handle);
    }
    D_001ECBDC = 0;
}
