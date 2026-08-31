void func_001074E8(int mode, int a, int *b, int *color);

void func_001074A8(int *p) {
    int color[4];

    color[0] = 0x80;
    color[1] = 0x80;
    color[2] = 0x80;
    color[3] = 0x80;
    func_001074E8(0, p[0], p + 1, color);
}
