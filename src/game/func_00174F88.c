typedef struct {
    char pad00[0x9A];
    unsigned short lo;
    unsigned short hi;
    char padA0[0x22];
} Ent00174F88;

extern Ent00174F88 *D_001ED6C0;
extern unsigned int D_002D8890[];

unsigned short func_00173148();

void func_00174F88(unsigned short id, unsigned int value) {
    unsigned short index;

    index = func_00173148(id);
    if (id != 0xFFFF) {
        D_002D8890[0] = (D_001ED6C0[index].hi << 16) | D_001ED6C0[index].lo;
    } else {
        D_002D8890[0] = value;
    }
}
