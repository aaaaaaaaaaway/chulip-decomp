typedef struct PokeCmd {
    int addr;
    int size;
    int data;
} PokeCmd;

extern PokeCmd D_002E3E80[];
extern int D_002E4080[];

extern int func_0019F818(void);
extern int func_0019B760(void *client, unsigned int rpc_number, unsigned int mode,
                         void *send, int ssize, void *recv, int rsize,
                         void (*end_function)(void *), void *end_param);

int func_001A0498(int addr, void *data, int size) {
    if (func_0019F818() < 0) {
        return -0x10000;
    }
    D_002E3E80->addr = addr;
    D_002E3E80->size = size;
    if (size == 0) {
        *(unsigned char *)&D_002E3E80->data = *(unsigned char *)data;
    } else if (size == 1) {
        *(unsigned short *)&D_002E3E80->data = *(unsigned short *)data;
    } else if (size == 2) {
        D_002E3E80->data = *(int *)data;
    } else {
        return -0x10002;
    }
    if (func_0019B760(D_002E4080, 2, 0, D_002E3E80, 0x20, D_002E3E80, 0x10, 0, 0) < 0) { return -0x10001; }
    return 0;
}
