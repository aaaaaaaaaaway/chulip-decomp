typedef struct Header {
    unsigned short kind;
    unsigned char pad2;
    unsigned char size;
    unsigned char pad[0xC];
} Header;

void func_0015F0B0(Header *header, long arg1, long arg2) {
    long *body = (long *)(header + 1);

    header->kind = 2;
    header->size = 0x10;
    body[0] = 0x1000000000008001L;
    body[1] = 0xE;
    body[2] = arg2;
    body[3] = arg1;
}
