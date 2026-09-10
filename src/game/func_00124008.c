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
void func_00124008(void) {
    int i, j;
    for (i = 0; i < 40; i++) {
        D_001ED258[0]->timers[i]++;
        if (D_001ED258[0]->timers[i] >= 0) {
            if (D_001ED258[0]->timers[i] > 60) {
                for (j = 0; j < 6; j++) {
                    D_001ED258[0]->trails[i][j][0] = 0.0f;
                    D_001ED258[0]->trails[i][j][1] = 0.0f;
                    D_001ED258[0]->trails[i][j][2] = 0.0f;
                    D_001ED258[0]->trails[i][j][3] =
                        (float)((func_00192568() - func_00192568()) % 10) + 30.0f;
                }
                D_001ED258[0]->timers[i] = -(func_00192568() % 60) - 1;
            } else {
                for (j = 0; j < 6; j++) {
                    D_001ED258[0]->trails[i][j][0] += D_001ED258[0]->trails[i][j][3];
                    D_001ED258[0]->trails[i][j][2] += D_001ED258[0]->trails[i][j][3];
                    D_001ED258[0]->trails[i][j][3] *= 0.98f;
                }
            }
        }
    }
}
