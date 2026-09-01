extern float D_001EE190[];
float func_0018B210(float angle);
float func_0018B2F8(float angle);

void func_00114340(void) {
    int i;
    int j;
    float a;
    float *p;

    for (j = 0; j < 5; j++) {
        p = (float *)(j * 0x210 + (int)D_001EE190);
        for (i = 0; i < 33; i++) {
            a = (float)i * 3.14159274f * 0.0625f;
            p[0] = func_0018B210(a) * 10000.0f;
            p[1] = (float)(j - 2) * 3.14159274f * 0.0625f * 10000.0f;
            p[2] = func_0018B2F8(a) * 10000.0f;
            p[3] = 1.0f;
            p += 4;
        }
    }
}
