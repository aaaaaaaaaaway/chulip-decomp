extern int D_001ED9F8[];
extern int func_00198E88(int arg);

int func_00198200(int *error, int arg) {
    int result;

    D_001ED9F8[0] = 0;
    result = func_00198E88(arg);
    if (result == -1) {
        if (D_001ED9F8[0] != 0) {
            *error = D_001ED9F8[0];
        }
    }
    return result;
}
