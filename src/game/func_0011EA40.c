typedef struct { unsigned int id; int pad[6]; int f1C; int f20; } Entry;

extern int D_001FA9D0[4];
extern Entry D_001FA9E8[];

void func_0011EA40(void) {
    int offset;

    D_001FA9D0[0] = 0;
    D_001FA9D0[1] = 0;
    D_001FA9D0[2] = -1;
    D_001FA9D0[3] = -1;
    for (offset = 0; offset < 144 * 0x24; offset += 0x24) {
        Entry *entry = (Entry *)((char *)D_001FA9E8 + offset);

        entry->id = 0xFFFFFFFFu;
        entry->f1C = -1;
        entry->f20 = -1;
    }
}
