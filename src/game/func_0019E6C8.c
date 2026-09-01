typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;
typedef struct { int sema; int *rbuf; int rsize; char name1[0x400]; char name2[0x400]; } StrPkt;

extern int D_001E5B80[];
extern StrPkt D_002E2940;
extern int D_002E3580[];
extern int D_002E3C00[];

extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_0019C4E8(void);
extern int func_0019AE70(void *addr, int size);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019E6C8(unsigned char *p1, unsigned char *p2) {
    StrPkt *pkt = &D_002E2940;
    SemaParam param;
    int i;
    int sema;
    int result;
    int status;

    func_0019C3E8(17);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    for (i = 0; i < 0x400; i++) {
        if ((pkt->name1[i] = p1[i]) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        pkt->name1[0x3FF] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        if ((pkt->name2[i] = p2[i]) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        pkt->name2[0x3FF] = 0;
    }
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    pkt->sema = sema;
    pkt->rbuf = &result;
    pkt->rsize = 4;
    func_0019AE70(&D_002E2940, 0x80C);
    if (func_0019B760(D_002E3C00, 17, 0, &D_002E2940, 0x80C, D_002E3580, 4, 0, 0) < 0) {
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
    func_001987E0(sema);
    func_001987B0(sema);
    return result;
}
