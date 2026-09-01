extern int D_001ED9F8[];
extern int func_00198F58(int arg0, int arg1);

int func_00198258(int *error, int arg0, int arg1) {
    int result;

    D_001ED9F8[0] = 0;
    result = func_00198F58(arg0, arg1);
    if (result == -1) {
        if (D_001ED9F8[0] != 0) {
            *error = D_001ED9F8[0];
        }
    }
    return result;
}
