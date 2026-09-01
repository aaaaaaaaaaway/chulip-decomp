typedef struct { float x; float y; float z; float w; } Vec4f;
typedef struct { float a; float p1; float p2; float p3; Vec4f b; int c[4]; } Item;

void func_0010D040(int index, int n, Item *p, Item *q);

void func_0010CF80(int index, char *table) {
    Item p;
    Item q;
    char *s;

    s = (char *)(index * 0x48 + (int)table);
    p.a = *(float *)(s + 0x00);
    p.b.x = *(float *)(s + 0x04);
    p.b.y = *(float *)(s + 0x08);
    p.b.z = *(float *)(s + 0x0C);
    p.b.w = 1.0f;
    p.c[0] = *(int *)(s + 0x14);
    p.c[1] = *(int *)(s + 0x18);
    p.c[2] = *(int *)(s + 0x1C);
    p.c[3] = *(int *)(s + 0x20);
    q.a = *(float *)(s + 0x24);
    q.b.x = *(float *)(s + 0x28);
    q.b.y = *(float *)(s + 0x2C);
    q.b.z = *(float *)(s + 0x30);
    q.b.w = 1.0f;
    q.c[0] = *(int *)(s + 0x38);
    q.c[1] = *(int *)(s + 0x3C);
    q.c[2] = *(int *)(s + 0x40);
    q.c[3] = *(int *)(s + 0x44);
    func_0010D040(index, 0xFA, &p, &q);
}
