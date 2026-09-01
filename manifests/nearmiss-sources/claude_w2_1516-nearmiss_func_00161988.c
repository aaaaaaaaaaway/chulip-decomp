extern int D_001ED570[2];
extern int D_001ED548[2];
extern unsigned char D_002D8600[];

void func_00189150(int arg);
void func_00161BE0(int index, int value);
void func_00161BF8(int index, int a, int b);
int func_001893B0(int index, int zero, unsigned char *buf);

void func_00161988(int a, int b, int c) {
    int i;

    func_00189150(0);
    for (i = 0; i < 2; i++) {
        D_001ED548[i] = 0;
        D_001ED570[i] = 1;
        func_00161BE0(i, a);
        func_00161BF8(i, b, c);
        while (func_001893B0(i, 0, &D_002D8600[i * 0x100]) != 1) {
        }
    }
}
