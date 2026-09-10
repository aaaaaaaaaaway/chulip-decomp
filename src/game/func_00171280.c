/* Select the nearest eligible kind within the distance and facing limits. */
struct Entry {
    unsigned char pad[110];
    unsigned short kind;
    unsigned char pad70[40];
    unsigned short flags;
    unsigned char tail[38];
};
struct ObjectList {
    unsigned char pad[16];
    unsigned short count;
};
extern struct ObjectList D_002D8840;
extern int D_001ED6C0;
extern int func_00158868(unsigned short kind, float *position);
extern int func_00154398(unsigned short kind);
extern float func_00154720(int index);
extern float func_001280C0(float x, float z);
extern float sqrtf(float value);
extern int abs(int value);

int func_00171280(void) {
    float position[4], origin[4];
    int i;
    int nearest = 30000;
    int selected = -1;
    float dx, dz, heading, bearing;
    int distance;

    func_00158868(0, origin);
    for (i = 1; i < D_002D8840.count; i++) {
        if ((((struct Entry *)D_001ED6C0)[i].flags & 0x80) &&
            func_00154398(((struct Entry *)D_001ED6C0)[i].kind)) {
            func_00158868(((struct Entry *)D_001ED6C0)[i].kind, position);
            dx = position[0] - origin[0];
            dz = position[2] - origin[2];
            heading = func_00154720(0);
            bearing = func_001280C0(dx, dz);
            distance = (int)sqrtf(dx * dx + dz * dz);
            if ((float)distance < 168.0f && distance < nearest &&
                314.15927f - abs((int)(bearing * 100.0f - heading * 100.0f)) < 157.07964f) {
                nearest = distance;
                selected = ((struct Entry *)D_001ED6C0)[i].kind;
            }
        }
    }
    return selected == -1 ? 0 : selected;
}
