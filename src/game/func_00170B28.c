/* Test the wrapped facing difference between the reference positions. */
extern float D_002D8BA0[4], D_002D8BB0[4];
extern float func_00154720(int index);
extern float func_001280C0(float x, float z);
extern int abs(int value);

int func_00170B28(void) {
    float heading = func_00154720(0);
    float difference = func_001280C0(D_002D8BA0[0] - D_002D8BB0[0],
                                    D_002D8BA0[2] - D_002D8BB0[2]) - heading;
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
