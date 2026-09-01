typedef struct {
    unsigned int unk00;
    unsigned int unk04;
    unsigned char pad08[0x66];
    unsigned short unk6E;
    unsigned char pad70[0x50];
} Actor;

typedef struct {
    unsigned char pad00[0x10];
    unsigned short count;
    unsigned char pad12[0x10];
} ActorTable;

extern Actor *D_001ED6C0;
extern ActorTable D_002D8840;

extern void func_00158C70(int, int);
extern void func_00119AA0(int, int);

void func_00172628(unsigned char enable) {
    Actor *actor;
    unsigned int value;
    int i;

    for (i = 1; i < D_002D8840.count; i++) {
        actor = &D_001ED6C0[i];
        if ((actor->unk00 & 0x800000) != 0) {
            continue;
        }
        if (actor->unk6E == 0xFFFF) {
            continue;
        }
        if ((actor->unk00 & 0x400) == 0) {
            if (enable != 0) {
                func_00158C70(actor->unk6E, 1);
            } else {
                func_00158C70(actor->unk6E, 0);
            }
        } else {
            if (enable == 1) {
                func_00158C70(actor->unk6E, 0);
            }
        }
        if ((actor->unk00 & 0x800) == 0) {
            if (enable != 0) {
                func_00158C70(actor->unk6E, 0);
            } else {
                func_00158C70(actor->unk6E, 1);
            }
        } else {
            if (enable == 0) {
                func_00158C70(actor->unk6E, 0);
            }
        }
        value = actor->unk04;
        if ((value & 0xF80) != 0) {
            if ((value & 0x1000000) == 0 || enable == 0) {
                func_00119AA0(actor->unk6E, 0);
                actor->unk04 &= ~0x1000;
            } else {
                actor->unk04 = value | 0x1000;
            }
        }
    }
}
