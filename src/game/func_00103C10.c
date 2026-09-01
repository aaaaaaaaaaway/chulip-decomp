#include "game/camera.h"

extern Vec4f D_001EDDC0;

void func_00105150(Vec4f *position, int angle);
int func_00128158(float x, float z);
void func_001039D8(Vec4f *position);
void func_0018A680(void *destination, const void *source);
float func_0018B210(float angle);
float func_0018B2F8(float angle);
int abs(int value);

int func_00103C10(void) {
    Vec4f position;
    float angle;
    float distance;
    float x_offset;
    float z_offset;
    int difference;

    func_0018A680(&position, &D_001EDDC0);
    func_00105150(&position, 0x8000);

    angle = -D_001EDE00.vector_30.x + 1.5707964f;
    difference = abs((int)(D_001EDDC0.y - D_001EDE00.position.y));
    distance = (float)difference;
    distance *= func_0018B2F8(angle);
    distance *= func_0018B210(angle);
    x_offset = distance * func_0018B2F8(D_001EDE00.vector_30.y);
    z_offset = distance * func_0018B210(D_001EDE00.vector_30.y);

    func_001039D8(&position);
    return func_00128158(position.x - x_offset, position.z - z_offset);
}
