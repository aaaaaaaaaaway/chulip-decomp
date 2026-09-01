typedef struct {
    float x;
    float y;
    float z;
    float w;
    float u;
} Rec;

typedef struct {
    float x;
    float y;
    float z;
} Vec;

typedef struct {
    float a;
    float b;
    int c;
} Aux;

extern Rec *D_001ED7B0;

int func_001024C8();
int func_001027A8();

void func_00174B60(short index, short arg1, unsigned char id) {
    Vec pos;
    Aux aux;
    Rec *r;

    if (index == -1) {
        func_001024C8(id);
        return;
    }
    r = &D_001ED7B0[index];
    pos.x = r->x;
    pos.y = r->y;
    pos.z = r->z;
    aux.a = r->u;
    aux.b = r->w;
    aux.c = 0;
    func_001027A8(&pos, &aux, arg1);
}
