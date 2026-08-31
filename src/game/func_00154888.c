typedef struct Entry64 {
    unsigned char bytes[64];
} Entry64;

extern Entry64 D_002ABA60[];

Entry64 *func_00154888(unsigned short index) {
    return &D_002ABA60[index];
}
