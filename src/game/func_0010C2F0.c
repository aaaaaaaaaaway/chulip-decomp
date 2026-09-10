typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[16] __attribute__((aligned(16)));
typedef int IVec4[4] __attribute__((aligned(16)));
typedef struct {
    Vec4 position;
    int color[4];
    int size;
} Endpoint;
extern int func_0010BDA0(int *, float *, Endpoint *);
extern int func_0010C150(unsigned int *, int, int, int, int, int, int, int, float, float, int);
int func_0010C2F0(unsigned char *packet, float *matrix, int segments, int count, Endpoint *first,
                  Endpoint *last) {
    IVec4 start, end, delta, color_delta;
    int size_delta, i, written, total;
    float radius;
    if (func_0010BDA0(start, matrix, first) != 0)
        return 0;
    if (func_0010BDA0(end, matrix, last) != 0)
        return 0;
    for (i = 0; i < 4; i++) {
        delta[i] = end[i] - start[i];
        color_delta[i] = last->color[i] - first->color[i];
    }
    size_delta = last->size - first->size;
    *(unsigned long *)(packet + 0) = 0x1000000000008002UL;
    *(unsigned long *)(packet + 8) = 14;
    *(unsigned long *)(packet + 16) = 0x8000000048UL;
    *(unsigned long *)(packet + 24) = 0x42;
    *(unsigned long *)(packet + 32) = 0x71401;
    *(unsigned long *)(packet + 40) = 0x47;
    packet += 48;
    total = 3;
    for (i = 0; i < count; i++) {
        radius = (float)(first->size + size_delta * i / count);
        written = func_0010C150((unsigned int *)packet, start[0] + delta[0] * i / count,
                                start[1] + delta[1] * i / count, start[2] + delta[2] * i / count,
                                first->color[0] + color_delta[0] * i / count,
                                first->color[1] + color_delta[1] * i / count,
                                first->color[2] + color_delta[2] * i / count,
                                first->color[3] + color_delta[3] * i / count, radius, radius * 0.5f,
                                segments);
        total += written;
        packet += written * 16;
    }
    return total;
}
