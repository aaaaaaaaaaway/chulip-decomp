#include "game/camera.h"

void func_0018A680(void *destination, const void *source);
void func_001010B8(
    void *field_90,
    void *field_D0,
    void *field_190,
    void *field_40,
    float value_0,
    float value_1,
    float value_2,
    float value_3,
    float value_4,
    float value_5,
    float value_6,
    float value_7,
    float value_8);
void func_00103DD0(void *destination, void *object);
void func_0018A400(void *destination, const void *source, const void *transform);

void func_00103CF8(CameraState *destination, const CameraState *source) {
    *destination = *source;
}

void func_00103D20(void *object, const void *source) {
    func_0018A680((unsigned char *)object + 0x40, source);
}

void func_00103D40(
    void *object,
    float value_0,
    float value_1,
    float value_2,
    float value_3,
    float value_4,
    float value_5,
    float value_6,
    float value_7,
    float value_8) {
    unsigned char *base = object;

    func_001010B8(
        base + 0x90,
        base + 0xD0,
        base + 0x190,
        base + 0x40,
        value_0,
        value_1,
        value_2,
        value_3,
        value_4,
        value_5,
        value_6,
        value_7,
        value_8);
}

void func_00103D78(void *object) {
    unsigned char *base = object;
    void *transform = base + 0x50;

    func_00103DD0(transform, object);
    func_0018A400(base + 0x110, base + 0x90, transform);
    func_0018A400(base + 0x150, base + 0xD0, transform);
}
