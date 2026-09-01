typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;
typedef struct {
    int f0; int f4; int f8; int fC; int f10; char name[0x400];
} PathCmd;

extern RpcClient D_002DEBC0;
extern PathCmd D_002DEC70;
extern int D_002E0180[];
extern char D_002DEC00[0x40];
extern int func_00198A20(int arg);
extern int D_001E4BC0[];
extern int D_001E4BC4[];

extern int func_001987C0(int sema);
extern int func_001987F0(int sema);
extern void func_0019AE70(void *addr, int size);
extern void func_00192B90(void *dst, void *src, int n);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_00191328(int arg, int arg1, char *path, char *path2) {
    int rc;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -200;
    }
    if (D_002DEBC0.server == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -100;
    }
    if (path == 0 || *path == 0 || path2 == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -210;
    }
    D_002DEC70.f0 = arg;
    D_002DEC70.f4 = arg1;
    D_002DEC70.f8 = 0x10;
    func_00192B90(D_002DEC70.name, path, 0x3FF);
    D_002DEC70.name[0x3FF] = 0;
    func_00192B90(&D_002DEC00[0x20], path2, 0x20);
    D_002DEC00[0x3F] = 0;
    D_002DEC70.f10 = (int)D_002DEC00;
    func_00198A20(0);
    rc = func_0019B760(&D_002DEBC0, 0xE, 1, &D_002DEC70, 0x414, D_002E0180, 4, 0, 0);
    if (rc == 0) {
        D_001E4BC0[0] = 0x13;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return rc;
}
