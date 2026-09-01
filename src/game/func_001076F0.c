typedef struct {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) Vec4f;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} __attribute__((aligned(16))) Vec4i;

typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    float f20;
    float f24;
    float f28;
    unsigned char f2C;
    unsigned char f2D;
    unsigned char f2E;
    signed char f2F;
} Params;

typedef struct {
    short f00;
    unsigned char pad;
    unsigned char f03;
} Hdr;

typedef struct {
    int state;
    int id;
    int frame;
    int f0C;
    float rx;
    float ry;
    float rz;
    float f1C;
    int red;
    int green;
    int blue;
    int alpha;
} Entry;

extern float D_001EDCC0[];
extern int D_001ED0B4;
extern int D_001ED0BC;

int func_00113228(void *packet, int count);
void func_0011FA48(Vec4f *out, int id, Vec4f *rot);
void func_00158868(unsigned short id, Vec4f *out);
int func_00120BE0(Vec4i *out, float *matrix, Vec4f *in);
int func_00118058(void *packet, Params *params);

int func_001076F0(char *packet, int count)
{
    Params params;
    Vec4i screen;
    Vec4f position;
    Vec4f rotation;
    Hdr *header;
    int used;
    int written;
    int i;

    if (D_001ED0BC != 0) {
        return 0;
    }

    header = (Hdr *)packet;
    packet += 0x10;
    header->f03 = 0x10;
    used = func_00113228(packet, 0x1018);
    packet += used * 16;
    *(long *)(packet + 0x0) = 0x1000000000008001L;
    *(long *)(packet + 0x8) = 0xEL;
    *(long *)(packet + 0x18) = 0x8L;
    *(long *)(packet + 0x10) = 0x5L;
    packet += 0x20;
    *(long *)(packet + 0x0) = 0x1000000000008001L;
    *(long *)(packet + 0x8) = 0xEL;
    *(long *)(packet + 0x18) = 0x42L;
    *(long *)(packet + 0x10) = 0x8000000048L;
    packet += 0x20;
    used += 4;

    params.f00 = 0;
    params.f10 = 0x600;
    params.f14 = 0x400;
    params.f18 = 0x200;
    params.f1C = 0x200;
    params.f24 = 1.0f;
    params.f28 = 0.5f;

    for (i = 0; i < count; i++) {
        if (((Entry *)(i * 0x30 + D_001ED0B4))->state != 1) {
            continue;
        }
        rotation.x = ((Entry *)(i * 0x30 + D_001ED0B4))->rx;
        rotation.y = ((Entry *)(i * 0x30 + D_001ED0B4))->ry;
        rotation.z = ((Entry *)(i * 0x30 + D_001ED0B4))->rz;
        rotation.w = 1.0f;
        func_0011FA48(&position, ((Entry *)(i * 0x30 + D_001ED0B4))->id, &rotation);
        func_00158868((unsigned short)((Entry *)(i * 0x30 + D_001ED0B4))->id, &rotation);
        position.x += rotation.x;
        position.y += rotation.y;
        position.z += rotation.z;
        if (func_00120BE0(&screen, D_001EDCC0, &position) != 0) {
            continue;
        }
        params.f04 = screen.x;
        params.f08 = screen.y;
        params.f0C = 0x7FFFF0;
        params.f2C = ((Entry *)(i * 0x30 + D_001ED0B4))->red;
        params.f2D = ((Entry *)(i * 0x30 + D_001ED0B4))->green;
        params.f2E = ((Entry *)(i * 0x30 + D_001ED0B4))->blue;
        params.f2F = (unsigned char)((Entry *)(i * 0x30 + D_001ED0B4))->alpha
                     - ((Entry *)(i * 0x30 + D_001ED0B4))->alpha
                       * ((Entry *)(i * 0x30 + D_001ED0B4))->frame / 5;
        params.f24 = (float)((Entry *)(i * 0x30 + D_001ED0B4))->frame / 5.0f + 1.0f;
        params.f28 = (float)((Entry *)(i * 0x30 + D_001ED0B4))->frame * 0.5f / 5.0f + 0.5f;
        params.f20 = (float)((Entry *)(i * 0x30 + D_001ED0B4))->f0C;
        written = func_00118058(packet, &params);
        used += written;
        packet += written * 16;
        params.f20 = params.f20 * 3.0f;
        written = func_00118058(packet, &params);
        used += written;
        packet += written * 16;
        *(int *)(i * 0x30 + D_001ED0B4 + 0x8) = *(int *)(i * 0x30 + D_001ED0B4 + 0x8) + 1;
        if (*(int *)(i * 0x30 + D_001ED0B4 + 0x8) >= 6) {
            *(int *)(i * 0x30 + D_001ED0B4) = 0;
        }
    }

    header->f00 = used;
    return used + 1;
}
