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

void func_0018AAB8(Matrix output, const Vector first, const Vector second, const Vector third) {
    Vector direction;
    func_0018A638(direction, first, -1.0f);
    func_0018A490(output[0], direction);
    func_0018A638(direction, second, -1.0f);
    func_0018A490(output[1], direction);
    func_0018A638(direction, third, -1.0f);
    func_0018A490(output[2], direction);
    output[3][0] = output[3][1] = output[3][2] = 0.0f;
    output[3][3] = 1.0f;
    func_0018A4D0(output, output);
}
