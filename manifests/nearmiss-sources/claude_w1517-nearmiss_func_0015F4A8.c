typedef struct Rec {
    int pad0;
    int mode;
    unsigned char pad[0x90];
} Rec;

extern Rec D_002D7F50[];

void func_0015F4A8(void) {
    int i;

    for (i = 3; i >= 0; i--) {
        D_002D7F50[i].mode = 4;
    }
}
