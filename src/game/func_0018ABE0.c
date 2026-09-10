typedef float Vector[4];
typedef float Matrix[4][4];
extern void func_0018A6F8(Matrix);
extern void func_0018A448(Vector, const Vector, const Vector);
extern void func_0018A490(Vector, const Vector);
extern void func_0018A638(Vector, const Vector, float);
extern void func_0018A650(Matrix, Matrix, const Vector);
extern void func_0018A518(Matrix, Matrix);
extern void func_0018A4D0(Matrix, Matrix);
extern void func_0018A400(Matrix, Matrix, Matrix);

void func_0018ABE0(Matrix output, float distance, float scale_x, float scale_y, float center_x,
                   float center_y, float depth_min, float depth_max, float near_z, float far_z) {
    Matrix transform;
    float cz = (-depth_max * near_z + depth_min * far_z) / (-near_z + far_z);
    float az = far_z * near_z * (-depth_min + depth_max) / (-near_z + far_z);
    func_0018A6F8(output);
    output[0][0] = distance;
    output[1][1] = distance;
    output[2][2] = 0.0f;
    output[3][3] = 0.0f;
    output[3][2] = 1.0f;
    output[2][3] = 1.0f;
    func_0018A6F8(transform);
    transform[0][0] = scale_x;
    transform[1][1] = scale_y;
    transform[2][2] = az;
    transform[3][0] = center_x;
    transform[3][1] = center_y;
    transform[3][2] = cz;
    func_0018A400(output, transform, output);
}
