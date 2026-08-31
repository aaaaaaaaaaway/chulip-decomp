#include "game/camera.h"

extern Vec3f D_001EDDC0;
extern void func_00136AF8(int index, int enabled);

void func_00101868(const Vec3f *offset) {
    D_001EDDC0.x += offset->x;
    D_001EDDC0.y += offset->y;
    D_001EDDC0.z += offset->z;
    func_00136AF8(0, 1);
}
