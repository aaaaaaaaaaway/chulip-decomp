int func_00115EF0(unsigned long *packet, int value)
{
    packet[1] = 0;
    packet[0] = value | 0x1400000000000000UL;
    return value - 2;
}
