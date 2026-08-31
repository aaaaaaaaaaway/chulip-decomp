typedef struct Target {
    unsigned char pad[0x28];
    float value;
} Target;

typedef struct Owner {
    unsigned char pad[0x14];
    Target *target;
} Owner;

typedef struct {
    unsigned char pad[0x20];
    union {
        long flags;
        struct {
            int bits;
            Owner *owner;
        } fields;
    } state;
    unsigned char tail[0x18];
} Entry;

typedef struct {
    unsigned char pad[0x18];
    float value;
    unsigned char tail[0x4];
} Slot;

extern Entry D_002ABA40[];
extern Slot D_002CFA40[];
extern void func_0015D280(unsigned short index);

void func_001584D8(unsigned short index, float value) {
    Entry *entry;
    Slot *slot;
    int bit;

    if (index >= 0x1C0) {
        return;
    }
    entry = D_002ABA40 + index;
    slot = D_002CFA40 + index;
    if (entry->state.fields.owner == 0) {
        slot->value = value;
        return;
    }
    entry->state.fields.owner->target->value = value;
    slot->value = value;
    bit = (int)(entry->state.flags >> 18) & 1;
    if (bit == 1) {
        func_0015D280(index);
    }
}
