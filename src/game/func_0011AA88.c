typedef struct {
    float scale;   /* 0x00 */
    float half;    /* 0x04 */
    float angle;   /* 0x08 */
    float radius;  /* 0x0C */
    float x;       /* 0x10 */
    float y;       /* 0x14 */
    float z;       /* 0x18 */
    float dx;      /* 0x1C */
    float dy;      /* 0x20 */
    float dz;      /* 0x24 */
    int active;    /* 0x28 */
    int unk2C;     /* 0x2C */
    int delay;     /* 0x30 */
    int unk34;     /* 0x34 */
} Particle;

extern Particle D_001FA340[];

extern int D_001ED1F8;
extern int D_001ED204;
extern int D_001ED208;
extern int D_001ED20C;
extern int D_001ED210;

extern int func_00192568(void);
extern void func_0011AE00(void);
extern void func_00112F40(void (*handler)(void));
extern void func_00112EB0(void (*handler)(void), int count, int arg);

int func_0011AA88(int a, int b, int c) {
    int i;
    int start;
    int count;

    for (i = 0; i < 30; i++) {
        D_001FA340[i].x = (float)((func_00192568() % 100 - func_00192568() % 100) * 16);
        D_001FA340[i].y = (float)((func_00192568() % 50 - func_00192568() % 50) * 16);
        D_001FA340[i].z = 0.0f;
        D_001FA340[i].dx = -D_001FA340[i].x;
        D_001FA340[i].dy = -D_001FA340[i].y;
        D_001FA340[i].dz = -D_001FA340[i].z;
        D_001FA340[i].unk2C = 0;
        D_001FA340[i].delay = (i % 10) * 5;
        D_001FA340[i].angle = (float)((i * 259 + func_00192568() % 360) % 360);
        D_001FA340[i].radius = (float)(func_00192568() % 700 + 300);
        D_001FA340[i].active = 0;
        D_001FA340[i].unk34 = 0;
        D_001FA340[i].scale = (float)(func_00192568() % 50) / 100.0f + 0.5f;
        D_001FA340[i].half = D_001FA340[i].scale * 0.5f;
    }

    count = b < 10;
    count += (b % 100) / 10;
    count += b / 100;
    start = (b % 100) / 10;
    for (i = start; i < count; i++) {
        D_001FA340[i].active = 1;
        D_001FA340[i].radius = 1000.0f;
        D_001FA340[i].delay += 40;
    }

    D_001ED204 = a;
    D_001ED208 = 1;
    D_001ED210 = c;
    D_001ED1F8 = 0;
    D_001ED20C = 0;
    func_00112F40(func_0011AE00);
    func_00112EB0(func_0011AE00, count, 0);
    return 0;
}
