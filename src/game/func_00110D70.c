typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int active, age, unknown08, unknown0C;
    Vec4 position, velocity;
} Particle;
typedef struct {
    int active, repeat, duration, unknown0C;
    int spread[4], spread2[4];
    Vec4 origin, velocity;
    int color[4];
    Particle particles[100];
} Emitter;
typedef struct {
    int flags, x, y, z, u, v, w, h, unused20;
    float sx, sy;
    unsigned char r, g, b, a;
} Sprite;
extern Emitter *D_001ED17C[1];
extern int D_001ED184;
extern float D_001EDCC0[];
extern int func_00192568(void);
extern int func_00113228(void *, int);
extern int func_00120BE0(int *, float *, float *);
extern int func_00117E58(unsigned char *, Sprite *);
int func_00110D70(unsigned char *packet, int count, int unused) {
    Sprite sprite;
    Vec4 position;
    int screen[4];
    unsigned char *head;
    int i, j, total, written;
    Emitter *emitter;
    Particle *p;
    if (D_001ED184 != 0)
        return 0;
    head = packet;
    packet += 16;
    head[3] = 0x10;
    total = func_00113228(packet, 9);
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
    sprite.flags = 0;
    sprite.u = 0x300;
    sprite.v = 0x300;
    sprite.w = 0x100;
    sprite.h = 0x100;
    sprite.r = 128;
    sprite.g = 140;
    sprite.b = 180;
    sprite.a = 10;
    sprite.sx = 1.0f;
    sprite.sy = 1.0f;
    for (i = 0; i < count; i++) {
        emitter = &D_001ED17C[0][i];
        if (emitter->active == 1) {
            sprite.r = emitter->color[0];
            sprite.g = emitter->color[1];
            sprite.b = emitter->color[2];
            sprite.a = emitter->color[3];
            for (j = 0; j < 100; j++) {
                p = &emitter->particles[j];
                p->age++;
                if (p->age < 0)
                    continue;
                if (p->age > emitter->duration) {
                    if (emitter->repeat != 1) {
                        p->age = emitter->duration;
                        p->active = 0;
                        continue;
                    }
                    p->active = 1;
                    p->age = -(func_00192568() % 100);
                    p->position[0] =
                        emitter->origin[0] +
                        (float)((func_00192568() - func_00192568()) % emitter->spread[0]);
                    p->position[1] =
                        emitter->origin[1] +
                        (float)((func_00192568() - func_00192568()) % emitter->spread[1]);
                    p->position[2] =
                        emitter->origin[2] +
                        (float)((func_00192568() - func_00192568()) % emitter->spread[2]);
                    p->velocity[0] =
                        emitter->velocity[0] +
                        (float)((func_00192568() - func_00192568()) % emitter->spread2[0]);
                    p->velocity[1] =
                        emitter->velocity[1] +
                        (float)((func_00192568() - func_00192568()) % emitter->spread2[1]);
                    p->velocity[2] =
                        emitter->velocity[2] +
                        (float)((func_00192568() - func_00192568()) % emitter->spread2[2]);
                }
                if (p->active != 1)
                    continue;
                position[0] = p->position[0];
                position[1] = p->position[1];
                position[2] = p->position[2];
                position[3] = 1.0f;
                if (func_00120BE0(screen, D_001EDCC0, position) != 0)
                    continue;
                /* Retail fills x/y here but leaves the Sprite z field uninitialized. */
                sprite.x = screen[0];
                sprite.y = screen[1];
                sprite.v = 0x300 - p->age / (emitter->duration / 3) * sprite.h;
                written = func_00117E58(packet, &sprite);
                total += written;
                packet += written * 16;
                p->position[0] += p->velocity[0];
                p->position[1] += p->velocity[1];
                p->position[2] += p->velocity[2];
                p->velocity[0] *= 0.985f;
                p->velocity[1] += 0.25f;
                p->velocity[2] *= 0.985f;
            }
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
