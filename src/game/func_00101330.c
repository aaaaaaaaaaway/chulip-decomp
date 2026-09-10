typedef float Vector[4] __attribute__((aligned(16)));
typedef struct GameState {
    long flags;
    unsigned char unknown08[0x3D];
    unsigned char camera_mode;
} GameState;
extern GameState *func_00136AE8(void);
extern void func_0018A680(Vector, const float *);
extern int func_00138468(unsigned int, int, unsigned int, unsigned short *);
extern int func_00173428(int);
extern Vector D_001EDDC0, D_001EDDD0;
void func_00101330(Vector position, unsigned char animate) {
    GameState *state = func_00136AE8();
    short values[4];
    int flag;
    flag = (int)(state->flags >> 14) & 1;
    if (flag == 1)
        return;
    position[3] = 1.0f;
    if (animate && state->camera_mode == 1) {
        D_001EDDC0[0] = position[0];
        D_001EDDC0[2] = position[2];
        flag = (int)(state->flags >> 18) & 1;
        if (flag == 1)
            values[0] = 10;
        else
            values[0] = 20;
        values[1] = 0;
        values[3] = 0;
        values[2] = (short)((position[1] - D_001EDDC0[1]) * 10.0f / values[0]);
        if (values[2] != 0)
            func_00138468(15, 0, 16, (unsigned short *)values);
    } else {
        func_0018A680(D_001EDDC0, position);
    }
    if (!(func_00173428(1) & 16))
        func_0018A680(D_001EDDD0, position);
    state->flags |= 1;
}
