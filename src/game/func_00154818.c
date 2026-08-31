typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector;

extern void func_00158868(unsigned short index, Vector *out);

void func_00154818(unsigned short first, unsigned short second, float *outX, float *outZ) {
    Vector origin;
    Vector target;

    func_00158868(first, &origin);
    func_00158868(second, &target);
    *outX = target.x - origin.x;
    *outZ = target.z - origin.z;
}
