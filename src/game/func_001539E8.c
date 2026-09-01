typedef struct Slot40 { unsigned char b[0x40]; } Slot40;

extern Slot40 D_002BDA40[];
extern Slot40 D_002BDA80[];
extern Slot40 D_002C3140[];
extern Slot40 D_002D4440[];

extern void func_00137F10(int index, int *output);
extern int func_00137F28(int index);
extern int func_00192344(void *destination, int value, int handle);
extern char func_001923F4(void *buffer, int value, unsigned int size);

void func_001539E8(unsigned char mode) {
    int value;
    int handle;

    if (mode == 0) {
        func_001923F4(D_002BDA40, 0, 0x7000);
        handle = func_00137F28(3);
        func_00137F10(3, &value);
        func_00192344(D_002BDA40, value, handle);
        D_002D4440[0] = D_002BDA40[0];
    } else if (mode == 1) {
        func_001923F4(D_002BDA80, 0, 0x6FC0);
        handle = func_00137F28(3) - 0x40;
        func_00137F10(3, &value);
        func_00192344(D_002BDA80, value + 0x40, handle);
    } else if (mode == 2) {
        func_00137F10(3, &value);
        func_00192344(D_002BDA40, value, 0x40);
        D_002D4440[0] = D_002BDA40[0];
    } else if (mode == 3) {
        D_002BDA40[0] = D_002D4440[0];
        return;
    } else {
        D_002D4440[0] = D_002BDA40[0];
        return;
    }
    handle = func_00137F28(4);
    func_00137F10(4, &value);
    func_00192344(D_002C3140, value, handle);
}
