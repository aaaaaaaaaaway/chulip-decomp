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
int func_001152F8(void) {
    int i;
    int phase, alpha;
    float scale;
    if (D_001ED1C8 <= 0)
        return 0;
    {
        phase = D_001ED1C8 - 11;
        if (phase < 0)
            phase = 0;
        --D_001ED1C8;
        alpha = (phase * 128) / 6;
        if (alpha > 128)
            alpha = 128;
        scale = ((30 - phase) * 0.2f + 1.0f) * D_001ED1CC;
        func_00114780(4, D_001F7BE0[0].position, scale, ((unsigned int)alpha << 24) | 0x808080);
        for (i = 1; i < 10; ++i) {
            alpha = (D_001ED1C8 * 128) / 10;
            if (alpha > 128)
                alpha = 128;
            func_00114780(5, D_001F7BE0[i].position, 0.7f,
                          ((unsigned int)alpha << 24) | (D_001F7BE0[i].color & 0xFFFFFF));
            func_0018A5F0(D_001F7BE0[i].position, D_001F7BE0[i].position, D_001F7BE0[i].velocity);
            func_0018A638(D_001F7BE0[i].velocity, D_001F7BE0[i].velocity, 0.8f);
        }
    }
    return 0;
}
