typedef struct {
    unsigned char pad[0x314];
    int field;
    unsigned char tail[0x30];
} Entry;

extern Entry D_002D78C0[];

int func_0015F1A0(int index) {
    return (D_002D78C0 + index)->field;
}
