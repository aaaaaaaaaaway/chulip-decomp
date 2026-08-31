typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector;

extern void func_00158960(unsigned short index, int mode, Vector *out);

int func_00158908(unsigned short index, Vector *out) {
    func_00158960(index, 3, out);
    out->w = 1.0f;
    out->y = out->y - 50.0f;
    return 0;
}
