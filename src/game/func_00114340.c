extern float D_001EE190[];

float func_0018B210(float angle);
float func_0018B2F8(float angle);

void func_00114340(void)
{
    int i;
    int j;
    float angle;
    float *vertices;

    for (j = 0; j < 5; j++) {
        vertices = (float *)(j * 0x210 + (int)D_001EE190);
        for (i = 0; i < 33; i++) {
            angle = (float)i * 3.14159274f * 0.0625f;
            vertices[i * 4] = func_0018B210(angle) * 10000.0f;
            vertices[i * 4 + 1] =
                (float)(j - 2) * 3.14159274f * 0.0625f * 10000.0f;
            vertices[i * 4 + 2] = func_0018B2F8(angle) * 10000.0f;
            vertices[i * 4 + 3] = 1.0f;
        }
    }
}
