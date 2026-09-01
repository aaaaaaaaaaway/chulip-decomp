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

void func_00171FD8(unsigned int mask) {
    int i;

    for (i = 0; i < D_002D8840[8]; i++) {
        D_001ED6C0[i].flags &= ~mask;
    }
}
