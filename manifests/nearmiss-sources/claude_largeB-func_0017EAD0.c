typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned char c;
} Step;

typedef struct {
    unsigned short f00;
    unsigned char f02;
    unsigned char pad0;
    unsigned short f04;
    unsigned char f06;
    unsigned char pad1;
    unsigned char f08[0x10];
    Step steps[0x20];
} Rec;

extern Rec D_001E1768[];

void func_0017EC38(int a, int b);
int func_00192568(void);

int func_0017EAD0(unsigned short idx, unsigned short sel) {
    unsigned char n;

    if (D_001E1768[idx].f02 == 0) {
        D_001E1768[idx].f04 = D_001E1768[idx].steps[D_001E1768[idx].f08[sel]].b;
        D_001E1768[idx].f02 = D_001E1768[idx].f08[sel];
    }
    if (D_001E1768[idx].f04 != 0) {
        D_001E1768[idx].f04 = D_001E1768[idx].f04 - 1;
    } else {
        func_0017EC38(D_001E1768[idx].f00,
                      (D_001E1768[idx].steps[D_001E1768[idx].f02 - 1].a + D_001E1768[idx].f06) & 0xFF);
        n = D_001E1768[idx].steps[D_001E1768[idx].f02 - 1].c;
        if (n == 0xFF) {
            D_001E1768[idx].f02 = 0;
            return -1;
        }
        D_001E1768[idx].f04 = D_001E1768[idx].steps[n - 1].b;
        D_001E1768[idx].f02 = n;
        if (n == 0xA) {
            D_001E1768[idx].f04 = D_001E1768[idx].f04 + (func_00192568() % 0x78) + 0x3C;
        }
    }
    return 0;
}
