struct Fader {
    unsigned short field_0x0;
    unsigned short field_0x2;
    unsigned short field_0x4;
    unsigned short field_0x6;
    unsigned short field_0x8;
    unsigned char field_0xA;
    unsigned char field_0xB;
    unsigned char field_0xC;
};

extern void func_00163370(void);
extern void func_00163378(int a, int b);
extern void func_00112F40(void (*task)(void));
extern void func_00112EB0(void (*task)(void), int arg1, struct Fader *arg2);

void func_001632E8(struct Fader *f) {
    func_00163378(2, 0x14);
    f->field_0x0 = 0;
    f->field_0x2 = 0x7600;
    f->field_0x4 = 0x7A00;
    f->field_0x6 = 0x8A00;
    f->field_0x8 = 0x8600;
    f->field_0xA = 0;
    f->field_0xB = 0;
    f->field_0xC = 0x3C;
    func_00112F40(func_00163370);
    func_00112EB0(func_00163370, 1, f);
}
