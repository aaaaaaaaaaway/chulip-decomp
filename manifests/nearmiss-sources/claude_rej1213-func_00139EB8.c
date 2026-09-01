struct Entry_00139EB8 {
    unsigned char pad_0x0[0x10];
    int field_0x10;
    unsigned char pad_0x14[0x10];
};

extern unsigned short D_001EC9F0;
extern unsigned short D_002050F0[];
extern struct Entry_00139EB8 D_00203C20[];

void func_00139EB8(int id) {
    int i;

    for (i = 0; i < D_001EC9F0; i++) {
        if (D_002050F0[i] == id) {
            return;
        }
    }
    D_002050F0[D_001EC9F0] = id;
    D_001EC9F0 = D_001EC9F0 + 1;
    D_00203C20[id].field_0x10 = D_00203C20[id].field_0x10 | 2;
}
