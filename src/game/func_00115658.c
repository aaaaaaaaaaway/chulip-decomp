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
int func_00115658(void) {
    int i, alpha;
    if (D_001ED1D0 <= 0)
        return 0;
    {
        --D_001ED1D0;
        for (i = 1; i < D_001ED1D4; ++i) {
            alpha = D_001ED1D0 * 2;
            if (alpha > 128)
                alpha = 128;
            func_00114780(2, D_001F7DC0[i].position, 0.45f, ((unsigned int)alpha << 24) | 0x808080);
            func_0018A5F0(D_001F7DC0[i].position, D_001F7DC0[i].position, D_001F7DC0[i].velocity);
            if (D_001F7DC0[i].position[1] > D_001F7DC0[0].position[1]) {
                D_001F7DC0[i].position[1] = D_001F7DC0[0].position[1];
                D_001F7DC0[i].velocity[1] *= -0.8f;
            }
            D_001F7DC0[i].velocity[1] += 2.0f;
            func_0018A638(D_001F7DC0[i].velocity, D_001F7DC0[i].velocity, 0.95f);
        }
    }
    return 0;
}
