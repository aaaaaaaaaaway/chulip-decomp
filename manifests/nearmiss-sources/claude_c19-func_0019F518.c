typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;

extern RpcClient D_002E3CC0;
extern int D_001E5B94[];

extern int func_0019B590(RpcClient *cd, unsigned int sid, int mode);

int func_0019F518(void) {
    int i;

    for (;;) {
        if (func_0019B590(&D_002E3CC0, 0x80000003, 0) < 0) {
            return -1;
        }
        if (D_002E3CC0.server != 0) {
            break;
        }
        for (i = 0x100000; i != -1; i--) {
        }
    }
    D_001E5B94[0] = 0;
    return 0;
}
