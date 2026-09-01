extern int D_001E3154[];
extern int D_001E3194[];
extern int D_001E3160[];
extern int D_001E3168[];
extern int D_001E316C[];
extern void func_001987C0(int semaphore);
extern void func_001987B0(int id);
extern void func_001A0828(void);
extern void func_0019AB68(int code);
extern void func_001A0870(void);

void func_0018EF48(void) {
    if (D_001E3154[0] != 0) {
        D_001E3194[0] = -1;
        func_001987C0(D_001E3160[0]);
    }
    func_001987B0(D_001E3168[0]);
    func_001987B0(D_001E316C[0]);
    func_001987B0(D_001E3160[0]);
    func_001A0828();
    func_0019AB68(0x80000012);
    func_001A0870();
}
