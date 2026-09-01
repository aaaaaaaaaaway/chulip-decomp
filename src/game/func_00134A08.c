typedef struct {
    unsigned short type;
    unsigned char reserved;
    unsigned char count;
} Header;

int func_00134A08(char *packet, long first, long second) {
    Header *header = (Header *)packet;
    long *body;

    packet += 0x10;
    header->count = 0x10;
    header->type = 2;
    body = (long *)packet;
    body[0] = 0x1000000000008001L;
    body[1] = 0xE;
    body[3] = first;
    body[2] = second;
    return 3;
}
