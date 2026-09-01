typedef struct {
    int f00;
    char pad0[8];
    int f0C;
    char pad1[0x2C];
    int f3C;
    int f40;
    int f44;
    int f48;
    int f4C;
    int f50;
    char pad2[0xC];
} Rec;

extern int D_001ED34C;
extern int D_001ED350;
extern Rec *D_001ED354;

#define RECS (*(Rec *volatile *)&D_001ED354)

Rec *func_00151A00(int size);
void func_00112F40(void *entry);
void func_00112EB0(void *entry, int count, int flags);
void func_00134570(void);

void func_00133858(int n) {
    int i;

    D_001ED34C = 1;
    D_001ED350 = n;
    D_001ED354 = func_00151A00(n * 0x60);
    for (i = 0; i < n; i++) {
        RECS[i].f00 = 0;
        RECS[i].f0C = -1;
        RECS[i].f3C = 0;
        RECS[i].f40 = 0;
        RECS[i].f44 = 0;
        RECS[i].f48 = 0;
        RECS[i].f4C = 0;
        RECS[i].f50 = 0;
    }
    func_00112F40(func_00134570);
    func_00112EB0(func_00134570, n, 0);
}
