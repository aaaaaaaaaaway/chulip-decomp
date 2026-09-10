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
extern int D_001ED254;
extern void *func_00151A00(int);
extern int func_00192568(void);
extern int func_00121C80();
extern void func_00112EB0(void (*)(void), int, int);
void func_001217A8(void) {
    int i, j;
    D_001ED258[0] = func_00151A00(sizeof(Environment));
    D_001ED254 = -1;
    D_001ED258[0]->active = 0;
    for (i = 0; i < 5; i++) {
        D_001ED258[0]->columns[i][0][0] = 0.0f;
        D_001ED258[0]->columns[i][0][1] = 0.0f;
        D_001ED258[0]->columns[i][0][2] = 0.0f;
        /* Retail seeds w before the inner loop replaces it. */
        D_001ED258[0]->columns[i][0][3] = func_00192568() % 10 + i / 4;
        for (j = 0; j < 7; j++) {
            D_001ED258[0]->columns[i][j][0] = D_001ED258[0]->columns[i][0][0] - 10.0f;
            D_001ED258[0]->columns[i][j][1] = j * 220.0f;
            D_001ED258[0]->columns[i][j][2] = D_001ED258[0]->columns[i][0][2];
            D_001ED258[0]->columns[i][j][3] = 1.0f;
        }
    }
    for (i = 0; i < 40; i++) {
        D_001ED258[0]->timers[i] = -(func_00192568() % 60);
        for (j = 0; j < 6; j++) {
            D_001ED258[0]->trails[i][j][0] = 0.0f;
            D_001ED258[0]->trails[i][j][1] = 0.0f;
            D_001ED258[0]->trails[i][j][2] = 0.0f;
            D_001ED258[0]->trails[i][j][3] =
                (float)((func_00192568() - func_00192568()) % 10) + 5.0f;
            /* Preserve the actual overwrite and preceding random calls. */
            D_001ED258[0]->trails[i][j][3] = 15.0f;
        }
    }
    for (i = 0; i < 200; i++) {
        D_001ED258[0]->particles[i].position[0] = (-func_00192568()) % 150;
        D_001ED258[0]->particles[i].position[1] = 0.0f;
        D_001ED258[0]->particles[i].position[2] = (func_00192568() - func_00192568()) % 150;
        D_001ED258[0]->particles[i].position[3] = func_00192568() % 30 + i;
        D_001ED258[0]->particles[i].velocity[0] = -(func_00192568() % 8);
        D_001ED258[0]->particles[i].velocity[1] = -(func_00192568() % 15);
        D_001ED258[0]->particles[i].velocity[2] = (func_00192568() - func_00192568()) % 8;
        D_001ED258[0]->particles[i].velocity[3] = 0.0f;
    }
    for (i = 0; i < 26; i++) {
        for (j = 0; j < 23; j++) {
            D_001ED258[0]->height[i][j] = 0.0f;
            D_001ED258[0]->velocity[i][j] = 0.0f;
        }
    }
    func_00112EB0((void (*)(void))func_00121C80, 0, 0);
}
