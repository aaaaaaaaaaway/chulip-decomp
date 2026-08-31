typedef struct {
    unsigned char pad[0x3B];
    unsigned char field;
    unsigned char tail[0x4];
} Entry;

extern Entry D_002ABA40[];

unsigned char func_00158678(unsigned short index) {
    return (D_002ABA40 + index)->field;
}
