typedef struct { int f0; int f4; int f8[4]; } S;

void func_0010C7E0(int index, int a, int b, int *out);

void func_0010C7B0(int index, S *table) {
    int out[4];

    func_0010C7E0(index, table[index].f0, table[index].f4, out);
}
