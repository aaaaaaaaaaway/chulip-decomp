struct Desc {
    char pad00[0xC];
    int f0C;
    char pad10[4];
    int f14;
    int f18;
    int f1C;
};

struct Obj {
    char pad00[0x18];
    int f18;
    int f1C;
    char pad20[8];
    float f28;
};

extern struct Obj *func_00151A00(int size);
extern struct Obj *func_00151A20(int size);
extern struct Obj *func_00100490(struct Obj *mem, int a, int b, int c, int d, int id);

struct Obj *func_00100290(struct Desc *s, int id) {
    int flag;
    struct Obj *obj;

    flag = 0;
    if ((unsigned int)(id - 0x11C) < 0x40 || (unsigned int)(id - 1) < 0xFB ||
        (unsigned int)(id - 0x3A0) < 0xB8 || id == 0) {
        flag = 1;
    }
    if (flag != 0) {
        obj = func_00151A20(0x30);
    } else {
        obj = func_00151A00(0x30);
    }
    if (obj == 0) {
        return 0;
    }
    obj = func_00100490(obj, s->f14, s->f18, s->f1C, s->f0C, id);
    if (obj == 0) {
        return 0;
    }
    obj->f18 = 0;
    obj->f28 = 1.0f;
    obj->f1C = 0;
    return obj;
}
