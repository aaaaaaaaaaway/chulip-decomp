typedef struct {
    unsigned char pad[0x320];
    int field;
    unsigned char tail[0x24];
} Entry;

extern Entry D_002D78C0[];

void func_0015E0F8(int index, int value) {
    (D_002D78C0 + index)->field = value;
}
