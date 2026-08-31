typedef struct PacketHeader {
    unsigned long tag;
    unsigned long register_count;
    unsigned long second_value;
    unsigned long first_value;
} PacketHeader;

int func_00113648(PacketHeader *packet, unsigned long first, unsigned long second) {
    packet->tag = 0x1000000000008001UL;
    packet->register_count = 14;
    packet->second_value = second;
    packet->first_value = first;
    return 2;
}
