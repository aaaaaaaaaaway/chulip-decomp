struct Rec14 { int flags; int field_0x4; int field_0x8; int field_0xc; int field_0x10; };

extern struct Rec14 D_00205440[];

int func_0014D380(int index) {
    int flags = D_00205440[index].flags & 2;

    return flags == 0;
}
