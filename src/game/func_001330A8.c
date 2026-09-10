struct Request_001330A8 {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
};

extern void *func_00151A20(int size);
extern void *func_00151A00(int size);
extern void func_00133190(void *object, int a, int b);

void *func_001330A8(struct Request_001330A8 *request, int id) {
    int temporary;
    void *object;

    temporary = 0;
    if (((unsigned int)(id - 0x11C) < 0x40) || ((unsigned int)(id - 1) < 0xFB) ||
        ((unsigned int)(id - 0x3A0) < 0xB8) || (id == 0)) {
        temporary = 1;
    }
    if (temporary != 0) {
        object = func_00151A20(0x30);
    } else {
        object = func_00151A00(0x30);
    }
    if (object == 0) {
        return 0;
    }
    func_00133190(object, request->field_0xc, request->field_0x4);
    return object;
}
