typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    Vec4 position;
    int r, g, b, a;
    int radius;
} Point;
typedef struct {
    int active;
    int owner;
    Point start[5];
    Point end[5];
} Effect;
extern int D_001ED0E0;
extern void func_0018A490(float *, float *);
extern void func_0018A638(float *, float *, float);
void func_00109498(int index, int owner, float *position) {
    Vec4 direction;
    float x[5] = {0.0f, -100.0f, 100.0f, -100.0f, 100.0f};
    float y[5] = {0.0f, 0.0f, 0.0f, 100.0f, 100.0f};
    int start_radius[5] = {300, 350, 350, 200, 200};
    int end_radius[5] = {2000, 350, 350, 200, 200};
    int i;
    Point *start, *end;
    ((Effect *)D_001ED0E0)[index].owner = owner;
    func_0018A490(direction, position);
    func_0018A638(direction, direction, 600.0f);
    direction[1] = 150.0f;
    for (i = 0; i < 5; i++) {
        start = &((Effect *)D_001ED0E0)[index].start[i];
        end = &((Effect *)D_001ED0E0)[index].end[i];
        start->position[0] = position[0] + x[i];
        start->position[1] = position[1] + y[i];
        start->position[2] = position[2];
        start->position[3] = 1.0f;
        end->position[0] = direction[0];
        end->position[1] = direction[1];
        end->position[2] = direction[2];
        end->position[3] = 1.0f;
        if (i > 0) {
            end->position[0] = 0.0f;
            end->position[1] = 0.0f;
            end->position[2] = 0.0f;
        }
        start->radius = start_radius[i];
        end->radius = end_radius[i];
        switch (i) {
        case 0:
            start->r = 128;
            start->g = 128;
            start->b = 112;
            start->a = 16;
            end->r = 128;
            end->g = 128;
            end->b = 112;
            end->a = 0;
            break;
        case 1:
        case 2:
            start->r = 128;
            start->g = 128;
            start->b = 112;
            start->a = 80;
            end->r = 128;
            end->g = 128;
            end->b = 112;
            end->a = 80;
            break;
        case 3:
        case 4:
            start->r = 128;
            start->g = 0;
            start->b = 0;
            start->a = 64;
            end->r = 128;
            end->g = 0;
            end->b = 0;
            end->a = 64;
            break;
        }
    }
}

extern int D_001ED0E8;
extern int D_001ED0E4;
extern void func_00112F40(void (*)(void));
extern int func_00151CA8(int);
int func_001097F8(unsigned char *, int, int);
void func_00109748(int value) { D_001ED0E8 = value; }
void func_00109750(int index, int value) {
    int off;
    if (index == -1) {
        if (D_001ED0E4 > 0) {
            index = 0;
            off = 0;
            do {
                *(int *)(off + D_001ED0E0) = value;
                index++;
                off += 0x1F0;
            } while (index < D_001ED0E4);
        }
        return;
    }
    ((Effect *)D_001ED0E0)[index].active = value;
}
int func_001097C0(void) {
    D_001ED0E8 = 1;
    D_001ED0E4 = 0;
    func_00112F40((void (*)(void))func_001097F8);
    return func_00151CA8(D_001ED0E0);
}

extern void func_0011FA48(void *, int, void *);
extern int func_00158868(unsigned short, void *);
extern int func_001251E8(unsigned char *, int, int, Point *, Point *);
int func_001097F8(unsigned char *packet, int count, int unused) {
    int segments[5] = {30, 3, 3, 3, 3};
    Vec4 world;
    Point start, end;
    int i, j, total, written;
    unsigned char *head;
    Point *a, *b;
    if (D_001ED0E8 != 0)
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
        if (((Effect *)D_001ED0E0)[i].active == 1) {
            for (j = 0; j < 5; j++) {
                a = &((Effect *)D_001ED0E0)[i].start[j];
                b = &((Effect *)D_001ED0E0)[i].end[j];
                func_0011FA48(start.position, ((Effect *)D_001ED0E0)[i].owner, a);
                func_0011FA48(end.position, ((Effect *)D_001ED0E0)[i].owner, b);
                func_00158868(((Effect *)D_001ED0E0)[i].owner, world);
                start.position[0] += world[0];
                start.position[1] += world[1];
                start.position[2] += world[2];
                end.position[0] += start.position[0];
                end.position[1] += start.position[1];
                end.position[2] += start.position[2];
                start.radius = a->radius;
                start.r = a->r;
                start.g = a->g;
                start.b = a->b;
                start.a = a->a;
                end.radius = b->radius;
                end.r = b->r;
                end.g = b->g;
                end.b = b->b;
                end.a = b->a;
                written = func_001251E8(packet, 10, segments[j], &start, &end);
                total += written;
                packet += written * 16;
            }
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
