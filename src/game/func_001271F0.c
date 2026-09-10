signed char D_001EC8D4 __attribute__((section(".sdata"))) = 0;

extern short D_001ED29A;
extern short D_001ED29C;
extern short D_001ED29E;
extern short D_001ED2A0;
extern short D_001ED2A2;
extern short D_001ED2A4;
extern short D_001ED2A6;

void func_001271F0(short x, short y, unsigned short z) {
    if (D_001EC8D4 != 0) {
        D_001ED2A2 = 0x79C0;
        D_001ED2A4 = 0x7DD0;
        D_001ED2A6 = 0x800;
    } else {
        D_001ED2A2 = x << 4;
        D_001ED2A4 = y << 4;
        D_001ED2A6 = z;
    }
    D_001ED29E = D_001ED2A2;
    D_001ED2A0 = D_001ED2A4;
}

