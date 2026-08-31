void func_001855A8(int *obj) {
    int old = obj[31];
    int limit = obj[35];

    obj[31] = old + 1;
    if (++obj[30] >= limit) {
        obj[31] = old;
        obj[30] = limit - 1;
    }
}
