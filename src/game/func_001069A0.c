typedef struct {
    int unk00;
    int unk04;
    int pad08[2];
    int unk10;
    int unk14;
    int unk18;
    float unk1C;
    int pad20[8];
} PoolItem;

typedef struct {
    int pad00[2];
    int unk08;
    int pad0C[13];
    PoolItem items[100];
} Pool;

extern Pool *D_001ED0A8[2];
extern int D_001ED0AC;
extern int D_001ED0B0[2];

extern void *func_00151A00(int);
extern void func_00112EB0(void *, int, int);
extern void func_00106E48(void);

void func_001069A0(int count) {
    int i;
    int j;

    D_001ED0A8[0] = func_00151A00(count * 0x1940);
    D_001ED0B0[0] = 1;
    D_001ED0AC = count;
    for (i = 0; i < count; i++) {
        D_001ED0A8[0][i].unk08 = 0;
        for (j = 0; j < 100; j++) {
            D_001ED0A8[0][i].items[j].unk04 = 0;
            D_001ED0A8[0][i].items[j].unk10 = 0;
            D_001ED0A8[0][i].items[j].unk14 = 0;
            D_001ED0A8[0][i].items[j].unk18 = 0;
            D_001ED0A8[0][i].items[j].unk1C = 1.0f;
        }
    }
    func_00112EB0(func_00106E48, count, 0);
}
