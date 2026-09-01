int func_001994C0(int *destination, const int *source, unsigned int size) {
    unsigned int count;
    unsigned int index;

    count = size >> 2;
    for (index = 0; index < count; index++) {
        *destination = *source;
        source++;
        destination++;
    }
    return 0;
}
