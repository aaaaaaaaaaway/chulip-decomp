typedef struct {
    char pad[0x10];
    unsigned short count;
} Tbl;

extern Tbl D_002D8840;
extern int D_001ED6C0;

void func_001721A8(unsigned char mode) {
    int i;

    if (mode != 0) {
        for (i = 0; i < (int)D_002D8840.count; i++) {
            if (!(*(unsigned int *)(i * 0xC0 + D_001ED6C0 + 4) & 0x2000000)) {
                *(unsigned int *)(i * 0xC0 + D_001ED6C0) |= 0x200;
            }
        }
    } else {
        for (i = 0; i < (int)D_002D8840.count; i++) {
            *(unsigned int *)(i * 0xC0 + D_001ED6C0) &= 0xFFFFFDFF;
        }
    }
}
