unsigned int func_00100E80(unsigned int x, unsigned int *tab, unsigned int n) {
    unsigned int i;
    unsigned int result;

    result = 0;
    for (i = 0; i < n; i++) {
        if (!(x < tab[i]) && !(tab[i + 1] < x)) {
            result = i;
            break;
        }
    }
    return result;
}
