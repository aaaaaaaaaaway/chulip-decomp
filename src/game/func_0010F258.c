typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    Vec4 position, velocity;
    int life, unknown24, unknown28, unknown2C;
} Particle;
typedef struct {
    int active, color, unknown08, unknown0C;
    Vec4 origin, velocity;
    Particle particles[64];
} Emitter;
typedef struct {
    int origin[3], velocity[3];
} Source;
extern Emitter *D_001ED164[1];
extern Source *D_001ED16C[1];
extern int func_00192568(void);
void func_0010F258(int index, int active) {
    int j;
    if (active == 0) {
        D_001ED164[0][index].active = 0;
        return;
    }
    if (D_001ED164[0][index].active != 0)
        return;
    D_001ED164[0][index].color = 0x80808080;
    D_001ED164[0][index].origin[0] = (float)D_001ED16C[0][index].origin[0];
    D_001ED164[0][index].origin[1] = (float)D_001ED16C[0][index].origin[1];
    D_001ED164[0][index].origin[2] = (float)D_001ED16C[0][index].origin[2];
    D_001ED164[0][index].origin[3] = 1.0f;
    D_001ED164[0][index].velocity[0] = (float)D_001ED16C[0][index].velocity[0];
    D_001ED164[0][index].velocity[1] = (float)D_001ED16C[0][index].velocity[1];
    D_001ED164[0][index].velocity[2] = (float)D_001ED16C[0][index].velocity[2];
    D_001ED164[0][index].velocity[3] = 1.0f;
    for (j = 0; j < 64; j++) {
        D_001ED164[0][index].particles[j].position[0] = D_001ED164[0][index].origin[0];
        D_001ED164[0][index].particles[j].position[1] = D_001ED164[0][index].origin[1];
        D_001ED164[0][index].particles[j].position[2] = D_001ED164[0][index].origin[2];
        D_001ED164[0][index].particles[j].position[3] = 1.0f;
        D_001ED164[0][index].particles[j].velocity[0] =
            (D_001ED164[0][index].velocity[0] + (float)(func_00192568() % 20) - 10.0f) * 0.3f;
        D_001ED164[0][index].particles[j].velocity[1] =
            (D_001ED164[0][index].velocity[1] + (float)(func_00192568() % 20) - 10.0f) * 0.3f;
        D_001ED164[0][index].particles[j].velocity[2] =
            (D_001ED164[0][index].velocity[2] + (float)(func_00192568() % 20) - 10.0f) * 0.3f;
        D_001ED164[0][index].particles[j].velocity[3] = 1.0f;
        D_001ED164[0][index].particles[j].life = func_00192568() % 64;
    }
    D_001ED164[0][index].active = 1;
    D_001ED164[0][index].active = active;
}
