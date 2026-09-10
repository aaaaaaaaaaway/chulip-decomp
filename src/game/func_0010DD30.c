typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int life, age, unknown08, unknown0C;
    Vec4 position, velocity;
} Particle;
typedef struct {
    int active, duration;
    float width, height, half_width, half_height;
    int unknown18, unknown1C;
    int color0[4], color1[4];
    Vec4 position, velocity;
    Particle particles[32];
} Effect;
typedef struct {
    int owner, bone, unknown08, unknown0C;
    Vec4 offset, direction;
    Effect effects[8];
} Chain;
extern Chain *D_001ED150[1];
extern int func_00158868(unsigned short, float *);
extern int func_00192568(void);
void func_0010DD30(int owner, int bone, int duration, float *offset, float *direction, int *color0,
                   int *color1) {
    Vec4 position;
    int i, j;
    func_00158868(owner, position);
    position[0] += offset[0];
    position[1] += offset[1];
    position[2] += offset[2];
    position[3] = 1.0f;
    for (i = 0; i < 8; i++) {
        D_001ED150[0]->effects[i].active = 0;
        D_001ED150[0]->owner = owner;
        D_001ED150[0]->bone = bone;
        D_001ED150[0]->offset[0] = offset[0];
        D_001ED150[0]->offset[1] = offset[1];
        D_001ED150[0]->offset[2] = offset[2];
        D_001ED150[0]->offset[3] = 1.0f;
        D_001ED150[0]->direction[0] = direction[0];
        D_001ED150[0]->direction[1] = direction[1];
        D_001ED150[0]->direction[2] = direction[2];
        D_001ED150[0]->direction[3] = 1.0f;
        D_001ED150[0]->effects[i].duration = duration;
        D_001ED150[0]->effects[i].color0[0] = color0[0];
        D_001ED150[0]->effects[i].color0[1] = color0[1];
        D_001ED150[0]->effects[i].color0[2] = color0[2];
        D_001ED150[0]->effects[i].color0[3] = color0[3];
        D_001ED150[0]->effects[i].color1[0] = color1[0];
        D_001ED150[0]->effects[i].color1[1] = color1[1];
        D_001ED150[0]->effects[i].color1[2] = color1[2];
        D_001ED150[0]->effects[i].color1[3] = color1[3];
        D_001ED150[0]->effects[i].width = 1.0f;
        D_001ED150[0]->effects[i].half_width = 0.5f;
        D_001ED150[0]->effects[i].height = (float)(func_00192568() % 3) + 2.0f;
        D_001ED150[0]->effects[i].half_height = D_001ED150[0]->effects[i].height * 0.5f;
        D_001ED150[0]->effects[i].position[0] = position[0];
        D_001ED150[0]->effects[i].position[1] = position[1];
        D_001ED150[0]->effects[i].position[2] = position[2];
        D_001ED150[0]->effects[i].velocity[0] = direction[0];
        D_001ED150[0]->effects[i].velocity[1] = direction[1];
        D_001ED150[0]->effects[i].velocity[2] = direction[2];
        for (j = 0; j < 32; j++) {
            D_001ED150[0]->effects[i].particles[j].position[0] = position[0];
            D_001ED150[0]->effects[i].particles[j].position[1] = position[1];
            D_001ED150[0]->effects[i].particles[j].position[2] = position[2];
            D_001ED150[0]->effects[i].particles[j].position[3] = 1.0f;
            D_001ED150[0]->effects[i].particles[j].velocity[0] =
                direction[0] + (float)((func_00192568() - func_00192568()) % 15) / 100.0f;
            D_001ED150[0]->effects[i].particles[j].velocity[1] =
                direction[1] + (float)((func_00192568() - func_00192568()) % 15) / 100.0f;
            D_001ED150[0]->effects[i].particles[j].velocity[2] =
                direction[2] + (float)((func_00192568() - func_00192568()) % 15) / 100.0f;
            D_001ED150[0]->effects[i].particles[j].velocity[3] =
                (float)(func_00192568() % 200) / 100.0f;
            D_001ED150[0]->effects[i].particles[j].life = duration;
        }
    }
}
