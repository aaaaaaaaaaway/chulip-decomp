typedef struct {
    unsigned char pad[0x24];
    int field;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

int func_001548A0(unsigned short index) {
    return (D_002ABA40 + index)->field;
}
