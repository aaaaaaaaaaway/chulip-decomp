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
extern void func_0011E988(unsigned short index);

void func_0011E858(int id, short *values, unsigned int field) {
    int i;
    int hit;

    for (i = 0; i < 0x90; i++) {
        hit = 0;
        if (D_001FA9E8[i].field_0x00 == id) {
            switch (field) {
            case 4:
                hit = D_001FA9E8[i].field_0x1A == values[3];
                break;
            case 3:
                hit = D_001FA9E8[i].field_0x18 == values[2];
                break;
            case 2:
                hit = D_001FA9E8[i].field_0x16 == values[1];
                break;
            case 1:
                hit = D_001FA9E8[i].field_0x14 == values[0];
                break;
            case 0:
                hit = 1;
                break;
            }
            if (hit) {
                func_0011E988(i);
            }
        }
    }
}
