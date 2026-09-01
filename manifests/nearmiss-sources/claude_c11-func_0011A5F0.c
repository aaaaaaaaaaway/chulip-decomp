typedef struct {
    int state;
    unsigned short id;
    unsigned short pad6;
    int pad8;
    int timer;
} Slot;

extern Slot D_001FA200[];
extern float D_001EDCC0[];

void func_00158908(int id, float *out);
void func_0018AED0(int *out, float *matrix, float *in, int mode);

int func_0011A5F0(unsigned char *packet, int index) {
    int ox[4];
    int oy[4];
    float world[4];
    int screen[4];
    int i;
    int step;
    int depth;

    D_001FA200[index].timer = D_001FA200[index].timer % 0x28;
    ox[0] = 0;
    oy[0] = 0;
    ox[1] = 0;
    depth = 0x8FFF0;
    oy[1] = 0;

    func_00158908(D_001FA200[index].id, world);
    world[3] = 1.0f;
    func_0018AED0(screen, D_001EDCC0, world, 0);

    for (i = 0, step = -0x28; i < 0x14; i++) {
        ox[0] = step;
        ox[1] = step;
        if ((i & 1) == 0) {
            oy[0] = i / 6 - 0x1E;
            oy[1] = (0xA - i) / 3;
        } else {
            oy[0] = -0x20 - i / 8;
            oy[1] = -((i - 0xA) / 4);
        }
        oy[1] += D_001FA200[index].timer / 2;

        *(long *)packet = 0x4024C00000008001L;
        *(long *)(packet + 8) = 0x4141L;
        packet += 0x10;

        *(int *)(packet + 0x00) = 0;
        *(int *)(packet + 0x04) = 0;
        *(int *)(packet + 0x08) = 0;
        *(int *)(packet + 0x0C) = 0x80;
        *(int *)(packet + 0x10) = screen[0] + (ox[0] << 4);
        *(int *)(packet + 0x14) = screen[1] + (oy[0] << 4);
        *(int *)(packet + 0x18) = depth;
        *(int *)(packet + 0x1C) = 0;
        *(int *)(packet + 0x20) = 0;
        *(int *)(packet + 0x24) = 0;
        *(int *)(packet + 0x28) = 0;
        *(int *)(packet + 0x2C) = 0;
        *(int *)(packet + 0x30) = screen[0] + (ox[1] << 4);
        *(int *)(packet + 0x34) = screen[1] + (oy[1] << 4);
        *(int *)(packet + 0x38) = depth;
        *(int *)(packet + 0x3C) = 0;
        packet += 0x40;
        step += 4;
    }
    return 0x64;
}
