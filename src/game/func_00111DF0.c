typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int active, width, depth;
    float height[10][10], velocity[10][10];
    Vec4 normal[10][10];
    float origin[3], phase;
    int color[4];
} Board;
extern void func_0018A448(float *, const float *, const float *);
extern void func_0018A490(float *, const float *);
void func_00111DF0(Board *board) {
    Vec4 step, tangent_x, tangent_z, normal;
    int i, j;
    tangent_x[3] = 1.0f;
    tangent_z[3] = 1.0f;
    step[0] = board->width / 10;
    step[2] = board->depth / 10;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            tangent_x[0] = step[0];
            tangent_x[1] = board->height[i][j + 1] - board->height[i][j];
            tangent_x[2] = 0.0f;
            tangent_z[0] = 0.0f;
            tangent_z[1] = board->height[i + 1][j] - board->height[i][j];
            tangent_z[2] = step[2];
            func_0018A448(normal, tangent_x, tangent_z);
            func_0018A490(normal, normal);
            board->normal[i][j][0] = normal[0] * 496.0f;
            board->normal[i][j][1] = normal[1] * 496.0f;
            board->normal[i][j][2] = normal[2] * 496.0f;
            board->normal[i][j][3] = 1.0f;
        }
    }
}
