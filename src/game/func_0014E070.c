struct Rec14 { int flags; int field_0x4; int field_0x8; int field_0xc; int field_0x10; };

extern struct Rec14 D_00205440[];
extern unsigned short D_001ECB08;

void func_0014E070(void) {
    unsigned int i;

    for (i = 0; i < D_001ECB08; i++) {
        D_00205440[i].flags &= 0xFD013FFF;
    }
}
