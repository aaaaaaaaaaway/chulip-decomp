extern unsigned char D_001E1F00[];
extern unsigned char D_001E2740[];

unsigned char *func_0017E7F8(int id) {
    if ((id & 0x1000) != 0) {
        return &D_001E2740[(id & ~0x1000) * 0x34];
    }
    return &D_001E1F00[id * 0x34];
}
