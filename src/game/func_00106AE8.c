typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[16] __attribute__((aligned(16)));
typedef struct {
    int state;
    int age;
    int unknown08;
    int unknown0C;
    Vec4 position;
    Vec4 unknown20;
    Vec4 unknown30;
} Particle;
typedef struct {
    int owner;
    int bone;
    int active;
    int angle;
    int step;
    int age;
    int duration;
    int unknown1C;
    Vec4 unknown20;
    int color[4];
    Particle particles[100];
} Emitter;
extern Emitter *D_001ED0A8[1];
extern void func_00158A00(unsigned short, unsigned char, void *);
extern void func_0018A3D0(void *, void *, void *);
extern int func_00192568(void);
void func_00106AE8(int index, int owner, int bone, int *color) {
    Matrix matrix;
    Vec4 position;
    int i;
    func_00158A00(owner, bone, matrix);
    D_001ED0A8[0][index].active = 0;
    D_001ED0A8[0][index].owner = owner;
    D_001ED0A8[0][index].bone = bone;
    D_001ED0A8[0][index].age = 0;
    D_001ED0A8[0][index].duration = 120;
    D_001ED0A8[0][index].step = 1;
    D_001ED0A8[0][index].angle = func_00192568() % 360;
    D_001ED0A8[0][index].color[0] = color[0];
    D_001ED0A8[0][index].color[1] = color[1];
    D_001ED0A8[0][index].color[2] = color[2];
    D_001ED0A8[0][index].color[3] = color[3];
    for (i = 0; i < 100; i++) {
        position[0] = (float)((func_00192568() - func_00192568()) % 20);
        position[1] = (float)((func_00192568() - func_00192568()) % 50);
        position[2] = (float)((func_00192568() - func_00192568()) % 20);
        position[3] = 1.0f;
        func_0018A3D0(position, matrix, position);
        D_001ED0A8[0][index].particles[i].position[0] = position[0];
        D_001ED0A8[0][index].particles[i].position[1] = position[1];
        D_001ED0A8[0][index].particles[i].position[2] = position[2];
        D_001ED0A8[0][index].particles[i].position[3] = 1.0f;
        D_001ED0A8[0][index].particles[i].age = (func_00192568() - func_00192568()) % 20;
    }
}
