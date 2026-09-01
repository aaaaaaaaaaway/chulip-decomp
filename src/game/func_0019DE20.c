typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;
typedef struct { int sema; int *rbuf; int rsize; int fd; int idx; } CmdPkt;

extern int D_001E5B80[];
extern CmdPkt D_002E2940;
extern int D_002E3580[];
extern int D_002E3C00[];

extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_0019C4E8(void);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019DE20(int arg) {
    CmdPkt *pkt = &D_002E2940;
    SemaParam param;
    int sema;
    int result;
    int status;

    func_0019C3E8(15);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    pkt->fd = arg;
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    D_002E2940.sema = sema;
    pkt->rbuf = &result;
    pkt->rsize = 4;
    if (func_0019B760(D_002E3C00, 15, 0, pkt, 0x10, D_002E3580, 4, 0, 0) < 0) {
        func_001987B0(sema);
        func_0019C418();
        return -1;
    }
    status = *(int *)((int)D_002E3580 | 0x20000000);
    func_0019C418();
    if (status == 0) {
        func_001987B0(sema);
        return -1;
    }
    func_001987E0(sema);
    func_001987B0(sema);
    return result;
}
