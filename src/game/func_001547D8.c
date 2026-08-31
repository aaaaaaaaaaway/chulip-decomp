typedef struct {
    unsigned char pad[0x31];
    unsigned char state;
    unsigned char tail[0xE];
} Slot;

typedef struct {
    unsigned char pad[0x36];
    unsigned short slot;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
extern Slot D_002BDA40[];

int func_001547D8(unsigned short index) {
    if (index >= 0x3E0) {
        return 0;
    }
    return (D_002BDA40 + (D_002ABA40 + index)->slot)->state;
}
