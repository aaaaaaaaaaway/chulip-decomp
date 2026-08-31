void func_00161640(int arg0, int arg1, int arg2) {
    int value;
    ((int *)arg0)[0] = (arg2 | 268435456);
    value = ((arg2 << 16) | 0x8000);
    ((int *)arg0)[1] = 0;
    ((int *)arg0)[2] = 0;
    ((int *)arg0)[3] = ((arg1 | value) | 1811939328);
}
