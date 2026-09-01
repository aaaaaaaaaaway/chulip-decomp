int func_0014E140(
    long *packet,
    int x1,
    int x2,
    int x3,
    int x4,
    int x5,
    int x6,
    int x7,
    int x8,
    int high,
    int payload)
{
    long upper = (long)high << 32;
    int ua = x5 + 8;
    int ub = x7 + 8;

    packet[0] = 1 | ((long)1 << 15) | ((long)1 << 58) | ((long)6 << 60);
    packet[1] = 0x535310;
    packet[2] = 0x156;
    packet[3] = payload;
    packet[4] = ua | ((x6 + 8) << 16);
    packet[5] = ((x1 + 0x800) << 4) | ((x2 + 0x1000) << 19) | upper;
    packet[6] = ub | ((x8 + 8) << 16);
    packet[7] = ((x3 + 0x800) << 4) | ((x4 + 0x1000) << 19) | upper;
    return 4;
}
