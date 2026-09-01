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

int func_0012FB88(unsigned short key);
unsigned short func_00155398(unsigned short index);
void func_00155800(unsigned short slot, unsigned short index);

void func_0015A7C8(void) {
    Entry *entry;
    Entry *entry2;
    unsigned short i;
    int b3;

    for (i = 0x3E0; i < 0x438; i++) {
        if (func_0012FB88(i) != 0) {
            entry = D_002ABA40 + i;
            b3 = (int)(entry->u.flags << 29 >> 32) & 1;
            if (b3 != 1) {
                func_00155398(i);
            }
            if (entry->u.s.owner == 0) {
                func_00155800(i + 0xFEE0, i);
            }
        } else {
            entry2 = D_002ABA40 + i;
            b3 = (int)(entry2->u.flags << 29 >> 32) & 1;
            if (b3 == 1) {
                if (entry2->u.s.owner == 0) {
                    func_00155800(i + 0xFEE0, i);
                }
            }
        }
    }
}
