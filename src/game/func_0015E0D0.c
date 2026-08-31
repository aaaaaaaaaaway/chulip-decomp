typedef struct Entry {
    unsigned char pad[0x2DC];
    int first;
    int second;
    int third;
    unsigned char tail[0x60];
} Entry;

extern Entry D_002D78C0[];

void func_0015E0D0(int index, int first, int second, int third) {
    Entry *entry = &D_002D78C0[index];

    entry->first = first;
    entry->second = second;
    entry->third = third;
}
