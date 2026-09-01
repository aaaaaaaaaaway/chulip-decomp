void func_0015DED8(unsigned char *destination, const unsigned char *source) {
    while (source[0] != 0 || source[1] != 0) {
        *destination++ = *source++;
    }
    destination[0] = 0;
    destination[1] = 0;
}
