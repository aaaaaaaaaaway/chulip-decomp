extern int func_00192A54(unsigned char *text);

unsigned char *func_0012DFF0(unsigned char *text) {
    int remaining = func_00192A54(text);
    unsigned char *start = text;

    while (remaining >= 2) {
        if (text[0] == 0x81 && text[1] == 0x5B) {
            text[1] = 0xF7;
        }
        remaining = remaining - 2;
        text = text + 2;
    }
    return start;
}
