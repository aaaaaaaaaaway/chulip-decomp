#include "game/camera.h"

extern void func_0018A680(void *destination, const void *source);

void func_00101630(const void *position, const void *orientation) {
    func_0018A680(&D_001EDE00.position, position);
    func_0018A680(&D_001EDE00.vector_30, orientation);
}
