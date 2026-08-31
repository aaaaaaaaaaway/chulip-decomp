typedef struct {
    unsigned char pad[0x318];
    int field;
    unsigned char tail[0x2C];
} Entry;

extern Entry D_002D78C0[];

int func_0015F1C0(int index) {
    return (D_002D78C0 + index)->field;
}
