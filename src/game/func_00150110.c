typedef struct {
    int mode;
    int limit;
} State;

extern volatile State D_001ED444;

int func_00150110(int value) {
    if (D_001ED444.mode == 2) {
        return 1;
    }
    if (D_001ED444.mode == 3) {
        return value <= D_001ED444.limit;
    }
    return -1;
}
