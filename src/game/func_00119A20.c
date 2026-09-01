struct Slot {
    int id;
    int a;
    int b;
    int timer;
};

extern struct Slot D_001FA200[];
extern int D_001ED1FC;
extern int D_001ED200;
extern void func_00112F40(void (*fn)(void));
extern void func_00112EB0(void (*fn)(void), int a, int b);
extern void func_00119BB8(void);

void func_00119A20(void) {
    int i;

    D_001ED1FC = 0;
    D_001ED200 = 0;
    for (i = 0; i < 20; i++) {
        D_001FA200[i].id = -1;
        D_001FA200[i].b = -1;
        D_001FA200[i].timer = 0;
        D_001FA200[i].a = -1;
    }
    func_00112F40(func_00119BB8);
    func_00112EB0(func_00119BB8, 0, 0);
}
