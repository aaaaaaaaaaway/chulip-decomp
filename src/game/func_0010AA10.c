typedef struct {
    int f0;
    float f4[4];
    int f14;
    float f18[4];
    int f28;
    int f2C;
    int f30[4];
} S;

void func_0010AA50(int a, int b, const float *c, const float *d, const int *e, int f, int g);

void func_0010AA10(int index, S *table) {
    func_0010AA50(table[index].f0, table[index].f14, table[index].f4, table[index].f18,
                  table[index].f30, table[index].f2C, table[index].f28);
}
