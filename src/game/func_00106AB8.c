typedef struct { int f0; int f4; int f8[4]; } S;

void func_00106AE8(int index, int a, int b, int *c);

void func_00106AB8(int index, S *table) {
    func_00106AE8(index, table[index].f0, table[index].f4, table[index].f8);
}
