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
    unsigned short id;
    unsigned short pad6;
    int pad8;
    int timer;
} Slot;

extern Slot D_001FA200[];
extern float D_001EDCC0[];

void func_00158908(int id, float *out);
void func_0018AED0(int *out, float *matrix, float *in, int mode);
int func_00117E58(unsigned char *packet, Sprite *sprite);

int func_00119FA0(unsigned char *packet, int index) {
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
    item.sx = 1.0f;
    item.sy = 0.5f;
    item.r = 0x48;
    item.g = 0x80;
    item.b = 0x60;

    func_00158908(D_001FA200[index].id, world);
    world[3] = 1.0f;
    func_0018AED0(screen, D_001EDCC0, world, 0);

    period = 0x78;
    for (i = 2; i >= 0; i--) {
        phase = D_001FA200[index].timer % period;
        item.y = screen[1] + ((-0x14 - phase / 4) << 4);
        item.sx = (float)phase / 80.0f;
        item.sy = (float)phase / 160.0f;
        item.x = screen[0] + ((phase / 3 + 0xC) << 4);
        item.a = -0x6C - phase * 0x94 / period;
        count = func_00117E58(packet, &item);
        total += count;
        packet += count * 16;
        period += 0x14;
    }
    return total;
}
