/* Find an active kind whose planar radius overlaps the supplied position. */
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
extern struct ObjectList D_002D8840;
extern float D_001ED828;
extern float D_001ED82C[1];
extern unsigned long *func_00136AE8(void);
extern int func_00154398(unsigned short kind);
extern int func_00158960(unsigned short kind, unsigned char point, float *position);
extern int abs(int value);
extern float sqrtf(float value);

int func_00170738(unsigned short index, float *position) {
    int i;
    float point[4];
    float dx, dz, radius;

    if (((int)(*func_00136AE8() >> 9) & 1UL) == 1) {
        return -1;
    }
    for (i = 0; i < D_002D8840.count; i++) {
        if (index == i) {
            continue;
        }
        if (!func_00154398(((struct Entry *)D_001ED6C0)[i].kind) && i != 0) {
            continue;
        }
        if ((((struct Entry *)D_001ED6C0)[i].flags[0] & 1) == 0) {
            continue;
        }
        func_00158960(((struct Entry *)D_001ED6C0)[i].kind, 4, point);
        dx = point[0] - position[0];
        dz = point[2] - position[2];
        if (((struct Entry *)D_001ED6C0)[i].kind == 0) {
            radius = ((struct Entry *)D_001ED6C0)[index].radius;
        } else {
            radius = ((struct Entry *)D_001ED6C0)[i].radius;
        }
        if (abs((int)dx) < radius && abs((int)dz) < radius) {
            D_001ED828 = sqrtf(dx * dx + dz * dz);
            if (D_001ED828 < radius) {
                D_001ED82C[0] = radius - D_001ED828;
                if (((struct Entry *)D_001ED6C0)[i].kind == 0) {
                    *(unsigned int *)(D_001ED6C0 + index * 192 + 4) |= 0x20000000;
                }
                if (((struct Entry *)D_001ED6C0)[index].kind == 0) {
                    *(unsigned int *)(D_001ED6C0 + i * 192 + 4) |= 0x20000000;
                }
                return ((struct Entry *)D_001ED6C0)[i].kind;
            }
        }
    }
    return -1;
}
