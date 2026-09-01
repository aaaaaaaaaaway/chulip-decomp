typedef struct {
    char pad0[6];
    short mode;
} DisplayInfo;

extern DisplayInfo D_001E2FD0[];

DisplayInfo *func_00187498(void) {
    return D_001E2FD0;
}
