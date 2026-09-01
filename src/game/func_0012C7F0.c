struct Entry_001FDB20 { unsigned char id; unsigned char count; };
struct List_001FDB20 { unsigned short count; unsigned short pad_0x2; struct Entry_001FDB20 entries[0x100]; };

extern struct List_001FDB20 D_001FDB20;
extern int D_001EC8F4;

void func_0012C7F0(unsigned short id) {
    int i;

    for (i = 0; i < D_001FDB20.count; i++) {
        if (D_001FDB20.entries[i].id == id) {
            break;
        }
    }
    if (i >= D_001FDB20.count) {
        D_001FDB20.entries[i].id = id;
        D_001FDB20.entries[i].count = 1;
        D_001EC8F4 = 1;
        D_001FDB20.count = D_001FDB20.count + 1;
        return;
    }
    if (D_001FDB20.entries[i].count < 0x63) {
        D_001EC8F4 = 0;
        D_001FDB20.entries[i].count = D_001FDB20.entries[i].count + 1;
    }
}
