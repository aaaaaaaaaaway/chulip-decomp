struct Set_001FDB00 { unsigned char count; unsigned char pad; unsigned char entries[0x200]; };
extern struct Set_001FDB00 D_001FDB00;
struct Set_001FDB20 { unsigned short count; unsigned short pad; unsigned char entries[0x200]; };
extern struct Set_001FDB20 D_001FDB20;

int func_0012FBF0(unsigned short key) {
    int i;
    for (i = 0; i < D_001FDB00.count; i++) {
        if (D_001FDB00.entries[i] == key) {
            return 1;
        }
    }
    return 0;
}

int func_0012FC40(unsigned short key) {
    int i;
    for (i = 0; i < D_001FDB20.count; i++) {
        if (D_001FDB20.entries[i * 2] == key) {
            return 1;
        }
    }
    return 0;
}
