typedef struct {
    unsigned int psize : 8;
    unsigned int dsize : 24;
    unsigned int dest;
    unsigned int cid;
    unsigned int opt;
    int f10;
    int f14;
    char name[0x50];
} __attribute__((aligned(16))) CmdPkt;
typedef struct { void *pkt; void *ee; int size; int mode; } Qent;

extern CmdPkt D_002E40C0;

extern void func_00198A70(void);
extern void *func_00198BB0(unsigned int arg);
extern void func_00198BA0(unsigned int a, unsigned int b);
extern int func_00198B60(Qent *q, int n);
extern void func_0019AE70(void *addr, int size);

int func_001A0578(char *name, int arg) {
    Qent q;
    void *ee;
    int i;

    func_00198A70();
    ee = func_00198BB0(0x80000000);
    D_002E40C0.f14 = arg;
    for (i = 0; name[i] != 0; i++) {
        D_002E40C0.name[i] = name[i];
    }
    D_002E40C0.dest = 0;
    D_002E40C0.f10 = i;
    D_002E40C0.cid = 0x80000003;
    D_002E40C0.dsize = 0;
    D_002E40C0.psize = 0x68;
    q.pkt = &D_002E40C0;
    q.ee = ee;
    q.size = 0x68;
    q.mode = 0x44;
    func_0019AE70(&D_002E40C0, 0x68);
    func_00198BA0(4, 0x40000);
    if (func_00198B60(&q, 1) != 0) {
        func_00198BA0(4, 0x10000);
        func_00198BA0(4, 0x20000);
        func_00198BA0(0x80000002, 0);
        func_00198BA0(0x80000000, 0);
        return 1;
    }
    return 0;
}
