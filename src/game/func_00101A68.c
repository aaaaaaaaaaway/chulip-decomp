#include "game/camera.h"

extern void func_00136AF8(int channel, int enabled);

void func_00101A68(const Vec3f *offset) {
    D_001EDE00.position.x += offset->x;
    D_001EDE00.position.y += offset->y;
    D_001EDE00.position.z += offset->z;

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}
