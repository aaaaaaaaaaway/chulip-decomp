float func_00100EF0(float t, float a, float b) {
    if (t < -1.0f) {
        t = -1.0f;
    }
    if (t > 1.0f) {
        t = 1.0f;
    }
    return (1.0f - t) * a + t * b;
}
