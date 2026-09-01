typedef struct {
    unsigned char pad[0x20];
    union {
        long flags;
        struct {
            int low;
            void *owner;
        } s;
    } u;
    unsigned char pad2[0xE];
    unsigned short id;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
extern int D_001ECC40;

void func_001599B0(int mode);
void func_0015BE88(unsigned short index, int a, int b);
void func_0015A4E0(unsigned short index);
void func_00155920(unsigned short index);
void func_00151858(unsigned short index, int value);

void func_00159C28(void) {
    Entry *entry;
    unsigned short i;
    unsigned short slot;
    unsigned short j;
    int b12;
    int b8;
    int b3;

    func_001599B0(0);
    for (i = 0; i < 0x1C0; i++) {
        entry = D_002ABA40 + i;
        if (entry->u.s.owner != 0) {
            b12 = (int)(entry->u.flags << 20 >> 32) & 1;
            if (b12 == 1) {
                func_0015BE88(i, 1, 0);
                entry->u.flags &= ~0x1000;
            }
            b8 = (int)(entry->u.flags << 24 >> 32) & 1;
            if (b8 == 1) {
                func_0015BE88(i, 2, 0);
                entry->u.flags &= ~0x100;
            }
            entry->u.flags &= ~0x20000;
        }
    }
    for (j = 0; j < 0x68; j++) {
        if (j < 0x28) {
            slot = j + 0x458;
            if (slot >= 0x458 && slot <= 0x45C) {
                continue;
            }
        } else {
            slot = j + 0xF4;
        }
        func_0015A4E0(slot);
        entry = D_002ABA40 + slot;
        b3 = (int)(entry->u.flags << 29 >> 32) & 1;
        if (b3 == 1) {
            func_00155920(slot);
        }
        entry->id = 0xFFFF;
        entry->u.s.low = D_001ECC40;
        func_00151858(slot, 0);
    }
}
