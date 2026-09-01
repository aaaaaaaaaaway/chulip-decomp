extern int D_002E3E80[];
extern int D_002E4080[];

extern int func_0019F818(void);
extern int func_0019F918(void);
extern int func_0019B760(void *client, unsigned int rpc_number, unsigned int mode,
                         void *send, int ssize, void *recv, int rsize,
                         void (*end_function)(void *), void *end_param);

int func_0019FDF0(int value) {
    if (func_0019F818() < 0) {
        return -0x10000;
    }
    if (func_0019F918() != 0) {
        return -0x10004;
    }
    D_002E3E80[0] = value;
    if (func_0019B760(D_002E4080, 8, 0, D_002E3E80, 4, D_002E3E80, 4, 0, 0) < 0) {
        return -0x10001;
    }
    return D_002E3E80[0];
}
