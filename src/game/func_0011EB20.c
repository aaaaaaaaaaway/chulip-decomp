struct Ent_001FA9E8 {
    int field_0x00;
    unsigned char field_0x04[0x10];
    short field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
    int field_0x1C;
    unsigned char field_0x20[0x4];
};

extern struct Ent_001FA9E8 D_001FA9E8[];
extern int D_001FA9D8[];

int func_0011EB20(int id, short *values, int field) {
    int i;
    int hit = 0;

    for (i = D_001FA9D8[0]; i != -1; i = D_001FA9E8[i].field_0x1C) {
        if (D_001FA9E8[i].field_0x00 != id) {
            continue;
        }
        switch (field) {
        case 4:
            if (D_001FA9E8[i].field_0x1A == values[3]) {
                hit = 1;
            }
            break;
        case 3:
            if (D_001FA9E8[i].field_0x18 == values[2]) {
                hit = 1;
            }
            break;
        case 2:
            if (D_001FA9E8[i].field_0x16 == values[1]) {
                hit = 1;
            }
            break;
        case 1:
            if (D_001FA9E8[i].field_0x14 == values[0]) {
                hit = 1;
            }
            break;
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
