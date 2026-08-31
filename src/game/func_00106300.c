typedef struct { int f0; int f4; int f8; float fC; int f10[4]; } S;

void func_00106338(int index, int a, int b, int *out, int *extra, int c, float f);

void func_00106300(int index, S *table) {
    int out[4];

    func_00106338(index, table[index].f0, table[index].f4, out,
                  table[index].f10, table[index].f8, table[index].fC);
}
