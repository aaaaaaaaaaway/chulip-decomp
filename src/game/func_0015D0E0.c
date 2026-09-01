typedef struct Vec4 {
    float x;
    int y;
    float z;
    float w;
} Vec4;

float func_00154720(unsigned short id);
float func_0018B2F8(float angle);
float func_0018B210(float angle);
void func_00155FE0(unsigned short index, Vec4 *v);

void func_0015D0E0(unsigned short index, unsigned short id, Vec4 *v) {
    float a = func_00154720(id) + 3.1415927f;

    if (a > 3.1415927f) {
        a -= 6.2831855f;
    }
    v->x = v->x * func_0018B2F8(a);
    v->y = 0;
    v->z = v->z * func_0018B210(a);
    v->w = 1.0f;
    func_00155FE0(index, v);
}
