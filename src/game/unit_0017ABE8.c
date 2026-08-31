struct Pair { short value; short pad; int rest; };
extern struct Pair A_001ED88C;
extern int D_001ED88C;
extern struct Pair A_001ED890;
extern int D_001ED890;

short func_0017ABE8(void) {
    short value = A_001ED88C.value;
    D_001ED88C = 0;
    return value;
}

short func_0017ABF8(void) {
    short value = A_001ED890.value;
    D_001ED890 = 0;
    return value;
}
