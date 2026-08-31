struct Rec14 { int flags; int field_0x4; int field_0x8; int field_0xc; int field_0x10; };

extern struct Rec14 D_00205440[];
extern unsigned short D_001ECB08;

void func_0014E0B8(unsigned int index, int mask, unsigned char set) {
    if (index < D_001ECB08) {
        if (set != 0) {
            D_00205440[index].flags |= mask;
        } else {
            D_00205440[index].flags &= ~mask;
        }
    }
}
