typedef struct Slot {
    unsigned char pad[0x2D];
    unsigned char b2D;
    unsigned char b2E;
    unsigned char b2F;
    unsigned char b30;
    unsigned char tail[0xF];
} Slot;

extern Slot D_002BDA40[];

void func_0015CB00(unsigned short index, unsigned char kind, unsigned char value) {
    switch (kind) {
    case 2:
        (D_002BDA40 + index)->b30 = value;
        break;
    case 1:
        (D_002BDA40 + index)->b2F = value;
        break;
    case 3:
        (D_002BDA40 + index)->b2E = value;
        break;
    case 4:
        (D_002BDA40 + index)->b2D = value;
        break;
    }
}
