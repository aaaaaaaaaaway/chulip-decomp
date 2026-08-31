typedef struct LookupOwner {
    unsigned char unknown_00[4];
    struct LookupEntry *entries;
} LookupOwner;

typedef struct LookupEntry {
    unsigned char unknown_00[0x18];
    float value_18;
    unsigned char unknown_1C[0x24];
} LookupEntry;

float func_001335A0(const LookupOwner *owner, unsigned char index) {
    return *(float *)((unsigned int)owner->entries + ((unsigned int)index << 6) + 0x18);
}
