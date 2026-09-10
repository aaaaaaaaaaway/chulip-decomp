extern unsigned char D_001A573C[];

unsigned char *func_0012F678(unsigned char group, unsigned char choice) {
    unsigned char *cursor = D_001A573C + group * 0x2A4;
    unsigned char *start = cursor;
    unsigned char index = 0;
    do {
        if (cursor[0] == 0 && cursor[1] == 0) {
            if (index == choice)
                return start;
            start = cursor + 2;
            index++;
            cursor++;
        }
        cursor++;
    } while (cursor[0] != '#' || cursor[1] != '#');
    return 0;
}
