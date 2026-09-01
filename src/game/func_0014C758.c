struct Rec {
    unsigned char pad_0x0[0x20];
    unsigned short field_0x20;
    unsigned char pad_0x22[0xA];
    unsigned short field_0x2C;
};

extern struct Rec *func_0017E7F8(int id);
extern unsigned long *D_001ECB00;

void func_0014C758(void) {
    struct Rec *tex;
    struct Rec *clut;
    int i;

    tex = func_0017E7F8(0x1000);
    clut = func_0017E7F8(0x1001);
    for (i = 1; i < tex->field_0x2C; i++) {
        int lo = (tex->field_0x20 + (i / 8) * 12) | 0x1D408000;
        unsigned long hi = ((unsigned long)(clut->field_0x20 + i) << 37) | ((unsigned long)4 << 30);
        D_001ECB00[i] = (lo | hi) | ((unsigned long)1 << 61);
    }
}
