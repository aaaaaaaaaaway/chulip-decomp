typedef struct { float x; float y; float z; } Vec3f;
typedef struct { int x; int y; int z; } Vec3i;
typedef struct { int a; int b; int c; int d; } Quad;
typedef struct { Vec3i a; int p0; Vec3i b; int p1; Vec3f c; int p2; Vec3f d; int p3; Quad e; } Src;
void func_00110810(int index, Vec3i *a, Vec3i *b, Vec3f *c, Vec3f *d, Quad *e);

void func_00110758(int index, Src *table) {
    Vec3f c;
    Vec3f d;
    Quad e;
    Vec3i a;
    Vec3i b;

    a.x = table[index].a.x;
    a.y = table[index].a.y;
    a.z = table[index].a.z;
    b.x = table[index].b.x;
    b.y = table[index].b.y;
    b.z = table[index].b.z;
    c.x = table[index].c.x;
    c.y = table[index].c.y;
    c.z = table[index].c.z;
    d.x = table[index].d.x;
    d.y = table[index].d.y;
    d.z = table[index].d.z;
    e.a = table[index].e.a;
    e.b = table[index].e.b;
    e.c = table[index].e.c;
    e.d = table[index].e.d;
    func_00110810(index, &a, &b, &c, &d, &e);
}
