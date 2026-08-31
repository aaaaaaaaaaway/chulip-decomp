#ifndef CHULIP_GAME_CAMERA_H
#define CHULIP_GAME_CAMERA_H

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Vec4f {
    float x;
    float y;
    float z;
    float w;
} Vec4f;

typedef struct CameraState {
    Vec3f position;
    unsigned char unknown_0C[0x24];
    Vec4f vector_30;
} __attribute__((aligned(16))) CameraState;

extern CameraState D_001EDE00;
extern Vec3f D_001EDDE0;
extern float D_001EC880;
extern float D_001EC884;
extern float D_001EC888;
extern int D_001EC88C;

#endif
