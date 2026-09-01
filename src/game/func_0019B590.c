typedef struct Slot {
    int f0; int f4; int f8; int fC;
    int flags;
    struct Slot *self;
    int id;
    void *client;
    unsigned int sid;
} Slot;
typedef struct Client {
    Slot *pkt;
    int rpc_id;
    int sema;
    int fC;
    int f10;
    int f14; int f18; int f1C; int f20;
    void *server;
} Client;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;

extern int D_002E28C0[];

extern Slot *func_0019B0E8(void *pool);
extern void func_0019B190(Slot *p);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987E0(int sema);
extern int func_0019ACC8(unsigned int cmd, void *pkt, int size, int a3, int t0, int t1);

int func_0019B590(Client *cd, unsigned int sid, int mode) {
    Slot *p;
    SemaParam param;

    cd->f10 = 0;
    cd->server = 0;
    p = func_0019B0E8(D_002E28C0);
    if (p == 0) {
        return -1;
    }
    cd->pkt = p;
    cd->rpc_id = p->id;
    p->sid = sid;
    p->self = p;
    p->client = cd;
    if ((mode & 1) == 0) {
        param.f4 = 1;
        param.f8 = 0;
        cd->sema = func_001987A0(&param);
        if (cd->sema < 0) {
            func_0019B190(p);
            return -3;
        }
        if (func_0019ACC8(0x80000009, p, 0x40, 0, 0, 0) == 0) {
            func_0019B190(p);
            func_001987B0(cd->sema);
            return -2;
        }
        func_001987E0(cd->sema);
        func_001987B0(cd->sema);
        return 0;
    }
    cd->sema = -1;
    if (func_0019ACC8(0x80000009, p, 0x40, 0, 0, 0) != 0) {
        return 0;
    }
    func_0019B190(p);
    return -2;
}
