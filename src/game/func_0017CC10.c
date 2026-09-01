extern long D_001FFB40;
extern int D_001ECF60;

long *func_00136AE8(void);
int func_001987E0(int handle);
int func_00192A54(char *str);
int func_0017C240(int opcode, void *data, int size);

int func_0017CC10(char *str) {
    long v;
    int b2;
    int b10;

    v = *func_00136AE8();
    b2 = (int)(v << 30 >> 32) & 1;
    if (b2 != 1) {
        b10 = (int)(v << 22 >> 32) & 1;
        if (b10 != 1) {
            func_001987E0(D_001ECF60);
            return func_0017C240(0x40, str, func_00192A54(str) + 1);
        }
    }
}
