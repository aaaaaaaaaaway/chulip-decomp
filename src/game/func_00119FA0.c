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
    int state;
    int id;
    int pad8;
    int timer;
} Slot;

extern Slot D_001FA200[];
extern float D_001EDCC0[];

int func_00158908(unsigned short id, float *out);
void func_0018AED0(int *out, float *matrix, float *in, int mode);
int func_00117E58(unsigned char *packet, Sprite *sprite);

int func_00119FA0(unsigned char *packet, int index, int unused) {
    Sprite item;
    float world[4];
    int screen[4];
    int i;
    int total;
    int period;
    int phase;
    int count;

    total = 0;
    item.flags = 0;
    item.z = 0x8FFF0;
    item.u = 0;
    item.v = 0x100;
    item.w = 0x100;
    item.h = 0x100;
    item.r = 0x48;
    item.g = 0x80;
    item.b = 0x60;
    item.sx = 1.0f;
    item.sy = 0.5f;

    func_00158908(D_001FA200[index].id, world);
    world[3] = 1.0f;
    func_0018AED0(screen, D_001EDCC0, world, 0);

    for (i = 0; i < 3; i++) {
        period = i * 0x14 + 0x78;
        phase = D_001FA200[index].timer % period;
        item.x = screen[0] + ((phase / 3 + 0xC) << 4);
        item.y = screen[1] + ((-0x14 - phase / 4) << 4);
        item.sx = (float)phase / 80.0f;
        item.sy = (float)phase / 160.0f;
        item.a = -0x6C - phase * 0x94 / period;
        count = func_00117E58(packet, &item);
        total += count;
        packet += count * 16;
    }
    return total;
}
