typedef struct Effect {
    int active, kind, frame, lifetime, delay;
    int state, step, intensity, red, green, blue, unknown2c;
    float origin[3], position[3], velocity[3];
    int unknown54, unknown58, unknown5c;
} Effect;
extern Effect *D_001ED354[1];
extern int func_00192568(void);
void func_00133990(int index, int kind, const float *position) {
    D_001ED354[0][index].active = 0;
    D_001ED354[0][index].kind = kind;
    D_001ED354[0][index].frame = 0;
    D_001ED354[0][index].origin[0] = D_001ED354[0][index].position[0] = position[0];
    D_001ED354[0][index].origin[1] = D_001ED354[0][index].position[1] = position[1];
    D_001ED354[0][index].origin[2] = D_001ED354[0][index].position[2] = position[2];
    D_001ED354[0][index].position[0] += func_00192568() % 500 - func_00192568() % 500;
    D_001ED354[0][index].position[1] += func_00192568() % 500;
    D_001ED354[0][index].position[2] += func_00192568() % 500 - func_00192568() % 500;
    switch (D_001ED354[0][index].kind) {
    case 0:
        D_001ED354[0][index].delay = func_00192568() % 200 + 50;
        D_001ED354[0][index].lifetime = func_00192568() % 20 + 5;
        D_001ED354[0][index].velocity[0] = (float)(func_00192568() % 10) + 5.0f;
        D_001ED354[0][index].velocity[1] = 0;
        D_001ED354[0][index].velocity[2] = func_00192568() % 30 - func_00192568() % 30;
        break;
    case 1:
        D_001ED354[0][index].delay = func_00192568() % 200 + 100;
        D_001ED354[0][index].lifetime = func_00192568() % 15 + 10;
        D_001ED354[0][index].velocity[0] = (float)(func_00192568() % 10) + 5.0f;
        D_001ED354[0][index].velocity[1] = 0;
        D_001ED354[0][index].velocity[2] = func_00192568() % 10 - func_00192568() % 10;
        D_001ED354[0][index].state = 0;
        D_001ED354[0][index].step = func_00192568() % 5 + 1;
        D_001ED354[0][index].intensity = func_00192568() % 200 + 60;
        D_001ED354[0][index].red = func_00192568() % 128 + 64;
        D_001ED354[0][index].green = func_00192568() % 128 + 128;
        D_001ED354[0][index].blue = func_00192568() % 128 + 128;
        break;
    }
}
