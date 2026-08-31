typedef struct {
    unsigned char pad[0x20];
    volatile long long low : 19;
    volatile long long value : 32;
    volatile long long high : 13;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

int func_00158830(unsigned short index, unsigned short flag) {
    if (flag == 0) {
        return (D_002ABA40 + index)->value & 1;
    }
    return 1;
}
