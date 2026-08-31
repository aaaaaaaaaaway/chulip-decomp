#include "game/camera.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u64;

typedef struct GameState {
    u64 flags;
    u8 unknown_08[0x36];
    u16 field_3E;
    u8 unknown_40;
    u8 field_41;
    u8 unknown_42[3];
    u8 field_45;
} GameState;

typedef struct CameraSnapshot {
    u8 active;
    u8 field_41;
    u8 field_45;
    u8 unknown_03[0x0D];
    CameraState camera;
} CameraSnapshot;

extern CameraSnapshot D_001EDE40;

void func_00101330(void *position, int mode);
void func_0012E630(int value);
GameState *func_00136AE8(void);
void func_00158868(int index, void *position);

void func_00103AD0(void) {
    GameState *state = func_00136AE8();

    D_001EDE40.camera = D_001EDE00;
    D_001EDE40.field_41 = state->field_41;
    D_001EDE40.field_45 = state->field_45;
    D_001EDE40.active = 1;
}

void func_00103B38(void) {
    float position[4];
    GameState *state = func_00136AE8();

    func_00158868(0, position);
    D_001EDE00 = D_001EDE40.camera;
    state->field_45 = D_001EDE40.field_45;
    state->field_3E = 0xFFFF;
    state->flags |= 1;
    state->flags &= ~0x20000UL;
    state->flags &= ~0x4000UL;
    state->flags &= ~0x2000UL;
    state->flags |= 0x2000000000UL;
    D_001EDE40.active = 0;

    func_00158868(0, position);
    func_00101330(position, 0);
    func_0012E630(D_001EDE40.field_41);
}
