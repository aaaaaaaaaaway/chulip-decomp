typedef void (*Fn)(void);
extern Fn *D_001E2F90[];

void func_001855F0(void) {
    while (*D_001E2F90[0] != 0) {
        Fn *next = D_001E2F90[0] + 1;
        D_001E2F90[0] = next;
        next[-1]();
    }
}
