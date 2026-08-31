typedef struct {
    unsigned char pad[0x20];
    long flags;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_00158E58(unsigned short index, unsigned char enable) {
    if (enable) {
        (D_002ABA40 + index)->flags |= 0x40000;
    } else {
        (D_002ABA40 + index)->flags &= ~0x40000;
    }
}
