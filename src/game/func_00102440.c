#include "game/camera.h"

void func_00136AF8(int channel, int enabled);
float func_0018B210(float angle);
float func_0018B2F8(float angle);

void func_00102440(float y, float radius) {
    D_001EDE00.position.y = y;
    D_001EDE00.position.x =
        radius * func_0018B2F8(D_001EDE00.vector_30.y) + D_001EC884;
    D_001EDE00.position.z =
        radius * func_0018B210(D_001EDE00.vector_30.y) + D_001EC888;
    D_001EC880 = radius;

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}
