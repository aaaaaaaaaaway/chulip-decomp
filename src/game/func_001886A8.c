extern int D_001E3008[];

int func_001886A8(int value) {
    int old = D_001E3008[0];
    D_001E3008[0] = value;
    return old;
}
