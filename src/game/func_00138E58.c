struct Ent_00203C20 {
    int field_0x00;
    unsigned char field_0x04[0xC];
    int field_0x10;
    short field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
    unsigned char field_0x1C[0x8];
};

extern void func_00139EB8(int index);
extern struct Ent_00203C20 D_00203C20[];

void func_00138E58(int id, short *values, unsigned int field) {
    int i;
    int hit;

    for (i = 0; i < 0x90; i++) {
        hit = 0;
        if (D_00203C20[i].field_0x00 == id) {
            switch (field) {
            case 4:
                hit = D_00203C20[i].field_0x1A == values[3];
                break;
            case 3:
                hit = D_00203C20[i].field_0x18 == values[2];
                break;
            case 2:
                hit = D_00203C20[i].field_0x16 == values[1];
                break;
            case 1:
                hit = D_00203C20[i].field_0x14 == values[0];
                break;
            case 0:
                hit = 1;
                break;
            }
            if (hit) {
                func_00139EB8(i);
            }
        }
    }
}
