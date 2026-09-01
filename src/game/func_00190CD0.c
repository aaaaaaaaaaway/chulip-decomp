extern char D_002DF180[];
extern unsigned int func_00192A54(char *text);
extern char *func_00192344(char *destination, char *source, int length);

void func_00190CD0(char *destination) {
    unsigned int length;
    if (destination != 0) {
        length = (func_00192A54((char *)((unsigned int)D_002DF180 | 0x20000000)) < 0x400u)
                     ? func_00192A54((char *)((unsigned int)D_002DF180 | 0x20000000))
                     : 0x3FF;
        func_00192344(destination, (char *)((unsigned int)D_002DF180 | 0x20000000), length);
        destination[length] = 0;
    }
}
