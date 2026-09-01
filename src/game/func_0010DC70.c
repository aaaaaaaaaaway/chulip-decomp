typedef struct { float x; float y; float z; float w; } Vec4f;
typedef struct { int a; int b; int c; int d; } Quad;

void func_0010DD30(int a, int b, int n, Vec4f *p, Vec4f *q, Quad *r, Quad *s);

void func_0010DC70(int *src) {
    Vec4f p;
    Vec4f q;
    Quad r;
    Quad s;

    p.x = *(float *)((char *)src + 0x08);
    p.y = *(float *)((char *)src + 0x0C);
    p.z = *(float *)((char *)src + 0x10);
    p.w = 1.0f;
    q.x = *(float *)((char *)src + 0x18);
    q.y = *(float *)((char *)src + 0x1C);
    q.z = *(float *)((char *)src + 0x20);
    q.w = 1.0f;
    r.a = src[10];
    r.b = src[11];
    r.c = src[12];
    r.d = src[13];
    s.a = src[14];
    s.b = src[15];
    s.c = src[16];
    s.d = src[17];
    func_0010DD30(src[0], src[1], 0x3C, &p, &q, &r, &s);
}
