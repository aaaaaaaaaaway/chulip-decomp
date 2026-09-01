typedef struct {
    unsigned int flags;
    unsigned char pad04[0x48];
    unsigned int unk4C;
    unsigned char pad50[0x1C];
    unsigned short unk6C;
    unsigned short unk6E;
    unsigned char pad70[0x24];
    unsigned short unk94;
    unsigned char pad96[0x2A];
} Actor;

typedef struct {
    unsigned char pad00[0x10];
    unsigned short count;
    unsigned char pad12[0x10];
} ActorTable;

typedef struct {
    unsigned char pad00[4];
    unsigned int unk04;
    unsigned char pad08[0x66];
    unsigned short unk6E;
} Owner;

extern Actor *D_001ED6C0[1];
extern Owner *D_001ED7E0[1];
extern ActorTable D_002D8840;

extern void func_00119AA0(int, int);

void func_00172918(unsigned short id, unsigned char keep) {
    int i;

    for (i = 1; i < D_002D8840.count; i++) {
        if (D_001ED6C0[0][i].unk6E == id && (D_001ED6C0[0][i].flags & 0x800000) == 0) {
            func_00119AA0(D_001ED7E0[0]->unk6E, 0);
            D_001ED7E0[0]->unk04 &= ~0x1F80;
            if (keep == 0) {
                D_001ED6C0[0][i].unk6C = 0xFFFF;
                D_001ED6C0[0][i].unk4C = 0xFFFFFFFF;
                D_001ED6C0[0][i].unk94 = 0xFFFF;
            }
            D_001ED6C0[0][i].flags |= 0x2000;
            return;
        }
    }
}
