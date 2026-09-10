typedef struct {
    unsigned char unknown00[32];
    long flags;
    unsigned char unknown28[14];
    unsigned short resource;
    unsigned char unknown38[8];
} Actor;
extern Actor D_002ABA40[];
unsigned char *func_00136AE8(void);
void *func_0014D860(unsigned short);
void func_001780D0(unsigned char);
void func_0015BA78(unsigned short);
void func_0015A188(unsigned short);
void func_0015A250(void);

void func_0015B578(unsigned char bank) {
    unsigned char *state;
    unsigned int *list;
    unsigned int *id;
    int i;
    Actor *actor;
    Actor *first;
    Actor *second;
    Actor *third;
    state = func_00136AE8();
    list = func_0014D860(bank);
    func_001780D0(1);
    for (i = 0; i < list[0]; ++i) {
        id = list + 6 + i * 8;
        if (*id < 0xfc)
            func_0015BA78(*id);
        first = D_002ABA40 + *id;
        first->flags &= ~0x10L;
        second = D_002ABA40 + *id;
        second->flags &= ~4L;
        third = D_002ABA40 + *id;
        third->flags &= ~1L;
        func_0015A188(*id);
    }
    for (i = 0x11c; i < 0x15c; ++i) {
        actor = D_002ABA40 + i;
        if ((unsigned int)(actor->resource - 1) < 0xfb) {
            actor->flags &= ~0x10L;
            actor->flags &= ~4L;
            actor->flags &= ~1L;
            func_0015A188(i);
        }
    }
    func_0015A250();
    state[0x46] = 255;
}
