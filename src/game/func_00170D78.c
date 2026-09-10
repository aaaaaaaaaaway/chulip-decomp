/* Test whether both kinds face each other within the supplied angular limit. */
struct Entry {
    unsigned char pad[110];
    unsigned short kind;
    unsigned char tail[80];
};
extern int D_001ED6C0;
extern struct Entry *D_001ED7E0;
extern int func_00158868(unsigned short kind, float *position);
extern float func_00154720(int index);
extern float func_001280C0(float x, float z);
extern int abs(int value);

int func_00170D78(int index, float limit) {
    float position[4], origin[4];
    float heading, other_heading, bearing, other_bearing;

    func_00158868(((struct Entry *)D_001ED6C0)[index].kind, position);
    func_00158868(0, origin);
    heading = func_00154720(0);
    other_heading = func_00154720(D_001ED7E0->kind);
    bearing = func_001280C0(position[0] - origin[0], position[2] - origin[2]);
    other_bearing = func_001280C0(origin[0] - position[0], origin[2] - position[2]);
    bearing *= 100.0f;
    heading *= 100.0f;
    limit *= 100.0f;
    if (314.15927f - abs((int)(bearing - heading)) < limit) {
        if (314.15927f - abs((int)(other_bearing * 100.0f - other_heading * 100.0f)) < limit) {
            return 1;
        }
    }
    return 0;
}
