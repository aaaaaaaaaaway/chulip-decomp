typedef struct {
    long flags;
} Object;

extern unsigned char D_001ECC90;
extern Object *func_00136AE8(void);

void func_0015B540(unsigned char value) {
    Object *object = func_00136AE8();

    D_001ECC90 = value;
    object->flags |= 2;
}
