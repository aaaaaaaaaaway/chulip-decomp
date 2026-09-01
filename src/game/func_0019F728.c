typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;
typedef struct { int f0; char name[0xFC]; } NameCmd;

extern RpcClient D_002E3CC0;
extern NameCmd D_002E3D80;
extern int D_002E3D00[];
extern int D_001E5B94[];

extern int func_0019B760(void *cd, int rpc, int mode, void *send, int ssize,
                         void *recv, int rsize, void *endf, void *endp);

int func_0019F728(unsigned char *path, int value) {
    int i;

    if (D_001E5B94[0] < 0) {
        return 0;
    }
    for (i = 0; i < 0xFC; i++) {
        if ((D_002E3D80.name[i] = path[i]) == 0) {
            break;
        }
    }
    if (i == 0xFC) {
        D_002E3D80.name[0xFB] = 0;
        i = 0xFB;
    }
    D_002E3D80.f0 = value;
    D_002E3D80.name[0xFB] = 0;
    if (func_0019B760(&D_002E3CC0, 3, 0, &D_002E3D80, i + 5, D_002E3D00, 4, 0, 0) < 0) {
        return -1;
    }
    return D_002E3D00[0];
}
