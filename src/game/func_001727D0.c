/* Apply visibility changes to eligible kinds and preserve two selected kinds. */
struct Entry {
    unsigned int flags[2];
    unsigned char pad08[102];
    unsigned short kind;
    unsigned char tail[80];
};
struct ObjectList {
    unsigned char pad[16];
    unsigned short count;
};
extern int D_001ED6C0;
extern struct ObjectList D_002D8840;
extern void func_00158C70(unsigned short kind, unsigned char value);
extern void func_00158BB8(unsigned short kind, unsigned char value);
extern void func_00158B40(unsigned short kind, unsigned char value);
extern int func_00119AA0(int kind, int value);

void func_001727D0(unsigned short kind, unsigned char value) {
    int i;
    for (i = 1; i < D_002D8840.count; i++) {
        if (((struct Entry *)D_001ED6C0)[i].kind != 0xFFFF &&
            (((struct Entry *)D_001ED6C0)[i].flags[0] & 0x800000) == 0) {
            if (((struct Entry *)D_001ED6C0)[i].kind != kind) {
                func_00158C70(((struct Entry *)D_001ED6C0)[i].kind, !value);
            }
            if (!value && (((struct Entry *)D_001ED6C0)[i].flags[1] & 0x1000)) {
                func_00119AA0(((struct Entry *)D_001ED6C0)[i].kind, 0);
            }
        }
    }
    func_00158BB8(0, 1);
    func_00158B40(0, 0);
    func_00158C70(0, 0);
    func_00158BB8(kind, 1);
    func_00158B40(kind, 0);
    func_00158C70(kind, 0);
}
