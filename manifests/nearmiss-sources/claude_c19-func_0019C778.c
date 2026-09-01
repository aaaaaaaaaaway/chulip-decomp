typedef struct { int unk0; int unk4; int unk8; int unkC; } Entry;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;
typedef struct {
    int sema;
    int *rbuf;
    int rsize;
    int flags;
    int mode;
    char name[0x400];
    int idx;
} OpenPkt;

extern Entry D_002E3A00[];
extern int D_001E5B80[];
extern int D_001E5B88[];
extern OpenPkt D_002E2940;
extern int D_002E3580[];
extern int D_002E3C00[];

extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_0019C4E8(void);
extern int func_0019C6B0(void);
extern Entry *func_0019BEE0(void);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987C0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019C778(unsigned char *path, int flags, ...) {
    Entry *e;
    OpenPkt *pkt = &D_002E2940;
    SemaParam param;
    char *ap;
    int mode;
    int i;
    int idx;
    int sema;
    int result;
    int status;
    int ret;

    func_0019C3E8(0);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    if (func_0019C6B0() != 0) {
        func_0019C418();
        return 0xFFFEFFFC;
    }
    e = func_0019BEE0();
    if (e == 0) {
        func_0019C418();
        return -19;
    }
    ap = (char *)__builtin_next_arg(flags);
    mode = *(int *)ap;
    for (i = 0; i < 0x400; i++) {
        if ((pkt->name[i] = path[i]) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        pkt->name[0x3FF] = 0;
    }
    idx = e - D_002E3A00;
    pkt->flags = flags & 0x6FFFFFFF;
    pkt->mode = mode;
    pkt->idx = idx;
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    pkt->sema = sema;
    pkt->rbuf = &result;
    pkt->rsize = 4;
    if (func_0019B760(D_002E3C00, 0, 0, &D_002E2940, 0x418, D_002E3580, 4, 0, 0) < 0) {
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
    if (result < 0) {
        func_001987E0(D_001E5B88[0]);
        e->unk4 = 0;
        func_001987C0(D_001E5B88[0]);
        return result;
    }
    ret = idx;
    func_001987E0(D_001E5B88[0]);
    e->unk4 = e->unk4 | flags;
    e->unk0 = result;
    func_001987C0(D_001E5B88[0]);
    return ret;
}
