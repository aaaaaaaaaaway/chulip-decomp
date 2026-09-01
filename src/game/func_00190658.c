typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;
typedef struct {
    int f0; int f4; int f8; int fC; int f10; unsigned int f14;
    int f18; int f1C; unsigned char data[0x10];
} CmdBuf;

extern RpcClient D_002DEBC0;
extern CmdBuf D_002DEC40;
extern int D_002E0180[];
extern int D_001E4BC0[];
extern int D_001E4BC4[];

extern int func_001987C0(int sema);
extern int func_001987F0(int sema);
extern int func_00198A20(int arg);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_00190658(int arg, unsigned char *buf, int size) {
    int rc;
    unsigned int i;
    unsigned int n;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -200;
    }
    if (D_002DEBC0.server == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -100;
    }
    D_002DEC40.f0 = arg;
    if (size <= 0x10) {
        D_002DEC40.f14 = size;
        D_002DEC40.fC = 0;
        D_002DEC40.f18 = 0;
    } else {
        n = (unsigned int)((((int)buf - 1) & 0xFFFFFFF0) + 0x10) - (unsigned int)buf;
        D_002DEC40.f14 = n;
        D_002DEC40.fC = size - n;
        D_002DEC40.f18 = (int)(buf + n);
    }
    for (i = 0; i < D_002DEC40.f14; i++) {
        D_002DEC40.data[i] = buf[i];
    }
    func_00198A20(0);
    rc = func_0019B760(&D_002DEBC0, 6, 1, &D_002DEC40, 0x30, D_002E0180, 4, 0, 0);
    if (rc == 0) {
        D_001E4BC0[0] = 6;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return rc;
}
