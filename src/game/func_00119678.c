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

extern float D_001EDCC0[];

void func_0018AED0(Vec4i *out, float *matrix, Vec4f *in, int mode);

int func_00119678(unsigned char *packet, Vec4f *line) {
    Vec4f source;
    Vec4i screen[2];
    Vec4f *from;
    Vec4i *to;
    int i;
    int used;

    used = 0;
    to = screen;
    from = line;
    for (i = 1; i >= 0; i--) {
        to->x = 0;
        to->y = 0;
        to->z = 0;
        to->w = 0;
        source.x = from->x;
        source.y = from->y;
        source.z = from->z;
        source.w = 1.0f;
        func_0018AED0(to, D_001EDCC0, &source, 0);
        if (to->x <= 0x6000 || to->y <= 0x6000 || to->x > 0x9FFF || to->y > 0x9FFF) {
            to->w = 0;
        }
        from++;
        to++;
    }

    if ((float)screen[0].w != 0.0f && (float)screen[1].w != 0.0f) {
        *(long *)packet = 0x4024C00000008001L;
        *(long *)(packet + 8) = 0x4141L;
        used = 5;
        packet += 0x10;

        *(Vec4i *)packet = *(Vec4i *)&line[2];
        packet += 0x10;
        *(int *)(packet + 0x0) = screen[0].x;
        *(int *)(packet + 0x4) = screen[0].y;
        *(int *)(packet + 0x8) = screen[0].z;
        *(int *)(packet + 0xC) = 0x8000;
        packet += 0x10;

        *(Vec4i *)packet = *(Vec4i *)&line[3];
        packet += 0x10;
        *(int *)(packet + 0x0) = screen[1].x;
        *(int *)(packet + 0x4) = screen[1].y;
        *(int *)(packet + 0x8) = screen[1].z;
        *(int *)(packet + 0xC) = 0;
    }

    return used;
}
