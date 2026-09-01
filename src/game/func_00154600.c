typedef union Slot {
    long flags;
    struct { volatile long low : 16; volatile long value : 32; volatile long high : 16; } b16;
} Slot;
typedef struct Entry {
    unsigned char pad[0x20];
    Slot u;
    float f28;
    unsigned char tail[0x14];
} Entry;

extern Entry D_002ABA40[];

float func_00154600(unsigned short index) {
    if (((int)D_002ABA40[index].u.b16.value & 1) == 0) {
        return 0.0f;
    }
    return D_002ABA40[index].f28;
}
