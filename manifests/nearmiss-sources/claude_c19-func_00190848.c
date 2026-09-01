typedef struct {
    int f0; int f4; int f8; int fC; int f10;
    int f14; int f18; int f1C; int f20; void *server;
} RpcClient;

extern RpcClient D_002DEBC0;
extern int D_002E0180[];
extern int D_001E4BC0[];
extern int D_001E4BC4[];

extern int func_001987C0(int sema);
extern int func_0019B950(RpcClient *cd);
extern void func_00190800(int ticks);

int func_00190848(int nowait, int *statep, int *resultp) {
    int busy;
    int done;

    if (D_001E4BC0[0] == 0) {
        return -1;
    }
    busy = func_0019B950(&D_002DEBC0);
    if (nowait == 0 && busy != 0) {
        while ((busy = func_0019B950(&D_002DEBC0)) != 0) {
            func_00190800(60);
        }
    }
    done = (busy == 0);
    if (statep != 0) {
        *statep = D_001E4BC0[0];
    }
    if (done == 0) {
        return done;
    }
    D_001E4BC0[0] = 0;
    if (resultp != 0) {
        *resultp = D_002E0180[0];
    }
    func_001987C0(D_001E4BC4[0]);
    return done;
}
