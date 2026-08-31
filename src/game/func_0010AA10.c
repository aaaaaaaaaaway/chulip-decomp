typedef struct {
    int f0;
    int f4[4];
    int f14;
    int f18[4];
    int f28;
    int f2C;
    int f30[4];
} S;

void func_0010AA50(int a, int b, int *c, int *d, int *e, int f, int g);

void func_0010AA10(int index, S *table) {
    func_0010AA50(table[index].f0, table[index].f14, table[index].f4,
                  table[index].f18, table[index].f30, table[index].f2C,
                  table[index].f28);
}
