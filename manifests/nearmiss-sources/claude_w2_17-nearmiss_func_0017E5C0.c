typedef struct {
    char pad00[0x30];
    unsigned short state;
} Obj0017E5C0;

extern Obj0017E5C0 *D_001ED940;

Obj0017E5C0 *func_0017D040();
int func_0017E6C8();

void func_0017E5C0(void) {
    unsigned int i;

    for (i = 0; i < 0x28; i++) {
        D_001ED940 = func_0017D040(i | 0x1000);
        if (D_001ED940->state != 0xFFFF) {
            func_0017E6C8(i | 0x1000, 0x40);
        }
    }
}
