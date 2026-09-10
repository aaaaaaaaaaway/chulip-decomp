typedef struct {
    float x, y, z, w;
} Vec4;
typedef struct {
    int frame, mode;
    float speed;
    unsigned char unknown0C[4];
    Vec4 position[400];
    Vec4 velocity[400];
} Rain;
extern Rain *D_001ED250[1];
extern int D_001ED24C;
extern void *func_00151A00(int);
extern int func_00192568(void);
extern int func_00120F48(char *, int, int);
extern void func_00112EB0(void (*)(void), int, int);

void func_00120C68(void) {
    int i;
    D_001ED250[0] = func_00151A00(sizeof(Rain));
    D_001ED24C = 1;
    D_001ED250[0]->mode = -1;
    D_001ED250[0]->frame = 0;
    D_001ED250[0]->speed = 2.0f;
    for (i = 0; i < 400; i++) {
        D_001ED250[0]->position[i].x = (float)(func_00192568() % 5 - func_00192568() % 5);
        D_001ED250[0]->position[i].y = 0.0f;
        D_001ED250[0]->position[i].z = (float)(func_00192568() % 5 - func_00192568() % 5);
        D_001ED250[0]->position[i].w = (float)(func_00192568() % 10 + i / 4);
        D_001ED250[0]->velocity[i].x = (float)(func_00192568() % 15 - func_00192568() % 15) / 10.0f;
        D_001ED250[0]->velocity[i].y = -D_001ED250[0]->speed;
        D_001ED250[0]->velocity[i].z = (float)(func_00192568() % 15 - func_00192568() % 15) / 10.0f;
        D_001ED250[0]->velocity[i].w = 0.0f;
    }
    func_00112EB0((void (*)(void))func_00120F48, 0, 0);
}
