typedef struct {
    int flags;
    int x;
    int y;
    int z;
    int u;
    int v;
    int w;
    int h;
    int unused20;
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
extern int func_00117E58(unsigned char *, Sprite *);
extern int func_00158908(unsigned short, float *);
extern float func_0018B210(float);
extern float func_0018B2F8(float);
int func_0011A3D8(unsigned char *packet, int index, int unused) {
    Sprite item;
    float world[4];
    int screen[4];
    int i, total, count, x, y;
    float angle;
    item.flags = 0;
    item.z = 0x8FFF0;
    item.u = 0;
    item.v = 0x300;
    item.w = 0x100;
    item.h = 0x100;
    item.r = 0xFF;
    item.g = 0x80;
    item.b = 0xC8;
    item.a = 0x80;
    item.sx = 1.0f;
    item.sy = 0.5f;
    func_00158908(D_001FA200[index].owner, world);
    world[3] = 1.0f;
    func_0018AED0(screen, D_001EDCC0, world, 0);
    total = 0;
    for (i = 0; i < 4; i++) {
        angle = (float)(D_001FA200[index].timer * 3 % 360 + i * 90);
        angle *= 3.141592f, angle /= 180.0f;
        x = (int)(func_0018B210(angle) * 40.0f);
        y = (int)(func_0018B2F8(angle) * 5.0f - 30.0f);
        item.x = screen[0] + x * 16;
        item.y = screen[1] + y * 16;
        count = func_00117E58(packet, &item);
        total += count;
        packet += count * 16;
    }
    return total;
}
