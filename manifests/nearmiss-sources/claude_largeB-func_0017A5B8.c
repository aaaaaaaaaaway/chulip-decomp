typedef struct Blk Blk;

struct Blk {
    int a;
    int b;
    int c;
    int n;
};

typedef struct {
    Blk *p0;
    Blk *p4;
    Blk *p8;
    Blk *pC;
    Blk *p10;
    Blk *p14;
    Blk *p18;
    Blk *p1C;
} Src;

typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    Blk *f10;
    Blk *f14;
    Blk *f18;
    Blk *f1C;
    Blk *f20;
    Blk *f24;
    int f28;
    int f2C;
    int f30;
    int f34;
    Blk *f38;
    Blk *f3C;
    Blk *f40;
    int f44;
    Blk *f48;
    int f4C;
} Dst;

void func_0017A6C8(void);

Dst *func_0017A5B8(Dst *dst, Src *src) {
    int n0;
    int n1;

    n0 = src->p4->n;
    dst->f00 = n0;
    dst->f04 = n0;
    n1 = src->p8->n;
    dst->f08 = n1;
    dst->f0C = n1;
    dst->f10 = src->p4 + 1;
    dst->f18 = dst->f10 + n0;
    dst->f14 = src->p8 + 1;
    dst->f1C = dst->f14 + n1;
    dst->f20 = src->pC + 1;
    dst->f24 = src->p10 + 1;
    dst->f28 = src->p14->c;
    dst->f30 = src->p14->n;
    dst->f38 = src->p14 + 1;
    dst->f2C = src->p18->c;
    dst->f34 = src->p18->n;
    dst->f3C = src->p18 + 1;
    dst->f44 = src->p0->n;
    dst->f40 = src->p0 + 1;
    dst->f4C = src->p1C->n;
    dst->f48 = src->p1C + 1;
    func_0017A6C8();
    return dst;
}
