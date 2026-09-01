typedef struct Ent {
    unsigned char pad[0x4];
    unsigned char kind;
    unsigned char pad2[0x3];
    unsigned short flag;
    unsigned char pad3[0x16];
} Ent;

extern Ent *D_001ECF70;

void func_0017EC38(unsigned short index, unsigned char kind);

void func_0017EDC8(void) {
    int i;

    for (i = 0; i < 0x38; i++) {
        if ((D_001ECF70 + i)->flag != 0) {
            func_0017EC38(i, (D_001ECF70 + i)->kind);
        }
    }
}
