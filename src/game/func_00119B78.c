struct Slot {
    int id;
    int a;
    int b;
    int timer;
};

extern struct Slot D_001FA200[];

void func_00119B78(void) {
    int i;

    for (i = 0; i < 20; i++) {
        if (D_001FA200[i].id != -1) {
            D_001FA200[i].timer++;
        }
    }
}
