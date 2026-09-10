typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct {
    int active, width, depth;
    float height[10][10], velocity[10][10];
    Vec4 normal[10][10];
    float origin[3], phase;
    int color[4];
} Board;
extern Board *D_001ED188[1];

extern int D_001ED190;

void func_00111300(int index, float x, float y, float *pos, int *color) {
    int i;
    int j;

    D_001ED188[0][index].active = 0;
    D_001ED188[0][index].width = (int)x;
    D_001ED188[0][index].depth = (int)y;
    D_001ED188[0][index].origin[0] = pos[0];
    D_001ED188[0][index].origin[1] = pos[1];
    D_001ED188[0][index].origin[2] = pos[2];
    D_001ED188[0][index].phase = 0;
    D_001ED188[0][index].color[0] = color[0];
    D_001ED188[0][index].color[1] = color[1];
    D_001ED188[0][index].color[2] = color[2];
    D_001ED188[0][index].color[3] = color[3];
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            D_001ED188[0][index].height[i][j] = 0;
            D_001ED188[0][index].velocity[i][j] = 0;
        }
    }
}

void func_00111448(int arg0) { D_001ED190 = arg0; }
