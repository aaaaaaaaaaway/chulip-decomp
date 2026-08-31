struct Rec1C {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    int field_0x14;
    int field_0x18;
};

extern struct Rec1C D_00288C40;
extern char D_001A88C8[];
extern char D_001E9630[];
extern char D_001ECB50[];

extern void func_00192660();
extern int func_0014E550(char *path, int arg1, int arg2);

int func_0014E650(void) {
    char path[0x100];
    int status;

    if (D_00288C40.field_0x0 != 0) {
        func_00192660(path, D_001E9630, D_001A88C8);
        status = func_0014E550(path, D_00288C40.field_0x0, 0x3C4);
        if (status == -3) {
            return -8;
        }
        if (status < 0) {
            return -2;
        }
    }
    if (D_00288C40.field_0x4 != 0) {
        func_00192660(path, D_001ECB50, D_001A88C8, D_00288C40.field_0x0 + 0x104);
        status = func_0014E550(path, D_00288C40.field_0x4, D_00288C40.field_0x8);
        if (status == -3) {
            return -8;
        }
        if (status < 0) {
            return -2;
        }
    }
    if (D_00288C40.field_0xc != 0) {
        func_00192660(path, D_001ECB50, D_001A88C8, D_00288C40.field_0x0 + 0x144);
        status = func_0014E550(path, D_00288C40.field_0xc, D_00288C40.field_0x10);
        if (status == -3) {
            return -8;
        }
        if (status < 0) {
            return -2;
        }
    }
    if (D_00288C40.field_0x14 != 0) {
        func_00192660(path, D_001ECB50, D_001A88C8, D_00288C40.field_0x0 + 0x184);
        status = func_0014E550(path, D_00288C40.field_0x14, D_00288C40.field_0x18);
        if (status == -3) {
            return -8;
        }
        if (status < 0) {
            return -2;
        }
    }
    return 0;
}
