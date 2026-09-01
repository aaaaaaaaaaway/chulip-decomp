typedef struct { float x; float y; float z; } Vec3f;
typedef struct { int a; int b; int c; int d; } Quad;
void func_00111300(int index, Vec3f *v, Quad *q, float a, float b);

void func_00111288(int index, char *base) {
    Vec3f v;
    Quad q;
    char *p;

    p = (char *)(index * 0x28 + (int)base);
    v.x = *(float *)(p + 8);
    v.y = *(float *)(p + 0xC);
    v.z = *(float *)(p + 0x10);
    q.a = *(int *)(p + 0x18);
    q.b = *(int *)(p + 0x1C);
    q.c = *(int *)(p + 0x20);
    q.d = *(int *)(p + 0x24);
    func_00111300(index, &v, &q, (float)*(int *)(p + 0), (float)*(int *)(p + 4));
}
