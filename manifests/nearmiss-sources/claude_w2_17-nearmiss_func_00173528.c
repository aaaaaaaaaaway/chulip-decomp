extern int (*D_001ED780)[8];

int func_00173340();

int func_00173528(unsigned short index) {
    int i;
    int value;

    for (i = 0; i < 8; i++) {
        value = D_001ED780[index][i];
        if (value == 0) {
            return 1;
        }
        if (func_00173340(value) == 0) {
            return 0;
        }
    }
    return 1;
}
