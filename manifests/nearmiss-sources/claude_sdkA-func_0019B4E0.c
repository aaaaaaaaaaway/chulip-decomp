typedef struct Node {
    char pad0[8];
    int unk8;
    char padC[8];
    int unk14;
} Node;

typedef struct {
    char pad0[0x14];
    int unk14;
    char pad18[4];
    int unk1C;
    int unk20;
    Node *unk24;
    int unk28;
    int unk2C;
} Packet;

extern Packet *func_0019B1B0(void *arg);
extern Node *func_0019B490(int id, void *arg);
extern void func_0019AD08(int cmd, Packet *packet, int size, int a, int b, int c);

void func_0019B4E0(Packet *src, void *arg) {
    Packet *dst;
    Node *node;

    dst = func_0019B1B0(arg);
    dst->unk14 = src->unk14;
    dst->unk1C = src->unk1C;
    dst->unk20 = 0x80000009;
    node = func_0019B490(src->unk20, arg);
    if (node != 0) {
        dst->unk24 = node;
        dst->unk28 = node->unk8;
        dst->unk2C = node->unk14;
    } else {
        dst->unk24 = 0;
        dst->unk28 = 0;
        dst->unk2C = 0;
    }
    func_0019AD08(0x80000008, dst, 0x40, 0, 0, 0);
}
