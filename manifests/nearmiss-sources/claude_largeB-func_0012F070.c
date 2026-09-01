typedef struct {
    char b[0x20];
} Rec;

typedef struct {
    Rec a;
    Rec b;
} Pair;

typedef struct {
    Rec rec;
    char pad0[0xE0];
    void *f100;
    void *f104;
    char pad1[0x20];
    unsigned char f128;
    unsigned char f129;
    char pad2[2];
    short f12C;
    short f12E;
} Ctx;

extern Pair D_001E7910;
extern Ctx D_001FD9C0;

void func_0012E738(int a);
void func_0015EDC0(Ctx *p);

void func_0012F070(unsigned short mode, short b, short c) {
    Pair tmp;

    D_001FD9C0.f12C = b;
    D_001FD9C0.f12E = c;
    D_001FD9C0.f128 = mode;
    tmp = D_001E7910;
    switch (mode) {
    case 0:
        D_001FD9C0.f104 = (char *)&D_001FD9C0 + 6;
        D_001FD9C0.f129 = 2;
        D_001FD9C0.f100 = &D_001FD9C0;
        D_001FD9C0.rec = tmp.a;
        break;
    case 1:
        D_001FD9C0.f104 = (char *)&D_001FD9C0 + 0xA;
        D_001FD9C0.f129 = 2;
        D_001FD9C0.f100 = &D_001FD9C0;
        D_001FD9C0.rec = tmp.b;
        break;
    }
    func_0012E738(3);
    func_0015EDC0(&D_001FD9C0);
}
