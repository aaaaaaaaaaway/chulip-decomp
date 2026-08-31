typedef struct {
    unsigned char pad[0x300];
    int field;
    unsigned char tail[0x44];
} Entry;

extern Entry D_002D78C0[];

void func_0015E178(int index, int value) {
    (D_002D78C0 + index)->field = value;
}
