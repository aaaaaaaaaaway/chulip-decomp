typedef struct {
    long flags;
    char pad0[0x43];
    unsigned char f4B;
    char pad1[0xC];
    unsigned char f58;
} St;

St *func_00136AE8(void);
int func_0017C450(int a, int b);
void func_0017EFE0(void);
void func_0017E5C0(void);
void func_00159DD8(int a);
void func_00137CC0(int a);
void func_0015A658(void);
int func_0015A678(void);
void func_00151DF8(int a);
void func_001519F0(void);
void func_0017E6C8(int a, int b);
void func_0017DBD0(int a, int b);
void func_001539E8(int a);
void func_0015ADF8(int a);
void func_00198A20(int a);
void func_001985E0(void);

void func_00137740(void) {
    St *p;

    p = func_00136AE8();
    while (func_0017C450(0, 0) == 0) {
    }
    p->flags = p->flags | 4;
    func_0017EFE0();
    func_0017E5C0();
    func_00159DD8(0);
    func_00137CC0(2);
    func_0015A658();
    func_00151DF8(0xB00000 - func_0015A678());
    func_00137CC0(1);
    func_001519F0();
    if (p->f4B == 0x63) {
        func_0017E6C8(0, 0x41);
        func_0017E6C8(0xA, 0x41);
        func_0017E6C8(9, 0x41);
        func_0017E6C8(5, 0x41);
        func_0017DBD0(0x1B, 3);
        func_0017DBD0(0x1C, 3);
        func_0017DBD0(0x19, 3);
        func_0017DBD0(0x1A, 3);
    } else if ((int)(((unsigned long)p->flags >> 42) & 1) == 1) {
        func_0017DBD0(0, 3);
        func_0017DBD0(0xA, 3);
        func_0017DBD0(9, 3);
        func_0017DBD0(5, 3);
    }
    if (p->f58 == 2) {
        func_001539E8(2);
        func_0015ADF8(0);
        func_0017DBD0(0x1000, 7);
        func_0017DBD0(0x1001, 8);
        func_0017DBD0(0x1018, 0);
    }
    func_00198A20(0);
    p->flags = p->flags & ~4;
    func_001985E0();
}
