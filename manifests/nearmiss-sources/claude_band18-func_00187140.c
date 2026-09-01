extern void func_001866B0(float *value, int *out);
extern void func_00186518(int a, int b, int c, long d);

void func_00187140(float value) {
    int out[4];
    float local = value;

    func_001866B0(&local, out);
    func_00186518(out[0], out[1], out[2], (long)(unsigned int)out[3] << 30);
}
