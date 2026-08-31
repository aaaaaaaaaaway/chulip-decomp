typedef struct {
    unsigned char pad[0x20];
    long flags;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_001546D8(unsigned short index) {
    (D_002ABA40 + index)->flags |= 0x80;
}
