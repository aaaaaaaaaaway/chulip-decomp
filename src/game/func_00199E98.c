extern int D_001E5AEC[];
extern char D_002E0DC0[];
extern void func_001A0E10(char *text);

void func_00199E98(int character) {
    int length = D_001E5AEC[0];
    if (length >= 0x7E) {
        D_001E5AEC[0] = 0;
        D_002E0DC0[0x7F] = 0;
        func_001A0E10(D_002E0DC0);
        length = D_001E5AEC[0];
    }
    if (character == 0xA) {
        D_001E5AEC[0] = 0;
        D_002E0DC0[length] = character;
        D_002E0DC0[length + 1] = 0;
        func_001A0E10(D_002E0DC0);
        return;
    }
    D_001E5AEC[0] = length + 1;
    D_002E0DC0[length] = character;
}
