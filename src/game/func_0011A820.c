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
    int id;
    int owner;
    int state;
    int timer;
} Slot;
extern Slot D_001FA200[];
extern float D_001EDCC0[];
extern void func_0018AED0(int *, float *, float *, int);
extern int func_00118058(unsigned char *, Sprite *);
extern int func_00158960(unsigned short, unsigned char, void *);
extern int D_001A3B08[];
extern int D_001A3B18[];
extern float D_001A3B28[];
extern float D_001A3B38[];
extern int D_001A3B48[2][4];
int func_0011A820(unsigned char *packet, int index, int unused) {
    Sprite item;
    float world[4];
    int screen[4];
    int i, total, count, period;
    item.flags = 0;
    item.z = 0x8FFF0;
    item.u = 0;
    item.v = 0x400;
    item.w = 0x100;
    item.h = 0x100;
    item.r = 0xFF;
    item.g = 0x80;
    item.b = 0xB4;
    item.a = 0x80;
    func_00158960(D_001FA200[index].owner, 3, world);
    world[3] = 1.0f;
    func_0018AED0(screen, D_001EDCC0, world, 0);
    period = D_001FA200[index].timer % 120;
    total = 0;
    for (i = 0; i < 4; i++) {
        item.x = screen[0] + D_001A3B08[i] * 16;
        item.y = screen[1] + D_001A3B18[i] * 16 - period * (i + 1) / 4;
        item.sx = 1.0f - D_001A3B28[i] * (float)(period % 60) / 60.0f;
        item.sy = 0.5f - D_001A3B38[i] * (float)(period % 60) / 60.0f;
        item.angle = (float)D_001A3B48[(period / 60) % 2][i];
        count = func_00118058(packet, &item);
        total += count;
        packet += count * 16;
    }
    return total;
}
