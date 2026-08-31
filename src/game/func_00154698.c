typedef struct {
    unsigned char pad[0x32];
    signed char field;
    unsigned char tail[0xD];
} Entry;

extern Entry D_002BDA40[];

signed char func_00154698(unsigned short index) {
    return (D_002BDA40 + index)->field;
}
