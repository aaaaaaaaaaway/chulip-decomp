typedef struct Entry {
    unsigned char pad[0x2E8];
    float first;
    float second;
    unsigned char tail[0x58];
} Entry;

extern Entry D_002D78C0[];

void func_0015E138(int index, float first, float second) {
    Entry *entry = &D_002D78C0[index];

    entry->first = first;
    entry->second = second;
}
