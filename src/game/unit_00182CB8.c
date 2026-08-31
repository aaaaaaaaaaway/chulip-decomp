extern int D_002DB640[];
extern void func_00185578(int *obj);
extern void func_001855A8(int *obj);

void func_00182CB8(void) {
    if (--D_002DB640[35] < 0) {
        D_002DB640[35] = 0;
    }
    func_00185578(D_002DB640);
}

void func_00182CF0(void) {
    if (++D_002DB640[35] >= 0x10) {
        D_002DB640[35] = 0x10;
    }
    func_001855A8(D_002DB640);
}
