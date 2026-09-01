typedef struct {
    unsigned int flags;
    char pad04[0x6A];
    unsigned short id;
    char pad70[0x45];
    unsigned char kind;
    char padB6[0xA];
} Ent;

extern Ent *D_001ED6C0;
extern unsigned short D_002D8840[];

void func_00172A48(unsigned short id) {
    int i;

    for (i = 1; i < D_002D8840[8]; i++) {
        if (D_001ED6C0[i].id == id && (D_001ED6C0[i].flags & 0x800000) == 0) {
            D_001ED6C0[i].flags &= ~0x2000U;
            return;
        }
    }
}
