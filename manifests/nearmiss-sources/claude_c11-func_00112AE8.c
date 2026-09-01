typedef struct {
    int flags;
    int x;
    int y;
    int z;
    int u;
    int v;
    int w;
    int h;
    float angle;
    float sx;
    float sy;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Sprite;

typedef struct {
    int age;
    int life;
    float ceiling;
    int pad0C;
    float x;
    float y;
    float z;
    int pad1C;
    float vx;
    float vy;
    float vz;
    int pad2C;
    int pad30[8];
    float dx;
    float dy;
    float dz;
} Particle;

extern int D_001ED1A0;
extern int D_001ED1A4;
extern int D_001ED1A8;
extern float D_001EDCC0[];

int func_00113228(unsigned char *packet, int size);
int func_00192568(void);
void func_00112860(int index, int life);
int func_00120BE0(int *out, float *matrix, float *in);
int func_00117E58(unsigned char *packet, Sprite *sprite);

int func_00112AE8(unsigned char *packet) {
    Sprite item;
    float world[4];
    int screen[4];
    unsigned char *out;
    Particle *e;
    int i;
    int used;
    float fade;
    int n;

    if (D_001ED1A4 != 1) {
        return 0;
    }
    packet[3] = 0x10;
    out = packet + 0x10;
    used = func_00113228(out, 0x1018);
    out += used * 16;

    *(long *)(out + 0x00) = 0x1000000000008001L;
    *(long *)(out + 0x08) = 0xEL;
    *(long *)(out + 0x10) = 0x8000000044L;
    *(long *)(out + 0x18) = 0x42L;
    out += 0x20;
    *(long *)(out + 0x00) = 0x1000000000008001L;
    *(long *)(out + 0x08) = 0xEL;
    *(long *)(out + 0x10) = 0x51001L;
    *(long *)(out + 0x18) = 0x47L;
    out += 0x20;
    used += 4;

    item.u = 0x600;
    item.v = 0x600;
    item.w = 0x200;
    item.h = 0x200;
    item.r = 0x80;
    item.g = 0x80;
    item.b = 0x80;
    item.a = 0x80;

    for (i = 0; i < D_001ED1A0; i++) {
        e = (Particle *)(D_001ED1A8 + i * 0x60);
        e->age = e->age + 1;
        if (e->age >= 0) {
            if (e->life < e->age) {
                func_00112860(i, func_00192568() % 0x78 + 0x78);
            } else {
                world[0] = e->x;
                world[1] = e->y;
                world[2] = e->z;
                world[3] = 1.0f;
                if (func_00120BE0(screen, D_001EDCC0, world) == 0) {
                    item.flags = func_00192568() % 3;
                    item.r = -0x80 - e->age * 128 / e->life;
                    item.g = -0x80 - e->age * 128 / e->life;
                    item.b = -0x80 - e->age * 128 / e->life;
                    item.a = 0x50 - e->age * 0x50 / e->life;
                    item.sx = 1.0f - (float)e->age / (float)e->life;
                    item.x = screen[0];
                    item.y = screen[1];
                    item.z = screen[2];
                    item.sy = 0.5f - (float)e->age * 0.0f / (float)e->life;
                    n = func_00117E58(out, &item);
                    out += n * 16;
                    used += n;

                    fade = e->vy * 0.9f;
                    e->x = e->x + e->vx + e->dx;
                    e->y = e->y + e->vy + e->dy;
                    e->z = e->z + e->vz + e->dz;
                    e->vx = e->vx * 0.9f;
                    e->vz = e->vz * 0.9f;
                    e->vy = fade;
                    if (e->y < e->ceiling) {
                        e->vy = fade + 1.0f;
                    } else {
                        fade = fade - 1.0f;
                        if (fade < -1.0f) {
                            fade = -1.0f;
                        }
                        e->vy = fade;
                    }
                }
            }
        }
    }
    *(short *)packet = used;
    return used + 1;
}
