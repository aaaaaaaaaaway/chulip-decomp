int func_001A0F30(unsigned int *destination, const unsigned int *source,
                  unsigned int size) {
    unsigned int count = size >> 2;
    unsigned int index;

    for (index = 0; index < count; index++) {
        *destination++ = *source++;
    }
    return 0;
}
