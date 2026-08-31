#include "game/camera.h"

extern Vec4f D_001EDDC0;

float D_001EC880 __attribute__((section(".sdata"))) = -999.0f;
float D_001EC884 __attribute__((section(".sdata"))) = 0.0f;
float D_001EC888 __attribute__((section(".sdata"))) = 0.0f;
int D_001EC88C __attribute__((section(".sdata"))) = 0;

float func_00127F80(float y, float x);
void func_00136AF8(int index, int enabled);

void func_00101928(float y_offset, float angle_offset) {
    D_001EC880 += angle_offset;
    D_001EDE00.position.y += y_offset;

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101978(float y_offset, float angle_offset) {
    D_001EDE00.position.y += y_offset;
    D_001EC880 += angle_offset;
    D_001EDE00.vector_30.x =
        -(func_00127F80(-(D_001EDE00.position.y - D_001EDDC0.y),
                         D_001EC880) + 1.5707964f);

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}
