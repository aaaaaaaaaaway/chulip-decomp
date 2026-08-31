typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector;

extern void func_00158960(unsigned short index, int mode, Vector *out);
extern void func_001280C0(float x, float z);

void func_001586F0(unsigned short first, unsigned short second) {
    Vector origin;
    Vector target;

    func_00158960(first, 4, &origin);
    func_00158960(second, 4, &target);
    func_001280C0(origin.x - target.x, origin.z - target.z);
}
