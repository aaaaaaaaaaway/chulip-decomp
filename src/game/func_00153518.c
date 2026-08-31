typedef struct {
    unsigned char pad[0x4];
    int *table;
} Request;

extern int D_002D81C0[];
extern void func_00161298(int context, int value);

void func_00153518(Request *request, unsigned char index) {
    func_00161298(D_002D81C0[1], request->table[index]);
    D_002D81C0[1] += 0x10;
}
