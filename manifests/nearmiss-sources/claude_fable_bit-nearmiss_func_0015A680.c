typedef struct {
    unsigned char pad[0x20];
    union {
        long flags;
        struct {
            int pad;
            void *owner;
        } s;
    } u;
    unsigned char pad2[0xE];
    unsigned short id;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
extern int D_001ECCB8;

long *func_00136AE8(void);
extern void func_00151CA8(int handle);
int func_00155878(unsigned short index);
void func_0015A188(unsigned short value);

void func_0015A680(unsigned char mode) {
    long *p;
    unsigned short i;
    Entry *entry;
    Entry *entry2;
    unsigned short id;
    int b3;
    long v;

    p = func_00136AE8();
    if (D_001ECCB8 == 0) {
        if (mode == 0) {
            return;
        }
    } else {
        func_00151CA8(D_001ECCB8);
        D_001ECCB8 = 0;
    }
    for (i = 0x11C; i < 0x15C; i++) {
        entry = D_002ABA40 + i;
        id = entry->id;
        if ((id >= 1 && id <= 0xFB) || (id >= 0x15C && id <= 0x1BF)) {
            func_00155878(i);
            b3 = (int)(entry->u.flags << 29 >> 32) & 1;
            if (b3 != 0) {
                func_0015A188(i);
            }
        }
    }
    for (i = 0x15C; i < 0x3A0; i++) {
        entry2 = D_002ABA40 + i;
        v = entry2->u.flags & ~4;
        entry2->u.flags = v;
        b3 = (int)(v << 29 >> 32) & 1;
        if (b3 == 1) {
            func_0015A188(i);
        }
    }
    *p |= 8;
}
