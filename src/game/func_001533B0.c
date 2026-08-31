typedef struct {
    int index;
    int reserved;
} Selector;

extern Selector D_001ED460;
extern int D_001A8AE0[];

int func_001533B0(void) {
    return D_001A8AE0[D_001ED460.index];
}
