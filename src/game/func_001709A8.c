/* Find the first active object radius containing the current kind position. */
struct Entry {
    unsigned int flags[2];
    unsigned char pad08[102];
    unsigned short kind;
    unsigned char pad70[50];
    unsigned short radius;
    unsigned char tail[28];
};
struct ObjectList {
    unsigned char pad[16];
    unsigned short count;
};
extern int D_001ED6C0;
extern struct Entry *D_001ED7E0;
extern struct ObjectList D_002D8840;
extern int func_00154398(unsigned short kind);
extern int func_00158868(unsigned short kind, float *position);
extern int abs(int value);
extern float sqrtf(float value);

int func_001709A8(float *position) {
    int i;
    float point[4];
    float dx, dz, radius;

    for (i = 0; i < D_002D8840.count; i++) {
        if ((((struct Entry *)D_001ED6C0)[i].flags[0] & 1) &&
            func_00154398(((struct Entry *)D_001ED6C0)[i].kind)) {
            func_00158868(D_001ED7E0->kind, point);
            dx = point[0] - position[0];
            dz = point[2] - position[2];
            radius = ((struct Entry *)D_001ED6C0)[i].radius;
            if (abs((int)dx) < radius && abs((int)dz) < radius) {
                if (sqrtf(dx * dx + dz * dz) < radius) {
                    return ((struct Entry *)D_001ED6C0)[i].kind;
                }
            }
        }
    }
    return -1;
}
