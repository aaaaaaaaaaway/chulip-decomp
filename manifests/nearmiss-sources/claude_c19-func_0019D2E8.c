typedef struct { int unk0; int unk4; int unk8; int unkC; } Entry;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;
typedef struct {
    int sema;
    int *rbuf;
    int rsize;
    int fd;
    int cmd;
    char data[0x400];
    int f414;
    int f418;
    int size;
} IoPkt;
typedef struct { long long q[4]; } Blk32;
typedef struct { int w[8]; } Blk32u;

extern int D_001E5B80[];
extern int D_001E5B8C[];
extern int D_001E5B00[];
extern int *D_002E2904[];
extern IoPkt D_002E2940;
extern int D_002E35D0[];
extern int D_002E3580[];
extern int D_002E3C00[];

extern Entry *func_0019BF68(int fd);
extern int func_0019C3E8(int lock);
extern void func_0019C418(void);
extern int func_0019C4E8(void);
extern void func_0019AE70(void *addr, int size);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001987C0(int sema);
extern int func_001987E0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019D2E8(int fd, int cmd, void *buf) {
    Entry *e;
    IoPkt *pkt = &D_002E2940;
    SemaParam param;
    int i;
    int sema;
    int result;
    int status;

    e = func_0019BF68(fd);
    func_0019C3E8(5);
    D_002E2904[0] = buf;
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    if (e == 0 || e->unk4 == 0) {
        func_0019C418();
        return -9;
    }
    pkt->f414 = 0;
    pkt->f418 = 0;
    switch (cmd) {
    case 1:
        func_001987E0(D_001E5B8C[0]);
        for (i = 0; i < 0x20; i++) {
            if (D_001E5B00[i] != -1) {
                break;
            }
        }
        if (i == 0x20) {
            *D_002E2904[0] = 0;
        } else {
            *D_002E2904[0] = 1;
        }
        func_001987C0(D_001E5B8C[0]);
        func_0019C418();
        return 0;
    case 2:
        *(int *)buf = *(int *)((int)D_002E35D0 | 0x20000000);
        func_0019C418();
        return 0;
    case 3:
        *(long long *)buf = *(long long *)((int)D_002E35D0 | 0x20000000);
        func_0019C418();
        return 0;
    }
    pkt->cmd = cmd;
    pkt->fd = e->unk0;
    if (buf == 0) {
        pkt->size = 0;
    } else {
        pkt->size = 0x400;
        if ((((int)buf | (int)pkt->data) & 7) != 0) {
            Blk32u *s = (Blk32u *)buf;
            Blk32u *d = (Blk32u *)pkt->data;
            Blk32u *end = s + 0x20;
            do {
                *d = *s;
                s++;
                d++;
            } while (s != end);
        } else {
            Blk32 *s = (Blk32 *)buf;
            Blk32 *d = (Blk32 *)pkt->data;
            Blk32 *end = s + 0x20;
            do {
                *d = *s;
                s++;
                d++;
            } while (s != end);
        }
    }
    param.f4 = 1;
    param.f8 = 0;
    param.f14 = 0;
    sema = func_001987A0(&param);
    pkt->sema = sema;
    pkt->rbuf = &result;
    pkt->rsize = 4;
    func_0019AE70(&D_002E2940, 0x420);
    if (func_0019B760(D_002E3C00, 5, 0, &D_002E2940, 0x420, D_002E3580, 4, 0, 0) < 0) {
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
