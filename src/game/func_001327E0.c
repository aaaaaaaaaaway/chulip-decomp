struct DrawList_002D81C0 {
    int field_0x0;
    unsigned char *cursor;
    int field_0x8;
    int field_0xc;
};
struct Slot {
    unsigned short id;
    unsigned short pad_0x2;
};

extern struct DrawList_002D81C0 D_002D81C0;
extern struct Slot D_002D71C0[];
extern struct Slot D_002D66C0[];
extern unsigned short D_001FE470[];
extern int D_001ED490;
extern int D_001ED480;
extern int D_001ED348;

extern void func_00161258(struct DrawList_002D81C0 *list);
extern void func_00130D30(void);
extern int func_00154398(unsigned short id);
extern int func_00154668(unsigned short id);
extern void func_00131F88(unsigned short id);

void func_001327E0(void) {
    int i;
    unsigned short id;

    func_00161258(&D_002D81C0);
    func_00130D30();
    for (i = 0; i < D_001ED490; i++) {
        id = D_002D71C0[i].id;
        if (func_00154398(id) != 0) {
            if (func_00154668(id) != 0) {
                D_001FE470[D_001ED348++] = id;
            } else {
                func_00131F88(id);
            }
        }
    }
    for (i = 0; i < D_001ED480; i++) {
        id = D_002D66C0[i].id;
        if (func_00154398(id) != 0) {
            func_00131F88(id);
        }
    }
    id = 0x458;
    do {
        if (func_00154398(id) != 0) {
            if (func_00154668(id) != 0) {
                D_001FE470[D_001ED348++] = id;
            } else {
                func_00131F88(id);
            }
        }
        id++;
    } while (id < 0x480);
}
