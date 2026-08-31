typedef struct Entry16 {
    unsigned char bytes[16];
} Entry16;

extern Entry16 D_001A6F58[];

Entry16 *func_00128FB8(unsigned char index) {
    return &D_001A6F58[index];
}
