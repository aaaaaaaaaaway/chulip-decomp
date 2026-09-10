typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int life, age, unknown08, unknown0C;
    Vec4 position, velocity;
} Particle;
typedef struct {
    int active, duration;
    float width, height, half_width, half_height;
    int unknown18, unknown1C;
    int color0[4], color1[4];
    Vec4 position, velocity;
    Particle particles[32];
} Effect;
typedef struct {
    int owner, bone, unknown08, unknown0C;
    Vec4 offset, direction;
    Effect effects[8];
} Chain;
extern Chain *D_001ED150[1];
typedef float Matrix[16] __attribute__((aligned(16)));
extern int D_001ED154;
extern int func_00113228(void *, int);
extern void func_00158A00(unsigned short, unsigned char, void *);
extern void func_0018A3D0(void *, void *, void *);
extern int func_0010D6F0(unsigned char *, Effect *);
int func_0010E290(unsigned char *packet, int unused1, int unused2) {
    Vec4 position, direction;
    Matrix matrix;
    unsigned char *head;
    int i, total, written;
    if (D_001ED154 != 0)
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
    *(unsigned long *)(packet + 24) = 0x47;
    *(unsigned long *)(packet + 16) = 0x53001;
    packet += 32;
    *(unsigned long *)(packet + 0) = 0x1000000000008001UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 24) = 0x42;
    *(unsigned long *)(packet + 16) = 0x8000000044UL;
    packet += 32;
    total += 6;
    func_00158A00(D_001ED150[0]->owner, D_001ED150[0]->bone, matrix);
    func_0018A3D0(position, matrix, D_001ED150[0]->offset);
    direction[0] = D_001ED150[0]->direction[0];
    direction[1] = D_001ED150[0]->direction[1];
    direction[2] = D_001ED150[0]->direction[2];
    direction[3] = 0.0f;
    func_0018A3D0(direction, matrix, direction);
    for (i = 0; i < 8; i++) {
        D_001ED150[0]->effects[i].position[0] = position[0];
        D_001ED150[0]->effects[i].position[1] = position[1] + (float)(i * 5);
        D_001ED150[0]->effects[i].position[2] = position[2];
        D_001ED150[0]->effects[i].position[3] = 1.0f;
        D_001ED150[0]->effects[i].velocity[0] = direction[0];
        D_001ED150[0]->effects[i].velocity[1] = direction[1];
        D_001ED150[0]->effects[i].velocity[2] = direction[2];
        D_001ED150[0]->effects[i].velocity[3] = 1.0f;
        written = func_0010D6F0(packet, &D_001ED150[0]->effects[i]);
        total += written;
        packet += written * 16;
    }
    *(unsigned short *)head = total;
    return total + 1;
}
