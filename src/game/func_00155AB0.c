typedef struct {
    unsigned char pad[0x3B];
    unsigned char state;
    unsigned char tail[0x4];
} Entry;

extern Entry D_002ABA40[];
extern void *func_001513E0(int kind, unsigned short index, int arg2);
extern void func_00159370(void *object, unsigned short index);

void func_00155AB0(unsigned short index) {
    void *object;

    (D_002ABA40 + index)->state = 0xFF;
    object = func_001513E0(0x12, index, 0);
    func_00159370(object, index);
}
