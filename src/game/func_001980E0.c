extern int D_001ED9F8[];
extern int func_00198D68(int a, int b, int c);

int func_001980E0(int *error, int a, int b, int c) {
    int result;
    D_001ED9F8[0] = 0;
    result = func_00198D68(a, b, c);
    if (result == -1) {
        if (D_001ED9F8[0] != 0) {
            *error = D_001ED9F8[0];
        }
    }
    return result;
}
