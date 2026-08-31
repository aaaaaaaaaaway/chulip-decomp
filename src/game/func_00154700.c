typedef struct {
    unsigned char pad[0x36];
    unsigned short field;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];

unsigned short func_00154700(unsigned short index) {
    return (D_002ABA40 + index)->field;
}
