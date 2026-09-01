extern unsigned int D_001ED9F8[];
extern unsigned int func_00198EA0(int argument);

unsigned int func_00192598(unsigned int *error, int argument) {
    unsigned int result;

    D_001ED9F8[0] = 0;
    result = func_00198EA0(argument);
    if (result == 0xFFFFFFFF) {
        if (D_001ED9F8[0] != 0) {
            *error = D_001ED9F8[0];
        }
    }
    return result;
}
