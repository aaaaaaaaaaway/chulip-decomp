typedef struct Slot {
    unsigned char pad[0x32];
    unsigned char flag;
    unsigned char pad2[0xD];
} Slot;

extern Slot D_002BDA40[];

void func_0015CBB0(void) {
    int i;

    for (i = 0x35F; i >= 0; i--) {
        D_002BDA40[i].flag = 0;
    }
}
