void func_00161530(int arg0, int arg1, int arg2, int arg3) {
    int value;
    ((int *)arg0)[0] = (arg3 | 805306368);
    value = ((arg3 << 16) | 0x8000);
    ((int *)arg0)[1] = (arg1 & 2147483647);
    ((int *)arg0)[2] = 0;
    ((int *)arg0)[3] = ((arg2 | value) | 1811939328);
}
