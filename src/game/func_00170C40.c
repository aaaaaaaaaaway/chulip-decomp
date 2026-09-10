/* Test the wrapped facing difference between an object and the reference position. */
struct Entry {
    unsigned char pad[110];
    unsigned short kind;
    unsigned char tail[80];
};
extern int D_001ED6C0;
extern int func_00158868(unsigned short kind, float *position);
extern float D_002D8BB0[4];
extern float func_00154720(int index);
extern float func_001280C0(float x, float z);
extern int abs(int value);

int func_00170C40(unsigned short index) {
    float position[4];
    float heading, difference;
    func_00158868(((struct Entry *)D_001ED6C0)[index].kind, position);
    heading = func_00154720(0);
    difference = func_001280C0(position[0] - D_002D8BB0[0],
                                    position[2] - D_002D8BB0[2]) - heading;
    if (difference < -3.1415927f) {
        difference += 6.2831855f;
    }
    if (difference > 3.1415927f) {
        difference -= 6.2831855f;
    }
    if (314.15927f - abs((int)(difference * 100.0f)) < 157.07964f) {
        return 1;
    }
    return 0;
}
