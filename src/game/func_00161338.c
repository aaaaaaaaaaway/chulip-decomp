typedef unsigned int u32;

typedef struct PacketQword {
    u32 word[4];
} PacketQword;

void func_00161338(PacketQword *packet, u32 word3, u32 word2, u32 word1,
                   u32 word0)
{
    packet->word[3] = word3;
    packet->word[2] = word2;
    packet->word[1] = word1;
    packet->word[0] = word0;
}
