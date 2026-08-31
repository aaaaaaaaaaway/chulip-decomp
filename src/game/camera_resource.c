extern unsigned short D_001ED088;
extern unsigned char D_001ED08C;

unsigned int func_00137EF8(int resource);
void func_00137EE0(int resource, void *destination);

void func_00104178(void) {
    unsigned int size = func_00137EF8(6);

    func_00137EE0(6, &D_001ED08C);
    D_001ED088 = size / 44;
}

void func_001041D0(void) {
}
