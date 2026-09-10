extern int D_002D8890[];
extern int D_002D8894[];
extern unsigned short D_002D88A6[];

int func_00172FE8(unsigned short sel) {
    switch (sel) {
    case 4:
        return D_002D8894[0];
    case 0xC:
        return D_002D8890[0];
    case 7:
        return D_002D88A6[0];
    }
    return -1;
}
