typedef struct {
    unsigned char unknown00[16];
    unsigned char primary_state[80];
    unsigned char secondary_state[80];
    unsigned char primary_control[16];
    unsigned char secondary_control[16];
    void *primary_data;
    unsigned int unknownD4, unknownD8, primary_qwc;
    void *secondary_data;
    unsigned int unknownE4, unknownE8, secondary_qwc;
} Part;
typedef struct {
    int count;
    Part *parts;
    int unknown08;
    void *packet;
    float transferred;
} Model;
typedef struct {
    char *pointers[2];
    int capacity;
} DrawList;
extern DrawList D_002D81B0;
extern unsigned char D_001E1680[];
extern int func_00161600(int, int);
extern void func_00161870(int, int, int);
extern void func_00161590(int, int);

void *func_0017D998(Model *model, unsigned char *skip) {
    char *start = D_002D81B0.pointers[1];
    char *packet = start;
    int i;
    if (model) {
        for (i = 0; i < model->count; ++i) {
            Part *parts;
            if (skip && i == skip[1]) {
                skip += 2;
                continue;
            }
            parts = model->parts;
            func_00161600((int)packet, 0);
            packet += 16;
            func_00161870((int)packet, (int)parts[i].primary_state, 5);
            packet += 16;
            func_00161870((int)packet, (int)parts[i].primary_control, 1);
            packet += 16;
            func_00161870((int)packet, (int)parts[i].primary_data, parts[i].primary_qwc);
            packet += 16;
            model->transferred += (float)parts[i].primary_qwc * 0.0000152587890625f;
            if (parts[i].secondary_qwc) {
                func_00161870((int)packet, (int)parts[i].secondary_state, 5);
                packet += 16;
                func_00161870((int)packet, (int)parts[i].secondary_control, 1);
                packet += 16;
                func_00161870((int)packet, (int)parts[i].secondary_data, parts[i].secondary_qwc);
                packet += 16;
                model->transferred += (float)parts[i].secondary_qwc * 0.0000152587890625f;
            }
            func_00161870((int)packet, (int)D_001E1680, 2);
            packet += 16;
        }
    }
    func_00161590((int)packet, 0);
    packet += 16;
    D_002D81B0.pointers[1] = packet;
    return start;
}
