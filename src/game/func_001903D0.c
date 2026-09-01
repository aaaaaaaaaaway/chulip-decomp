typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;
typedef struct {
    int f0; int f4; int f8; int fC; int f10; int f14;
    int f18; int f1C; int f20; int f24; int f28; int f2C;
} CmdBuf;

extern RpcClient D_002DEBC0;
extern CmdBuf D_002DEC40;
extern int D_002E0180[];
extern int D_001E4BC0[];
extern int D_001E4BC4[];

extern int func_001987C0(int sema);
extern int func_001987F0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_001903D0(int arg, int arg1, int arg2) {
    int rc;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -200;
    }
    if (D_002DEBC0.server == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -100;
    }
    D_002DEC40.f0 = arg;
    D_002DEC40.f10 = arg1;
    D_002DEC40.f14 = arg2;
    rc = func_0019B760(&D_002DEBC0, 4, 1, &D_002DEC40, 0x30, D_002E0180, 4, 0, 0);
    if (rc == 0) {
        D_001E4BC0[0] = 4;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return rc;
}
