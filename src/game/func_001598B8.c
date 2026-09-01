typedef struct {
    unsigned char pad[0x20];
    union {
        long flags;
        struct {
            int pad;
            void *owner;
        } s;
    } u;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_001548C0(unsigned short index);

void func_001598B8(void) {
    Entry *entry;
    unsigned short i;
    int b3;

    for (i = 0x43C; i < 0x449; i++) {
        entry = D_002ABA40 + i;
        b3 = (int)(entry->u.flags << 29 >> 32) & 1;
        if (b3 == 1) {
            if (entry->u.s.owner == 0) {
                func_001548C0(i);
                entry->u.flags |= 0x400;
            }
        }
    }
    b3 = (int)(D_002ABA40[0x43A].u.flags << 29 >> 32) & 1;
    if (b3 == 1) {
        if (D_002ABA40[0x43A].u.s.owner == 0) {
            func_001548C0(0x43A);
            D_002ABA40[0x43A].u.flags |= 0x400;
        }
    }
}
