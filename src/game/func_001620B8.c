extern unsigned char D_001ED530[8];
extern int D_001ED528[2];
extern unsigned short D_001ECD44;

extern void func_00161C20(void);
extern void func_00162078(int index, unsigned char *dst);
extern int func_00161FE0(int index, int which);

void func_001620B8(void) {
    unsigned char raw[16];
    unsigned short value;
    unsigned short previous;

    func_00161C20();
    func_00162078(0, raw);
    D_001ED530[0] = raw[0];
    D_001ED530[1] = raw[1];
    D_001ED530[2] = raw[2];
    D_001ED530[3] = raw[3];
    value = func_00161FE0(0, 0);
    previous = D_001ECD44;
    D_001ECD44 = value;
    D_001ED528[0] = (value << 16) | (value & ~previous);
}
