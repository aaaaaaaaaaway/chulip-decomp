typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[16] __attribute__((aligned(16)));
typedef int IVec4[4] __attribute__((aligned(16)));
typedef struct {
    Vec4 position;
    int color[4];
    int size;
} Endpoint;
typedef unsigned int Qword __attribute__((mode(TI)));
typedef struct {
    int active, owner, bone, count;
    Vec4 first_position, last_position;
    int first_color[4], last_color[4];
    int first_size, last_size, unknown58, unknown5C;
} Emitter;
extern Emitter *D_001ED128[1];
extern int D_001ED12C, D_001ED130;
extern float D_001EDCC0[];
extern void func_00158A00(unsigned short, unsigned char, void *);
extern void func_0018A400(void *, void *, void *);
extern void func_0018A680(void *, const void *);
extern int func_0010C2F0(unsigned char *, float *, int, int, Endpoint *, Endpoint *);
int func_0010C570(unsigned char *packet, int unused_count, int unused_context) {
    Endpoint first, last;
    Matrix matrix;
    unsigned char *head;
    int i, total, written;
    if (D_001ED130 != 0)
        return 0;
    *(Qword *)packet = 0;
    head = packet;
    packet += 16;
    head[3] = 0x10;
    total = 0;
    for (i = 0; i < D_001ED12C; i++) {
        if (D_001ED128[0][i].active != 0) {
            func_00158A00(D_001ED128[0][i].owner, D_001ED128[0][i].bone, matrix);
            func_0018A400(matrix, D_001EDCC0, matrix);
            func_0018A680(first.position, D_001ED128[0][i].first_position);
            func_0018A680(last.position, D_001ED128[0][i].last_position);
            first.color[0] = D_001ED128[0][i].first_color[0];
            first.color[1] = D_001ED128[0][i].first_color[1];
            first.color[2] = D_001ED128[0][i].first_color[2];
            first.color[3] = D_001ED128[0][i].first_color[3];
            first.size = D_001ED128[0][i].first_size * 16;
            last.color[0] = D_001ED128[0][i].last_color[0];
            last.color[1] = D_001ED128[0][i].last_color[1];
            last.color[2] = D_001ED128[0][i].last_color[2];
            last.color[3] = D_001ED128[0][i].last_color[3];
            last.size = D_001ED128[0][i].last_size * 16;
            written = func_0010C2F0(packet, matrix, 16, D_001ED128[0][i].count, &first, &last);
            total += written;
            packet += written * 16;
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
