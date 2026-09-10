void func_00111300(int index, float width, float depth, float *position, int *color);

void func_00111288(int index, char *base) {
    float position[3];
    int color[4];
    char *p;

    p = (char *)(index * 0x28 + (int)base);
    position[0] = *(float *)(p + 8);
    position[1] = *(float *)(p + 0xC);
    position[2] = *(float *)(p + 0x10);
    color[0] = *(int *)(p + 0x18);
    color[1] = *(int *)(p + 0x1C);
    color[2] = *(int *)(p + 0x20);
    color[3] = *(int *)(p + 0x24);
    func_00111300(index, (float)*(int *)(p + 0), (float)*(int *)(p + 4), position, color);
}
