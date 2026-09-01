struct Callback {
    void (*fn)(void);
    int arg0;
    int arg1;
};

extern struct Callback D_001EDE90[];
extern int D_001ED1B0;

void func_00112F40(void (*fn)(void)) {
    int i;
    int count;

    i = 0;
    count = D_001ED1B0;
    goto test;
next:
    i++;
test:
    if (i >= count) {
        return;
    }
    if (D_001EDE90[i].fn != fn) {
        goto next;
    }
    D_001EDE90[i].fn = 0;
    if (i == count - 1) {
        D_001ED1B0 = i;
    }
}
