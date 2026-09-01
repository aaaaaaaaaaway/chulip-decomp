typedef struct {
    float x;
    float y;
    float z;
} Vec3;

extern void func_0018A798(void *destination, void *source, float angle);
extern void func_0018A8E8(void *destination, void *source, float angle);
extern void func_0018A840(void *destination, void *source, float angle);

void func_0018A990(void *destination, void *source, const Vec3 *angles) {
    func_0018A798(destination, source, angles->z);
    func_0018A8E8(destination, destination, angles->y);
    func_0018A840(destination, destination, angles->x);
}
