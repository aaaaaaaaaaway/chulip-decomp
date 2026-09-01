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

typedef struct {
    unsigned char pad[0x20];
    unsigned char kind;
    unsigned char pad2[0x13];
    int size;
    unsigned char tail[0x8];
} Record;

extern Entry D_002ABA40[];
extern Record D_002BDA40[];
extern int D_001ECCAC;

unsigned int func_001513E0(int kind, int id, int arg);
void *func_00192344(void *dest, void *src, int n);

void func_00155B58(unsigned short index, unsigned short other) {
    Entry *entry;
    unsigned int src;
    unsigned int buf;
    int size;
    int off;
    int b3;
    unsigned int k;
    int *p;
    Entry *p1;
    Entry *p2;
    long f;

    entry = D_002ABA40 + index;
    b3 = (int)(entry->u.flags << 29 >> 32) & 1;
    if (b3 != 1) {
        return;
    }
    src = func_001513E0(0x12, index, 0);
    size = D_002BDA40[entry->id].size;
    if (other == 0) {
        buf = D_001ECCAC;
        off = 0;
    } else {
        buf = func_001513E0(0x10, other, size);
        (D_002ABA40 + other)->u.flags |= 0x800;
        off = other << 6;
    }
    func_00192344((void *)buf, (void *)src, size);
    for (k = 0, p = (int *)buf; k < 0xF; k++) {
        if (*p != 0) {
            *p = *p - src;
        }
        p++;
    }
    for (k = 0, p = (int *)buf; k < 0xF; k++) {
        if (*p != 0) {
            *p = *p + buf;
        }
        p++;
    }
    if (D_002BDA40[D_002ABA40[index].id].kind == 1) {
        p1 = (Entry *)((char *)D_002ABA40 + off);
        p1->u.flags |= 0x40;
    }
    p2 = (Entry *)((char *)D_002ABA40 + off);
    f = p2->u.flags | 8;
    p2->u.flags = f | 0x2000;
}
