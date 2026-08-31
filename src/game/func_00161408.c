typedef unsigned int u32;

void func_00161408(u32 *packet, u32 index, u32 value, u32 upper)
{
    upper = (upper << 16) | 0x8000;
    value |= upper;
    value |= 0x6C000000;
    packet[index] = value;
}
