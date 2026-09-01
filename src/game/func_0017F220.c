int func_0017F220(int mode, int value) {
    int result;

    if (mode == 0x13 || mode == 0x14) {
        result = ((value + 0x7F) / 128) * 2;
        result = (result == 1) ? 2 : result;
    } else {
        result = (value + 0x3F) / 64;
    }
    return result;
}
