struct IdList_001E7970 { unsigned short id[10]; };
struct DrawList_002D81C0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; };

extern struct IdList_001E7970 D_001E7970;
extern struct DrawList_002D81C0 D_002D81C0;

extern void func_00161258(struct DrawList_002D81C0 *list);
extern void func_00130D30(void);
extern int func_00154398(int id);
extern int func_00154668(int id);
extern void func_00131F88(int id);
extern void func_001312E0(void);

void func_00132E60(void) {
    struct IdList_001E7970 ids;
    unsigned short i;
    unsigned short j;

    ids = D_001E7970;
    func_00161258(&D_002D81C0);
    func_00130D30();
    for (i = 0x438; i < 0x43C; i++) {
        if (func_00154398(i) != 0) {
            if (func_00154668(i) == 0) {
                func_00131F88(i);
            }
        }
    }
    func_001312E0();
    for (j = 0; j < 0xA; j++) {
        unsigned short id = ids.id[j];

        if (func_00154398(id) != 0) {
            if (func_00154668(id) == 0) {
                func_00131F88(id);
            }
        }
    }
}
