typedef struct {
    float x;
    float y;
    float z;
} Vec3001791D8;

int func_0010D490(int id, float x, float y, float z);
int func_00133E68(int id, float x, float y, float z);

void func_001791D8(unsigned short kind, unsigned short id, Vec3001791D8 *pos) {
    switch (kind) {
    case 3:
    case 0xC:
        func_00133E68(id, pos->x, pos->y, pos->z);
        break;
    case 7:
        func_0010D490(id, pos->x, pos->y, pos->z);
        break;
    }
}
