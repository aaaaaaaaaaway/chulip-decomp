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

void func_0018AA08(Matrix output, const Vector position, const Vector direction, const Vector up) {
    Matrix frame;
    Vector cross;
    func_0018A6F8(frame);
    func_0018A448(cross, up, direction);
    func_0018A490(frame[0], cross);
    func_0018A490(frame[2], direction);
    func_0018A448(frame[1], frame[2], frame[0]);
    func_0018A650(frame, frame, position);
    func_0018A518(output, frame);
}
