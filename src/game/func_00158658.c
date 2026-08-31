typedef struct {
    unsigned char pad[0x3A];
    unsigned char field;
    unsigned char tail[0x5];
} Entry;

extern Entry D_002ABA40[];

unsigned char func_00158658(unsigned short index) {
    return (D_002ABA40 + index)->field;
}
