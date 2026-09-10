typedef float Vec4[4] __attribute__((aligned(16)));
typedef int IVec4[4] __attribute__((aligned(16)));
typedef struct {
    int disabled, delay, age, duration, width;
} Strand;
typedef struct {
    int unknown0, unknown4, first_owner, second_owner;
    Vec4 first_offset, second_offset;
    int color[4];
    Strand strands[10];
} Emitter;
extern Emitter *D_001ED104[1];
extern int func_00192568(void);
extern void func_0018A680(float *, const float *);
void func_0010AA50(int first_owner, int second_owner, const float *first_offset,
                   const float *second_offset, const int *color, int parameter, int duration) {
    Emitter *emitter = D_001ED104[0];
    Strand *strand = emitter->strands;
    int i;
    emitter->first_owner = first_owner;
    emitter->second_owner = second_owner;
    emitter->unknown4 = parameter;
    emitter->unknown0 = 0;
    emitter->color[0] = color[0];
    emitter->color[1] = color[1];
    emitter->color[2] = color[2];
    emitter->color[3] = color[3];
    func_0018A680(D_001ED104[0]->first_offset, first_offset);
    func_0018A680(D_001ED104[0]->second_offset, second_offset);
    for (i = 0; i < 10; i++, strand++) {
        strand->disabled = 0;
        strand->delay = func_00192568() * 10;
        strand->age = 0;
        strand->duration = duration;
        strand->width = func_00192568() % 24 + 8;
    }
}
