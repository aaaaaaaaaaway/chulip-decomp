#include "game/camera.h"

extern void func_00136AF8(int channel, int enabled);

void func_00101A00(const Vec3f *offset) {
    D_001EDDE0.x += offset->x;
    D_001EDDE0.y += offset->y;
    D_001EDDE0.z += offset->z;

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}
