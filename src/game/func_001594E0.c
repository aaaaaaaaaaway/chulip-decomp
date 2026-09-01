typedef struct {
    void *f00;
    int f04;
    int f08;
    int f0C;
} Item;

typedef union {
    long bits;
    struct {
        int lo;
        Item *item;
    } ref;
} SlotHead;

typedef struct {
    char pad0[0x20];
    SlotHead head;
    char pad1[0x18];
} Slot;

typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
} Src;

extern Slot D_002ABA40[];

int func_001533D8(Src *s, int idx, int cur);
int func_0017D088(Src *s, int idx, int cur);
int func_00179818(Src *s, int idx, int cur, int b);
void func_0015BE88(int idx, int a, int b);

Item *func_001594E0(Src *s, unsigned short idx) {
    Item *it;
    Slot *sl;

    it = D_002ABA40[idx].head.ref.item;
    it->f00 = s;
    if (s->f10 != 0) {
        it->f04 = func_001533D8(s, idx, it->f04);
    } else {
        it->f04 = 0;
    }
    if (s->f08 != 0) {
        it->f0C = func_0017D088(s, idx, it->f0C);
    } else {
        it->f0C = 0;
    }
    if (s->f00 != 0) {
        it->f08 = func_00179818(s, idx, it->f08, it->f04);
    } else {
        it->f08 = 0;
    }
    sl = &D_002ABA40[idx];
    if (((int)(sl->head.bits >> 8) & 1) != 0) {
        func_0015BE88(idx, 2, 1);
    }
    if (((int)(sl->head.bits >> 12) & 1) != 0) {
        func_0015BE88(idx, 1, 1);
    }
    return it;
}
