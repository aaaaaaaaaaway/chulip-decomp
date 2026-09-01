typedef struct {
    long flags;
    char pad0[0x40];
    unsigned char f48;
    unsigned char f49;
} St;

St *func_00136AE8(void);
void func_0017CCF0(void);
void func_00178470(void);
void func_0017C908(int a);
void func_0017EDC8(void);
void func_001163B8(int a, int b);
void func_001172F0(int a, int b);
void func_0012E738(int a);
void func_0012E630(int a);
void func_0010BC88(void);
void func_00112F98(void);
void func_0015B6F8(void);
void func_00159C28(void);
void func_00163A58(void);
void func_001639D8(void);
void func_00138070(void);
void func_0015E418(int a);
void func_0017E6C8(int a, int b);
void func_0011FAD8(int a, int b);
void func_00103638(int a);
void func_00135A58(void);
void func_0015D6D0(void);
void func_00117538(void);
void func_00198A20(int a);
void func_001519F0(void);
void func_001159E0(void);
void func_00113388(void);
void func_00117568(void);

void func_001283C0(void) {
    St *p;

    p = func_00136AE8();
    func_0017CCF0();
    p->flags = p->flags & ~0x400000;
    func_00178470();
    func_0017C908(0x10);
    func_0017EDC8();
    func_001163B8(0, 0);
    func_001172F0(0, 0);
    func_0012E738(0);
    func_0012E630(0);
    func_0010BC88();
    func_00112F98();
    if (p->f49 != 0xFF) {
        func_0015B6F8();
        p->f49 = 0xFF;
        p->f48 = 0xFF;
    }
    func_00159C28();
    func_00163A58();
    func_001639D8();
    func_00138070();
    func_0015E418(1);
    func_0017E6C8(0xF, 0x41);
    func_0017E6C8(0x10, 0x41);
    func_0017E6C8(0xD, 0x41);
    func_0017E6C8(0xE, 0x41);
    func_0017E6C8(0x11, 0x41);
    func_0017E6C8(0x12, 0x41);
    func_0017E6C8(4, 0x41);
    func_0011FAD8(-1, -1);
    func_00103638(0);
    func_00135A58();
    func_0015D6D0();
    func_00117538();
    func_00198A20(0);
    func_001519F0();
    func_001159E0();
    func_00113388();
    func_00117568();
    func_001519F0();
}
