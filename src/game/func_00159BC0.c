typedef struct {
    unsigned char pad[0x24];
    void *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];
extern void func_00158D60(unsigned short index, int arg1, int arg2);

void func_00159BC0(void) {
    unsigned short index;

    for (index = 0; index < 0x1C0; index++) {
        if ((D_002ABA40 + index)->owner != 0) {
            func_00158D60(index, 0xFF, 0);
        }
    }
}
