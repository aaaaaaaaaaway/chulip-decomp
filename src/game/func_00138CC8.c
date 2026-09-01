struct Ent_00203C20 {
    int field_0x00;
    unsigned char field_0x04[0xC];
    unsigned int field_0x10;
    short field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
    unsigned char field_0x1C[0x8];
};

extern struct Ent_00203C20 D_00203C20[];

int func_00138CC8(int id, short *values, int field) {
    int i;
    int hit = 0;

    for (i = 0; i < 0x90; i++) {
        if ((D_00203C20 + i)->field_0x00 != id) {
            continue;
        }
        if (((D_00203C20 + i)->field_0x10 >> 1) & 1) {
            continue;
        }
        switch (field) {
        case 4:
            if (D_00203C20[i].field_0x1A == values[3]) {
                hit = 1;
            }
            break;
        case 3:
            if (D_00203C20[i].field_0x18 == values[2]) {
                hit = 1;
            }
            break;
        case 2:
            if (D_00203C20[i].field_0x16 == values[1]) {
                hit = 1;
            }
            break;
        case 1:
            if (D_00203C20[i].field_0x14 == values[0]) {
                hit = 1;
            }
            break;
        case -1:
        case 0:
            hit = 1;
            break;
        }
        if (hit) {
            return i;
        }
    }
    return -1;
}
