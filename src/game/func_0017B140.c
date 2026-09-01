typedef struct PacketHeader {
    unsigned long tag;
    unsigned long register_count;
    unsigned long value_at_10;
    unsigned long value_at_18;
} PacketHeader;

typedef struct PacketPrefix {
    unsigned short command_count;
    unsigned char unused;
    unsigned char command_size;
    unsigned char pad[12];
} PacketPrefix;

int func_0017B140(PacketPrefix *packet, unsigned long first, unsigned long second) {
    PacketPrefix *prefix = packet++;
    PacketHeader *header;

    prefix->command_size = 16;
    prefix->command_count = 2;
    header = (PacketHeader *)packet;
    header->tag = 0x1000000000008001UL;
    header->register_count = 14;
    header->value_at_18 = first;
    header->value_at_10 = second;
    return 3;
}
