typedef struct {
    unsigned int flags;
    char pad04[4];
    int angle;
    char pad0C[0x14];
    float mat[4];
    char pad30[0x85];
    unsigned char kind;
    char padB6[0xA];
} Ent001782E0;

extern Ent001782E0 *D_001ED6C0;
extern unsigned short D_002D8840[];

int func_00128158(float x, float z);
unsigned short func_00173148();
int func_00156BC8();
int func_0018A680();

void func_001782E0(unsigned short kind, unsigned short id) {
    Ent001782E0 *e;
    unsigned short index;
    float *mat;
    int i;

    for (i = 0; i < D_002D8840[8]; i++) {
        e = &D_001ED6C0[i];
        if ((e->flags & 0x80000000) != 0 && e->kind == kind) {
            mat = e->mat;
            func_00156BC8(id, mat);
            index = func_00173148(id);
            func_0018A680(D_001ED6C0[index].mat, mat);
            D_001ED6C0[index].angle = func_00128158(e->mat[0], e->mat[2]);
            return;
        }
    }
}
