typedef struct {
    long lo;
    long hi;
} Qword;

typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    float f24;
    float f28;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Params;

extern int func_00113228(Qword *dst, int arg);
extern int func_00117E58(Qword *dst, Params *params);

int func_00185018(Qword *dst, int a, int b, int c, int arg) {
    Params params;
    int used = func_00113228(dst, arg);

    params.f04 = a;
    params.f08 = b;
    params.f0C = c;
    params.a = 0x80;
    params.f14 = 0xE00;
    params.f1C = 0x200;
    params.f24 = 1.0f;
    params.f28 = 0.5f;
    params.f00 = 0;
    params.r = 0x80;
    params.g = 0x80;
    params.b = 0x80;
    params.f10 = 0;
    params.f18 = 0x200;
    params.f20 = 0;
    return used + func_00117E58(&dst[used], &params);
}
