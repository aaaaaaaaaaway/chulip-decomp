extern unsigned int D_001ED970;
extern int D_001ED974;

int func_0017E1A0(int id, int offset, int size);
void func_001985E0(void);
void func_0017E330(unsigned int id, int bytes_per_frame, int frame);

void func_0017F170(void *argument) {
    func_0017E1A0(D_001ED970, 0, D_001ED974);
    func_001985E0();
}

void func_0017F1A8(void *argument) {
    func_0017E330(D_001ED970, D_001ED974, 0);
}

void func_0017F1D8(void *argument) {
    func_0017E1A0(D_001ED970, 0, D_001ED974);
    func_0017E330(D_001ED970, D_001ED974, 0);
    func_001985E0();
}
