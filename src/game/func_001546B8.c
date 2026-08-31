typedef struct {
    unsigned char pad[0x32];
    signed char field;
    unsigned char tail[0xD];
} Entry;

extern Entry D_002BDA40[];

void func_001546B8(unsigned short index, signed char value) {
    (D_002BDA40 + index)->field = value;
}
