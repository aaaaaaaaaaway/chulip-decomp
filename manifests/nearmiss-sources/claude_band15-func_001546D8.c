typedef struct {
    unsigned char pad[0x20];
    volatile long long low : 7;
    volatile long long flag : 1;
    volatile long long high : 56;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_001546D8(unsigned short index) {
    (D_002ABA40 + index)->flag = 1;
}
