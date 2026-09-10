typedef float Vector[4] __attribute__((aligned(16)));
typedef struct {
    Vector position, velocity;
    unsigned int color;
} BurstParticle;
typedef struct {
    Vector position, velocity;
} BounceParticle;
extern BurstParticle D_001F7BE0[10];
extern BounceParticle D_001F7DC0[];
extern int D_001ED1C8, D_001ED1D0;
extern float D_001ED1CC, D_001ED1D4;
extern void func_00114780(int, float *, float, int);
extern void func_0018A680(float *, const float *);
extern void func_0018A5F0(float *, const float *, const float *);
extern void func_0018A638(float *, const float *, float);
extern int func_00192568(void);
extern float func_0018B210(float), func_0018B2F8(float);
void func_001151B0(const float *position, float scale) {
    int i;
    D_001ED1C8 = 30;
    D_001ED1CC = scale;
    for (i = 0; i < 10; ++i) {
        func_0018A680(D_001F7BE0[i].position, position);
        D_001F7BE0[i].position[3] = 1.0f;
        D_001F7BE0[i].velocity[0] = func_00192568() % 100 - 50;
        D_001F7BE0[i].velocity[1] = -(func_00192568() % 50);
        D_001F7BE0[i].velocity[2] = func_00192568() % 100 - 50;
        D_001F7BE0[i].velocity[3] = 0.0f;
        if (func_00192568() & 1)
            D_001F7BE0[i].color = 0x80808040;
        else
            D_001F7BE0[i].color = 0x80408080;
    }
}
