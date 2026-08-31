#include "game/camera.h"

extern void func_00136AF8(int index, int enabled);

void func_00101BA0(const Vec3f *position) {
    D_001EDE00.position.x = position->x;
    D_001EDE00.position.y = position->y;
    D_001EDE00.position.z = position->z;
    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}
