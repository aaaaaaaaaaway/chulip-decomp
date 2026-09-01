typedef struct Entry {
    unsigned char pad[0x36];
    unsigned short id;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];

unsigned short func_0015CBE8(unsigned short id) {
    int i;

    for (i = 0x47F; i >= 0; i--) {
        if (id == D_002ABA40[i].id) {
            return i;
        }
    }
    return 0;
}
