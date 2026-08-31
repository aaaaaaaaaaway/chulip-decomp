typedef struct Entry {
    unsigned char pad[0x2F0];
    int first;
    int second;
    unsigned char tail[0x50];
} Entry;

extern Entry D_002D78C0[];

void func_0015E118(int index, int first, int second) {
    Entry *entry = &D_002D78C0[index];

    entry->first = first;
    entry->second = second;
}
