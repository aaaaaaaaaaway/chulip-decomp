typedef struct {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) Vec4f;

extern short D_001ED220;
extern short D_001ED222;
extern int D_001FA9D4;

float func_0014D568(float x, float z);
void func_00114730(int kind, Vec4f *position, int color);

void func_0011EE78(void) {
    Vec4f position;
    int phase;
    float ground;

    phase = D_001FA9D4 % 0x20;
    position.x = (float)D_001ED220;
    position.z = (float)D_001ED222;
    ground = func_0014D568((float)D_001ED220, (float)D_001ED222);
    if (phase >= 0x10) {
        position.y = (float)(-0x178 - phase) + ground;
    } else {
        position.y = (float)(phase - 0x198) + ground;
    }
    position.w = 1.0f;
    func_00114730(2, &position, 0x80808080);
}
