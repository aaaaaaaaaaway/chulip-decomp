typedef struct LoadCmd {
    int result;
    int modres;
    char path[0xFC];
    char args[0xFC];
} LoadCmd;

typedef struct LoadResult {
    int id;
    int result;
} LoadResult;

extern LoadCmd D_002E3E80[];
extern int D_002E4080[];

extern int func_0019F818(void);
extern int func_0019F918(void);
extern void *func_00192B90(void *dest, const void *src, unsigned int n);
extern int func_0019B760(void *client, unsigned int rpc_number, unsigned int mode,
                         void *send, int ssize, void *recv, int rsize,
                         void (*end_function)(void *), void *end_param);

int func_001A0258(const char *path, const char *args, LoadResult *out, unsigned int rpc_number) {
    if (func_0019F818() < 0) {
        return -0x10000;
    }
    if (func_0019F918() != 0) {
        return -0x10004;
    }
    func_00192B90(D_002E3E80->path, path, 0xFC);
    D_002E3E80->path[0xFB] = 0;
    func_00192B90(D_002E3E80->args, args, 0xFC);
    D_002E3E80->args[0xFB] = 0;
    if (func_0019B760(D_002E4080, rpc_number, 0, D_002E3E80, 0x200, D_002E3E80, 0x10, 0, 0) < 0) {
        return -0x10001;
    }
    if (D_002E3E80->result == 0) {
        return -0x10003;
    }
    out->id = D_002E3E80->result;
    out->result = D_002E3E80->modres;
    return 0;
}
