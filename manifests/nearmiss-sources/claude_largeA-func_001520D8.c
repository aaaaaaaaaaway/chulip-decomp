typedef struct {
    unsigned int key;
    unsigned int value;
} Block;

typedef struct {
    unsigned int next;
    unsigned int prev;
} BlockLink;

extern unsigned int D_001ECBD0;
extern unsigned int D_001ECBD4;
extern int D_001ED45C;
extern Block D_00288E80[];
extern BlockLink D_00294E80[];

int func_001520D8(unsigned int key) {
    unsigned int i;
    unsigned int next;
    unsigned int prev;
    int result;

    i = D_001ECBD4;
    if (i != 0xFFFFFFFF) {
        while (key != D_00288E80[i].key) {
            i = D_00294E80[i].next;
            if (i == 0xFFFFFFFF) {
                break;
            }
        }
    }
    next = D_00294E80[i].next;
    prev = D_00294E80[i].prev;
    if (i == D_001ECBD0) {
        D_001ECBD0 = prev;
        if (prev != 0xFFFFFFFF) {
            D_00294E80[prev].next = 0xFFFFFFFF;
        }
    } else if (i == D_001ECBD4) {
        D_001ECBD4 = next;
        if (next != 0xFFFFFFFF) {
            D_00294E80[next].prev = 0xFFFFFFFF;
        }
    } else {
        D_00294E80[next].prev = prev;
        D_00294E80[prev].next = next;
    }
    result = D_00288E80[i].value - D_00288E80[i].key;
    D_00288E80[i].key = 0xFFFFFFFF;
    D_00294E80[i].next = 0xFFFFFFFF;
    D_00294E80[i].prev = 0xFFFFFFFF;
    D_00288E80[i].value = 0xFFFFFFFF;
    D_001ED45C--;
    return result;
}
