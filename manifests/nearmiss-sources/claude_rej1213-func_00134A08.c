int func_00134A08(unsigned char *packet, long arg1, long arg2) {
    *(short *)packet = 2;
    packet[3] = 0x10;
    packet = packet + 0x10;
    *(long *)(packet + 0x00) = 0x1000000000008001L;
    *(long *)(packet + 0x08) = 0xE;
    *(long *)(packet + 0x10) = arg2;
    *(long *)(packet + 0x18) = arg1;
    return 3;
}
