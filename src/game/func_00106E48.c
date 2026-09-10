typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[16] __attribute__((aligned(16)));
typedef struct {
    int state;
    int age;
    int unknown08;
    int unknown0C;
    Vec4 position;
    Vec4 unknown20;
    Vec4 unknown30;
} Particle;
typedef struct {
    int owner;
    int bone;
    int active;
    int angle;
    int step;
    int age;
    int duration;
    int unknown1C;
    Vec4 unknown20;
    int color[4];
    Particle particles[100];
} Emitter;
extern Emitter *D_001ED0A8[1];
extern void func_00158A00(unsigned short, unsigned char, void *);
extern void func_0018A3D0(void *, void *, void *);
extern int func_00192568(void);
typedef struct {
    int flags, x, y, z, u, v, w, h;
    int unused20;
    float sx, sy;
    unsigned char r, g, b, a;
} Sprite;
extern int D_001ED0B0;
extern float D_001EDCC0[];
extern int func_00113228(void *, int);
extern int func_00120BE0(int *, float *, float *);
extern float func_0018B2F8(float);
extern int func_00117E58(void *, Sprite *);
int func_00106E48(unsigned char *packet, int count, int unused) {
    int screen[4];
    Sprite item;
    Vec4 position;
    Matrix matrix;
    unsigned char *head;
    int i, j, total, written, frame;
    float scale, screen_y, angle;
    Particle *p;
    if (D_001ED0B0 != 0)
        return 0;
    head = packet;
    position[0] = 0.0f;
    position[1] = 0.0f;
    packet += 16;
    head[3] = 0x10;
    total = func_00113228(packet, 0x1018);
    packet += total * 16;
    *(unsigned long *)(packet + 0) = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 8;
    *(unsigned long *)(packet + 16) = 5;
    packet += 32;
    *(unsigned long *)(packet + 0) = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 0x42;
    *(unsigned long *)(packet + 16) = 0x8000000048UL;
    packet += 32;
    total += 4;
    item.flags = 0;
    item.u = 0;
    item.v = 0x200;
    item.w = 0x100;
    item.h = 0x100;
    for (i = 0; i < count; i++) {
        if (D_001ED0A8[0][i].active == 1) {
            item.r = D_001ED0A8[0][i].color[0];
            item.g = D_001ED0A8[0][i].color[1];
            item.b = D_001ED0A8[0][i].color[2];
            item.a = D_001ED0A8[0][i].color[3];
            D_001ED0A8[0][i].angle = (D_001ED0A8[0][i].angle + 2) % 360;
            for (j = 0; j < 100; j++) {
                p = &D_001ED0A8[0][i].particles[j];
                p->age++;
                if (p->age > 20) {
                    p->age = -(func_00192568() % 20);
                    position[0] = (float)((func_00192568() - func_00192568()) % 20);
                    position[1] = (float)((func_00192568() - func_00192568()) % 50);
                    position[2] = (float)((func_00192568() - func_00192568()) % 20);
                    position[3] = 1.0f;
                    func_00158A00(D_001ED0A8[0][i].owner, D_001ED0A8[0][i].bone, matrix);
                    func_0018A3D0(position, matrix, position);
                    p->position[0] = position[0];
                    p->position[1] = position[1];
                    p->position[2] = position[2];
                }
                if (p->age < 0)
                    continue;
                p->position[1] -= (float)(func_00192568() % 10 + 5);
                if (func_00120BE0(screen, D_001EDCC0, p->position) != 0)
                    continue;
                if (screen[0] < 0x6000 || screen[0] > 0xA000 || screen[1] < 0x7200 ||
                    screen[1] > 0x8E00)
                    continue;
                frame = p->age % 4;
                item.v = 0x200 + frame * item.h;
                item.x = screen[0];
                item.y = screen[1];
                item.z = screen[2];
                item.a = (unsigned char)D_001ED0A8[0][i].color[3] -
                         D_001ED0A8[0][i].color[3] * p->age / 20;
                screen_y = (float)item.y;
                angle = (float)D_001ED0A8[0][i].angle * 3.1415927f;
                angle /= 180.0f;
                item.y = screen_y + func_0018B2F8(angle) * 64.0f;
                scale = ((float)D_001ED0A8[0][i].age / (float)D_001ED0A8[0][i].duration);
                item.sx = ((float)(p->age / 5) + 2.0f) * scale;
                item.sy = ((float)(p->age / 5) + 1.0f) * scale;
                written = func_00117E58(packet, &item);
                total += written;
                packet += written * 16;
            }
            D_001ED0A8[0][i].age += D_001ED0A8[0][i].step;
            if (D_001ED0A8[0][i].age < 0)
                D_001ED0A8[0][i].age = 0;
            else if (D_001ED0A8[0][i].age > D_001ED0A8[0][i].duration)
                D_001ED0A8[0][i].age = D_001ED0A8[0][i].duration;
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
