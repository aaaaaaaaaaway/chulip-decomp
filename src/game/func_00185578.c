void func_00185578(int *obj) {
    int old = obj[31];

    obj[31] = old - 1;
    if (--obj[30] < 0) {
        obj[31] = old;
        obj[30] = 0;
    }
}
