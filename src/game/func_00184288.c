typedef struct {
    int r;
    int g;
    int b;
    int a;
} __attribute__((aligned(16))) PacketColor;

struct PacketVertex {
    int u;
    int v;
    int uv_pad_0x8;
    int uv_pad_0xC;
    int x;
    int y;
    int z;
    int flags;
};

extern int func_00113228(unsigned char *packet, int count);

int func_00184288(unsigned char *packet, int x, int y, int z, int width, int height,
                  PacketColor *color, int texture) {
    unsigned char *p;
    struct PacketVertex *vert;
    int index;

    index = func_00113228(packet, texture);
    p = packet + index * 16;
    *(long *)p = 0x90AA400000008001L;
    *(long *)(p + 8) = 0x434343431L;
    p += 0x10;
    *(PacketColor *)p = *color;
    p += 0x10;
    vert = (struct PacketVertex *)p;
    vert[0].u = 8;
    vert[0].v = 8;
    vert[0].uv_pad_0x8 = 0;
    vert[0].uv_pad_0xC = 0;
    vert[1].u = 0xfe8;
    vert[1].v = 8;
    vert[1].uv_pad_0x8 = 0;
    vert[1].uv_pad_0xC = 0;
    vert[2].u = 8;
    vert[2].v = 0xBF8;
    vert[2].uv_pad_0x8 = 0;
    vert[2].uv_pad_0xC = 0;
    vert[3].u = 0xfe8;
    vert[3].v = 0xBF8;
    vert[3].uv_pad_0x8 = 0;
    vert[3].uv_pad_0xC = 0;
    vert[0].x = x;
    vert[0].y = y;
    vert[0].z = z;
    vert[0].flags = 0x8000;
    vert[1].x = x + width;
    vert[1].y = y;
    vert[1].z = z;
    vert[1].flags = 0x8000;
    vert[2].x = x;
    vert[2].y = y + height;
    vert[2].z = z;
    vert[2].flags = 0;
    vert[3].x = x + width;
    vert[3].y = y + height;
    vert[3].z = z;
    vert[3].flags = 0;
    return index + 10;
}
