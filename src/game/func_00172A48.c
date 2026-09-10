/* Clear the temporary-state flag on the first eligible matching kind. */
struct Entry {
    unsigned int flags;
    unsigned char pad04[106];
    unsigned short kind;
    unsigned char tail[80];
};
struct ObjectList {
    unsigned char pad[16];
    unsigned short count;
};
extern int D_001ED6C0;
extern struct ObjectList D_002D8840;

void func_00172A48(unsigned short kind) {
    int i;
    for (i = 1; i < D_002D8840.count; i++) {
        if (((struct Entry *)D_001ED6C0)[i].kind == kind &&
            (((struct Entry *)D_001ED6C0)[i].flags & 0x800000) == 0) {
            *(unsigned int *)(D_001ED6C0 + i * 192) &= ~0x2000;
            return;
        }
    }
}
