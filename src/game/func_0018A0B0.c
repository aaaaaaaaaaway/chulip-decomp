typedef struct PadData PadData;

typedef struct PadState {
    PadData *data;
    void *buffer;
    void *iop_buffer;
    int dma_id;
    int open;
    int field14;
    int field18;
} PadState;
extern PadState D_002DE690[][4];

extern int func_00189FA0(int, int, int);
int func_0018A0B0(int port, int slot) {
    if (!D_002DE690[port][slot].open)
        return 0;
    return func_00189FA0(port, slot, 0xFFF);
}
