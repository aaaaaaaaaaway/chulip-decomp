typedef struct Sub {
    unsigned short first;
    unsigned short count;
    unsigned char flag;
    unsigned char pad;
} Sub;

typedef struct Entry68 {
    unsigned char pad_0x0[0x2C];
    Sub sub[4];
} Entry68;

typedef struct Ctx {
    unsigned char pad_0x0[0x4B];
    unsigned char field_0x4B;
} Ctx;

extern unsigned short D_001ED088;
extern int D_001ED08C;

extern Ctx *func_00136AE8(void);
extern Entry68 *func_0014B4A8(int index);
extern unsigned short func_0014D910(void);

void func_00105530(int index, unsigned char mode) {
    Ctx *ctx;
    Entry68 *entry68;
    int slot;
    int columns;
    int first;
    int last;
    float left;
    float right;
    float top;
    float bottom;
    int i;
    int entry;
    unsigned short flags;

    ctx = func_00136AE8();
    if (ctx->field_0x4B < 0x5B) {
        entry68 = func_0014B4A8(ctx->field_0x4B);
    } else {
        entry68 = func_0014B4A8(ctx->field_0x4B - 0x59);
    }
    first = entry68->sub[index].first;
    last = first + entry68->sub[index].count;
    columns = func_0014D910();
    if (entry68->sub[index].flag == 0) {
        left = (float)(first % columns) * 1574.8033447265625f;
        right = (float)columns * 1574.8033447265625f;
        top = (float)(first / columns) * 1574.8033447265625f;
        bottom = (float)(last / columns + 1) * 1574.8033447265625f;
    } else {
        top = (float)(first % columns) * 1574.8033447265625f;
        bottom = (float)columns * 1574.8033447265625f;
        left = (float)(first / columns) * 1574.8033447265625f;
        right = (float)(last / columns + 1) * 1574.8033447265625f;
    }
    for (i = 0; i < D_001ED088; i++) {
        entry = D_001ED08C + i * 0x2C;
        flags = *(unsigned short *)entry;
        if (flags & 0x400) {
            if (flags & 0x800) { *(unsigned short *)entry = flags | 0x8000; }
            else { goto set_low; }
        } else if (flags & 0x200) {
            *(unsigned short *)entry = flags & 0x7FFF;
        } else {
            *(unsigned short *)entry = flags | 0x8000;
        }
        goto did;
set_low:
        *(unsigned short *)entry = flags & 0x7FFF;
did:
        if (mode != 1) {
            if (!(left <= *(float *)(entry + 0x04) && *(float *)(entry + 0x04) <= right &&
                  top <= *(float *)(entry + 0x08) && *(float *)(entry + 0x08) <= bottom)) {
                if (!(left <= *(float *)(entry + 0x0C) && *(float *)(entry + 0x0C) <= right &&
                      top <= *(float *)(entry + 0x10) && *(float *)(entry + 0x10) <= bottom)) {
                    if (*(float *)(i * 0x2C + D_001ED08C + 0x14) == 0.0f) {
                        *(unsigned short *)entry &= 0x7FFF;
                    } else if (!(left <= *(float *)(entry + 0x14) && *(float *)(entry + 0x14) <= right &&
                                 top <= *(float *)(entry + 0x18) && *(float *)(entry + 0x18) <= bottom)) {
                        if (!(left <= *(float *)(entry + 0x1C) && *(float *)(entry + 0x1C) <= right &&
                              top <= *(float *)(entry + 0x20) && *(float *)(entry + 0x20) <= bottom)) {
                            *(unsigned short *)entry &= 0x7FFF;
                        }
                    }
                }
            }
        }
    }
}
