typedef struct {
    unsigned char pad[0x24];
    void *field;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void *func_001548A0(unsigned short index) { return (D_002ABA40 + index)->field; }
