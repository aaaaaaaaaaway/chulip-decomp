typedef float Vector[4] __attribute__((aligned(16)));
typedef int Color[4] __attribute__((aligned(16)));
typedef struct {
    Vector position, velocity;
} Particle;
typedef struct {
    Color color;
    int active;
    int timers[40];
    int unknownB4[3];
    Vector trails[40][6];
    Particle particles[200];
    float height[26][23], velocity[26][23];
    Vector normals[26][23];
    Vector columns[5][7];
} Environment;
extern Environment *D_001ED258[1];
extern void func_0018A448(Vector, const Vector, const Vector);
extern void func_0018A490(Vector, const Vector);
void func_00123A90(void) {
    Vector tangent_x, tangent_z, normal;
    int i, j;
    tangent_x[3] = 1.0f;
    tangent_z[3] = 1.0f;
    for (i = 0; i < 25; ++i) {
        for (j = 0; j < 22; ++j) {
            tangent_x[0] = 48.0f;
            tangent_x[1] = D_001ED258[0]->height[i][j + 1] - D_001ED258[0]->height[i][j];
            tangent_x[2] = 0.0f;
            tangent_z[0] = 0.0f;
            tangent_z[1] = D_001ED258[0]->height[i + 1][j] - D_001ED258[0]->height[i][j];
            tangent_z[2] = 48.0f;
            func_0018A448(normal, tangent_x, tangent_z);
            func_0018A490(normal, normal);
            D_001ED258[0]->normals[i][j][0] = normal[0] * 496.0f;
            D_001ED258[0]->normals[i][j][1] = normal[1] * 496.0f;
            D_001ED258[0]->normals[i][j][2] = normal[2] * 496.0f;
            D_001ED258[0]->normals[i][j][3] = 1.0f;
        }
    }
}
