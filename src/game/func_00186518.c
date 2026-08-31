typedef struct {
    int a;
    int b;
    int c;
    long d;
} Packed;

extern void func_001858A8(Packed *args);

void func_00186518(int a, int b, int c, long d) {
    Packed args;

    args.a = a;
    args.b = b;
    args.c = c;
    args.d = d;
    func_001858A8(&args);
}
