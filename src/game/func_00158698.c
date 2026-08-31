typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector;

extern void func_00158868(unsigned short index, Vector *out);
extern void func_00158960(unsigned short index, int mode, Vector *out);
extern void func_001280C0(float x, float z);

void func_00158698(unsigned short first, unsigned short second) {
    Vector origin;
    Vector target;

    func_00158868(first, &origin);
    func_00158960(second, 2, &target);
    func_001280C0(origin.x - target.x, origin.z - target.z);
}
