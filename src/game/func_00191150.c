typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;
typedef struct {
    int f0; int f4; int f8; int fC; int f10; char name[0x400];
} PathCmd;
typedef struct { int w[16]; } Blk;

extern RpcClient D_002DEBC0;
extern PathCmd D_002DEC70;
extern Blk D_002DEC00;
extern int D_002E0180[];
extern int D_001E4BC0[];
extern int D_001E4BC4[];

extern int func_001987C0(int sema);
extern int func_001987F0(int sema);
extern int func_00198A20(int arg);
extern int func_00192B90(void *dst, void *src, int n);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_00191150(int arg, int arg1, char *path, Blk *src, int flags) {
    int rc;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -200;
    }
    if (D_002DEBC0.server == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -100;
    }
    if (path == 0 || *path == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -210;
    }
    D_002DEC70.f0 = arg;
    D_002DEC70.f4 = arg1;
    flags = flags & 7;
    D_002DEC70.f8 = flags;
    D_002DEC00 = *src;
    D_002DEC70.f10 = (int)&D_002DEC00;
    func_00192B90(D_002DEC70.name, path, 0x3FF);
    D_002DEC70.name[0x3FF] = 0;
    func_00198A20(0);
    rc = func_0019B760(&D_002DEBC0, 0xE, 1, &D_002DEC70, 0x414, D_002E0180, 4, 0, 0);
    if (rc == 0) {
        D_001E4BC0[0] = 0xE;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return rc;
}
