void func_00161738(int arg0, int arg1, int arg2, int arg3) {
    int value;
    ((int *)arg0)[0] = (arg3 | 268435456);
    value = ((arg3 << 16) | 0x8000);
    ((int *)arg0)[1] = 0;
    ((int *)arg0)[2] = (arg1 | 83886080);
    ((int *)arg0)[3] = ((arg2 | value) | 1811939328);
}

void func_00161770(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    ((int *)arg0)[0] = (arg3 | 805306368);
    ((int *)arg0)[1] = (arg1 & 2147483647);
    ((int *)arg0)[2] = ((arg5 | (arg4 << 8)) | 16777216);
    ((int *)arg0)[3] = ((arg2 | (arg3 << 16)) | 1811939328);
}

void func_001617B8(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int value;
    ((int *)arg0)[0] = (arg3 | 805306368);
    value = ((arg3 << 16) | 0x8000);
    ((int *)arg0)[1] = (arg1 & 2147483647);
    ((int *)arg0)[2] = ((arg5 | (arg4 << 8)) | 16777216);
    ((int *)arg0)[3] = ((arg2 | value) | 1811939328);
}
