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
extern int D_002DF0C0[];
extern void func_001904A8(void *param);
extern void func_0019AE70(void *addr, int size);
extern int D_001E4BC0[];
extern int D_001E4BC4[];

extern int func_001987C0(int sema);
extern int func_001987F0(int sema);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_00190538(int arg, void *buf, int size) {
    int rc;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -200;
    }
    if (D_002DEBC0.server == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -100;
    }
    D_002DEC40.f0 = arg;
    D_002DEC40.f18 = (int)buf;
    D_002DEC40.fC = size;
    D_002DEC40.f1C = (int)D_002DF0C0;
    func_0019AE70(buf, size);
    func_0019AE70(D_002DF0C0, 0xC0);
    rc = func_0019B760(&D_002DEBC0, 5, 1, &D_002DEC40, 0x30, D_002E0180, 4, func_001904A8, D_002DF0C0);
    if (rc == 0) {
        D_001E4BC0[0] = 5;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return rc;
}
