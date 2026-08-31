typedef struct {
    unsigned char pad[0x31];
    unsigned char field;
    unsigned char tail[0xE];
} Entry;

extern Entry D_002BDA40[];

int func_001547A8(unsigned short index) {
    int result;

    if (index < 0x3E0) {
        result = (D_002BDA40 + index)->field;
    } else {
        result = 0;
    }
    return result;
}
