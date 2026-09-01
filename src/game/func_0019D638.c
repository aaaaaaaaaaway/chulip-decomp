typedef struct { int unk0; int unk4; int unk8; int unkC; } Entry;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;
typedef struct {
    int sema;
    int *rbuf;
    int rsize;
    int fd;
    int arg;
    char data[0x400];
    int f414;
    int f418;
    int size;
} IoPkt;

extern int D_001E5B80[];
extern IoPkt D_002E2940;
extern int D_002E3580[];
extern int D_002E3C00[];

extern Entry *func_0019BF68(int fd);
extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_0019C4E8(void);
extern void func_0019AE70(void *addr, int size);
extern int func_00192344(void *dst, void *src, unsigned int n);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019D638(int fd, int arg, void *buf, unsigned int size, int a4, unsigned int a5) {
    Entry *e;
    IoPkt *pkt = &D_002E2940;
    SemaParam param;
    int sema;
    int result;
    int status;
    int fdv;

    e = func_0019BF68(fd);
    func_0019C3E8(26);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    if (e == 0 || e->unk4 == 0) {
        func_0019C418();
        return -9;
    }
    if (size > 0x400 || a5 > 0x400) {
        func_0019C418();
        return -22;
    }
    if (buf == 0) {
        pkt->size = 0;
    } else {
        func_00192344(pkt->data, buf, size);
    }
    fdv = e->unk0;
    pkt->arg = arg;
    pkt->fd = fdv;
    pkt->size = size;
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    pkt->f418 = a5;
    pkt->rbuf = &result;
    pkt->rsize = 4;
    pkt->f414 = a4;
    pkt->sema = sema;
    func_0019AE70(&D_002E2940, 0x420);
    if (func_0019B760(D_002E3C00, 26, 0, &D_002E2940, 0x420, D_002E3580, 4, 0, 0) < 0) {
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
