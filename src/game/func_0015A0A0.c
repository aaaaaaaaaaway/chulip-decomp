typedef union Slot {
    long flags;
    struct { int lo; void *owner; } p;
    struct { volatile long l : 3; volatile long v : 32; volatile long h : 29; } b29;
} Slot;

typedef struct Entry {
    unsigned char pad[0x20];
    Slot u;
    unsigned char pad28[0xE];
    unsigned short slot;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
extern int D_001ECC40;
extern void *D_001ECCB8;

void func_0015A4E0(int index);
void func_00155878(int index);
void func_00155920(int index);
void func_00151858(int index, int mode);
void func_00151CA8(void *ptr);

void func_0015A0A0(void) {
    unsigned short i;
    Entry *e;

    i = 0;
    do {
        func_0015A4E0(i);
        func_00155878(i);
        e = D_002ABA40 + i;
        if ((int)e->u.b29.v & 1) {
            func_00155920(i);
        }
        if ((unsigned int)(i - 0x438) >= 0x20) {
            e->slot = 0xFFFF;
            e->u.p.lo = D_001ECC40;
            func_00151858(i, 0);
            e->u.flags &= ~0x400;
        }
        i = i + 1;
    } while (i < 0x480);
    if (D_001ECCB8 != 0) {
        func_00151CA8(D_001ECCB8);
        D_001ECCB8 = 0;
    }
}
