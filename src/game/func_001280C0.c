extern float func_00127F80(void);

float func_001280C0(void) {
    float angle;

    angle = -func_00127F80() + 1.5707963705062866f;
    if (angle < -3.1415927410125732f) {
        angle = angle + 6.2831854820251465f;
    }
    if (3.1415927410125732f < angle) {
        angle = angle - 6.2831854820251465f;
    }
    return angle;
}
