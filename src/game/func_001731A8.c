typedef struct {
    unsigned int flags;
    char pad04[0x6A];
    unsigned short id;
    char pad70[0x45];
    unsigned char kind;
    char padB6[0xA];
} Ent;

extern Ent *D_001ED6C0;
extern unsigned short D_002D8850[];

unsigned short func_001731A8(unsigned short kind) {
    int i;

    for (i = 0; i < D_002D8850[0]; i++) {
        if (D_001ED6C0[i].kind == kind && (D_001ED6C0[i].flags & 0x40000000) != 0) {
            return i;
        }
    }
    return 0xFFFF;
}
