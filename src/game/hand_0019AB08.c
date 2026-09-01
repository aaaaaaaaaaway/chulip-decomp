/* One object: two accessors over one record, at 0x0C/0x10 and 0x14/0x18. */
typedef struct {
    int pad[3];
    int f0C;
    int f10;
    int f14;
    int f18;
} S;

extern S D_002E0F18;

int func_0019AB08(int a, int b) {
    int old = D_002E0F18.f14;
    D_002E0F18.f14 = a;
    D_002E0F18.f18 = b;
    return old;
}

int func_0019AB20(int a, int b) {
    int old = D_002E0F18.f0C;
    D_002E0F18.f0C = a;
    D_002E0F18.f10 = b;
    return old;
}
