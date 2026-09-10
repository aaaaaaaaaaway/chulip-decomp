typedef struct {
    int sides;
    int x, y, z;
    int r, g, b, a;
    float radius, scale_x, scale_y;
} Primitive;
typedef struct {
    int r, g, b, a;
    int x, y, z, control;
} Vertex;
extern float func_0018B210(float);
extern float func_0018B2F8(float);
int func_00120118(unsigned char *packet, Primitive *primitive) {
    Vertex *vertex;
    int total = 3;
    int i;
    float angle, width, height;
    int x, y;
    unsigned long tag;
    tag = (unsigned long)((primitive->sides + 2) | 0x8000) | (0x9B00UL << 38);
    tag |= 0x8000UL << 46;
    *(unsigned long *)(packet + 8) = 0x41;
    *(unsigned long *)packet = tag;
    packet += 16;
    vertex = (Vertex *)packet;
    vertex->r = primitive->r;
    vertex->g = primitive->g;
    vertex->b = primitive->b;
    vertex->a = primitive->a;
    vertex->x = primitive->x;
    vertex->y = primitive->y;
    vertex->z = primitive->z;
    vertex->control = 0x8000;
    ++vertex;
    for (i = 0; i < primitive->sides + 1; ++i) {
        angle = (float)((i * 360) / primitive->sides) * 3.141592f;
        angle /= 180.0f;
        width = primitive->radius * primitive->scale_x;
        x = width * func_0018B210(angle);
        height = primitive->radius * primitive->scale_y;
        y = height * func_0018B2F8(angle);
        vertex->r = 0;
        vertex->g = 0;
        vertex->b = 0;
        vertex->a = 0;
        vertex->x = primitive->x + x;
        vertex->y = primitive->y + y;
        vertex->z = primitive->z;
        vertex->control = 0;
        ++vertex;
        total += 2;
    }
    return total;
}
