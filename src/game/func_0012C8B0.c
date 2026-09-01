struct Entry_001FDB20 { unsigned char id; unsigned char count; };
struct List_001FDB20 { unsigned short count; unsigned short pad_0x2; struct Entry_001FDB20 entries[0x100]; };

extern struct List_001FDB20 D_001FDB20;
extern int D_001EC8F4;

void func_0012C8B0(unsigned short id) {
    int i;

    for (i = D_001FDB20.count - 1; i >= 0; i--) {
        if (D_001FDB20.entries[i].id == id) {
            break;
        }
    }
    if (i < 0) {
        return;
    }
    if (D_001FDB20.entries[i].count == 0) {
        return;
    }
    D_001FDB20.entries[i].count = D_001FDB20.entries[i].count - 1;
    if (D_001FDB20.entries[i].count == 0) {
        for (; i < D_001FDB20.count - 1; i++) {
            D_001FDB20.entries[i].id = D_001FDB20.entries[i + 1].id;
            D_001FDB20.entries[i].count = D_001FDB20.entries[i + 1].count;
        }
        D_001EC8F4 = 1;
        D_001FDB20.count = D_001FDB20.count - 1;
    } else {
        D_001EC8F4 = 0;
    }
}
