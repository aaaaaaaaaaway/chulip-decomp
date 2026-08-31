int func_00189020(unsigned int *state, unsigned int value) {
    unsigned int previous = *state;
    *state = value;
    return (previous >> 8) & 1;
}
