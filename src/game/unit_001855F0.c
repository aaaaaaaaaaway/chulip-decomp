typedef void (*func_ptr)();

extern func_ptr *D_001E2F90;
extern func_ptr D_001ED9E8[];
extern int D_002DE5E8[];

#define DO_GLOBAL_CTORS_BODY                                      \
    do {                                                          \
        unsigned long nptrs = (unsigned long)D_001ED9E8[0];       \
        unsigned i;                                               \
        if (nptrs == (unsigned long)-1)                            \
            for (nptrs = 0; D_001ED9E8[nptrs + 1] != 0; nptrs++); \
        for (i = nptrs; i >= 1; i--)                              \
            D_001ED9E8[i]();                                      \
    } while (0)

void func_001855F0()
{
    while (*D_001E2F90) {
        D_001E2F90++;
        (*(D_001E2F90 - 1))();
    }
}

void func_00185648()
{
    DO_GLOBAL_CTORS_BODY;
}

void func_001856F8()
{
    if (D_002DE5E8[0] == 0) {
        D_002DE5E8[0] = 1;
        func_00185648();
    }
}
