typedef struct { long pad0[4]; long out; long pad1; long packed; } Sprite;

void func_00187DF8(Sprite *sprite, short x, short y, short offset) {
    unsigned long packed = (unsigned long)sprite->packed;
    int cy = (int)((packed >> 48) & 0x7FF);
    int cx = (int)((packed >> 16) & 0x7FF);
    long hy = (unsigned long)(long)(cy + 1) >> 1;
    long hx = (unsigned long)(long)(cx + 1) >> 1;
    long dy = (long)y - hy;
    long dx = (long)x - hx;
    long hi;

    long shifted = dy << 4;

    if (offset != 0) {
        hi = (shifted + 8) << 32;
    } else {
        hi = shifted << 32;
    }
    sprite->out = (dx << 4) | hi;
}
