typedef struct {
    int id;
    int pad[3];
    int flags;
    int pad2[4];
} Entry;

extern Entry D_001FA9E8[];

void func_0011EA98(int id) {
    int offset;

    for (offset = 0; offset < 144 * 0x24; offset += 0x24) {
        Entry *entry = (Entry *)((char *)D_001FA9E8 + offset);

        if (entry->id == id) {
            entry->flags |= 1;
        }
    }
}
