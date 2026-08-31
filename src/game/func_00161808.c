void func_00161808(int arg0, int arg1, int arg2, int arg3, int arg4) {
    int value;

    ((int *)arg0)[0] = (arg2 | 268435456);
    value = ((arg2 << 16) | 0x8000);
    ((int *)arg0)[1] = 0;
    ((int *)arg0)[2] = ((arg4 | (arg3 << 8)) | 16777216);
    ((int *)arg0)[3] = ((arg1 | value) | 1811939328);
}
