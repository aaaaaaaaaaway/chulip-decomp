struct Slot {
    int id;
    int a;
    int b;
    int timer;
};

extern struct Slot D_001FA200[];
extern int D_001ED200;

int func_00119AA0(int a, int id) {
    int i;
    int count;

    for (i = 0; i < 20; i++) {
        if (D_001FA200[i].a == a) {
            D_001FA200[i].id = -1;
            D_001FA200[i].a = -1;
            D_001FA200[i].b = -1;
            D_001ED200--;
            if (D_001ED200 < 0) {
                D_001ED200 = 0;
            }
        }
    }
    if (id != 0) {
        count = D_001ED200;
        for (i = 0; i < 20; i++) {
            if (D_001FA200[i].b == -1) {
                count++;
                D_001FA200[i].a = a;
                D_001FA200[i].id = id;
                D_001FA200[i].timer = 0;
                D_001FA200[i].b = 0;
                if (count > 20) {
                    count = 20;
                }
                break;
            }
        }
        D_001ED200 = count;
    }
    return 20 - D_001ED200;
}
