typedef struct Entry32 {
    unsigned char bytes[32];
} Entry32;

extern Entry32 D_001A6AF8[];
extern unsigned char D_001FDB00[];

int func_0012FC88(void) {
    return D_001FDB00[0] >= D_001FDB00[1];
}

Entry32 *func_0012FCA8(unsigned char index) {
    return &D_001A6AF8[index];
}
