typedef struct {
    long unk0;
} DisplayInfo;

extern DisplayInfo *func_00187498(void);

short func_001881B0(short arg0, short arg1, short arg2) {
    DisplayInfo *d;
    int w;
    int h;

    d = func_00187498();
    w = (arg1 + 63) / 64;
    if (arg0 & 2) {
        h = (arg2 + 63) / 64;
    } else {
        h = (arg2 + 31) / 32;
    }
    if ((d->unk0 & 0x0000FFFF0000FFFFL) == 1) {
        return w * h;
    }
    return w * h * 2;
}
