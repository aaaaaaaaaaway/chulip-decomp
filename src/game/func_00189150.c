typedef struct PadRpcClient {
    void *packet_address;
    unsigned int rpc_id;
    int semaphore_id;
    unsigned int mode;
    unsigned int command;
    void *buffer;
    void *callback_buffer;
    void (*end_function)(void *);
    void *end_parameter;
    struct PadRpcServer *server;
} PadRpcClient;
extern int D_001E30A0, D_001E30A4;
extern char D_001EB010[], D_001EB038[];
extern PadRpcClient D_002DE640[2];
extern int func_0019B590(PadRpcClient *, unsigned int, int);
extern int func_0018A300(void);
extern int func_00192508(const char *, ...);
extern int func_00189290(int);
int func_00189150(int mode) {
    int version;
    int delay;
    D_001E30A0 = 1;
    while (1) {
        func_0019B590(&D_002DE640[0], 0x80000100, 0);
        if (D_002DE640[0].server != 0)
            break;
        for (delay = 0x10000; delay != -1; --delay) {
        }
    }
    while (1) {
        func_0019B590(&D_002DE640[1], 0x80000101, 0);
        if (D_002DE640[1].server != 0)
            break;
        for (delay = 0x10000; delay != -1; --delay) {
        }
    }
    version = func_0018A300();
    if ((version >> 8) != 4) {
        if (D_001E30A4 != 0) {
            func_00192508(D_001EB010);
            func_00192508(D_001EB038, 4, 0, version >> 8, version & 0xff);
        }
        return 0;
    }
    return func_00189290(mode);
}
