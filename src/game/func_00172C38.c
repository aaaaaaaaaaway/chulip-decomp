typedef struct {
    float x;
    float y;
    float z;
} Vec00172C38;

typedef struct {
    char pad00[8];
    int angle;
    char pad0C[0x14];
    char mat[0xA0];
} Ent00172C38;

extern Ent00172C38 *D_001ED6C0;

int func_00128158(float x, float z);
unsigned short func_00173148();
int func_00156BC8();
int func_0018A680();

void func_00172C38(unsigned short id, Vec00172C38 *pos) {
    unsigned short index;

    index = func_00173148(id);
    if (index != 0xFFFF) {
        func_00156BC8(id, pos);
        func_0018A680(D_001ED6C0[index].mat, pos);
        D_001ED6C0[index].angle = func_00128158(pos->x, pos->z);
    }
}
