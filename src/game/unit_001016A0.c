extern void func_00136AF8(int, int);

#include "game/camera.h"
void func_001016A0(float amount) {
    D_001EDE00.vector_30.x -= amount;
    if (D_001EDE00.vector_30.x < -3.1415927f) {
        D_001EDE00.vector_30.x += 6.2831855f;
    }
    if (D_001EDE00.vector_30.x > 3.1415927f) {
        D_001EDE00.vector_30.x -= 6.2831855f;
    }
    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

#include "game/camera.h"
void func_00101748(float amount) {
    D_001EDE00.vector_30.y -= amount;
    if (D_001EDE00.vector_30.y < -3.1415927f) {
        D_001EDE00.vector_30.y += 6.2831855f;
    }
    if (D_001EDE00.vector_30.y > 3.1415927f) {
        D_001EDE00.vector_30.y -= 6.2831855f;
    }
    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}
