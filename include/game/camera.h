#ifndef CHULIP_GAME_CAMERA_H
#define CHULIP_GAME_CAMERA_H

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct CameraState {
    Vec3f position;
    unsigned char unknown_0C[0x24];
    float field_30;
    float field_34;
} CameraState;

extern CameraState D_001EDE00;
extern float D_001EC884;
extern float D_001EC888;

#endif
