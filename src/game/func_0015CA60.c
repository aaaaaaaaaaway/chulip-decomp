typedef struct Slot {
    unsigned char pad[0x2D];
    unsigned char b2D;
    unsigned char b2E;
    unsigned char b2F;
    unsigned char b30;
    unsigned char tail[0xF];
} Slot;

extern Slot D_002BDA40[];

unsigned char func_0015CA60(unsigned short index, unsigned char kind) {
    switch (kind) {
    case 2:
        return (D_002BDA40 + index)->b30;
    case 1:
        return (D_002BDA40 + index)->b2F;
    case 3:
        return (D_002BDA40 + index)->b2E;
    case 4:
        return (D_002BDA40 + index)->b2D;
    }
    return 0;
}
