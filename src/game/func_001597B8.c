typedef struct {
    unsigned char pad00[0x24];
    int handle;
    unsigned char pad28[0x18];
} ActorSlot;

extern ActorSlot D_002ABA40[];

extern void func_001018E8(float *);
extern void func_001039D8(float *);
extern void func_00156B00(int, int, float);
extern float func_0018B2F8(float);
extern float func_0018B210(float);
extern void func_0015BE88(int, int, int);
extern void func_00156BC8(int, float *);

void func_001597B8(unsigned short id, unsigned char mode) {
    float base[4];
    float result[4];
    float angle[4];

    func_001018E8(angle);
    func_001039D8(base);
    switch (mode) {
    case 0:
        break;
    case 1:
        func_00156B00(id, 0, angle[2]);
        func_00156B00(id, 1, angle[1]);
        result[0] = base[0] + func_0018B2F8(angle[1]) * 600.0f;
        result[2] = base[2] + func_0018B210(angle[1]) * 600.0f;
        result[1] = base[1] - func_0018B2F8(angle[0]) * 1400.0f;
        if ((D_002ABA40 + id)->handle != 0) {
            func_0015BE88(id, 2, 1);
        }
        func_00156BC8(id, result);
        break;
    }
}
