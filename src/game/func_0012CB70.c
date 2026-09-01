struct Slot_001ED300 { unsigned char pad_0x0[0x1C]; unsigned char field_0x1C; unsigned char field_0x1D; unsigned char field_0x1E; unsigned char field_0x1F; };

extern struct Slot_001ED300 *D_001ED300;

extern void func_0015DE90(void *arg, struct Slot_001ED300 *slot);

int func_0012CB70(int index, unsigned char kind, void *arg) {
    switch (kind) {
    case 0:
        func_0015DE90(arg, &D_001ED300[index]);
        return 1;
    case 1:
        return (D_001ED300 + index)->field_0x1C;
    case 2:
        return (D_001ED300 + index)->field_0x1D;
    case 3:
        return (D_001ED300 + index)->field_0x1E;
    }
    return 0;
}
