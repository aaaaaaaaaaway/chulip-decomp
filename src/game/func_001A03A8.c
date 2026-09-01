typedef struct PeekCmd {
    int addr;
    int size;
    int data;
} PeekCmd;

extern PeekCmd D_002E3E80[];
extern int D_002E4080[];

extern int func_0019F818(void);
extern int func_0019B760(void *client, unsigned int rpc_number, unsigned int mode,
                         void *send, int ssize, void *recv, int rsize,
                         void (*end_function)(void *), void *end_param);

int func_001A03A8(int addr, void *out, int size) {
    if (func_0019F818() < 0) {
        return -0x10000;
    }
    if ((unsigned int)size >= 3) {
        return -0x10002;
    }
    D_002E3E80->addr = addr;
    D_002E3E80->size = size;
    if (func_0019B760(D_002E4080, 3, 0, D_002E3E80, 0x20, D_002E3E80, 0x20, 0, 0) < 0) {
        return -0x10001;
    }
    if (size == 0) {
        *(unsigned char *)out = *(unsigned char *)D_002E3E80;
    } else if (size == 1) {
        *(unsigned short *)out = *(unsigned short *)D_002E3E80;
    } else if (size == 2) {
        *(int *)out = *(int *)D_002E3E80;
    } else {
        return -0x10002;
    }
    return 0;
}
