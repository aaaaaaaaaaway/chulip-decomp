typedef float Matrix[4][4] __attribute__((aligned(16)));
extern void func_0018A6F8(Matrix);
extern void func_0018A400(Matrix, Matrix, Matrix);
void func_001010B8(Matrix projection, Matrix clip, Matrix viewport, const float *extent,
                   float focal, float scale_x, float scale_y, float center_x, float center_y,
                   float depth_min, float depth_max, float near_z, float far_z) {
    Matrix screen;
    float az, cz, right, top, viewport_x, viewport_y;
    cz = (-depth_max * near_z + depth_min * far_z) / (-near_z + far_z);
    az = far_z * near_z * (-depth_min + depth_max) / (-near_z + far_z);
    right = near_z * extent[0] / focal;
    top = near_z * extent[1] / focal;
    func_0018A6F8(projection);
    projection[0][0] = focal;
    projection[1][1] = focal;
    projection[3][2] = 1.0f;
    projection[2][3] = 1.0f;
    projection[2][2] = 0.0f;
    projection[3][3] = 0.0f;
    func_0018A6F8(screen);
    screen[0][0] = scale_x;
    screen[1][1] = scale_y;
    screen[2][2] = az;
    screen[3][2] = cz;
    screen[3][0] = center_x;
    screen[3][1] = center_y;
    func_0018A400(projection, screen, projection);
    func_0018A6F8(clip);
    clip[3][3] = 0.0f;
    clip[2][3] = 1.0f;
    clip[2][2] = (far_z + near_z) / (far_z - near_z);
    clip[3][2] = (far_z * near_z * -2.0f) / (far_z - near_z);
    clip[1][1] = (near_z * 2.0f) / (top * 2.0f);
    clip[0][0] = (near_z * 2.0f) / (right * 2.0f);
    func_0018A6F8(viewport);
    viewport_x = (focal * scale_x * right) / near_z;
    viewport_y = (focal * scale_y * top) / near_z;
    viewport[3][3] = 1.0f;
    viewport[3][0] = center_x;
    viewport[3][1] = center_y;
    viewport[2][2] = (-depth_max + depth_min) * 0.5f;
    viewport[3][2] = (depth_max + depth_min) * 0.5f;
    viewport[0][0] = viewport_x;
    viewport[1][1] = viewport_y;
}
