extern void *func_001513E0(int kind, unsigned short index, int arg2);
extern void *func_001594E0(void *object, unsigned short index);

void *func_00155B08(unsigned short index) {
    void *object = func_001513E0(0x12, index, 0);

    if (object == 0) {
        return 0;
    }
    return func_001594E0(object, index);
}
