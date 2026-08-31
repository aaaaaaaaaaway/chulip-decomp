typedef struct {
    unsigned char pad[0x20];
    long flags;
    unsigned char pad28[0x12];
    unsigned char state;
    unsigned char tail[0x5];
} Entry;

extern Entry D_002ABA40[];

void func_00158D18(unsigned short index, unsigned char state, unsigned char enable) {
    (D_002ABA40 + index)->state = state;
    if (enable) {
        (D_002ABA40 + index)->flags |= 0x100;
    } else {
        (D_002ABA40 + index)->flags &= ~0x100;
    }
}
