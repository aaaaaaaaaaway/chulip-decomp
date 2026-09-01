typedef struct {
    unsigned int id;
    int mode;
    short unk08;
    short unk0A;
    int unk0C;
    int unk10;
    short unk14;
    short unk16;
    short unk18;
    short unk1A;
    int next;
    int prev;
} EventSlot;

extern EventSlot D_001FA9E8[];
extern int D_001FA9D0[];

int func_0011E540(int id, int value, int mode, unsigned short *params) {
    int i;
    int last;

    i = 0x90;
    if (mode == 8 || mode == 0x10) {
        for (i = 0; i < 0x90; i++) {
            if (D_001FA9E8[i].id == id) {
                break;
            }
        }
    }
    if (mode == 8 && i != 0x90) {
        return -1;
    }
    if (mode == 0x10 && i != 0x90) {
        D_001FA9E8[i].id = id;
        D_001FA9E8[i].unk08 = value;
        D_001FA9E8[i].unk0A = value;
        D_001FA9E8[i].mode = mode;
        D_001FA9E8[i].unk14 = params[0];
        D_001FA9E8[i].unk16 = params[1];
        D_001FA9E8[i].unk18 = params[2];
        D_001FA9E8[i].unk1A = params[3];
        return i;
    }
    for (i = 0; i < 0x90; i++) {
        if (D_001FA9E8[i].id == 0xFFFFFFFF) {
            break;
        }
    }
    last = D_001FA9D0[3];
    D_001FA9E8[i].id = id;
    D_001FA9E8[i].unk08 = value;
    D_001FA9E8[i].unk0A = value;
    D_001FA9E8[i].mode = mode;
    D_001FA9E8[i].next = -1;
    if (last != -1) {
        D_001FA9E8[i].prev = last;
        D_001FA9E8[last].next = i;
    } else {
        D_001FA9E8[i].prev = last;
    }
    if (params != 0) {
        D_001FA9E8[i].unk14 = params[0];
        D_001FA9E8[i].unk16 = params[1];
        D_001FA9E8[i].unk18 = params[2];
        D_001FA9E8[i].unk1A = params[3];
    }
    D_001FA9D0[3] = i;
    if (D_001FA9D0[2] == -1) {
        D_001FA9D0[2] = i;
    }
    return i;
}
