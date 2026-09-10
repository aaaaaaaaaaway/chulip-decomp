typedef struct PadData {
    unsigned char data[32];
    unsigned char actuator_direct[8];
    unsigned char actuator_align[8];
    unsigned char actuator_data[4][4];
    unsigned char combination_data[4][4];
    unsigned short modes[4];
    int frame;
    int find_retries;
    int length;
    unsigned char mode_config;
    unsigned char mode_id;
    unsigned char model;
    unsigned char buttons_ready;
    unsigned char mode_count;
    unsigned char mode_offset;
    unsigned char actuator_count;
    unsigned char combination_count;
    unsigned char field_6c;
    unsigned char mode;
    unsigned char lock;
    unsigned char actuator_size;
    unsigned char state;
    unsigned char request_state;
    unsigned char current_task;
    unsigned char run_task;
    unsigned char stat70bit;
    unsigned char fields75[4];
    unsigned char button_mask[4];
    unsigned char fields7d[3];
} PadData;

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
extern PadData *func_00189650(int port, int slot);
extern void func_00199098(void *start, void *end);

extern int D_001E30A4;
extern char D_001EB060[], D_001EB090[];
extern int D_002DE880[];
extern unsigned char D_002DE640[];
extern int func_00192508(const char *, ...);
extern void *func_001923F4(void *, int, unsigned int);
extern int func_0019B760(void *, int, int, void *, int, void *, int, void (*)(void *), void *);

int func_00189EE8(int port, int slot) {
    PadData *data;
    if (D_002DE690[port][slot].open == 0)
        return 0;
    data = func_00189650(port, slot);
    if (data->current_task != 1)
        return 0;
    if (data->mode_config < 2)
        return 0;
    if (data->model < 2)
        return 0;
    return data->button_mask[0] + ((unsigned long)data->button_mask[1] << 8) +
           ((unsigned long)data->button_mask[2] << 16) +
           ((unsigned long)data->button_mask[3] << 24);
}
