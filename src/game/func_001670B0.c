void func_0010E6D8(int id, unsigned char flag);
void func_0010E938(int id, float x, float y, float z);
void func_0010E6F8(short id, int mode);

void func_001670B0(int id, const float *v, unsigned char flag) {
    func_0010E6D8(id, flag);
    if (flag != 0) {
        func_0010E938(id, v[0], v[1], v[2]);
    }
    func_0010E6F8((short)id, 0);
}
