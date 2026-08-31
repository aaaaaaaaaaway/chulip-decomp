struct Slot_001392F0 { unsigned char data[0x10]; };

extern struct Slot_001392F0 D_001A7EA0[];
extern struct Slot_001392F0 D_001A7EE0[];

extern void func_0018A680(struct Slot_001392F0 *slot, int value);

void func_001392F0(unsigned short index, int arg1, int arg2) {
    func_0018A680(&D_001A7EA0[index], arg1);
    func_0018A680(&D_001A7EE0[index], arg2);
}
