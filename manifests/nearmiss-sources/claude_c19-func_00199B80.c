typedef struct {
    short size;
    char pad[5];
    char b7;
    int pad2;
    char data[0x100];
} SioPkt;
typedef struct {
    int f0;
    int f4;
    int f8;
    int busy;
    SioPkt *pkt;
} SioState;

extern SioState D_002E0B10;
extern int D_002E0B40[];

extern void func_001A0828(void);
extern void func_001A0870(void);
extern int func_001A0CC8(int a, int b);
extern void func_001A0CF8(int a);

int func_00199B80(char *buf, int len) {
    SioPkt *p;
    char *d;
    int n;
    int i;

    n = 0;
    i = 0;
    if (D_002E0B10.busy != 0) {
        return -1;
    }
    func_001A0828();
    p = (SioPkt *)((int)D_002E0B40 | 0x20000000);
    D_002E0B10.busy = 1;
    D_002E0B10.pkt = p;
    d = p->data;
    while (len-- != 0) {
        if (*buf == '\n') {
            *d = '\r';
            i++;
            if (i >= 0x100) {
                break;
            }
            d++;
        }
        *d = *buf;
        i++;
        buf++;
        d++;
        n++;
        if (i >= 0x100) {
            break;
        }
    }
    D_002E0B10.f4 = i + 0xC;
    p->size = D_002E0B10.f4;
    if (func_001A0CC8(D_002E0B10.f0, p->b7) < 0) {
        D_002E0B10.busy = 0;
        func_001A0870();
        return -1;
    }
    while (D_002E0B10.busy != 0) {
        func_001A0CF8(D_002E0B10.f0);
    }
    func_001A0870();
    return n;
}
