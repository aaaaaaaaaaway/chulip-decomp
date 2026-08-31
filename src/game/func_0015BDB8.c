typedef struct Target {
    unsigned char pad[0x18];
    unsigned short first;
    unsigned char pad1A[0x2];
    unsigned short second;
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
    unsigned char pad[0x4];
    unsigned short first;
    unsigned char pad6[0x6];
    unsigned short second;
    unsigned char tail[0x12];
} Slot;

extern Entry D_002ABA40[];
extern Slot D_002CFA40[];

unsigned short func_0015BDB8(unsigned short index) {
    Target *target;

    if (index == 0xFFFF) {
        return 0;
    }
    if ((D_002ABA40 + index)->owner == 0 && index < 0x1C0) {
        return D_002CFA40[index].second;
    }
    target = (D_002ABA40 + index)->owner->target;
    if (target == 0) {
        return 0;
    }
    return target->second;
}
