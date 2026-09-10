typedef struct Rec {
    unsigned char pad[0x324];
    int f324;
    int f328;
    int f32C;
    unsigned char pad330[4];
    int f334;
    int f338;
    int f33C;
    int f340;
    int f344;
} Rec;

extern Rec D_002D78C0[];

void func_0015E4D0(int index);

void func_0015E518(int index, int a, int b, int c, int d, int e) {
    Rec *r;

    func_0015E4D0(index);
    r = D_002D78C0 + index;
    r->f324 = a;
    r->f334 = b;
    r->f340 = d;
    r->f338 = -1;
    r->f32C = r->f328;
    r->f33C = c;
    r->f344 = e;
}
