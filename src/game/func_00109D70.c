typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    Vec4 position;
    int r, g, b, a;
    int radius;
} Point;
typedef struct {
    int active;
    int owner;
    Point start;
    Point end;
} Effect;
extern Effect *D_001ED0EC;
extern int D_001ED0F4;
extern void func_0011FA48(void *, int, void *);
extern int func_00158868(unsigned short, void *);
extern int func_001251E8(unsigned char *, int, int, Point *, Point *);
int func_00109D70(unsigned char *packet, int count, int unused) {
    Vec4 world;
    Point start, end;
    int i, total, written, owner;
    unsigned char *head;
    Point *a, *b;
    if (D_001ED0F4 != 0)
        return 0;
    head = packet;
    head[3] = 0x10;
    *(unsigned long *)(packet + 16) = 0x1000000000008001UL;
    packet += 16;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 0x42;
    *(unsigned long *)(packet + 16) = 0x8000000048UL;
    packet += 32;
    total = 2;
    for (i = 0; i < count; i++) {
        if (D_001ED0EC[i].active == 1) {
            a = &D_001ED0EC[i].start;
            b = &D_001ED0EC[i].end;
            owner = D_001ED0EC[i].owner;
            func_00158868(owner, world);
            func_0011FA48(start.position, owner, a);
            start.position[0] += world[0];
            start.position[1] += world[1];
            start.position[2] += world[2];
            start.radius = a->radius;
            start.r = a->r;
            start.g = a->g;
            start.b = a->b;
            start.a = a->a;
            func_0011FA48(end.position, owner, b);
            end.position[0] += start.position[0];
            end.position[1] += start.position[1];
            end.position[2] += start.position[2];
            end.radius = b->radius;
            end.r = b->r;
            end.g = b->g;
            end.b = b->b;
            end.a = b->a;
            written = func_001251E8(packet, 16, 24, &start, &end);
            total += written;
            packet += written * 16;
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
