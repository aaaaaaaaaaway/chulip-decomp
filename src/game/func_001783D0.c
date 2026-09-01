typedef struct {
    unsigned int flags;
    char pad04[0x6A];
    unsigned short id;
    char pad70[0x45];
    unsigned char kind;
    char padB6[0xA];
} Ent001783D0;

extern Ent001783D0 *D_001ED6C0;
extern unsigned short D_002D8840[];

int func_00158B40();
int func_00158BB8();
int func_00172AC8();

void func_001783D0(unsigned short kind) {
    Ent001783D0 *e;
    int i;

    for (i = 0; i < D_002D8840[8]; i++) {
        e = &D_001ED6C0[i];
        if ((e->flags & 0x80000000) != 0 && e->kind == kind) {
            func_00158BB8(e->id, 0);
            func_00158B40(e->id, 1);
            func_00172AC8(e->id);
            return;
        }
    }
}
