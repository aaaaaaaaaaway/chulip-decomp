#include "game/camera.h"

typedef struct GameState {
    unsigned char unknown_00[0x45];
    unsigned char camera_mode;
} GameState;

extern GameState *func_00136AE8(void);
extern void func_00136AF8(int index, int enabled);
extern float func_0018B210(float angle);
extern float func_0018B2F8(float angle);

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
