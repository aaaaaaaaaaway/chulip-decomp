typedef struct Target {
    unsigned char pad[0x28];
    float value;
} Target;
typedef struct Owner {
    unsigned char pad[0x14];
    Target *target;
} Owner;
typedef struct {
    unsigned char pad[0x24];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;
typedef struct {
    unsigned char pad[0x18];
    float value;
    unsigned char tail[0x4];
} Slot;
extern Entry D_002ABA40[];
extern Slot D_002CFA40[];
float func_00158478(unsigned short slot) {
    unsigned int index = slot;
    Entry *entry;
    Slot *fallback;
    Slot *temp;
    if (index >= 0x1C0) {
        return 0.0f;
    }
    temp = D_002CFA40 + index;
    entry = D_002ABA40 + index;
    fallback = temp;
    if (entry->owner == 0) {
        return fallback->value;
    }
    if (entry->owner->target == 0) {
        return 0.0f;
    }
    return entry->owner->target->value;
}
