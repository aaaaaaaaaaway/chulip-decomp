extern int D_001ED9F8[];
extern int func_00198E98(int arg0, int arg1, int arg2);

int func_001982B8(int *error, int arg0, int arg1, int arg2) {
    int result;

    D_001ED9F8[0] = 0;
    result = func_00198E98(arg0, arg1, arg2);
    if (result == -1) {
        if (D_001ED9F8[0] != 0) {
            *error = D_001ED9F8[0];
        }
    }
    return result;
}
