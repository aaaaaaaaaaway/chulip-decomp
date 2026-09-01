typedef struct { int unk0; int unk4; int unk8; int unkC; } Entry;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;
typedef struct { int sema; int *rbuf; int rsize; int fd; int arg; int arg2; int idx; } CmdPkt;

extern Entry D_002E3A00[];
extern int D_001E5B80[];
extern int D_001E5B8C[];
extern int D_001E5B00[];
extern CmdPkt D_002E2940;
extern int D_002E3580[];
extern int D_002E3C00[];

extern Entry *func_0019BF68(int fd);
extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987C0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019CB80(int fd, int arg, int arg2) {
    Entry *e;
    CmdPkt *pkt = &D_002E2940;
    SemaParam param;
    int sema;
    int result;
    int status;
    int flags;
    int i;
    int fdv;

    e = func_0019BF68(fd);
    func_0019C3E8(4);
    if (D_001E5B80[0] == 0) {
        func_0019C418();
        return -1;
    }
    if (e == 0 || (flags = e->unk4) == 0) {
        func_0019C418();
        return -9;
    }
    fdv = e->unk0;
    pkt->arg = arg;
    pkt->fd = fdv;
    pkt->arg2 = arg2;
    pkt->idx = e - D_002E3A00;
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    pkt->rsize = 4;
    pkt->rbuf = &result;
    D_002E2940.sema = sema;
    if (flags & 0x8000) {
        func_001987E0(D_001E5B8C[0]);
        for (i = 0; i < 0x20; i++) {
            if (D_001E5B00[i] == -1) {
                D_001E5B00[i] = D_002E2940.sema;
                D_002E2940.sema = -D_002E2940.sema;
                break;
            }
        }
        func_001987C0(D_001E5B8C[0]);
    }
    if (func_0019B760(D_002E3C00, 4, 0, &D_002E2940, 0x1C, D_002E3580, 4, 0, 0) < 0) {
        func_001987B0(sema);
        func_0019C418();
        return -11;
    }
    status = *(int *)((int)D_002E3580 | 0x20000000);
    func_0019C418();
    if (status == 0) {
        func_001987B0(sema);
        return -11;
    }
    if (flags & 0x8000) {
        func_001987B0(sema);
        return 0;
    }
    func_001987E0(sema);
    func_001987B0(sema);
    return result;
}
