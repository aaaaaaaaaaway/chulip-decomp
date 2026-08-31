typedef struct {
    unsigned char pad[0x330];
    int x;
    int y;
    int z;
    unsigned char tail[0xC];
} Entry;

extern Entry D_002D78C0[];
extern void func_0017CA50(int x, int arg1, int y, int z, int arg4, int arg5);

void func_0015E4D0(int index) {
    Entry *entry = D_002D78C0 + index;

    func_0017CA50(entry->x, 0, entry->y, entry->z, 0, 0x40);
}
