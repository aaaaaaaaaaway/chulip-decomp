typedef struct {
    unsigned char pad[0x2];
    short field;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002D48C0[];

void func_0015D218(unsigned short index, short value) {
    D_002D48C0[index].field = value;
}
