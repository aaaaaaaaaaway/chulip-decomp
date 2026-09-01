typedef struct {
    unsigned short type;
    unsigned char reserved;
    unsigned char count;
} Header;

int func_0017FBB0(char *packet) {
    Header *header = (Header *)packet;
    long *body;
    long cmd = 0x47;

    packet += 0x10;
    header->count = 0x10;
    header->type = 2;
    body = (long *)packet;
    body[0] = 0x1000000000008001L;
    body[1] = 0xE;
    body[3] = cmd;
    body[2] = 0x31001;
    return 3;
}
