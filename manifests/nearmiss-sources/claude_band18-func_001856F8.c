extern int D_002DE5E8[];
extern void func_00185648(void);

void func_001856F8(void) {
    if (D_002DE5E8[0] == 0) {
        D_002DE5E8[0] = 1;
        func_00185648();
    }
}
