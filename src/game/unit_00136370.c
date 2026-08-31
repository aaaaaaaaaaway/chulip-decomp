extern int D_001FF1A0[];
extern int D_001FF1B0[];
extern int D_001FF8E0[];
extern int D_001FFB20[];

int func_0018A680();

int func_00136370(int arg0) {
    return func_0018A680(arg0, D_001FF1A0);
}

int func_00136390(int arg0) {
    return func_0018A680(arg0, D_001FF1B0);
}

int func_001363B0(int arg0, int arg1) {
    func_0018A680(arg0, D_001FF8E0);
    return func_0018A680(arg1, D_001FFB20);
}
