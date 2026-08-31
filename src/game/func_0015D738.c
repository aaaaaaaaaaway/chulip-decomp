typedef struct {
    unsigned char pad[0x36];
    short field;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];

void func_0015D738(unsigned short index, short value) {
    (D_002ABA40 + index)->field = value;
}
