/* Measure a kind's planar distance to the reference position within its range. */
struct Entry {
    unsigned char pad[110];
    unsigned short kind;
    unsigned char pad70[48];
    unsigned short range;
    unsigned char tail[30];
};
extern int D_001ED6C0;
extern float D_002D8BB0[4];
extern int func_00154398(unsigned short kind);
extern int func_00158960(unsigned short kind, unsigned char point, float *position);
extern float sqrtf(float value);

int func_001711A0(int index) {
    float position[4];
    float dx, dz, distance;
    if (func_00154398(((struct Entry *)D_001ED6C0)[index].kind)) {
        func_00158960(((struct Entry *)D_001ED6C0)[index].kind, 4, position);
        dx = position[0] - D_002D8BB0[0];
        dz = position[2] - D_002D8BB0[2];
        distance = sqrtf(dx * dx + dz * dz);
        if (distance < (float)((struct Entry *)D_001ED6C0)[index].range) {
            return (int)distance;
        }
    }
    return 0;
}
