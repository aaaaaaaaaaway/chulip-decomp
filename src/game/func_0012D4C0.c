extern unsigned int func_00138CC8(int arg0, int arg1, int arg2);
extern unsigned short *func_00138DF0(unsigned int handle);
extern void func_00158BB8(unsigned short index, int arg1);
extern void func_00138988(int arg0);

void func_0012D4C0(void) {
    unsigned int handle = func_00138CC8(0x1F, 0, 0);

    if (handle != 0xFFFFFFFFU) {
        func_00158BB8(*func_00138DF0(handle), 0);
    }
    func_00138988(0x1F);
}
