typedef struct Prim { unsigned char b[0x10]; } Prim;

typedef struct Ctx {
    int pad0;
    Prim *cursor;
    unsigned char rest[0x8];
} Ctx;

typedef struct Obj {
    unsigned char pad[0x20];
    int field20;
} Obj;

extern Ctx D_002D81B0;

void func_00161570(Prim *prim, int arg, int flag);
void func_00161770(Prim *prim, int value, int a, int b, int c, int d);
void func_001615B0(Prim *prim, int a, int b);

Prim *func_001536A8(Obj *obj, int arg, int width, int value) {
    Prim *prim = D_002D81B0.cursor;
    Prim *base = prim;

    obj->field20 = value;
    func_00161570(prim, arg, 0);
    prim++;
    func_00161770(prim, value, 0x10, 0x34, 1, 1);
    prim++;
    func_001615B0(prim, 0x78, (0x388 - width) / 2);
    prim++;
    D_002D81B0.cursor = prim;
    return base;
}
