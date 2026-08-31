typedef struct Target {
    unsigned char pad[0x1C];
    int count;
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

extern Entry D_002ABA40[];

int func_0015BE38(unsigned short index) {
    Owner *owner;

    if (index == 0xFFFF) {
        return 0;
    }
    owner = (D_002ABA40 + index)->owner;
    if (owner == 0) {
        return 0;
    }
    if (owner->target == 0) {
        return 0;
    }
    return owner->target->count != 0;
}
