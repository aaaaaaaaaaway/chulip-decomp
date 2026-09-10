typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int state;
    int age;
    int unknown08;
    int unknown0C;
    Vec4 position;
    Vec4 velocity;
    Vec4 unknown30;
} Particle;
typedef struct {
    int active;
    int angle;
    int unknown08;
    int unknown0C;
    Vec4 position;
    int color[4];
    Particle first[30];
    Particle second[15];
} Emitter;
extern Emitter *D_001ED0C0[1];
extern int func_00192568(void);
void func_00107BD8(int index, float *position, int *color) {
    int i;
    D_001ED0C0[0][index].angle = func_00192568() % 360;
    D_001ED0C0[0][index].position[0] = position[0];
    D_001ED0C0[0][index].position[1] = position[1];
    D_001ED0C0[0][index].position[2] = position[2];
    D_001ED0C0[0][index].color[0] = color[0];
    D_001ED0C0[0][index].color[1] = color[1];
    D_001ED0C0[0][index].color[2] = color[2];
    D_001ED0C0[0][index].color[3] = color[3];
    for (i = 0; i < 30; i++) {
        D_001ED0C0[0][index].first[i].position[0] =
            position[0] + (float)((func_00192568() - func_00192568()) % 10);
        D_001ED0C0[0][index].first[i].position[1] = position[1] + (float)(func_00192568() % 50);
        D_001ED0C0[0][index].first[i].position[2] =
            position[2] + (float)((func_00192568() - func_00192568()) % 10);
        D_001ED0C0[0][index].first[i].position[3] = 1.0f;
        D_001ED0C0[0][index].first[i].velocity[0] =
            (float)((func_00192568() - func_00192568()) % 5);
        D_001ED0C0[0][index].first[i].velocity[1] = (float)(-(func_00192568() % 10));
        D_001ED0C0[0][index].first[i].velocity[2] =
            (float)((func_00192568() - func_00192568()) % 5);
        D_001ED0C0[0][index].first[i].age = (func_00192568() - func_00192568()) % 20;
    }
    for (i = 0; i < 15; i++) {
        D_001ED0C0[0][index].second[i].position[0] =
            position[0] + (float)((func_00192568() - func_00192568()) % 50);
        D_001ED0C0[0][index].second[i].position[1] =
            position[1] + (float)((func_00192568() - func_00192568()) % 50);
        D_001ED0C0[0][index].second[i].position[2] =
            position[2] + (float)((func_00192568() - func_00192568()) % 50);
        D_001ED0C0[0][index].second[i].position[3] = 1.0f;
        /* Retail updates the first pool velocities while initializing the second pool. */
        D_001ED0C0[0][index].first[i].velocity[0] =
            (float)((func_00192568() - func_00192568()) % 10);
        D_001ED0C0[0][index].first[i].velocity[1] =
            (float)((func_00192568() - func_00192568()) % 20);
        D_001ED0C0[0][index].first[i].velocity[2] =
            (float)((func_00192568() - func_00192568()) % 10);
        D_001ED0C0[0][index].first[i].velocity[3] = 1.0f;
        D_001ED0C0[0][index].second[i].age = -(func_00192568() % 60);
    }
}
