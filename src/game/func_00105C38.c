typedef struct { int f0; int f4; int f8[4]; } S;

void func_00105C70(int index, int a, int b, int *out, int *extra);

void func_00105C38(int index, S *table) {
    int out[4];

    func_00105C70(index, table[index].f0, table[index].f4, out, table[index].f8);
}
