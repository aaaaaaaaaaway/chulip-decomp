struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };

extern struct List_001FDB00 D_001FDB00;
extern int D_001EC8F0;

extern void func_00173468(int mask, int flag);

void func_0012C698(unsigned short id) {
    unsigned int index;

    if (D_001FDB00.count < D_001FDB00.limit) {
        index = id;
        func_00173468((((index >> 4) + 0xA8) << 16) | (1 << (index & 0xF)), 1);
        D_001EC8F0 = 1;
        D_001FDB00.entries[D_001FDB00.count] = index;
        D_001FDB00.count = D_001FDB00.count + 1;
    }
}
