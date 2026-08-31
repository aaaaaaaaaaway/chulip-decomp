#include "game/camera.h"

extern Vec4f D_001EDDC0;

typedef struct GameState {
    unsigned char unknown_00[0x45];
    unsigned char camera_mode;
} GameState;

float D_001EC880 __attribute__((section(".sdata"))) = -999.0f;
float D_001EC884 __attribute__((section(".sdata"))) = 0.0f;
float D_001EC888 __attribute__((section(".sdata"))) = 0.0f;
int D_001EC88C __attribute__((section(".sdata"))) = 0;

float func_00127F80(float y, float x);
GameState *func_00136AE8(void);
void func_00136AF8(int index, int enabled);
void func_0018A680(void *destination, const void *source);
float func_0018B210(float angle);
float func_0018B2F8(float angle);

void func_001017F0(float amount) {
    D_001EDE00.position.y += amount;
    D_001EDE00.vector_30.x =
        -(func_00127F80(-D_001EDE00.position.y + -200.0f, D_001EC880) +
          1.5707964f);

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101868(const Vec3f *offset) {
    Vec3f *position = (Vec3f *)&D_001EDDC0;

    position->x += offset->x;
    position->y += offset->y;
    position->z += offset->z;
    func_00136AF8(0, 1);
}

float func_001018C8(void) {
    return D_001EDE00.vector_30.y;
}

float func_001018D8(void) {
    return D_001EDE00.vector_30.x;
}

void func_001018E8(void *destination) {
    func_0018A680(destination, &D_001EDE00.vector_30);
}

void func_00101908(float value) {
    D_001EDE00.vector_30.x = value;
}

void func_00101918(float value) {
    D_001EDE00.vector_30.y = value;
}

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

void func_00101A00(const Vec3f *offset) {
    D_001EDDE0.x += offset->x;
    D_001EDDE0.y += offset->y;
    D_001EDDE0.z += offset->z;

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101A68(const Vec3f *offset) {
    D_001EDE00.position.x += offset->x;
    D_001EDE00.position.y += offset->y;
    D_001EDE00.position.z += offset->z;

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101AD0(const float *offset) {
    D_001EC884 += offset[0];
    D_001EC888 += offset[2];
}

void func_00101AF8(void) {
    if (func_00136AE8()->camera_mode == 2) {
        D_001EDE00.position.x = 0.0f;
        D_001EDE00.position.z = 0.0f;
    } else {
        D_001EDE00.position.x =
            D_001EC880 * func_0018B2F8(D_001EDE00.vector_30.y) + D_001EC884;
        D_001EDE00.position.z =
            D_001EC880 * func_0018B210(D_001EDE00.vector_30.y) + D_001EC888;
    }
    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101BA0(const Vec3f *position) {
    D_001EDE00.position.x = position->x;
    D_001EDE00.position.y = position->y;
    D_001EDE00.position.z = position->z;
    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101BF0(float y, float radius) {
    D_001EC880 = radius;
    D_001EDE00.position.y = y;

    D_001EDE00.position.x =
        D_001EC880 * func_0018B2F8(D_001EDE00.vector_30.y) + D_001EC884;
    D_001EDE00.position.z =
        D_001EC880 * func_0018B210(D_001EDE00.vector_30.y) + D_001EC888;
    D_001EDE00.vector_30.x =
        -(func_00127F80(-D_001EDE00.position.y + -200.0f, D_001EC880) +
          1.5707964f);

    func_00136AF8(0, 1);
    func_00136AF8(17, 0);
}

void func_00101CA8(float x, float z) {
    D_001EC884 = x;
    D_001EC888 = z;
}

void func_00101CB8(void) {
    D_001EC884 = 0.0f;
    D_001EC888 = 0.0f;
}
