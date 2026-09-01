typedef struct { unsigned char b[0x40]; } __attribute__((aligned(16))) Blk64;
struct B { int pad[4]; int f10; };
struct A { struct B *p; };
extern Blk64 D_001EDE00;
extern unsigned char D_001EDBB0[];
void func_00103D78(void *p);
void func_0018A690(int a, void *b);

void func_00101020(struct A *arg) {
    *(Blk64 *)D_001EDBB0 = D_001EDE00;
    func_00103D78(D_001EDBB0);
    func_0018A690(arg->p->f10, D_001EDBB0 + 0x110);
    func_0018A690(arg->p->f10 + 0x40, D_001EDBB0 + 0x150);
    func_0018A690(arg->p->f10 + 0x80, D_001EDBB0 + 0x190);
}
