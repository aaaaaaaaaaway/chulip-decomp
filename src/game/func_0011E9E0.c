extern unsigned short D_001EC8CC;
extern unsigned short D_001FBE28[];
void func_0011E718(unsigned short id);

void func_0011E9E0(void) {
    int i;

    for (i = 0; i < D_001EC8CC; i++) {
        func_0011E718(D_001FBE28[i]);
    }
    D_001EC8CC = 0;
}
