struct Callback {
    void (*fn)(void);
    int arg0;
    int arg1;
};

extern struct Callback D_001EDE90[];
extern int D_001ED1B0;

void func_00112EB0(void (*fn)(void), int arg0, int arg1) {
    int i;

    for (i = 0; i < D_001ED1B0; i++) {
        if (D_001EDE90[i].fn == 0) {
            break;
        }
    }
    if (i == D_001ED1B0) {
        D_001ED1B0 = i + 1;
    }
    D_001EDE90[i].arg0 = arg0;
    D_001EDE90[i].arg1 = arg1;
    D_001EDE90[i].fn = fn;
}
