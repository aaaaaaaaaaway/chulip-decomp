extern char D_002E40A8[];
extern char D_001E5334[];
extern char *D_001E5B9C[];
extern int func_001922B0(char *a, char *b, int length);
int func_0019F918(void) {
    int result = 0;
    char *D_001E5334_value = D_001E5334;
    if (func_001922B0(D_002E40A8, D_001E5334_value, 4) != 0) {
        if (func_001922B0(D_002E40A8, D_001E5B9C[0], 4) != 0) {
            result = func_001922B0(D_001E5334_value, D_001E5B9C[0], 4) != 0;
        }
    }
    return result;
}
