typedef struct {
    unsigned int flags;
    char pad04[0x6A];
    unsigned short id;
    char pad70[0x45];
    unsigned char kind;
    char padB6[0xA];
} Ent00173148;

extern Ent00173148 *D_001ED6C0;
extern unsigned short D_002D8850[];

unsigned short func_00173148(unsigned short id) {
    int i;

    for (i = 0; i < D_002D8850[0]; i++) {
        if (D_001ED6C0[i].id == id && (D_001ED6C0[i].flags & 0x800000) == 0) {
            return i;
        }
    }
    return 0xFFFF;
}
