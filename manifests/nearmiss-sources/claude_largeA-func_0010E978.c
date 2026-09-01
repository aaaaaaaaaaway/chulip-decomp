typedef struct {
    float position[4];
    float velocity[4];
    int life;
    int pad24[3];
} Particle;

typedef struct {
    int active;
    char pad04[0x2C];
    Particle particles[0x20];
} ParticleGroup;

extern ParticleGroup *D_001ED158[1];
extern int D_001ED15C[1];

void func_0010E978(void) {
    int i;
    int j;
    int k;

    for (i = 0; i < D_001ED15C[0]; i++) {
        if (D_001ED158[0][i].active == 0) {
            continue;
        }
        for (j = 0; j < 0x20; j++) {
            if (D_001ED158[0][i].particles[j].life > 0) {
                D_001ED158[0][i].particles[j].life--;
                for (k = 0; k < 3; k++) {
                    D_001ED158[0][i].particles[j].position[k] +=
                        D_001ED158[0][i].particles[j].velocity[k];
                    D_001ED158[0][i].particles[j].velocity[k] *= 0.8f;
                }
                D_001ED158[0][i].particles[j].velocity[1] -= 0.5f;
            }
        }
    }
}
