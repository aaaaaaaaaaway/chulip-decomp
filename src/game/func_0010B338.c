typedef float Vec4[4] __attribute__((aligned(16)));
typedef int IVec4[4] __attribute__((aligned(16)));
typedef struct {
    int inactive, age;
    float phase;
} Ring;
typedef struct {
    int unknown00, unknown04, lifetime;
    Ring rings[16];
    IVec4 color;
    Vec4 origin, offset;
} Emitter;
extern Emitter *D_001ED110[1];
extern void func_0018A680(void *, const void *);
extern int func_00192568(void);
void func_0010B338(float *origin, float *offset) {
    Emitter *emitter = D_001ED110[0];
    Ring *ring;
    int i;
    emitter->lifetime = 120;
    func_0018A680(emitter->origin, origin);
    func_0018A680(emitter->offset, offset);
    emitter->color[0] = 48;
    emitter->color[1] = 128;
    emitter->color[2] = 80;
    emitter->color[3] = 8;
    emitter->origin[3] = 0;
    emitter->offset[3] = 0;
    for (i = 0; i < 16; i++) {
        ring = &emitter->rings[i];
        ring->inactive = 0;
        ring->age = -(func_00192568() % 60);
        ring->phase = 3.1415927f / (float)(func_00192568() % 10 + 1);
    }
}
