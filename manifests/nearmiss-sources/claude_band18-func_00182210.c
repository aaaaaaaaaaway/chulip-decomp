typedef struct {
    short a;
    char pad;
    char b;
    int reserved[3];
    long q[4];
} Packet;

int func_00182210(Packet *packet, long x, long y) {
    packet->a = 2;
    packet->b = 0x10;
    packet->q[0] = 0x1000000000008001L;
    packet->q[1] = 0xE;
    packet->q[2] = y;
    packet->q[3] = x;
    return 3;
}
