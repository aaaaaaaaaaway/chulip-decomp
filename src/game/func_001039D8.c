#include "game/camera.h"

struct Session_00136AE8 {
    unsigned char field_0x00[0x45];
    unsigned char field_0x45;
};

extern struct Session_00136AE8 *func_00136AE8(void);
extern void func_0018A5F0(Vec3f *out, Vec3f *a, CameraState *b);
extern void func_0018A680(Vec3f *out, CameraState *b);
extern float func_0014D568(float x, float z);
extern Vec3f D_001EDDC0;

void func_001039D8(Vec3f *out) {
    float x;
    float z;
    struct Session_00136AE8 *session = func_00136AE8();

    switch (session->field_0x45) {
    case 1:
    case 5:
        func_0018A5F0(out, &D_001EDDC0, &D_001EDE00);
        break;
    case 2:
        out->x = D_001EDDC0.x;
        out->z = D_001EDDC0.z;
        out->y = -3000.0f;
        break;
    case 3:
    case 4:
        x = D_001EDDC0.x;
        out->x = x;
        z = D_001EDDC0.z + -1000.0f;
        out->z = z;
        out->y = func_0014D568(x, z) + -893.3333f;
        break;
    case 6:
    case 7:
    case 8:
        func_0018A680(out, &D_001EDE00);
        break;
    }
}
