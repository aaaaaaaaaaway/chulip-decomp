/* Advance the current threshold level and publish the resulting stat deltas. */
typedef struct {
    unsigned char unknown00[0x54];
    unsigned short value54, limit56;
    unsigned short value58, limit5a;
    int value5c, value60;
    unsigned char value64, value65;
    unsigned short value66;
} PlayerStats;
extern PlayerStats D_001A6998;
extern unsigned char *D_001ED300;
void func_001734C0(int, int);

int func_0012F8A8(void) {
    int level;
    int delta;
    for (level = D_001A6998.value64; level < 24; level++) {
        if (D_001ED300[level * 32 + 0x3d] > D_001A6998.value66)
            break;
    }
    if (D_001A6998.value64 < level) {
        func_001734C0(14, (short)level);
        delta = D_001ED300[level * 32 + 0x3d] - D_001A6998.value66;
        func_001734C0(15, (short)delta);
        delta = D_001ED300[level * 32 + 0x1c] - D_001A6998.limit56;
        func_001734C0(18, (short)delta);
        D_001A6998.value64 = level;
        return 1;
    }
    func_001734C0(20, 0);
    func_001734C0(19, 0);
    func_001734C0(18, 0);
    return 0;
}
