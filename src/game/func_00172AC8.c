/* Remove a live kind and clear its object record after releasing snapshots. */
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
extern void func_0015BA00(unsigned short kind);
extern void func_00158B40(unsigned short kind, unsigned char value);
extern void func_00171C88(int index);
extern void func_00158BB8(unsigned short kind, unsigned char value);

void func_00172AC8(unsigned short kind) {
    int i;
    for (i = 1; i < D_002D8840.count; i++) {
        if (((struct Entry *)D_001ED6C0)[i].kind == kind &&
            (((struct Entry *)D_001ED6C0)[i].flags[0] & 0x800000) == 0) {
            break;
        }
    }
    if ((int)((struct Entry *)D_001ED6C0)[i].flags[1] < 0) {
        func_0015BA00(kind);
        func_00158B40(kind, 1);
        return;
    }
    if (i < D_002D8840.count) {
        func_00171C88(i);
        func_00158BB8(((struct Entry *)D_001ED6C0)[i].kind, 0);
        *(unsigned int *)(D_001ED6C0 + i * 192) = 0x200;
        *(unsigned int *)(D_001ED6C0 + i * 192 + 4) = 0x10;
        *(unsigned short *)(D_001ED6C0 + i * 192 + 152) = 0;
        *(unsigned int *)(D_001ED6C0 + i * 192 + 76) = 0xFFFFFFFF;
        *(unsigned short *)(D_001ED6C0 + i * 192 + 148) = 0xFFFF;
        *(unsigned short *)(D_001ED6C0 + i * 192 + 110) = 0xFFFF;
    }
}
