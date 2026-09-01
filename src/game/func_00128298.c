extern int func_0014D920(void);

int func_00128298(int value) {
    int rem;
    int quot;

    rem = value % func_0014D920();
    quot = value / func_0014D920();
    return rem / 16 + quot / 16 * 9;
}
