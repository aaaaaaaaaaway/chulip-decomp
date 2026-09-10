typedef struct Rec {
    unsigned char b00;
    unsigned char pad_01[0x2BF];
    int f2C0;
    unsigned char pad_2C4[0x18];
    int f2DC;
    int f2E0;
    int f2E4;
    float f2E8;
    float f2EC;
    int f2F0;
    int f2F4;
    int f2F8;
    int f2FC;
    int f300;
    int f304;
    int f308;
    int f30C;
    int f310;
    int f314;
    int f318;
    int f31C;
    int f320;
    int f324;
    int f328;
    int f32C;
    int f330;
    int f334;
    int f338;
    int f33C;
    int f340;
    int f344;
} Rec;

extern Rec D_002D78C0[];

void func_0015E418(int index) {
    Rec *r = D_002D78C0 + index;

    r->b00 = 0;
    r->f2DC = 0x800;
    r->f2E0 = 0x800;
    r->f2E4 = 0;
    r->f2E8 = 1.0f;
    r->f2EC = 0.5f;
    r->f2F0 = 1;
    r->f2F4 = 0;
    r->f2F8 = 0;
    r->f2FC = 1;
    r->f300 = 0;
    r->f304 = 0;
    r->f308 = 0;
    r->f30C = 0;
    r->f310 = 0;
    r->f2C0 = 0;
    r->f314 = 0;
    r->f318 = 0;
    r->f31C = -1;
    r->f324 = 0;
    r->f328 = 0;
    r->f32C = 0;
    r->f330 = index + 0x20000010;
    r->f334 = 0;
    r->f338 = 0;
    r->f340 = 12;
    r->f33C = 5;
    r->f344 = 0;
}
