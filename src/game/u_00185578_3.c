void func_00185578(int *obj) {
    int old = obj[31];

    obj[31] = old - 1;
    if (--obj[30] < 0) {
        obj[31] = old;
        obj[30] = 0;
    }
}

void func_001855A8(int *obj) {
    int old = obj[31];
    int limit = obj[35];

    obj[31] = old + 1;
    if (++obj[30] >= limit) {
        obj[31] = old;
        obj[30] = limit - 1;
    }
}

void func_001855E0(int arg0, int arg1, int arg2) {
    ((int *)arg0)[35] = arg1;
    ((int *)arg0)[36] = arg2;
}
