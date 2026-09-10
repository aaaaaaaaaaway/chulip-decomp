typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[16] __attribute__((aligned(16)));
typedef struct {
    int unknown00, age, unknown08, unknown0C;
    Vec4 position, unknown20, unknown30;
} Particle;
typedef struct {
    int active, owner, bone, step, fade, duration, alpha;
    float scale;
    Vec4 unknown20;
    int color[4];
    Particle particle;
} Emitter;
extern Emitter *D_001ED09C[1];
typedef struct {
    int flags, x, y, z, u, v, w, h, unused20;
    float sx, sy;
    unsigned char r, g, b, a;
} Sprite;
extern int D_001ED0A4;
extern float D_001EDCC0[];
extern int func_00192568(void);
extern int func_00113228(void *, int);
extern int func_00120BE0(int *, float *, float *);
extern int func_00117E58(unsigned char *, Sprite *);
extern void func_00158A00(unsigned short, unsigned char, void *);
extern void func_0018A3D0(void *, void *, void *);
int func_001065B0(unsigned char *packet, int count, int unused) {
    Matrix matrix;
    Vec4 position;
    int screen[4];
    Sprite sprite;
    unsigned char *head;
    int i, total, written;
    Particle *p;
    if (D_001ED0A4 != 0)
        return 0;
    head = packet;
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
    sprite.flags = 0;
    sprite.u = 0;
    sprite.v = 0;
    sprite.w = 0x200;
    sprite.h = 0x200;
    sprite.r = 255;
    sprite.g = 220;
    sprite.b = 160;
    for (i = 0; i < count; i++) {
        if (D_001ED09C[0][i].active == 1) {
            p = &D_001ED09C[0][i].particle;
            func_00158A00(D_001ED09C[0][i].owner, D_001ED09C[0][i].bone, matrix);
            position[0] = p->position[0];
            position[1] = p->position[1];
            position[2] = p->position[2];
            position[3] = 1.0f;
            func_0018A3D0(position, matrix, position);
            if (func_00120BE0(screen, D_001EDCC0, position) != 0)
                continue;
            sprite.x = screen[0];
            sprite.y = screen[1];
            sprite.z = screen[2];
            sprite.r = D_001ED09C[0][i].color[0];
            sprite.g = D_001ED09C[0][i].color[1];
            sprite.b = D_001ED09C[0][i].color[2];
            sprite.a = D_001ED09C[0][i].alpha + (func_00192568() - func_00192568()) % 4;
            sprite.sx =
                D_001ED09C[0][i].scale + (float)((func_00192568() - func_00192568()) % 50) / 100.0f;
            sprite.sy = D_001ED09C[0][i].scale * 0.5f +
                        (float)((func_00192568() - func_00192568()) % 25) / 100.0f;
            sprite.r = sprite.r * D_001ED09C[0][i].fade / D_001ED09C[0][i].duration;
            sprite.g = sprite.g * D_001ED09C[0][i].fade / D_001ED09C[0][i].duration;
            sprite.b = sprite.b * D_001ED09C[0][i].fade / D_001ED09C[0][i].duration;
            sprite.a = sprite.a * D_001ED09C[0][i].fade / D_001ED09C[0][i].duration;
            written = func_00117E58(packet, &sprite);
            total += written;
            packet += written * 16;
            p->age++;
            D_001ED09C[0][i].fade += D_001ED09C[0][i].step;
            if (D_001ED09C[0][i].fade < 0)
                D_001ED09C[0][i].fade = 0;
            else if (D_001ED09C[0][i].fade > D_001ED09C[0][i].duration)
                D_001ED09C[0][i].fade = D_001ED09C[0][i].duration;
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
