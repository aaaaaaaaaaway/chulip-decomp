typedef float Vec4[4] __attribute__((aligned(16)));
typedef int IVec4[4] __attribute__((aligned(16)));
typedef struct {
    Vec4 position;
    int r, g, b, a;
    int radius;
} Point;
typedef struct {
    int sides;
    int x, y, z;
    int r, g, b, a;
    float radius, scale, edge;
} __attribute__((aligned(16))) Primitive;
extern float D_001EDCC0[];
extern int func_00120BE0(IVec4, float *, Vec4);
extern int func_00120118(unsigned char *, Primitive *);

int func_001251E8(unsigned char *packet, int sides, int segments, Point *start, Point *end) {
    IVec4 first, last, delta;
    Primitive primitive;
    int dr, dg, db, da, radius_delta;
    int i, written, total;
    int divisor = segments;
    primitive.sides = sides;
    if (func_00120BE0(first, D_001EDCC0, start->position))
        return 0;
    if (func_00120BE0(last, D_001EDCC0, end->position))
        return 0;
    delta[0] = last[0] - first[0];
    delta[1] = last[1] - first[1];
    delta[2] = last[2] - first[2];
    radius_delta = end->radius - start->radius;
    dr = end->r - start->r;
    dg = end->g - start->g;
    db = end->b - start->b;
    da = end->a - start->a;
    *(unsigned long *)packet = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 0x42;
    *(unsigned long *)(packet + 16) = 0x8000000048UL;
    packet += 32;
    total = 2;
    primitive.z = first[2];
    primitive.scale = 1.0f;
    primitive.edge = 0.5f;
    for (i = 0; i < segments; ++i) {
        primitive.radius = start->radius + (radius_delta * i) / divisor;
        primitive.x = first[0] + (delta[0] * i) / divisor;
        primitive.y = first[1] + (delta[1] * i) / divisor;
        primitive.r = start->r + (dr * i) / divisor;
        primitive.g = start->g + (dg * i) / divisor;
        primitive.b = start->b + (db * i) / divisor;
        primitive.a = start->a + (da * i) / divisor;
        written = func_00120118(packet, &primitive);
        total += written;
        packet += written * 16;
    }
    return total;
}
