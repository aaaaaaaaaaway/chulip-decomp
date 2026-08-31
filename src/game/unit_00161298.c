typedef unsigned int u32;

typedef struct PacketQword {
    u32 word[4];
} PacketQword;

#define MMIO32(address) (*(volatile u32 *)(address))

void func_00161298(PacketQword *packet, u32 address)
{
    PacketQword *next;

    packet[0].word[0] = 0x50000000;
    packet[0].word[1] = address & 0x0FFFFFFF;
    packet[0].word[3] = 0;
    packet[0].word[2] = 0;
    next = packet + 1;
    next->word[3] = 0;
    next->word[2] = 0;
    next->word[1] = 0;
    next->word[0] = 0x70000000;
}

void func_001612D8(PacketQword *packet)
{
    MMIO32(0x10009020) = 0;
    MMIO32(0x10009030) = packet->word[0] & 0x0FFFFFFF;
    MMIO32(0x1000E010) = 2;
    MMIO32(0x10009000) = 0x145;
}
