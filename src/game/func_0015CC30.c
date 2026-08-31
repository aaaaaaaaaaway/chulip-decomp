typedef struct {
    unsigned char name[0x40];
} Slot;

extern Slot D_002BDA40[];
extern char D_001E9C00[];
extern int func_001927FC(const char *left, const char *right);

unsigned short func_0015CC30(void) {
    int index;

    for (index = 0x47F; index >= 0; index--) {
        if (func_001927FC(D_002BDA40[index].name, D_001E9C00) == 0) {
            return index;
        }
    }
    return 0xFFFF;
}
