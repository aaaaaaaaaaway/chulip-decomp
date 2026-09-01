typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;
typedef struct { char c[4]; } W4;

extern RpcClient D_002E4080;
extern W4 D_002E40A8[];
extern W4 D_002E3E80[];
extern int D_001E5B98[];

extern int func_0019B590(RpcClient *cd, unsigned int sid, int mode);
extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019F818(void) {
    int i;

    if (D_001E5B98[0] < 0) {
retry:
        if (func_0019B590(&D_002E4080, 0x80000006, 0) < 0) {
            return -1;
        }
        if (D_002E4080.server == 0) {
            goto spin;
        }
        D_001E5B98[0] = 0;
        if (func_0019B760(&D_002E4080, 0xFF, 0, 0, 0, D_002E3E80, 4, 0, 0) < 0) {
            return 0xFFFEFFFF;
        }
        D_002E40A8[0] = D_002E3E80[0];
        return 0;
spin:
        for (i = 0x100000; i != -1; i--) {
        }
        goto retry;
    }
    return 0;
}
