/* Mark a kind whose radius overlaps the player and return the planar distance. */
struct Entry {
    unsigned int flags[2];
    unsigned char pad08[102];
    unsigned short kind;
    unsigned char pad70[50];
    unsigned short radius;
    unsigned char tail[28];
};
extern int D_001ED6C0;
extern float D_002D8BB0[4];
extern float D_001ED828, D_001ED82C[1];
extern int func_00173148(unsigned short kind);
extern int func_00154398(unsigned short kind);
extern int func_00158868(unsigned short kind, float *position);
extern int abs(int value);
extern float sqrtf(float value);

int func_00170ED0(unsigned short kind) {
    int index = func_00173148(kind);
    float position[4];
    float dx, dz, radius;

    if (func_00154398(kind)) {
        func_00158868(0, D_002D8BB0);
        func_00158868(kind, position);
        dx = D_002D8BB0[0] - position[0];
        dz = D_002D8BB0[2] - position[2];
        radius = ((struct Entry *)D_001ED6C0)[index].radius;
        if (abs((int)dx) < radius && abs((int)dz) < radius) {
            D_001ED828 = sqrtf(dx * dx + dz * dz);
            if (D_001ED828 < radius) {
                D_001ED82C[0] = radius - D_001ED828;
                *(unsigned int *)(D_001ED6C0 + index * 192 + 4) |= 0x20000000;
                return (int)D_001ED828;
            }
        }
    }
    return 0;
}
