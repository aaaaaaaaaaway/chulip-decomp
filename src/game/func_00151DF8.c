extern int D_001ECBDC;
extern int func_00151A00(int arg0);
extern int func_00151A40(int arg0);

void func_00151DF8(int arg0) {
    if (D_001ECBDC == 0) {
        if (func_00151A40(arg0) != 0) {
            D_001ECBDC = func_00151A00(arg0);
        }
    }
}
