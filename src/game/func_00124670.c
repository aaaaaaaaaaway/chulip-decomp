extern int D_001ED25C;
extern int D_001ED260;

extern void func_001255F0(void);
extern void func_00112AA0(void);
extern void func_001121C0(void);

void func_00124670(void) {
    func_001255F0();
    switch (D_001ED25C) {
    case 0:
    case 1:
        break;
    case 2:
        func_00112AA0();
        func_001121C0();
        break;
    }
    D_001ED260 = -1;
    D_001ED25C = -1;
}
