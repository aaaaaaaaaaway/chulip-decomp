typedef struct {
    int steps;      /* 0x00 */
    int hold;       /* 0x04 */
    int unk08;      /* 0x08 */
    float pos[3];   /* 0x0C */
    float prev[3];  /* 0x18 */
    float vel[3];   /* 0x24 */
} Shake;

extern Shake D_002DB6D8;
extern int func_00192568(void);

void func_00182F00(void) {
    if (D_002DB6D8.steps > 0) {
        D_002DB6D8.steps--;
        D_002DB6D8.prev[0] = D_002DB6D8.pos[0];
        D_002DB6D8.prev[1] = D_002DB6D8.pos[1];
        D_002DB6D8.prev[2] = D_002DB6D8.pos[2];
        D_002DB6D8.pos[0] += D_002DB6D8.vel[0];
        D_002DB6D8.pos[1] += D_002DB6D8.vel[1];
        D_002DB6D8.pos[2] += D_002DB6D8.vel[2];
    } else if (--D_002DB6D8.hold > 0) {
        D_002DB6D8.vel[0] -= D_002DB6D8.vel[0] * 0.25f;
        D_002DB6D8.vel[1] -= D_002DB6D8.vel[1] * 0.25f;
        D_002DB6D8.vel[2] -= D_002DB6D8.vel[2] * 0.25f;
    } else {
        D_002DB6D8.steps = func_00192568() % 0x78 + 0x3C;
        D_002DB6D8.hold = func_00192568() % 0xF0 + 0x3C;
        D_002DB6D8.pos[0] = 0.0f;
        D_002DB6D8.pos[1] = 0.0f;
        D_002DB6D8.pos[2] = 0.0f;
        D_002DB6D8.vel[0] = (float)(func_00192568() % 0x32 - func_00192568() % 0x32);
        D_002DB6D8.vel[1] = (float)(func_00192568() % 0x19 - func_00192568() % 0x19);
        D_002DB6D8.vel[2] = (float)(func_00192568() % 0x32 - func_00192568() % 0x32);
        D_002DB6D8.vel[0] /= 5000.0f;
        D_002DB6D8.vel[1] /= 5000.0f;
        D_002DB6D8.vel[2] /= 5000.0f;
    }
}
