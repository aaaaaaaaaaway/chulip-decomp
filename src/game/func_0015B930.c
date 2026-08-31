typedef struct {
    long flags;
    unsigned char pad[0x41];
    unsigned char state;
} Object;

extern unsigned char D_001ECCA0;
extern Object *func_00136AE8(void);

void func_0015B930(unsigned char value) {
    Object *object = func_00136AE8();

    object->state = value;
    D_001ECCA0 = value;
    object->flags |= 2;
}
