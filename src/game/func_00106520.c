typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[16] __attribute__((aligned(16)));
typedef struct {
    int unknown00, age, unknown08, unknown0C;
    Vec4 position, unknown20, unknown30;
} Particle;
typedef struct {
    int active, owner, bone, step, fade, duration, alpha;
    float scale;
    Vec4 unknown20;
    int color[4];
    Particle particle;
} Emitter;
extern Emitter *D_001ED09C[1];
void func_00106520(int index, int mode) {
    D_001ED09C[0][index].active = 1;
    switch (mode) {
    case 1:
        D_001ED09C[0][index].step = 1;
        break;
    case 0:
    default:
        D_001ED09C[0][index].step = -1;
        break;
    }
}
