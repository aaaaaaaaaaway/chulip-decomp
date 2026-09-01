struct Obj {
    int f00;
    int f04;
    int *f08;
    int *f0C;
    int f10;
    int f14;
    char pad18[0xC];
    int f24;
};

struct Chunk {
    int f00;
    int f04;
    int count;
    int f0C;
};

extern int *func_001513E0(int kind, int id, int size);

struct Obj *func_00100490(struct Obj *obj, struct Chunk *p1, struct Chunk *p2, struct Chunk *p3, struct Chunk *p4, int id) {
    int i;
    int n;
    struct Chunk *cur;
    struct Chunk *cur2 = p3 + 1;
    int q;

    obj->f24 = 0;
    obj->f00 = (int)(p1 + 1);
    obj->f10 = p1->f0C;
    obj->f04 = (int)(p4 + 1);
    n = p2->f0C;
    obj->f08 = func_001513E0(0xB, id, n * 4);
    if (obj->f08 == 0) {
        return 0;
    }
    cur = p2 + 1;
    for (i = 0; i < n; i++) {
        obj->f08[i] = (int)(cur + 1);
        cur = (struct Chunk *)((char *)cur + cur->count * 4 + 0x10);
    }
    n = p3->f0C;
    obj->f0C = func_001513E0(0xC, id, n * 4);
    for (i = 0; i < n; i++) {
        obj->f0C[i] = (int)(cur2 + 1);
        cur2 = (struct Chunk *)((char *)cur2 + cur2->count * 4 + 0x10);
    }
    q = obj->f00;
    obj->f14 = *(int *)(obj->f08[*(int *)(q + 8)] + *(int *)(q + 4) * 4 - 4);
    return obj;
}
