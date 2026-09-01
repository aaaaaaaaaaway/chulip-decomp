extern int D_001ECF60;
extern int D_001ED900;

int func_001987C0();
int func_001987E0();
int func_001987F0();

int func_0017C450(int wait, int *out) {
    if (wait == 0) {
        if (func_001987F0(D_001ECF60) < 0) {
            return 0;
        }
    } else {
        func_001987E0(D_001ECF60);
    }
    if (out != 0) {
        *out = D_001ED900;
    }
    func_001987C0(D_001ECF60);
    return 1;
}
