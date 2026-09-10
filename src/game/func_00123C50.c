typedef float Vector[4] __attribute__((aligned(16)));
typedef struct {
    Vector position, velocity;
} Particle;
typedef struct {
    int color[4] __attribute__((aligned(16)));
    int active;
    int timers[40];
    int unknownB4[3];
    Vector trails[40][6];
    Particle particles[200];
    float height[26][23], velocity[26][23];
    Vector normals[26][23];
    Vector columns[5][7];
} Environment;
/* One four-byte pointer slot; the original declaration is unknown. */
extern Environment *D_001ED258[1];
extern int func_00192568(void);
void func_00123C50(void) {
    int i, j, x, z;
    float force;
    if (D_001ED258[0]->active % (func_00192568() % 40 + 1) == 0) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                x = (func_00192568() - func_00192568()) % 4;
                x += 18;
                z = (func_00192568() - func_00192568()) % 4;
                z += 8;
                D_001ED258[0]->height[i + z][j + x] = 50.0f;
                D_001ED258[0]->height[i + z][j + x] = 50.0f;
            }
        }
    }
    for (i = 1; i < 25; i++) {
        for (j = 1; j < 22; j++) {
            force = 0.0f;
            force += D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i][j - 1];
            force += D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i][j + 1];
            force += D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i - 1][j];
            force += D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i + 1][j];
            force += (D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i - 1][j - 1]) * 0.5f;
            force += (D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i - 1][j + 1]) * 0.5f;
            force += (D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i + 1][j - 1]) * 0.5f;
            force += (D_001ED258[0]->height[i][j] - D_001ED258[0]->height[i + 1][j + 1]) * 0.5f;
            D_001ED258[0]->velocity[i][j] += force / 6.0f * 0.45f;
            D_001ED258[0]->velocity[i][j] -= D_001ED258[0]->height[i][j] * 0.6f;
            D_001ED258[0]->velocity[i][j] *= 0.985f;
        }
    }
    for (i = 0; i < 26; i++) {
        for (j = 0; j < 23; j++) {
            D_001ED258[0]->height[i][j] += D_001ED258[0]->velocity[i][j];
        }
    }
}
