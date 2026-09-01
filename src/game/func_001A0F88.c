typedef struct Slot {
    int handle;
    int arg;
} Slot;

extern Slot D_001E66E8[];
extern int D_001E6378[];

extern void func_001A0F78(int handle, int arg);
extern void func_001A0F20(int addr, void *src, int size);
extern void func_00198A20(int mode);
extern int func_001A0F68(int handle);

void func_001A0F88(void) {
    unsigned int i;

    func_001A0F78(D_001E66E8[0].handle, D_001E66E8[0].arg);
    func_001A0F20(0x80075000, D_001E6378, 0x328);
    func_00198A20(0);
    func_00198A20(2);
    func_001A0F78(D_001E66E8[1].handle, D_001E66E8[1].arg);
    func_001A0F78(D_001E66E8[2].handle, D_001E66E8[2].arg);
    for (i = 3; i < 8; i++) {
        func_001A0F78(D_001E66E8[i].handle, func_001A0F68(D_001E66E8[i].handle));
    }
}
