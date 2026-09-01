typedef struct Slot {
    int handle;
    int arg;
} Slot;

extern Slot D_001E6360[];
extern int D_001E5BB8[];

extern int func_001A0A30(void);
extern void func_001A09C8(int handle, int arg);
extern void func_001A09D8(int addr, void *src, int size);
extern void func_00198A20(int mode);
extern int func_001A0A20(int handle);

void func_001A0A98(void) {
    unsigned int i;

    if (func_001A0A30() == 0) {
        return;
    }
    func_001A09C8(D_001E6360[0].handle, D_001E6360[0].arg);
    func_001A09D8(0x80074000, D_001E5BB8, 0x7A8);
    func_00198A20(0);
    func_00198A20(2);
    func_001A09C8(D_001E6360[1].handle, D_001E6360[1].arg);
    for (i = 2; i < 3; i++) {
        func_001A09C8(D_001E6360[i].handle, func_001A0A20(D_001E6360[i].handle));
    }
}
