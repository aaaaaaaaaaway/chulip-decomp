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
    unsigned char reserved75[11];
} PadData;

typedef struct PadState {
    PadData *data;
    void *buffer;
    int port;
    int slot;
    int open;
    int field14;
    int field18;
} PadState;
extern PadState D_002DE690[][4];
extern PadData *func_00189650(int port, int slot);
extern void func_00199098(void *start, void *end);

int func_00189B60(int port, int slot, int mode, int index) {
    PadData *data;
    if (D_002DE690[port][slot].open == 0)
        return 0;
    data = func_00189650(port, slot);
    if (data->current_task != 1)
        return 0;
    if (data->request_state == 2)
        return 0;
    switch (mode) {
    case 1:
        if (data->mode_id == 0xf3)
            return 0;
        return data->mode_id >> 4;
    case 2:
        if (data->mode_config == 1)
            return 0;
        return data->modes[data->mode_offset];
    case 3:
        if (data->mode_config == 1)
            return 0;
        return data->mode_offset;
    case 4:
        if (data->mode_config == 1)
            return 0;
        if (index == -1)
            return data->mode_count;
        if (index < data->mode_count)
            return data->modes[index];
    }
    return 0;
}
