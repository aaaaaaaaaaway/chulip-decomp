typedef struct {
    int phase;
    int life;
    int pad08;
    int pad0C;
    float x;
    float y;
    float z;
    int pad1C;
    float vx;
    float vy;
    float vz;
    int pad2C;
    float ox;
    float oy;
    float oz;
    int pad3C;
    int spreadx;
    int spready;
    int spreadz;
} Emitter;

extern int D_001ED1A8;

int func_00192568(void);

void func_00112860(int index, int life) {
    Emitter *e;

    e = (Emitter *)(D_001ED1A8 + index * 0x60);
    e->phase = (func_00192568() - func_00192568()) % (life / 8);
    e->life = life;
    e->x = e->ox;
    e->y = e->oy;
    e->z = e->oz;
    e->vx = 0.0f;
    e->vy = 0.0f;
    e->vz = 0.0f;
    if (e->spreadx != 0) {
        e->x += (float)((func_00192568() - func_00192568()) % e->spreadx);
        e->vx += (float)((func_00192568() - func_00192568()) % e->spreadx);
    }
    if (e->spready != 0) {
        e->y += (float)((func_00192568() - func_00192568()) % e->spready);
        e->vy += (float)((func_00192568() - func_00192568()) % e->spready);
    }
    if (e->spreadz != 0) {
        e->z += (float)((func_00192568() - func_00192568()) % e->spreadz);
        e->vz += (float)((func_00192568() - func_00192568()) % e->spreadz);
    }
}
